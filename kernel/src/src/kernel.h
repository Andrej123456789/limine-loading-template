#pragma once

#include <stdint.h>
#include <stddef.h>

struct Framebuffer
{
    void *BaseAddress;
    size_t BufferSize;
    unsigned int Width;
    unsigned int Height;
    unsigned int PixelsPerScanLine;
};

struct PSF1_HEADER
{
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
};

struct PSF1_FONT
{
    struct PSF1_HEADER *psf1_Header;
    void *glyphBuffer;
};

void kernel(Framebuffer fb, PSF1_FONT* psf1_font);
