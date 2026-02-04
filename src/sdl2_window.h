//
// Created by admin on 2025/12/4.
//

#ifndef SDL2WINDOW_H
#define SDL2WINDOW_H
#include "graphics_renderer.h"
#include "pixels_buffer.h"
#include <SDL.h>
#include <functional>
#include <memory>
#include <string>

class Sdl2Window
{
  public:
    Sdl2Window(const std::string& title, const int32_t width, const int32_t height);
    ~Sdl2Window();

    /**
     * @brief sdl2 开启事件循环
     */
    void EventLoop();

    /**
     * @brief 获取图形渲染器，用于绘制图元
     */
    GraphicsRenderer& graphicsRenderer()
    {
        return *_graphics_renderer;
    }

    const GraphicsRenderer& graphicsRenderer() const
    {
        return *_graphics_renderer;
    }

    /**
     * @brief 每帧回调：在复制到屏幕前调用，用于 Clear、更新状态（如 UV 滚动）、重绘图元等。
     * 参数：(GraphicsRenderer& renderer, float dt_sec)
     */
    using FrameCallback = std::function<void(GraphicsRenderer&, float dt_sec)>;

    void SetFrameCallback(FrameCallback cb)
    {
        _on_frame = std::move(cb);
    }

  private:
    /**
     * @brief
     */
    void Draw() const;

    /**
     * @brief 窗口命中测试回调（用于窗口拖动）
     * @param window
     * @param area
     * @param data
     * @return
     */
    static SDL_HitTestResult HitTestCallback(SDL_Window* window, const SDL_Point* area, void* data);

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Texture* _texture;

    std::string title;
    int32_t _width;
    int32_t _height;
    std::atomic<bool> _quit;

    // 像素缓冲区和图形渲染器
    std::unique_ptr<PixelsBuffer> _pixels_buffer;
    std::unique_ptr<GraphicsRenderer> _graphics_renderer;

    FrameCallback _on_frame;
};

#endif // SDL2WINDOW_H
