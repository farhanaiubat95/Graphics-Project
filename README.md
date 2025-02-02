# To install OpenGL (FreeGLUT) on your system, follow these step-by-step instructions based on your operating system.
 1. For Windows :
    1. Download VS Code (https://code.visualstudio.com/download)
    2. Download MSYS2 (https://www.msys2.org/)
    3. Generate and Download Glad (https://glad.dav1d.de/) with the latest version(4.6)
    4. Install VS Code
    5. Install MSYS2
    6. Put Glad on MSYS2
    7. Edit Environment Variables for MSYS2
       1. System Variable:
          1. Variable Name : MSYS2
          2. Variable Value : C:\msys64
             
       2. Go to Path > Edit > New > C:\msys64\mingw64\bin
          
    8. Configure VS Code
       1. Install Extension(C++)
       2. Install Extension Run++
       3. Code Runner
       4. Add IncludePath
          
 2. MSYS2 MINGW command:
    
    $ pacman -Syu

    $ pacman -S mingw-w64-ucrt-x86_64-gcc

    $ gcc --version

    $ pacman -S mingw-w64-x86_64-glew

    $ pacman -S mingw-w64-x86_64-glfw

    $ pacman -S mingw-w64-x86_64-freeglut
    
    $ pacman -S mingw-w64-x86_64-toolchain
    
 4. Go to settings in Vs Code >  write includepath >
     1. ${env:MSYS2}/mingw64/include/ > add item
     
 5.  Download code Zip from my repository
    
