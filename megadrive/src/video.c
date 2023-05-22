#include "genesis.h"
#include "supaplex/video.h"

uint8_t kScreenPixels[1]; // @TODO pladaria: remove this

uint8_t *gScreenPixels = kScreenPixels; // @TODO pladaria: remove this
ScalingMode gScalingMode = ScalingModeAspectFit; // @TODO pladaria: remove this

void initializeVideo(uint8_t fastMode)
{
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();

    PAL_setPalette(0, palette_black, CPU);
    PAL_setPalette(1, palette_black, CPU);
    PAL_setPalette(2, palette_black, CPU);
    PAL_setPalette(3, palette_black, CPU);

    SPR_init();
    VDP_clearPlane(BG_A, 0);
    VDP_clearPlane(BG_B, 0);
}

void render()
{
    // Do nothing
}

void present()
{
    // Do nothing
}

void destroyVideo()
{
    SPR_end();
}

ScalingMode getScalingMode(void)
{
    return gScalingMode;
}

void setScalingMode(ScalingMode mode)
{
    gScalingMode = mode;
}

void getWindowSize(int *width, int *height)
{
    // Do nothing
}

void centerMouse()
{
    // Do nothing
}

void moveMouse(int x, int y)
{
    // Do nothing
}

void hideMouse(void)
{
    // Do nothing
}

void getMouseState(int *x, int *y, uint8_t *leftButton, uint8_t *rightButton)
{
    // Do nothing
}

void toggleFullscreen()
{
    // Do nothing
}

void setFullscreenMode(uint8_t fullscreen)
{
    // Do nothing
}

uint8_t getFullscreenMode(void)
{
    // Do nothing
    return 1;
}

void setGlobalPaletteColor(const uint8_t index, const Color color)
{
    // Do nothing
}

void setColorPalette(const ColorPalette palette)
{
    // Do nothing
}