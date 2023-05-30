#include "genesis.h"
#include "supaplex/graphics.h"
#include "supaplex/system.h"
#include "../res/resources.h"

#define kPaleteDataSize (kNumberOfColors * 4)
#define kNumberOfPalettes 4

typedef uint8_t ColorPaletteData[kPaleteDataSize];

ColorPalette gCurrentPalette;

// Game palettes:
// - 0: level credits
// - 1: main menu
// - 2: ???
// - 3: ???
//

// @TODO pladaria: instead of converting dat to rgb, we could store in ROM rgb directly
ColorPalette gPalettes[kNumberOfPalettes];

const ColorPalette gBlackPalette = {
    // 60D5h
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
};

const ColorPaletteData gTitlePaletteData = {
    0x02, 0x03, 0x05, 0x00, 0x0D, 0x0A, 0x04, 0x0C, 0x02, 0x06, 0x06, 0x02, 0x03, 0x09, 0x09, 0x03,
    0x0B, 0x08, 0x03, 0x06, 0x02, 0x07, 0x07, 0x0A, 0x08, 0x06, 0x0D, 0x09, 0x06, 0x04, 0x0B, 0x01,
    0x09, 0x01, 0x00, 0x04, 0x0B, 0x01, 0x00, 0x04, 0x0D, 0x01, 0x00, 0x0C, 0x0F, 0x01, 0x00, 0x0C,
    0x0F, 0x06, 0x04, 0x0C, 0x02, 0x05, 0x06, 0x08, 0x0F, 0x0C, 0x06, 0x0E, 0x0C, 0x0C, 0x0D, 0x0E,
};

const ColorPaletteData gTitle1PaletteData = {
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x0A, 0x0A, 0x0A, 0x07,
    0x0A, 0x0A, 0x0A, 0x07, 0x0B, 0x0B, 0x0B, 0x07, 0x0E, 0x01, 0x01, 0x04, 0x09, 0x09, 0x09, 0x07,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09, 0x00, 0x00, 0x04, 0x0B, 0x00, 0x00, 0x0C,
    0x08, 0x08, 0x08, 0x08, 0x05, 0x05, 0x05, 0x08, 0x06, 0x06, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08,
};

const ColorPaletteData gTitle2PaletteData = {
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x06, 0x06, 0x06, 0x08, 0x0A, 0x0A, 0x0A, 0x07,
    0x0A, 0x0A, 0x0A, 0x07, 0x0B, 0x0B, 0x0B, 0x07, 0x0E, 0x01, 0x01, 0x04, 0x09, 0x09, 0x09, 0x07,
    0x01, 0x03, 0x07, 0x00, 0x08, 0x08, 0x08, 0x08, 0x09, 0x00, 0x00, 0x04, 0x0B, 0x00, 0x00, 0x0C,
    0x00, 0x02, 0x0A, 0x01, 0x05, 0x05, 0x05, 0x08, 0x06, 0x06, 0x06, 0x08, 0x08, 0x08, 0x08, 0x07,
};

uint8_t gCurrentPanelHeight;

// This buffer has the contents of TITLE2.DAT after it's been "decoded" (i.e. after picking the different channels
// every 40 bytes and forming the 4 bit palette index for each pixel).
//
uint8_t gTitle2DecodedBitmapData[kFullScreenFramebufferLength];

uint8_t gScrollDestinationScreenBitmapData[kFullScreenFramebufferLength];

// Time difference between 2 consecutive renders
uint32_t gRenderDeltaTime;

static Sprite *cursorSprite;

void readMenuDat(void)
{
}

void loadMurphySprites(void)
{
    kprintf("*** Load cursor sprite");
    cursorSprite = SPR_addSprite(&sprCursor, 160, 112, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    SPR_setVisibility(cursorSprite, HIDDEN);
    kprintf("MEM_getFree: %d", MEM_getFree());
    kprintf("MEM_getLargestFreeBlock: %d", MEM_getLargestFreeBlock());
}

void readPanelDat(void)
{
}

void readBackDat(void)
{
}

void readBitmapFonts(void)
{
    VDP_loadFont(fontChars8.tileset, CPU);
}

void readAndRenderTitleDat(void)
{
    VDP_drawImageEx(BG_A, &imgTitle, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, TILE_USER_INDEX), 0, 0, FALSE, FALSE);
}

void readAndRenderTitle1Dat(void)
{
    VDP_drawImageEx(BG_A, &imgTitle1, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, TILE_USER_INDEX), 0, 0, FALSE, FALSE);
}

void readTitle2Dat(void)
{
    u16 tileIndex = TILE_USER_INDEX + imgTitle1.tileset->numTile;
    VDP_drawImageEx(BG_B, &imgTitle2, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, tileIndex), 0, 0, FALSE, FALSE);
}

void readGfxDat(void)
{
}

void readControlsDat(void)
{
}

void saveLastMouseAreaBitmap(void)
{
}

void restoreLastMouseAreaBitmap(void)
{
}

void drawMouseCursor(void)
{
    SPR_setVisibility(cursorSprite, VISIBLE);
}

void drawMenuBackground(void)
{
    kprintf("*** drawMenuBackground");
    VDP_drawImageEx(BG_A, &imgMenu, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX), 0, 0, FALSE, FALSE);
}

void drawOptionsBackground(uint8_t *dest)
{
}

void drawBackBackground(void)
{
}

void drawGfxTutorBackground(uint8_t *dest)
{
}

void drawFixedLevel(void)
{
}

void drawLevelViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
}

void drawCurrentLevelViewport(uint16_t panelHeight)
{
}

void drawMovingSpriteFrameInLevel(uint16_t srcX, uint16_t srcY, uint16_t width, uint16_t height, int16_t dstX,
                                  int16_t dstY)
{
}

void drawMovingFrame(uint16_t srcX, uint16_t srcY, uint16_t destPosition)
{
}

void scrollTerminalScreen(int16_t position)
{
}

void clearGamePanel(void)
{
}

void clearAdditionalInfoInGamePanel(void)
{
}

void saveScreenForAdvancedMenu(void)
{
}

void restoreScreenFromAdvancedMenu(void)
{
}

void renderAdvancedOptionsMenu(AdvancedOptionsMenu *menu)
{
}

void drawTextWithChars6FontWithOpaqueBackground(size_t destX, size_t destY, uint8_t color, const char *text)
{
    kprintf("drawTextWithChars6FontWithOpaqueBackground: %s", text);
    VDP_drawTextEx(BG_A, text, TILE_ATTR(color, FALSE, FALSE, FALSE), destX >> 3, destY >> 3, CPU);
}

void drawTextWithChars6FontWithTransparentBackground(size_t destX, size_t destY, uint8_t color, const char *text)
{
    kprintf("drawTextWithChars6FontWithTransparentBackground: %s", text);
    VDP_drawTextEx(BG_A, text, TILE_ATTR(color, FALSE, FALSE, FALSE), destX >> 3, destY >> 3, CPU);
}

void drawTextWithChars8Font(size_t destX, size_t destY, uint8_t color, const char *text)
{
    kprintf("drawTextWithChars8Font: %s", text);
    VDP_drawTextEx(BG_A, text, TILE_ATTR(color, FALSE, FALSE, FALSE), destX >> 3, destY >> 3, CPU);
}

void drawTextWithChars8FontToGamePanel(size_t destX, size_t destY, uint8_t color, const char *text)
{
    kprintf("drawTextWithChars8FontToGamePanel: %s", text);
    VDP_drawTextEx(BG_A, text, TILE_ATTR(color, FALSE, FALSE, FALSE), destX >> 3, destY >> 3, CPU);
}

void videoLoop(void)
{
    handleSystemEvents(); // Make sure the app stays responsive
    render();
    present();

    // @TODO pladaria: remove previous calls, probably not needed at all
    SPR_update();
    SYS_doVBlankProcess();
}

void readPalettes(void)
{
    kprintf("*** readPalettes");
    convertPaletteDataToPalette(&binPalettes[0], gPalettes[0]);
    convertPaletteDataToPalette(&binPalettes[64], gPalettes[1]);
    convertPaletteDataToPalette(&binPalettes[128], gPalettes[2]);
    convertPaletteDataToPalette(&binPalettes[192], gPalettes[3]);
}

void replaceCurrentPaletteColor(uint8_t index, Color color)
{
}

static void convertRgbPaletteToVdpPalette(const ColorPalette palette, u16 *outVdpPalette)
{
    kprintf("*** convertRgbPaletteToVdpPalette");
    for (int i = 0; i < 16; i++)
    {
        const u32 color = palette[i].r << 16 | palette[i].g << 8 | palette[i].b;
        // const u32 color = *((u32 *)&palette[i]) >> 8;
        outVdpPalette[i] = RGB24_TO_VDPCOLOR(color);
        // KLog_U2("Index: ", i, " => ", outVdpPalette[i]);
        // KLog_U3("Color: ", palette[i].r, ", ", palette[i].g, ", ", palette[i].b);
    }
}

void setPalette(const ColorPalette palette)
{
    u16 pal[16];
    convertRgbPaletteToVdpPalette(palette, pal);
    PAL_setPalette(PAL0, pal, CPU);
}

void fadeToPalette(const ColorPalette palette)
{
    kprintf("*** fadeToPalette");
    // The original animation consisted of 64 steps and was designed to be displayed on screens with a refresh rate of
    // 70Hz. However, since the Megadrive console only supports 8 levels of color intensity per channel, I am reducing
    // the number of fade steps. This adjustment ensures that the color transition is subtle yet still perceptible.
    u16 steps = 12;
    u16 pal[16];
    convertRgbPaletteToVdpPalette(palette, pal);
    PAL_fadeIn(0, 15, pal, steps, FALSE);
}

void convertPaletteDataToPalette(const ColorPaletteData paletteData, ColorPalette outPalette)
{
    int kExponent = 4; // no idea why (yet)

    kprintf("*** convertPaletteDataToPalette");
    for (int i = 0; i < kNumberOfColors; ++i)
    {
        outPalette[i].r = paletteData[i * 4 + 0] << kExponent;
        outPalette[i].g = paletteData[i * 4 + 1] << kExponent;
        outPalette[i].b = paletteData[i * 4 + 2] << kExponent;
        outPalette[i].a = paletteData[i * 4 + 3] << kExponent; // intensity, for now
        // KLog_U1("Index: ", i);
        // KLog_U3("Color: ", outPalette[i].r, ", ", outPalette[i].g, ", ", outPalette[i].b);
    }
}

void startTrackingRenderDeltaTime(void)
{
}

uint32_t updateRenderDeltaTime(void)
{
    return 0;
}
