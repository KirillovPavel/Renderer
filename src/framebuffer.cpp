#include "framebuffer.hpp"
using namespace std;

Color::Color(unsigned char R, unsigned char B, unsigned char G){
    b = B;
    r = R;
    g = G;
    a = 255;
}

char const *path = "/dev/fb0";
Framebuffer::Framebuffer():
    data(nullptr),
    w(0),
    h(0),
    bpp(0),
    v_w(0),
    v_h(0)
{

    int fb = open(path, O_RDONLY);
    if(fb < 0)
        throw runtime_error(string("can't open ") + path + string(": ") + strerror(errno));
    struct fb_fix_screeninfo fsinfo;
    if(ioctl(fb, FBIOGET_FSCREENINFO, &fsinfo) < 0){
        throw runtime_error(string("ioctl crash in fsinfo: ") + strerror(errno));
        close(fb);
    }
    struct fb_var_screeninfo vsinfo;
    if(ioctl(fb, FBIOGET_VSCREENINFO, &vsinfo) < 0){
        close(fb);
        throw runtime_error(string("ioctl crash in vsinfo: ") + strerror(errno));
    }
    bpp = vsinfo.bits_per_pixel;
    v_w = vsinfo.xres;
    v_h = vsinfo.yres;
    w = fsinfo.line_length * 8 / bpp;
    h = fsinfo.smem_len / fsinfo.line_length;
    close(fb);
    data = new Color[w * h];
    depth = new float[w * h];
    float infinity = INFINITY;
    wchar_t inf = *(wchar_t *)(&infinity);
    wmemset((wchar_t*) depth, inf, w * v_h);
}
size_t Framebuffer::width() const noexcept{
    return v_w;
}
size_t Framebuffer::heigh() const noexcept{
    return v_h;
}
Color* Framebuffer::operator[](unsigned int i) noexcept{
    return data + w * (v_h - i - 1);
}
Color const* Framebuffer::operator[](unsigned int i) const noexcept{
    return data + w * (v_h - i - 1);
}

void Framebuffer::setdepth(unsigned int x, unsigned int y, float dep){
    depth[w * y + x] = dep;
}
float Framebuffer::getdepth(unsigned int x, unsigned int y){
    return depth[w * y + x];
}

void Framebuffer::update(){
    int fb = open(path, O_WRONLY);
    if(fb < 0)
        throw runtime_error(string("can't open for write ") + path + string(": ") + strerror(errno));
    write(fb, data, w * v_h * sizeof(Color));
    close(fb);

}
void Framebuffer::clear(){
    Color c(0, 0, 0);
    wchar_t wchar = *(wchar_t *)(&c);
    wmemset((wchar_t *)(data), wchar, w * v_h);
    float infinity = INFINITY;
    wchar_t inf = *(wchar_t *)(&infinity);
    wmemset((wchar_t*) (depth), inf, w * v_h);
}

Framebuffer::~Framebuffer(){
    delete[] data;
    delete[] depth;
}
