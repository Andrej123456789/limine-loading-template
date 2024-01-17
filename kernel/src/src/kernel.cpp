#include "kernel.h"
#include "BasicRenderer.hpp"

static BasicRenderer r = BasicRenderer(NULL, NULL);

void kernel(Framebuffer framebuffer, PSF1_FONT* psf1_font)
{
    // Note: we assume the framebuffer model is RGB with 32-bit pixels.
    /*for (size_t i = 0; i < 100; i++) {
        volatile uint32_t *fb_ptr = (uint32_t*)framebuffer.BaseAddress;
        fb_ptr[i * (framebuffer.PixelsPerScanLine) + i] = 0xffff00;
    }*/

    r = BasicRenderer(&framebuffer, psf1_font);
    GlobalRenderer = &r;

    GlobalRenderer->Clear(Colors.black, true);
    GlobalRenderer->Print("This text comes from ZAP font!\n");

    return;
}
