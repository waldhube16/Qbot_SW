<img src="./GUI/Resources/Logo_sharper.png" height="200" />

# QBOT - Rubik's Cube Solver Software
## Overview
This software can be used standalone or with an actual hardware solver. The firmware for the original implementation can be found [here](https://github.com/Axodarap/QBot_firmware).
## Functionality 
- Apply simple moves on a 'simulated' cube.
- Apply patterns to the cube.  
- Randomize cube. 
- Generate solutions for arbitrary cubes. This uses the Python package `kociemba` which can be found [here](https://github.com/muodov/kociemba).
- Communicate via Serial connection with solver hardware. 
- Scan a real cube and analyze the current state.
## Requirements 
The following Python packages were used during development. 

| Package                | Version       | Installed Using |
| ---------------------- |:-------------:| --------------- |
| Python                 | 3.7.9 64bit   | miniconda       |
| kociemba               | 1.2.1         | pip             |
| numpy                  | 1.19.5        | pip             |
| opencv-python-headless | 1.2.1         | pip             |
| PyQt5                  | 1.2.1         | pip             |
| pyserial               | 1.2.1         | pip             |

In order for PyQt to work the Qt framework with the correct version (`5.12.8`) must be installed. 
