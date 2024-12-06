#include "image.hpp"
#include <stdexcept>
#include <format>

namespace dirt{


Image::Image():xsz{0}, ysz{0}, renderer{nullptr}, texture{nullptr}{
    
}
Image::~Image(){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}
void Image::setPixel(int x, int y, double r, double g, double b){
    if(x > xsz || y > ysz){
        throw std::runtime_error(std::format("cannot set pixel more that xsz / ysz xsz={}, ysz={}, x={}, y={}", xsz, ysz, x, y));
    }
    redChannel.at(x).at(y)   = r;
    blueChannel.at(x).at(y)  = g;
    greenChannel.at(x).at(y) = b;
}

void Image::init(const int xsz, const int ysz, SDL_Renderer* renderer){
    this->xsz = xsz;
    this->ysz = ysz;
    this->renderer = renderer;

    redChannel.resize(xsz, std::vector<double>(ysz, 0.0));
    greenChannel.resize(xsz, std::vector<double>(ysz, 0.0));
    blueChannel.resize(xsz, std::vector<double>(ysz, 0.0));        


    initTexture();
}

void Image::initTexture(){
    uint32_t rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else 
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif 


    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }

    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, xsz, ysz, 32, rmask, gmask, bmask, amask);
    texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}
uint32_t Image::color2int(double r, double g, double b){
    unsigned char red   = static_cast<unsigned char>(r);
    unsigned char green = static_cast<unsigned char>(g);
    unsigned char blue  = static_cast<unsigned char>(b);
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        uint32_t pixelColor = (red << 24) + (green << 16) + (blue << 8) + 255;
    #else 
        uint32_t pixelColor = (255 << 24) + (red << 16) + (green << 8) + (blue << 0);
    #endif 
    return pixelColor;
}
void Image::display(){
    uint32_t* tempPixels = new uint32_t[xsz * ysz];
    for(uint32_t i = 0; i < xsz; ++i){
        for(uint32_t j = 0; j < xsz; ++j){
            tempPixels[(j*xsz) + i] = color2int(redChannel.at(i).at(j), greenChannel.at(i).at(j), blueChannel.at(i).at(j));
        }        
    }

    SDL_UpdateTexture(texture, nullptr, tempPixels, xsz * sizeof(uint32_t));
    delete[] tempPixels;

    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = xsz;
    srcRect.h = ysz;
    bounds = srcRect;

    SDL_RenderCopy(renderer, texture, &srcRect, &bounds);
}

}