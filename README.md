#Vcam
##Overview
Vcam reads description of world made of prisms from json file, projects them on 2D plane, and simulates coverage with painters algorithm.
##Build
```Console
mkdir build;cd build
cmake ..;
make
```
##Controls
* Arrow keys: Camera movement along X and Y axes
* + - : Camera movement along Z axis
* Num5 : Zoom in
* Num0 : Zoom out
* x y z: Clockwise camera rotation along given axis
