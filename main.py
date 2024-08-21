import ctypes
# import kivy
import threading
import time

libDSP = ctypes.cdll.LoadLibrary("./audio_process/build/lib/libSharedAudioProcess.dylib")

def audio_process():
    libDSP.main()

if __name__ == "__main__":
    dsp = threading.Thread(target = audio_process)
    dsp.start()
    time.sleep(5)
    libDSP.stop_proc()
    dsp.join()
    pass