#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
    // 압력센서에서 착석을 인지할 때까지 기다린다.
    int seated = 0;
    while (seated) {
        seated = 1; // 압력 센서값을 계속 읽어드린다.
        /*if(seated > threshold){
            seated = 1;
        }*/
    }

    pid_t volume_control_pid = fork();
    if(volume_control_pid == 0){
        if(execlp("./audio_control","./audio_control", NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("%d\n",getpid());
       if(execlp("python3", "python3", "music_player.py", NULL) == -1) {
            perror("execlp"); // 오류 메시지 출력
            exit(EXIT_FAILURE); // 실패 시 자식 프로세스 종료
        }
    }
}