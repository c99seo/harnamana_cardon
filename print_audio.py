import sys
import os
import signal
import time

parent_pid = os.getppid()
print("parent_pid ",parent_pid)

os.kill(parent_pid, signal.SIGUSR1)

print("Arguments:", sys.argv[1])

time.sleep(2)
os.kill(parent_pid, signal.SIGUSR2)