from kivy.uix.accordion import BooleanProperty
# for audio_process
import ctypes
import threading

# for kivy-GUI
from kivy.app import App
from kivy.core.window import Window
from kivy.lang import Builder
from kivy.uix.widget import Widget
from kivy.uix.screenmanager import Screen
from kivy.properties import StringProperty, NumericProperty, BooleanProperty

''' !CAUTION! .dylib on MacOS, .so in Linux, .dll on Windows '''
audio_process = ctypes.cdll.LoadLibrary("./audio_process/build/lib/libSharedAudioProcess.dylib")

def set_command(cmd):
    cmd = cmd.encode('utf-8')
    cmd = ctypes.create_string_buffer(cmd)
    audio_process.set_command(cmd)

class Home(Widget):
    volume_icon = StringProperty('atlas://data/images/defaulttheme/audio-volume-high')
    volume_value = NumericProperty(1.0)
    background_color = StringProperty('#000000')
    left_screen = StringProperty('Gain')
    right_screen = StringProperty('Gain')
    
    def volume_sld(self, instance):
        self.volume_value = instance.value
        set_command(f'Volume,^,{self.volume_value}')
        
        if(self.volume_value == 0.0):
            self.volume_icon = 'atlas://data/images/defaulttheme/audio-volume-muted'
        elif(self.volume_value < 0.5):
            self.volume_icon = 'atlas://data/images/defaulttheme/audio-volume-low'
        else:
            self.volume_icon = 'atlas://data/images/defaulttheme/audio-volume-high'

    def to_left_screen(self):
        pass
        
    def to_right_screen(self):
        pass

class GainMenu(Screen):
    background_color = StringProperty('#000000')
    is_enable = BooleanProperty(True)
    
    def toggle(self):
        self.is_enable = (False if self.is_enable else True)
        set_command(f'Gain,|')
    
    def sld(self, instance):
        set_command(f'Gain,^,{instance.value}')
        
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
    set_command('FIN')
    dsp.join()
