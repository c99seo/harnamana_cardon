#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <vector>
#include <mutex>
#include <algorithm>
#include <string>

using namespace std;

vector<int> event;
mutex mtx;
pid_t ppid = getppid();

void sleepCheckHandler(int sig){
    event.push_back(0);
}

void tempCheckHandler(int sig){
   printf("tempcheckhandler\n");
   event.push_back(1);
}

void dustCheckHandler(int sig){
   printf("dustcheckhandler\n");
   event.push_back(2);
}

void soundCheckHandler(int sig){
   printf("soundcheckhandler\n");
   event.push_back(3);
}

void dashboardCheckHandler(int sig){
   printf("dashboardcheckhandler\n");
   //무슨 경고인지 확인해서 event.push 할 것
   //event.push_back(4);
}

void sleepDectection() {
    // 자식 프로세스의 작업
    printf("Sleep Detection Start\n");
    if (execlp("python3", "python3", "Sleep_Detection.py", NULL) == -1) {
        perror("execlp"); // 오류 메시지 출력
        exit(EXIT_FAILURE); // 실패 시 자식 프로세스 종료
    }
    // execlp 함수가 성공적으로 실행되면 아래의 코드는 실행되지 않음
    printf("This line won't be executed\n");
}

void sensorDetection(){
    //4가지 센서 값을 받아드리고 기준치 이상인 경우
    pid_t parent_pid = getppid();
    //온습도
    kill(parent_pid, SIGRTMIN + 2);
    //미세먼지 센서
    //kill(parent_pid, SIGRTMIN + 3);
    //소리감지 센서
    //kill(parent_pid, SIGRTMIN + 4);
    //계기판 경고인식해서 
    //kill(parent_pid, SIGRTMIN + 5);
}

void audioSchedule() {
    // 자식 프로세스의 작업
    lock_guard<mutex> lock(mtx);
    printf("Audio Scheduling Start\n");
    if(event.size() != 0){
        auto it = find(event.begin(), event.end(), 0);
        if(it == event.end()){
            int temp = event.front();
            event.erase(event.begin());
            if (execlp("python3", "python3", "print_audio.py",to_string(temp), NULL) == -1) {
                perror("execlp"); // 오류 메시지 출력
                exit(EXIT_FAILURE); // 실패 시 자식 프로세스 종료
            }
        }
        else{
            int temp = *it;
            event.erase(it);
            if (execlp("python3", "python3", "print_audio.py",to_string(temp), NULL) == -1) {
                perror("execlp"); // 오류 메시지 출력
                exit(EXIT_FAILURE); // 실패 시 자식 프로세스 종료
            }
        }
        
        // execlp 함수가 성공적으로 실행되면 아래의 코드는 실행되지 않음
        printf("This line won't be executed\n");
    }
    else{
        printf("no event\n");
    }
}

int main() {
        struct sigaction sleepcheck;
        sleepcheck.sa_handler = sleepCheckHandler;
        sigemptyset(&sleepcheck.sa_mask);
        sleepcheck.sa_flags = 0;
        sigaction(SIGUSR1, &sleepcheck, 0);
        
        struct sigaction tempcheck;
        tempcheck.sa_handler = tempCheckHandler;
        sigemptyset(&tempcheck.sa_mask);
        tempcheck.sa_flags = 0;
        sigaction(SIGRTMIN + 2, &tempcheck, 0);

        struct sigaction dustcheck;
        dustcheck.sa_handler = dustCheckHandler;
        sigemptyset(&dustcheck.sa_mask);
        dustcheck.sa_flags = 0;
        sigaction(SIGRTMIN + 3, &dustcheck, 0);

        struct sigaction soundcheck;
        dustcheck.sa_handler = soundCheckHandler;
        sigemptyset(&soundcheck.sa_mask);
        soundcheck.sa_flags = 0;
        sigaction(SIGRTMIN + 4, &soundcheck, 0);

        struct sigaction dashboardcheck;
        dashboardcheck.sa_handler = dashboardCheckHandler;
        sigemptyset(&dashboardcheck.sa_mask);
        dashboardcheck.sa_flags = 0;
        sigaction(SIGRTMIN + 5, &dashboardcheck, 0);
        pid_t sleep_pid = fork();

        if(sleep_pid == 0){
            sleepDectection();
        }

        pid_t sensor_pid = fork();

        if(sensor_pid == 0){
            sensorDetection();
        }


        else{
            while(event.empty()){}
            audioSchedule();
            sleep(10);
        }
}