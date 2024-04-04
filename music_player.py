# 음악 프로그램 실행
import os
import signal
import time

volume = 50

def sigusr1_handler(signum, frame):
    global volume
    volume = volume -1

def sigusr2_handler(signum, frame):
    global volume
    volume = volume +1

signal.signal(signal.SIGUSR1, sigusr1_handler)
signal.signal(signal.SIGUSR2, sigusr2_handler)

while(1):
    print("Music Volume :",volume )
    time.sleep(1)