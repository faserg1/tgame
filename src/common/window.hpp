#pragma once

#include <memory>

namespace tgame
{
    struct WindowImpl;

    class Window
    {
    public:
        Window(int width, int height);
        ~Window();

        WindowImpl &getImpl() const;
        int getWidth() const;
        int getHeight() const;

        int getViewportSquareSize() const;
    private:
        std::unique_ptr<WindowImpl> impl_;
        const int width_;
        const int height_;
    };
}