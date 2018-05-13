import snowboydecoder
import sys
import os
import signal

interrupted = False
def retpid():
    snowboydecoder.play_audio_file()
    pid=os.getpid()
    print(pid)
    return pid

def signal_handler(signal, frame):
    global interrupted
    interrupted = True


def interrupt_callback():
    global interrupted
    return interrupted

if len(sys.argv) == 1:
    print("Error: need to specify model name")
    print("Usage: python demo.py your.model")
    sys.exit(-1)

model = sys.argv[1]

# capture SIGINT signal, e.g., Ctrl+C
signal.signal(signal.SIGINT, signal_handler)

detector = snowboydecoder.HotwordDetector(model, sensitivity=0.5)
print('Listening... Press Ctrl+C to exit')

# main loop
detector.start(detected_callback=retpid,
               interrupt_check=interrupt_callback,
               sleep_time=0.03)

detector.terminate()
