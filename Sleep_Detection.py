import os
import signal
import time

# 부모 프로세스의 PID를 가져옵니다.


#sleeping Detection 구현

# 시그널을 보냅니다.
parent_pid = os.getppid()
print("sleeping parent pid",parent_pid,"\n")
os.kill(parent_pid, signal.SIGUSR1)