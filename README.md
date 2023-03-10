


#Building and installing

### Linux

#### Get glew binaries
    sudo apt install glew

#### Configure, build and run with CMake
    scripts\configure.sh #cmake configure
    scripts\build.sh     #build with cmake
    scripts\install.sh   #install with cmake
    scripts\run.sh       #run
   
### Windows

#### Get glew binaries

- Download glew from https://glew.sourceforge.net/ and unpack
- Set environment variable `GLM_ROOT` to root directory

#### Configure, build and run with CMake

    scripts\configure.bat #cmake configure
    scripts\build.bat     #build with cmake
    scripts\install.bat   #install with cmake
    scripts\run.bat       #run
