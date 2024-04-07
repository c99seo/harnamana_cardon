# 음악 프로그램 실행
import os
import signal
import multiprocessing
import time
import pygame

lock = multiprocessing.Lock()

def sigusr1_handler(signum, frame):
    with lock:
        pygame.mixer.music.set_volume(0.2)
        child_process = multiprocessing.Process(target=sleep_child_process)
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        pygame.mixer.music.set_volume(1.0)

def sleep_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "sleep")

def temp_handler(signum, frame):
    with lock:
        pygame.mixer.music.set_volume(0.2)
        child_process = multiprocessing.Process(target=temp_child_process)
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        pygame.mixer.music.set_volume(1.0)

def temp_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "temp")

def dust_handler(signum, frame):
    with lock:
        pygame.mixer.music.set_volume(0.2)
        child_process = multiprocessing.Process(target=dust_child_process)
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        pygame.mixer.music.set_volume(1.0)

def dust_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "dust")

def sound_handler(signum, frame):
    with lock:
        pygame.mixer.music.set_volume(0.2)
        child_process = multiprocessing.Process(target=sound_child_process)
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        pygame.mixer.music.set_volume(1.0)

def sound_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "sound")

def dashboard_handler(signum, frame):
    with lock:
        pygame.mixer.music.set_volume(0.2)
        child_process = multiprocessing.Process(target=dashboard_child_process)
        print(os.getpid())
        child_process.start()
        # 자식 프로세스의 종료를 대기합니다.
        child_process.join()
        # 자식 프로세스가 종료되면 락을 해제합니다.
        pygame.mixer.music.set_volume(1.0)

def dashboard_child_process():
    # 자식 프로세스가 해야 할 작업을 수행합니다.
    os.execlp("python3", "python3", "print_audio.py", "dashboard")

signal.signal(signal.SIGUSR1, sigusr1_handler)
signal.signal(signal.SIGRTMIN + 2, temp_handler)
signal.signal(signal.SIGRTMIN + 3, dust_handler)
signal.signal(signal.SIGRTMIN + 4, sound_handler)
signal.signal(signal.SIGRTMIN + 5, dashboard_handler)

#날씨 정보 출력
def play_background_music(music_file):
    # 초기화
    pygame.mixer.init()
    # 배경음악 로드 및 재생 (반복 재생)
    pygame.mixer.music.load(music_file)
    pygame.mixer.music.play(-1)  # -1을 전달하여 반복 재생을 설정합니다.

music_file = "sunlit-whistle-200168.mp3"
play_background_music(music_file)

while(1):
    # 음악 프로그램 구현
    pass