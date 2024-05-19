# STL_Slicer

STL_Slicer is a simple slicing program for 3D printing. It generates printable `.gcode` files from any `.stl` files.

## Usage

First, build the project using the `mingw32-make` command. The executable `.exe` file can be found in the `/bin` directory.

To run the program, execute the `./main.exe` file. The format of the parameter list is demonstrated with an example. It's recommended to copy the full path from the `/stl_testfiles` directory as a parameter to ensure the program finds the test file.

The optimal slicing thickness ranges between 0.2 and 0.35 mm. You can also try extreme cases like 1 or 0.001 mm, but in these cases, the program's runtime may significantly increase or the output file's resolution may degrade.

The program determines its progress based on an iterating variable in a "for" loop.

The program outputs a `<filename>.gcode` file, which it places in the `/stl_testfiles` directory.

## Visualization

The easiest way to visualize the output is to open it with CURA Slicer. Here's the output of `bintest.gcode`:

![Alt text](Doxygen/bintest_cura.png)