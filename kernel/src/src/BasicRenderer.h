#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "kernel.h"

struct Point
{
    unsigned int x;
    unsigned int y;
};

#define WHITE 0xffffffff,
#define SILVER 0xffc0c0c0,
#define GRAY 0xff808080,
#define BGRAY 0xffC0C0C0,
#define DGRAY 0xff404040,
#define BLACK 0xff000000,
#define PINK 0xffFF1493,
#define GREEN 0xff008000,
#define RED 0xff800000,
#define PURPLE 0xff800080,
#define ORANGE 0xffFF4500,
#define CYAN 0xff008080,
#define YELLOW 0xffFFD700,
#define BROWN 0xffA52A2A,
#define BLUE 0xff000080,
#define DBLUE 0xff000030,
#define BRED 0xffFF0000,
#define BBLUE 0xff0000FF,
#define BGREEN 0xff00FF00,
#define TBLACK 0x00000000;

typedef struct
{
    struct Point cursor_position;
    struct Framebuffer *framebuffer;
    struct PSF1_FONT *psf1_font;

    unsigned int color;
    bool overwrite;
} BasicRenderer;

void init_renderer(BasicRenderer *basicrenderer, struct Framebuffer *framebuffer, struct PSF1_FONT *psf1_font);

void print(BasicRenderer *basicrenderer, const char* str);
void put_char(BasicRenderer *basicrenderer, char chr, unsigned int xOff, unsigned int yOff);
void clear(BasicRenderer *basicrenderer, uint32_t color, bool resetCursor);

extern BasicRenderer *global_renderer;
