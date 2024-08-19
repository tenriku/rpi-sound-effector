import ctypes

libc = ctypes.cdll.LoadLibrary("./audio_process/build/lib/libSharedAudioProcess.dylib")

if __name__ == "__main__":
    libc.main()