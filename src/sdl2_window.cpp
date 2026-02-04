//
// Created by admin on 2025/12/4.
//

#include "sdl2_window.h"

#include <iostream>
#include <chrono>

Sdl2Window::Sdl2Window(const std::string& title, const int32_t width, const int32_t height)
    : _width(width), _height(height), _quit(false)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height,
                               SDL_WINDOW_SHOWN);
    if (_window == nullptr)
    {
        std::cerr << "Failed to create SDL2 window." << std::endl;
        SDL_Quit();
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr)
    {
        std::cerr << "Failed to create SDL2 renderer." << std::endl;
        SDL_Quit();
    }

    _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, _width, _height);
    if (_texture == nullptr)
    {
        std::cerr << "Failed to create SDL2 texture." << std::endl;
        SDL_Quit();
    }

    // 初始化像素缓冲区和图形渲染器
    _pixels_buffer = std::make_unique<PixelsBuffer>(_width, _height);
    _graphics_renderer = std::make_unique<GraphicsRenderer>(*_pixels_buffer);
    // 清除为黑色背景
    _graphics_renderer->Clear(Color(0, 0, 0, 255)); // 不透明黑色

    // 设置窗口命中测试回调，用于窗口拖动
    if (SDL_SetWindowHitTest(_window, &Sdl2Window::HitTestCallback, this) != 0)
    {
        std::cerr << "Warning: Hit-test not supported, window dragging may not "
                     "work properly: "
                  << SDL_GetError() << std::endl;
    }
}

Sdl2Window::~Sdl2Window()
{
    if (_texture != nullptr)
        SDL_DestroyTexture(_texture);
    if (_renderer != nullptr)
        SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Sdl2Window::EventLoop()
{
    SDL_Event e;

    Uint64 t_prev =
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    while (!_quit.load())
    {
        // 处理事件
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                _quit.store(true);
            }
        }

        if (_on_frame)
        {
            Uint64 t_now = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            float dt = static_cast<float>(t_now - t_prev);
            t_prev = t_now;
            _on_frame(*_graphics_renderer, dt);
        }

        Draw();
    }
}

void Sdl2Window::Draw() const
{
    if (_texture == nullptr || _renderer == nullptr || _window == nullptr || _pixels_buffer == nullptr)
    {
        return;
    }

    // 将像素缓冲区复制到纹理
    void* texture_pixels{nullptr};
    int texture_pitch;
    SDL_LockTexture(_texture, nullptr, &texture_pixels, &texture_pitch);

    // 逐行复制，处理可能的pitch对齐差异
    const uint8_t* src_pixels = reinterpret_cast<const uint8_t*>(_pixels_buffer->Pixels());
    uint8_t* dst_pixels = reinterpret_cast<uint8_t*>(texture_pixels);
    const int src_pitch = _pixels_buffer->Pitch();
    const int height = _pixels_buffer->Height();

    for (int y = 0; y < height; ++y)
    {
        memcpy(dst_pixels, src_pixels, src_pitch);
        src_pixels += src_pitch;
        dst_pixels += texture_pitch;
    }

    SDL_UnlockTexture(_texture);

    // 渲染纹理到屏幕
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, _texture, nullptr, nullptr);
    SDL_RenderPresent(_renderer);
}

SDL_HitTestResult Sdl2Window::HitTestCallback(SDL_Window* window, const SDL_Point* area, void* data)
{
    static_cast<void>(window);
    static_cast<void>(data);
    // 定义可拖动区域
    constexpr int draggable_height = 30;
    if (area->y < draggable_height)
    {
        return SDL_HITTEST_DRAGGABLE;
    }
    return SDL_HITTEST_NORMAL;
}
