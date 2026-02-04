# HappySisyphus

My personal project creating a game engine. It might sound obsured but it makes me happy.

This project started by following _Hazel_ engine tutorials and then I added 3D rendering with OpenGL to it.

## Screen Shots

![image](ScreenShot.jpg)

## Build

**Note**: For safety, binary files are not included in this repository. Download the following binaries from their official sources and place them in the specified directories:

- **premake.exe** → `.\vendor\bin\premake\`  
  [Official website](https://premake.github.io/)

- **assimp** → `.\Sisyphus\vendor\`
  [Official website](https://assimp.org/)

- **build_assimp** → `.\Sisyphus\vendor\`  
  [Official website](https://assimp.org/)

Assimp is used for 3D model loading.

Premake is used to create the suitable project build environment. To use it you can run the `GenerateProjects.bat` script. Currently only Windows is supported. You might be able to build in Linux or MAC with a few modifications and testing as well.
