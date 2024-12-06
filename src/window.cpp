#include "window.hpp"
#include <stdexcept>
#include "imgui_impl_sdlrenderer2.h"
#include "imgui_impl_sdl2.h"
#include "imgui.h"


namespace dirt{

Window::~Window(){
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::beginDrawUI(){
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);


    ImGui::Begin("MainDockSpace", nullptr, mainDockingFlags);
    ImGuiID dockspaceId = ImGui::GetID("dockSpaceId");
    ImGui::DockSpace(dockspaceId, ImVec2(0, 0), ImGuiDockNodeFlags_None);
    ImGui::End();
}

void Window::endDrawUI(){
    // ImGui::End();
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

}


Window::Window(uint32_t width, uint32_t height): width{width}, height{height}, window{nullptr}, renderer{nullptr}{

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        throw std::runtime_error("cannot initialize sdl");
    }

    window = SDL_CreateWindow(
        "Ray cast in one elephan",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, 
        height, 
        SDL_WINDOW_SHOWN
    );



    if(!window){
        SDL_Quit();
        throw std::runtime_error("cannot create sdl window");
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer){
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("cannot create sdl renderer");
    }    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    mainDockingFlags = ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_NoResize   |
        ImGuiWindowFlags_NoMove     |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_MenuBar;

}


void Window::processFrames(){
    bool running = true;
    while(running){
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = false;
            }
            ImGui_ImplSDL2_ProcessEvent(&e);
        }


        SDL_SetRenderDrawColor(renderer, 120, 180, 255, 255);
        SDL_RenderClear(renderer);

        beginDrawUI();

        ImGui::Begin("test");
        ImGui::Text("Hello wurlds");
        ImGui::End();

        ImGui::Begin("test2");
        ImGui::Text("Hello wurlds");
        ImGui::End();

        endDrawUI();

        SDL_RenderPresent(renderer);

    } 
}


}