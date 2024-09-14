#include "kernel.h"
#include "BasicRenderer.h"

static BasicRenderer r;
BasicRenderer *global_renderer;

void kernel(struct Framebuffer framebuffer, struct PSF1_FONT* psf1_font)
{
    init_renderer(&r, &framebuffer, psf1_font);
    global_renderer = &r;

    clear(global_renderer, 0xff000080, true); // color blue
    print(global_renderer, "This text comes from ZAP font!\n");

    return;
}
