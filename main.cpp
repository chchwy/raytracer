
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

void plot(int x, int y, color c)
{
    plot(x, y, c[0], c[1], c[2], 1.0f);
}

color rayColor(const Ray& r)
{
    vec3 unitDirection = unit_vector(r.direction());
    auto t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    constexpr double aspectRatio = double(WIDTH) / double(HEIGHT);

    // Camera
    const double viewportHeight = 2.0;
    const double viewportWidth = viewportHeight * aspectRatio;
    const double focalLength = 1.0;

    point3 origin(0, 0, 0);
    vec3 horizontal(viewportWidth, 0, 0);
    vec3 vertical(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - vec3(0, 0, focalLength);

    for (int y = 0; y < HEIGHT; ++y)
    {
        std::cerr << "Scanlines remaining: " << (HEIGHT - y) << "\n" << std::flush;
        for (int x = 0; x < WIDTH; ++x)
        {
            float u = float(x) / (WIDTH - 1);
            float v = float(y) / (HEIGHT - 1);

            Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            color c = rayColor(ray);
            plot(x, y, c);
        }
    }
    stbi_write_png("out.png", WIDTH, HEIGHT, CHANNELS, g_img, STRIDE);
    stbi_write_jpg("out.jpg", WIDTH, HEIGHT, CHANNELS, g_img, 90);

    std::cerr << "\nDone.\n";
    system("start out.png");

    return 0;
}
