#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <array>
#include <SDL2/SDL.h>

namespace dirt{

class Image{
public:
    Image();
    ~Image();

    void init(const int xsz, const int ysz, SDL_Renderer* renderer);
    void setPixel(int x, int y, double r, double g, double b);
    void display();
private:
    uint32_t xsz;
    uint32_t ysz;


    uint32_t color2int(double r, double g, double b);
    void initTexture();

    std::vector<std::vector<double>> redChannel;
    std::vector<std::vector<double>> greenChannel;
    std::vector<std::vector<double>> blueChannel;

    // TODO remove from this
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture   = nullptr;
};

}

#endif 