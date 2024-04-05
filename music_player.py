# 음악 프로그램 실행
import sys
import os
import signal
import time

volume = 50

def sigusr1_handler(signum, frame):
    global volume
    print("Sig Handle Volume Down")
    volume = volume -1
    pid = os.fork()
    if pid == 0:
        # 자식 프로세스에서는 다른 파이썬 파일을 실행합니다.
        os.execlp("python3", "python3", "print_audio.py","sleep")

def temp_handler(signum, frame):
    global volume
    print("Sig Handle Volume Down")
    volume = volume -1
    pid = os.fork()
    if pid == 0:
        # 자식 프로세스에서는 다른 파이썬 파일을 실행합니다.
        os.execlp("python3", "python3", "print_audio.py","temp")

def dust_handler(signum, frame):
    global volume
    print("Sig Handle Volume Down")
    volume = volume -1
    pid = os.fork()
    if pid == 0:
        # 자식 프로세스에서는 다른 파이썬 파일을 실행합니다.
        os.execlp("python3", "python3", "print_audio.py","dust")

def sound_handler(signum, frame):
    global volume
    print("Sig Handle Volume Down")
    volume = volume -1
    pid = os.fork()
    if pid == 0:
        # 자식 프로세스에서는 다른 파이썬 파일을 실행합니다.
        os.execlp("python3", "python3", "print_audio.py","sound")

def dashboard_handler(signum, frame):
    global volume
    volume = volume -1
    print("Music Volume :",volume )
    print("Sig Handle Volume Down")
    pid = os.fork()
    if pid == 0:
        # 자식 프로세스에서는 다른 파이썬 파일을 실행합니다.
        os.execlp("python3", "python3", "print_audio.py","dashboard")

def sigusr2_handler(signum, frame):
    global volume
    volume = volume +1
    print("Sig Handle Volume Up")
    print("Music Volume :",volume )
    os.kill(int(sys.argv[1]), signal.SIGRTMIN + 6)

signal.signal(signal.SIGUSR1, sigusr1_handler)
signal.signal(signal.SIGUSR2, sigusr2_handler)
signal.signal(signal.SIGRTMIN + 2, temp_handler)
signal.signal(signal.SIGRTMIN + 3, dust_handler)
signal.signal(signal.SIGRTMIN + 4, sound_handler)
signal.signal(signal.SIGRTMIN + 5, dashboard_handler)

print("Music Player PID:",os.getpid())

#날씨 정보 출력

while(1):
    # 음악 프로그램 구현
    print("Music Volume :",volume )
    time.sleep(1)