#include "BasicRenderer.hpp"

BasicRenderer::BasicRenderer(Framebuffer *framebuffer, PSF1_FONT *psf1_font)
{
    color = 0xffffffff;
    cursor_position = {0, 0};
    this->framebuffer = framebuffer;
    this->psf1_font = psf1_font;
}

void BasicRenderer::PutChar(char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int *pixPtr = (unsigned int *)framebuffer->base_address;
    char *fontPtr = (char *)psf1_font->glyph_buffer + (chr * psf1_font->psf1_header->charsize);

    for (unsigned long y = yOff; y < yOff + 16; y++)
    {
        for (unsigned long x = xOff; x < xOff + 8; x++)
        {
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0)
            {
                *(unsigned int *)(pixPtr + x + (y * framebuffer->pixels_per_scan_line)) = color;
            }
        }
        fontPtr++;
    }
}

void BasicRenderer::Print(const char *str)
{
    char *chr = (char *)str;
    while (*chr != 0)
    {
        switch (*chr)
        {
            case '\n':
                cursor_position.x = 0;
                cursor_position.y += 16;
                break;

            case '\t':
                cursor_position.x += 8;
                break;
            
            default:
                PutChar(*chr, cursor_position.x, cursor_position.y);
                cursor_position.x += 8;
                break;
        }

        if (cursor_position.x + 8 > framebuffer->width)
        {
            cursor_position.x = 0;
            cursor_position.y += 16;
        }

        chr++;
    }
}

void BasicRenderer::Clear(uint32_t color, bool resetCursor)
{
    uint64_t fbBase = (uint64_t)framebuffer->base_address;
    uint64_t pxlsPerScanline = framebuffer->pixels_per_scan_line;
    uint64_t fbHeight = framebuffer->height;

    for (int64_t y = 0; y < framebuffer->height; y++)
    {
        for (int64_t x = 0; x < framebuffer->width; x++)
        {
            *((uint32_t *)(fbBase + 4 * (x + pxlsPerScanline * y))) = color;
        }
    }

    if (resetCursor)
    {
        cursor_position = {0, 0};
    }
}
