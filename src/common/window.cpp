#include "window.hpp"
#include "window-impl.hpp"
#include <SDL2/SDL.h>
using namespace tgame;

Window::Window(int width, int height) :
    impl_(std::make_unique<WindowImpl>()), width_(width), height_(height)
{
    impl_->wnd = SDL_CreateWindow("TGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
}

Window::~Window()
{
    SDL_DestroyWindow(impl_->wnd);
}

WindowImpl &Window::getImpl() const
{
    return *impl_;
}

int Window::getWidth() const
{
    return width_;
}

int Window::getHeight() const
{
    return height_;
}

int Window::getViewportSquareSize() const
{
    return std::min(width_, height_);
}