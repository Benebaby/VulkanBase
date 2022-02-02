# VulkanBase
Minimal Vulkan.hpp based implementation of the vulkan tutorial.

# Installation
This project can be confgured with cmake.
It is recommended to use vscode with the cmake and cmake tools extension. All major c++ compilers are supported and tested (Clang, G++, MSVC)

### Windows
install vulkan sdk from https://www.lunarg.com/vulkan-sdk/
It is recommended to use the latest Visual Studio C++ Compiler for faster build times.<br>
Visual Studio Build Tools:<br>
https://visualstudio.microsoft.com/de/downloads/#build-tools-for-visual-studio-2022

### MacOS
On mac os the MoltenVk implementation of the official Vulkan SDK is used as a translation layer for the native Metal API used by Apple. MoltenVk lacks some features that are not implemented in metal but it is vulkan conformant.<br>
install vulkan sdk from https://www.lunarg.com/vulkan-sdk/<br>
install clang compiler via xcode

### Ubuntu

##### Install Vulkan Graphicsdrivers 
```
sudo apt-get install mesa-vulkan-drivers
```

##### Install C++ Compiler
```
sudo apt install build-essential
```

##### Install Vulkan SDK
```
sudo wget -qO - http://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-focal.list http://packages.lunarg.com/vulkan/lunarg-vulkan-focal.list
sudo apt update
sudo apt install vulkan-sdk
```

##### Install Dependencies
```
sudo apt install libx11-dev
sudo apt install libxrandr-dev
sudo apt install libxinerama-dev
sudo apt install libxcursor-dev
sudo apt install libxi-dev
```
