#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>

namespace dirt{

class Window{
public:
    Window(uint32_t width, uint32_t height);
    ~Window();
    void processFrames();
    void beginDrawUI();
    void endDrawUI();
private:
    uint32_t width, height;
    SDL_Window* window;
    SDL_Renderer* renderer;

    uint64_t mainDockingFlags;
};

}

#endif 