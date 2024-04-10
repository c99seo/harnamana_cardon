#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <cstdlib>

#include <wiringPi.h>
#include <string>

using namespace std;

#define trigPin 1	//gpio 21
#define echoPin 29	//gpio 18

void pedestrianCheckHandler(int sig){
    //초음파 센서로 거리 측정하고
    //속도에 따라서 제동 거리 계산(90-110db로 제동거리를 scale)
    //보행자 거리를 측정해서 제동 거리 내에 있으면 즉각 가상 배기음 출력
    
    int distance=0;
	int pulse = 0;
	
	long startTime;
	long travelTime;
	
	if(wiringPiSetup () == -1)
	{
		printf("Unable GPIO Setup"); 
	}
		
	pinMode (trigPin, OUTPUT);
	pinMode (echoPin, INPUT);
	
	for(;;)
	{
		digitalWrite (trigPin, LOW);
		usleep(2);
		digitalWrite (trigPin, HIGH);
		usleep(20);
		digitalWrite (trigPin, LOW);
		
		while(digitalRead(echoPin) == LOW);
		
		startTime = micros();
		
		while(digitalRead(echoPin) == HIGH);
		travelTime = micros() - startTime;
		
		int distance = travelTime / 58;
		if(distance < 10){
            const char* mp3FilePath = "watchout.mp3";
            system("amixer -D pulse sset Master 70%");
            system(("mpg123 " + string(mp3FilePath)).c_str());
            break;
        }
		printf( "Distance: %dcm\n", distance);
		delay(200);
	}

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
        sleep(1);
        printf("%d\n",getpid());
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