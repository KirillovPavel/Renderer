#include "framebuffer.hpp"

int main(){
    Framebuffer buffer;
    Color red(255);
    Color blue(0, 255);
    Color green(0, 0, 255);
    for(unsigned int i = 0; i < buffer.heigh(); i++)
        for(unsigned int j = 1; j < buffer.width(); j++)
            buffer[i][j] = red;
    buffer.update();
    return 0;
}
