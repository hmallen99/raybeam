#include <windows.h>
#include <gl/GL.h>
#include <stdint.h>

class draw {
    private:
        int height;
        int width;
    public:
        draw(int h, int w) {
            height = h;
            width = w;
        }

        void writeFrame(int** data) {
            

            glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
            
        }
};