#include "kernel.h"
#include "BasicRenderer.hpp"

static BasicRenderer r = BasicRenderer(nullptr, nullptr);

void kernel(struct Framebuffer framebuffer, struct PSF1_FONT* psf1_font)
{
    r = BasicRenderer(&framebuffer, psf1_font);
    GlobalRenderer = &r;

    GlobalRenderer->Clear(Colors.blue, true);
    GlobalRenderer->Print("This text comes from ZAP font!\n");

    return;
}
