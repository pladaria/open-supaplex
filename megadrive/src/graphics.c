#include "supaplex/graphics.h"

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
ColorPalette gPalettes[kNumberOfPalettes];
ColorPalette gBlackPalette; // 60D5h

ColorPaletteData gTitlePaletteData;
ColorPaletteData gTitle1PaletteData;
ColorPaletteData gTitle2PaletteData;

uint8_t gCurrentPanelHeight;

// This buffer has the contents of TITLE2.DAT after it's been "decoded" (i.e. after picking the different channels
// every 40 bytes and forming the 4 bit palette index for each pixel).
//
uint8_t gTitle2DecodedBitmapData[kFullScreenFramebufferLength];

uint8_t gScrollDestinationScreenBitmapData[kFullScreenFramebufferLength];

// Time difference between 2 consecutive renders
uint32_t gRenderDeltaTime;

void readMenuDat(void)
{
}
void loadMurphySprites(void)
{
}
void readPanelDat(void)
{
}
void readBackDat(void)
{
}
void readBitmapFonts(void)
{
}
void readAndRenderTitleDat(void)
{
}
void readAndRenderTitle1Dat(void)
{
}
void readTitle2Dat(void)
{
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
}
void drawMenuBackground(void)
{
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
}

void drawTextWithChars6FontWithTransparentBackground(size_t destX, size_t destY, uint8_t color, const char *text)
{
}

void drawTextWithChars8Font(size_t destX, size_t destY, uint8_t color, const char *text)
{
}

void drawTextWithChars8FontToGamePanel(size_t destX, size_t destY, uint8_t color, const char *text)
{
}

void videoLoop(void)
{
}

void readPalettes(void)
{
}

void replaceCurrentPaletteColor(uint8_t index, Color color)
{
}

void setPalette(ColorPalette palette)
{
}

void fadeToPalette(ColorPalette palette)
{
}

void convertPaletteDataToPalette(ColorPaletteData paletteData, ColorPalette outPalette)
{
}

void startTrackingRenderDeltaTime(void)
{
}

uint32_t updateRenderDeltaTime(void)
{
    return 0;
}
