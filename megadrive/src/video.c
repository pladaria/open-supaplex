#include "genesis.h"
#include "supaplex/video.h"

uint8_t kScreenPixels[1]; // @TODO pladaria: remove this

uint8_t *gScreenPixels = kScreenPixels;          // @TODO pladaria: remove this
ScalingMode gScalingMode = ScalingModeAspectFit; // @TODO pladaria: remove this

Sprite *cursorSprite;
static s16 mouseX = 320 / 2;
static s16 mouseY = 224 / 2;

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
    *width = VDP_getScreenWidth();
    *height = VDP_getScreenHeight();
}

void centerMouse()
{
    mouseX = VDP_getScreenWidth() >> 1;
    mouseY = VDP_getScreenHeight() >> 1;
}

void moveMouse(int x, int y)
{
    mouseX = x;
    mouseY = y;
}

void hideMouse(void)
{
    SPR_setVisibility(cursorSprite, HIDDEN);
}

void getMouseState(int *x, int *y, uint8_t *leftButton, uint8_t *rightButton)
{
    u16 joy1 = JOY_readJoypad(JOY_1);
    if (joy1 & BUTTON_LEFT)
    {
        mouseX -= 2;
    }
    else if (joy1 & BUTTON_RIGHT)
    {
        mouseX += 2;
    }
    if (joy1 & BUTTON_UP)
    {
        mouseY -= 2;
    }
    else if (joy1 & BUTTON_DOWN)
    {
        mouseY += 2;
    }
    *x = clamp(mouseX, 0, VDP_getScreenWidth() - 1);
    *y = clamp(mouseY, 0, VDP_getScreenHeight() - 1);
    *leftButton = (joy1 & BUTTON_A) != 0;
    *rightButton = (joy1 & BUTTON_B) != 0;
}

void toggleFullscreen()
{
}

void setFullscreenMode(uint8_t fullscreen)
{
}

uint8_t getFullscreenMode(void)
{
    return 1;
}

void setGlobalPaletteColor(const uint8_t index, const Color color)
{
}

void setColorPalette(const ColorPalette palette)
{
}