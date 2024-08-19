sudo apt update && sudo apt upgrade -y
sudo apt install git cmake libasound-dev portaudio19-dev -y
cd /opt 
sudo git clone https://github.com/PortAudio/portaudio.git
sudo ./configure
sudo make
sudo make install
sudo git clone https://github.com/ArthurSonzogni/FTXUI.git
sudo mkdir build && cd build
sudo cmake ..
sudo make
sudo make install