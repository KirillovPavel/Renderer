#pragma once
#include <stdexcept>
extern "C"{
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <poll.h>
#include <errno.h>
#include <wchar.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
}

struct Color{
    unsigned char b, g, r, a;
    Color(unsigned char R = 0, unsigned char B = 0, unsigned char G = 0);
};

class Framebuffer{
public:
    Color *data;
    float *depth;
    size_t w, h, bpp, v_w, v_h;
    Framebuffer();
    size_t width() const noexcept;
    size_t heigh() const noexcept;
    Color *operator[](unsigned int i) noexcept;
    Color const *operator[](unsigned int i) const noexcept;

    void setdepth(unsigned int x, unsigned int y, float dep);
    float getdepth(unsigned int x, unsigned int y);

    void update();
    void clear();

    ~Framebuffer();
};
