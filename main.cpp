
#include "pch.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "vec3.h"
#include "ray.h"


constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int CHANNELS = 4;
constexpr int STRIDE = WIDTH * CHANNELS;

uint8_t g_img[WIDTH * HEIGHT * CHANNELS];

void plot(int x, int y, float r, float g, float b, float a)
{
    int p = (y * WIDTH + x) * CHANNELS;
    g_img[p + 0] = uint8_t(r * 255);
    g_img[p + 1] = uint8_t(g * 255);
    g_img[p + 2] = uint8_t(b * 255);
    g_img[p + 3] = uint8_t(a * 255);
}

int main()
{
    for (int y = 0; y < HEIGHT; ++y)
    {
        std::cerr << "Scanlines remaining: " << (HEIGHT - y) << "\n" << std::flush;
        for (int x = 0; x < WIDTH; ++x)
        {
            float r = float(x) / (WIDTH - 1);
            float g = float(y) / (HEIGHT - 1);
            float b = 0.25f;
            plot(x, y, r, g, b, 1.0f);
        }
    }
    stbi_write_png("out.png", WIDTH, HEIGHT, CHANNELS, g_img, STRIDE);
    stbi_write_jpg("out.jpg", WIDTH, HEIGHT, CHANNELS, g_img, 90);

    std::cerr << "\nDone.\n";
    system("start out.png");

    return 0;
}
