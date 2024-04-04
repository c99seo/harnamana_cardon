#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int volume = 50;

void sigUSR1Action(int sig) {
    volume--;
    printf("Volume Down %d\n", volume);
}

void sigUSR2Action(int sig) {
    volume++;
    printf("Volume up %d\n", volume);
}

int main() {
    // 압력센서에서 착석을 인지할 때까지 기다린다.
    int seated = 0;
    while (seated) {
        seated = 1; // 압력 센서값을 계속 읽어드린다.
        /*if(seated > threshold){
            seated = 1;
        }*/
    }

    struct sigaction vol_down;
    vol_down.sa_handler = sigUSR1Action;
    sigemptyset(&vol_down.sa_mask);
    vol_down.sa_flags = 0;
    sigaction(SIGUSR1, &vol_down, 0);

    struct sigaction vol_up;
    vol_up.sa_handler = sigUSR2Action;
    sigemptyset(&vol_up.sa_mask);
    vol_up.sa_flags = 0;
    sigaction(SIGUSR2, &vol_up, 0);

    pid_t pid = fork();

    if (pid == 0) {
        pid_t ppid = getppid(); // 부모 프로세스의 PID를 가져옵니다.
        printf("%d\n", ppid);
        /*명령을 실행하다가 볼륨을 줄여야 할 때*/

        kill(ppid, SIGUSR1);
        sleep(3);
        // 끝나고 나서 다시 볼륨을 키워야 할 때

        kill(ppid, SIGUSR2);
        sleep(3);
        return 123;
    } else {
        int status;
        // 뮤직 플레이어
        printf("parent pid\n");
        while (!waitpid(0, &status, WNOHANG)) {
            printf("parent Volume %d\n", volume);
            sleep(1);
        }
        printf("end\n");
    }
    return 0;
}