#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

vector<pair<string,int>> event;
pid_t ppid = getppid(); //music player pid

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void sleepCheckHandler(int sig){
    printf("sleepcheckhandler\n");
    event.push_back(pair<string,int> ("sleep",0));
}

void tempCheckHandler(int sig){
   printf("tempcheckhandler\n");
   event.push_back(pair<string,int> ("temp",1));
}

void dustCheckHandler(int sig){
   printf("dustcheckhandler\n");
   event.push_back(pair<string,int> ("dust",2));
}

void soundCheckHandler(int sig){
   printf("soundcheckhandler\n");
   event.push_back(pair<string,int> ("sound",3));
}

void dashboardCheckHandler(int sig){
   printf("dashboardcheckhandler\n");
   //무슨 경고인지 확인해서 event.push 할 것
   event.push_back(pair<string,int> ("dashboard",4));
}

void mutexlockCheckHandler(int sig){
    printf("mutexlockcheckhandler\n");
    pthread_mutex_unlock(&mutex);
}

void sleepDectection() {
    printf("Sleep Detection Start\n");
    if (execlp("python3", "python3", "Sleep_Detection.py", NULL) == -1) {
        perror("execlp"); 
        exit(EXIT_FAILURE);
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
        pthread_mutex_lock(&mutex);
        printf("Audio Scheduling Start\n");
        auto it = find(event.begin(), event.end(), pair<string,int> ("sleep",0));
        if(it == event.end()){
            int temp = event.front().second;
            event.erase(event.begin());
            switch(temp){
                case 1:
                    kill(ppid, SIGRTMIN + 2);
                    break;
                case 2:
                    kill(ppid, SIGRTMIN + 3);
                    break;
                case 3:
                    kill(ppid, SIGRTMIN + 4);
                    break;
                case 4:
                    kill(ppid, SIGRTMIN + 5);
                    break;
            }
        }
        else{
            event.erase(it);
            kill(ppid, SIGUSR1);
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
        soundcheck.sa_handler = soundCheckHandler;
        sigemptyset(&soundcheck.sa_mask);
        soundcheck.sa_flags = 0;
        sigaction(SIGRTMIN + 4, &soundcheck, 0);

        struct sigaction dashboardcheck;
        dashboardcheck.sa_handler = dashboardCheckHandler;
        sigemptyset(&dashboardcheck.sa_mask);
        dashboardcheck.sa_flags = 0;
        sigaction(SIGRTMIN + 5, &dashboardcheck, 0);

        struct sigaction mutexlockcheck;
        mutexlockcheck.sa_handler = mutexlockCheckHandler;
        sigemptyset(&mutexlockcheck.sa_mask);
        mutexlockcheck.sa_flags = 0;
        sigaction(SIGRTMIN + 6, &mutexlockcheck, 0);

        pthread_mutex_init(&mutex, NULL);

        pid_t sleep_pid = fork();

        if(sleep_pid == 0){
            sleep(2);
            sleepDectection();
        }else{
            pid_t sensor_pid = fork();

            if(sensor_pid == 0){
                sleep(2);
                sensorDetection();
            }
            else{
                sleep(2);
                
                while(1){
                    if(event.size() != 0){
                        audioSchedule();
                    }
                }
                pthread_mutex_destroy(&mutex);
            }
        }
}