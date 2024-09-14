#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

struct Framebuffer
{
    void *base_address;
    size_t buffer_size;
    unsigned int width;
    unsigned int height;
    unsigned int pixels_per_scan_line;
};

struct PSF1_HEADER
{
    unsigned char magic[2];
    unsigned char mode;
    unsigned char charsize;
};

struct PSF1_FONT
{
    struct PSF1_HEADER *psf1_header;
    void *glyph_buffer;
};

void kernel(struct Framebuffer fb, struct PSF1_FONT* psf1_font);
