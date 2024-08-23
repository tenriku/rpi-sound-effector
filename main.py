# for audio_process
from ctypes import cdll, c_float
import threading
import subprocess

# for kivy-GUI
from kivy.app import App
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.uix.widget import Widget
from kivy.uix.screenmanager import Screen
from kivy.properties import StringProperty, NumericProperty

''' !CAUTION! .dylib on MacOS, .so in Linux, .dll on Windows '''
audio_process = cdll.LoadLibrary("./audio_process/build/lib/libSharedAudioProcess.dylib")

class Home(Widget):
    volume_icon = StringProperty('atlas://data/images/defaulttheme/audio-volume-high')
    volume_value = NumericProperty(1.0)
    
    def volume_move(self, instance):
        self.volume_value = instance.value
        # audio_process.volume_set(c_float(self.volume_value))
        
        if(self.volume_value == 0.0):
            self.volume_icon = 'atlas://data/images/defaulttheme/audio-volume-muted'
        elif(self.volume_value < 0.5):
            self.volume_icon = 'atlas://data/images/defaulttheme/audio-volume-low'
        else:
            self.volume_icon = 'atlas://data/images/defaulttheme/audio-volume-high'

class EffectMenu(Screen):
    effector_now = StringProperty('[EMPTY]')
    background_color = StringProperty('#000000')
    pos_now = 0
    dsp = []
    
    def left_screen(self):
        self.pos_now += 1
        # if self.pos_now > self.dsp.len() - 1:
        #     self.effector_now = dsp[self.pos_now]
        # else:
        #     self.effector_now = '[EMPTY]'
        
    def right_screen(self):
        self.pos_now -= 1

class GainMenu(Screen):
    def sld(self, instance):
        pass
        # audio_process.gain_set(c_float(instance.value))]
        # terminalに打つ
        
        
class MainApp(App):
    def __init__(self, **kwargs):
        super(MainApp, self).__init__(**kwargs)
        self.title = 'rpi-sound-effector'
    
    def build(self):
        return Home()

if __name__ == "__main__":
    # start audio_process
    dsp = threading.Thread(target = lambda: audio_process.main())
    dsp.start()
    
    # run kivy-GUI
    MainApp().run()
    
    # stop audio_process
    audio_process.finish()
    dsp.join()
