//
// Created by Claude Code on 2025/12/4.
//

#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

// 端序检测
#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define COLOR_LITTLE_ENDIAN 1
#define COLOR_BIG_ENDIAN 0
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    #define COLOR_LITTLE_ENDIAN 0
    #define COLOR_BIG_ENDIAN 1
#elif defined(__LITTLE_ENDIAN__) || defined(_WIN32)
    #define COLOR_LITTLE_ENDIAN 1
    #define COLOR_BIG_ENDIAN 0
#elif defined(__BIG_ENDIAN__)
    #define COLOR_LITTLE_ENDIAN 0
    #define COLOR_BIG_ENDIAN 1
#else
    #error "Cannot determine endianness"
#endif

class Color
{
public:
    // 默认构造函数（透明黑色）
    Color() : _rgba(0x00000000)
    {
    }

    // 从 RGBA 分量构造
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : _rgba(PackRGBA(r, g, b, a))
    {
    }

    // 从 uint32_t RGBA8888 值构造（按SDL_PIXELFORMAT_RGBA8888格式）
    explicit Color(uint32_t rgba) : _rgba(rgba)
    {
    }

    /**
     * @brief 线性插值函数(t与end正相关)
     * @param start 起点颜色
     * @param end 终点颜色
     * @param t 插值参数
     * @return 返回差值颜色
     */
    static Color Lerp(const Color &start, const Color &end, float t)
    {
        // t = 0 → start颜色, t = 1 → end颜色
        uint8_t r = t * static_cast<float>(end.R()) + (1.0f - t) * static_cast<
                        float>(start.R());
        uint8_t g = t * static_cast<float>(end.G()) + (1.0f - t) * static_cast<
                        float>(start.G());
        uint8_t b = t * static_cast<float>(end.B()) + (1.0f - t) * static_cast<
                        float>(start.B());
        uint8_t a = t * static_cast<float>(end.A()) + (1.0f - t) * static_cast<
                        float>(start.A());
        return Color(r, g, b, a);
    }

    // 获取分量
    uint8_t R() const { return ExtractR(_rgba); }
    uint8_t G() const { return ExtractG(_rgba); }
    uint8_t B() const { return ExtractB(_rgba); }
    uint8_t A() const { return ExtractA(_rgba); }

    bool operator==(const Color &other) const
    {
        return _rgba == other._rgba;
    }

    // 获取原始 uint32_t 值（SDL_PIXELFORMAT_RGBA8888格式）
    uint32_t ToUint32() const { return _rgba; }

    /**
     * @brief 黑色
     * @return Color 黑色(0, 0, 0)
     */
    static Color Black() { return Color(0, 0, 0); }
    
    /**
     * @brief 白色
     * @return Color 白色(255, 255, 255)
     */
    static Color White() { return Color(255, 255, 255); }
    
    /**
     * @brief 红色
     * @return Color 红色(255, 0, 0)
     */
    static Color Red() { return Color(255, 0, 0); }
    
    /**
     * @brief 绿色
     * @return Color 绿色(0, 255, 0)
     */
    static Color Green() { return Color(0, 255, 0); }
    
    /**
     * @brief 蓝色
     * @return Color 蓝色(0, 0, 255)
     */
    static Color Blue() { return Color(0, 0, 255); }
    
    /**
     * @brief 黄色
     * @return Color 黄色(255, 255, 0)
     */
    static Color Yellow() { return Color(255, 255, 0); }
    
    /**
     * @brief 青色
     * @return Color 青色(0, 255, 255)
     */
    static Color Cyan() { return Color(0, 255, 255); }
    
    /**
     * @brief 洋红色
     * @return Color 洋红色(255, 0, 255)
     */
    static Color Magenta() { return Color(255, 0, 255); }
    
    /**
     * @brief 橙色
     * @return Color 橙色(255, 165, 0)
     */
    static Color Orange() { return Color(255, 165, 0); }
    
    /**
     * @brief 紫色
     * @return Color 紫色(128, 0, 128)
     */
    static Color Purple() { return Color(128, 0, 128); }
    
    /**
     * @brief 粉色
     * @return Color 粉色(255, 192, 203)
     */
    static Color Pink() { return Color(255, 192, 203); }
    
    /**
     * @brief 柠檬绿
     * @return Color 柠檬绿(0, 255, 0)
     */
    static Color Lime() { return Color(0, 255, 0); }
    
    /**
     * @brief 蓝绿色
     * @return Color 蓝绿色(0, 128, 128)
     */
    static Color Teal() { return Color(0, 128, 128); }
    
    /**
     * @brief 海军蓝
     * @return Color 海军蓝(0, 0, 128)
     */
    static Color Navy() { return Color(0, 0, 128); }
    
    /**
     * @brief 栗色
     * @return Color 栗色(128, 0, 0)
     */
    static Color Maroon() { return Color(128, 0, 0); }
    
    /**
     * @brief 橄榄色
     * @return Color 橄榄色(128, 128, 0)
     */
    static Color Olive() { return Color(128, 128, 0); }
    
    /**
     * @brief 银色
     * @return Color 银色(192, 192, 192)
     */
    static Color Silver() { return Color(192, 192, 192); }
    
    /**
     * @brief 灰色
     * @return Color 灰色(128, 128, 128)
     */
    static Color Gray() { return Color(128, 128, 128); }
    
    /**
     * @brief 透明色
     * @return Color 透明色(0, 0, 0, 0)
     */
    static Color Transparent() { return Color(0, 0, 0, 0); }

private:
    uint32_t _rgba; // SDL_PIXELFORMAT_RGBA8888格式

    // SDL_PIXELFORMAT_RGBA8888的位布局处理 内存从左到右递增
    // 在小端系统上：uint32_t值: 0xRRGGBBAA (内存[AA,BB,GG,RR])
    // 在大端系统上：uint32_t值: 0xAABBGGRR (内存[RR,GG,BB,AA])
    static uint32_t PackRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
#if COLOR_LITTLE_ENDIAN
        // 小端：R在最高字节，A在最低字节
        return (static_cast<uint32_t>(r) << 24) |
               (static_cast<uint32_t>(g) << 16) |
               (static_cast<uint32_t>(b) << 8) |
               static_cast<uint32_t>(a);
#else
        // 大端：A在最高字节，R在最低字节
        return (static_cast<uint32_t>(a) << 24) |
               (static_cast<uint32_t>(b) << 16) |
               (static_cast<uint32_t>(g) << 8) |
               static_cast<uint32_t>(r);
#endif
    }

    static uint8_t ExtractR(uint32_t rgba)
    {
#if COLOR_LITTLE_ENDIAN
        // 小端：R在最高字节
        return static_cast<uint8_t>((rgba >> 24) & 0xFF);
#else
        // 大端：R在最低字节
        return static_cast<uint8_t>(rgba & 0xFF);
#endif
    }

    static uint8_t ExtractG(uint32_t rgba)
    {
#if COLOR_LITTLE_ENDIAN
        // 小端：G在16-23位
        return static_cast<uint8_t>((rgba >> 16) & 0xFF);
#else
        // 大端：G在8-15位
        return static_cast<uint8_t>((rgba >> 8) & 0xFF);
#endif
    }

    static uint8_t ExtractB(uint32_t rgba)
    {
#if COLOR_LITTLE_ENDIAN
        // 小端：B在8-15位
        return static_cast<uint8_t>((rgba >> 8) & 0xFF);
#else
        // 大端：B在16-23位
        return static_cast<uint8_t>((rgba >> 16) & 0xFF);
#endif
    }

    static uint8_t ExtractA(uint32_t rgba)
    {
#if COLOR_LITTLE_ENDIAN
        // 小端：A在0-7位
        return static_cast<uint8_t>(rgba & 0xFF);
#else
        // 大端：A在24-31位
        return static_cast<uint8_t>((rgba >> 24) & 0xFF);
#endif
    }
};

#endif // COLOR_H