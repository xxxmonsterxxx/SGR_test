# Simple Graphics Renderer

![Image of project](https://i.postimg.cc/52B9yHT0/Logo-5.png)

How to use?

You could build this, but other option is to download release builded version as static or shared library.
In additional to this you need to download (or include as submodule of git project) and include to your project follows libraries:
GLM (https://github.com/g-truc/glm)
STB (https://github.com/nothings/stb)
Vulkan (https://www.lunarg.com/vulkan-sdk/)
GLFW (https://github.com/glfw/glfw)

How to build?

For build you need only Vulkan and GLFW libraries.

MacOS & Linux & Windows build is same:

:cmake CMakeLists.txt
:make