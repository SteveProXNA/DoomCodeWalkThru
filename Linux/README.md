# Doom on Linux
### prboom-plus

![prboom-plus](https://github.com/SteveProXNA/DoomCodeWalkThru/blob/main/Images/VScodeDebug.png)

Launch Terminal
```
sudo apt-get install libghc-opengl-dev
sudo apt-get install libghc-sdl-dev
sudo apt-get install libsdl1.2-dev
sudo apt-get install libsdl-mixer1.2-dev
sudo apt-get install libsdl-net1.2-dev

cd ~/prboom-plus
chmod +x configure
./configure
make
chmod +x src/prboom-plus
```
Visual Studio Code
```
~/GitHub/SteveProXNA/Doom/Linux/prboom-plus
touch build.sh
chmod +x build.sh
touch .vscode/tasks.json
touch .vscode/launch.json
```
WAD files
```
cp ../Files/* ~/.prboom-plus
```
i_main.c
```
Ctrl+Shift+B
F5
```
