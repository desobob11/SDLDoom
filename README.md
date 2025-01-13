
<a id="readme-top"></a>





<br />
<div align="center">
  <a href="https://github.com/desobob11/SDLDoom">
  </a>

  <h3 align="center">SDLDoom</h3>

  <p align="center">
    A simple raycasting rendering engine implented in C using SDL2. It's like jumping back to 1993!
  </p>
</div>





## About The Project

I got the inspiration for this project from the one and only John Carmack himself. I was listening to <a href="https://www.youtube.com/watch?v=I845O57ZSy4">John's appearance on the Lex Fridman podcast </a> during my morning commute one day. I was particularly interested with John's recollection of the development of Wolfenstein 3D, which was built using a raycasting techniques. shortly thereafter, I decided that I wanted to try implementing a raycasting engine myself!

Principles of the Engine:
* I use SDL2 for managing a window and receiving user inputs
* I am able to access the pixel buffer of the window to write individual pixels to any color of my choosing!
* By using some vector artihmetic, I can cast rays out from the player's position, one for each vertical line of the framebuffer, out into the game world
* When a ray hits a wall, I draw a vertical line of pixels according to the distance of the array
* This gives the illusion of a 3D gameworld without the use of polygons or a 3D rendering pipeline!

### Built With

This section should list any major frameworks/libraries used to bootstrap your project. Leave any add-ons/plugins for the acknowledgements section. Here are a few examples.

* ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
* SDL2

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Getting Started

The repository comes with two compiled executables:
* **Main.exe** is a Windows executable compiled for x86_64 architecture. If your PC satisfies this requirement, run this executable!
* **Main** is a Mac executable compiled for Intel's x86_64 chips. If your Mac satisfies this requirement, run this executable!
* Compilation details can be found below

### Prerequisites

* <a href="https://www.libsdl.org/"> SDL2 </a> (the required binaries and DLLs are included in the repo)
* GCC, or on Windows, <a href="https://cygwin.com/"> Cygwin with mingw-64 is preferred </a>

### Installation

This section is for compiling the program.

**Windows**
1. The **make.bat** can be used to compile your program using GCC, ocne your Cygwin installation has been configured.
2. The template assumes that SDLDoom is installed in your C: directory. If this is not the case, please update any paths!
3. The script will create the **Main.exe** executable.

**Mac/Linux**
1. A makefile has been included in the repo! Please execute if you would like to recompile the program.
2. The makefile will create the **Main** executable.

<p align="right">(<a href="#readme-top">back to top</a>)</p>







## Contact

Desmond O'Brien -- desmondobrien01@outlook.com

Project Link: [https://github.com/desobob11/SDLDoom](https://github.com/desobob11/SDLDoom)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

