#include "BasicRenderer.h"

void init_renderer(BasicRenderer *basicrenderer, struct Framebuffer *framebuffer, struct PSF1_FONT *psf1_font)
{
    basicrenderer->color = 0xffffffff;

    basicrenderer->cursor_position.x = 0;
    basicrenderer->cursor_position.y = 0;

    basicrenderer->framebuffer = framebuffer;
    basicrenderer->psf1_font = psf1_font;

    return;
}

void print(BasicRenderer *basicrenderer, const char* str)
{
    char *chr = (char *)str;
    while (*chr != 0)
    {
        switch (*chr)
        {
            case '\n':
                basicrenderer->cursor_position.x = 0;
                basicrenderer->cursor_position.y += 16;
                break;

            case '\t':
                basicrenderer->cursor_position.x += 8;
                break;
            
            default:
                put_char(basicrenderer, *chr, basicrenderer->cursor_position.x, basicrenderer->cursor_position.y);
                basicrenderer->cursor_position.x += 8;
                break;
        }

        if (basicrenderer->cursor_position.x + 8 > basicrenderer->framebuffer->width)
        {
            basicrenderer->cursor_position.x = 0;
            basicrenderer->cursor_position.y += 16;
        }

        chr++;
    }

    return;
}

void put_char(BasicRenderer *basicrenderer, char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int *pixPtr = (unsigned int *)basicrenderer->framebuffer->base_address;
    char *fontPtr = (char *)basicrenderer->psf1_font->glyph_buffer + (chr * basicrenderer->psf1_font->psf1_header->charsize);

    for (unsigned long y = yOff; y < yOff + 16; y++)
    {
        for (unsigned long x = xOff; x < xOff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int *)(pixPtr + x + (y * basicrenderer->framebuffer->pixels_per_scan_line)) = basicrenderer->color;
            }
        }
        fontPtr++;
    }

    return;
}

void clear(BasicRenderer *basicrenderer, uint32_t color, bool resetCursor)
{
    uint64_t fbBase = (uint64_t)basicrenderer->framebuffer->base_address;
    uint64_t pxlsPerScanline = basicrenderer->framebuffer->pixels_per_scan_line;
    uint64_t fbHeight = basicrenderer->framebuffer->height;

    for (int64_t y = 0; y < basicrenderer->framebuffer->height; y++)
    {
        for (int64_t x = 0; x < basicrenderer->framebuffer->width; x++)
        {
            *((uint32_t *)(fbBase + 4 * (x + pxlsPerScanline * y))) = color;
        }
    }

    if (resetCursor)
    {
        basicrenderer->cursor_position.x = 0;
        basicrenderer->cursor_position.y = 0;
    }

    return;
}
