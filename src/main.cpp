#include <iostream>

// #include "GL/glew.h"
#include "SDL.h"
#include "p2d.hpp"

int main(int, char**)
{
    p2d::Instance instance;
    instance.run();

    return 0;
} // int main