#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void pedestrianCheckHandler(int sig){
    //초음파 센서로 거리 측정하고
    //속도에 따라서 제동 거리 계산(90-110db로 제동거리를 scale)
    //보행자 거리를 측정해서 제동 거리 내에 있으면 즉각 가상 배기음 출력
}

int main(){
    pid_t camera = fork();
    if(camera == 0){
        if(execlp("/usr/bin/python3", "python3", "pedestrian_detection.py", NULL) == -1) {
            perror("execlp"); // 오류 메시지 출력
            exit(EXIT_FAILURE); // 실패 시 자식 프로세스 종료
        }
    }
    else{
        struct sigaction pedestriancheck;
        pedestriancheck.sa_handler = pedestrianCheckHandler;
        sigemptyset(&pedestriancheck.sa_mask);
        pedestriancheck.sa_flags = 0;
        sigaction(SIGUSR1, &pedestriancheck, 0);

        while(true){
            //내부 라즈베리파이로부터 값을 받아오기
            
        }
    }
}