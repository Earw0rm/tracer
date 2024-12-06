#include <iostream>
#include "window.hpp"
int main(int argc, char const *argv[])
{
    dirt::Window window{1024, 1024};
    window.processFrames();
    return 0;
}
