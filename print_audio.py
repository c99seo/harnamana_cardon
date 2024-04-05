import sys
import os
import signal
import time

parent_pid = os.getppid()
print("Arguments:", sys.argv[1])

#TTS

os.kill(parent_pid, signal.SIGUSR2)