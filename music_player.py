# 음악 프로그램 실행
import os
import signal
import multiprocessing
import time

lock = multiprocessing.Lock()

volume = 50

def sigusr1_handler(signum, frame):
    with lock:
        global volume
        volume = volume - 1
        print("Sig Handle Volume Down", volume)
        child_process = multiprocessing.Process(target=sleep_child_process)
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        volume = volume + 1
        print("Sig Handle Volume up", volume)

def sleep_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "sleep")

def temp_handler(signum, frame):
    with lock:
        global volume
        volume = volume - 1
        print("Sig Handle Volume Down", volume)
        child_process = multiprocessing.Process(target=temp_child_process)
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        volume = volume + 1
        print("Sig Handle Volume up", volume)

def temp_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "temp")

def dust_handler(signum, frame):
    with lock:
        global volume
        volume = volume - 1
        print("Sig Handle Volume Down", volume)
        child_process = multiprocessing.Process(target=dust_child_process)
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        volume = volume + 1
        print("Sig Handle Volume up", volume)

def dust_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "dust")

def sound_handler(signum, frame):
    with lock:
        global volume
        volume = volume - 1
        print("Sig Handle Volume Down", volume)
        child_process = multiprocessing.Process(target=sound_child_process)
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        volume = volume + 1
        print("Sig Handle Volume up", volume)

def sound_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "sound")

def dashboard_handler(signum, frame):
    with lock:
        global volume
        volume = volume - 1
        print("Sig Handle Volume Down", volume)
        child_process = multiprocessing.Process(target=dashboard_child_process)
        print(getpid())
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        volume = volume + 1
        print("Sig Handle Volume up", volume)

def dashboard_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "dashboard")

signal.signal(signal.SIGUSR1, sigusr1_handler)
signal.signal(signal.SIGRTMIN + 2, temp_handler)
signal.signal(signal.SIGRTMIN + 3, dust_handler)
signal.signal(signal.SIGRTMIN + 4, sound_handler)
signal.signal(signal.SIGRTMIN + 5, dashboard_handler)

#날씨 정보 출력

while(1):
    # 음악 프로그램 구현
    print("Music Volume :",volume )
    time.sleep(1)