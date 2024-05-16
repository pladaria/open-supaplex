#include "genesis.h"
#include "supaplex/virtualKeyboard.h"
#include "../res/resources.h"
#include "supaplex/graphics.h"
#include "supaplex/controller.h"

#define KEYBOARD_HEIGHT 88
#define SCREEN_HEIGHT 224
#define KEY_0_X 13
#define KEY_0_Y ((SCREEN_HEIGHT - KEYBOARD_HEIGHT) + (45 - 32))
#define cycle(value, min, max) (((value) < (min)) ? (max) : (((value) > (max)) ? (min) : (value)))

static void waitUntilKeyReleased(uint16_t timeoutFrames)
{
    if (!timeoutFrames)
    {
        while (isAnyGameControllerButtonPressed())
        {
            videoLoop();
        }
    }
    else
    {
        while (isAnyGameControllerButtonPressed() && (timeoutFrames > 0))
        {
            videoLoop();
            timeoutFrames--;
        }
    }
}

uint8_t inputVirtualKeyboardText(const char *title, uint16_t maxLength, char *outText)
{
    uint16_t tileIndex = TILE_USER_INDEX + imgMenu.tileset->numTile;
    hideMouse();
    VDP_clearPlane(BG_B, TRUE);
    VDP_drawImageEx(BG_B, &imgKeyboard, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, tileIndex), 0, SCREEN_HEIGHT / 8,
                    FALSE, FALSE);
    PAL_setPalette(PAL1, imgKeyboard.palette->data, CPU);
    videoLoop();
    VDP_setVerticalScroll(BG_B, 0);
    VDP_setHilightShadow(TRUE);
    Sprite *keySprite = SPR_addSprite(&sprKeyboardKeys, KEY_0_X, KEY_0_Y, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    SPR_setVisibility(keySprite, HIDDEN);
    videoLoop();

    memset(outText, 0, maxLength);
    int16_t scroll = 0;
    uint8_t key = 0;
    uint8_t col = 0;
    uint8_t row = 0;
    uint8_t textLength = 0;
    uint8_t done = FALSE;

    // 10 keys per row
    const char keys[] = "0123456789QWERTYUIOPASDFGHJKL-ZXCVBNM ";

    // scroll up
    while (scroll < KEYBOARD_HEIGHT)
    {
        scroll = scroll + max(1, (KEYBOARD_HEIGHT - scroll) >> 3);
        VDP_setVerticalScroll(BG_B, scroll);
        videoLoop();
    }
    SPR_setVisibility(keySprite, VISIBLE);

    // read string
    while (!done)
    {
        videoLoop();
        if (getGameControllerX() < 0)
        {
            col = cycle(col - 1, 0, 9);
            waitUntilKeyReleased(7);
        }
        else if (getGameControllerX() > 0)
        {
            col = cycle(col + 1, 0, 9);
            waitUntilKeyReleased(7);
        }
        if (getGameControllerY() < 0)
        {
            row = cycle(row - 1, 0, 3);
            waitUntilKeyReleased(7);
        }
        else if (getGameControllerY() > 0)
        {
            row = cycle(row + 1, 0, 3);
            waitUntilKeyReleased(7);
        }

        key = row * 10 + col;

        if (getGameControllerButtonA())
        {
            if (key >= 38)
            {
                if (textLength > 0)
                {
                    if (key == 38)
                    {
                        textLength--;
                        outText[textLength] = 0;
                    }
                    else if (key == 39)
                    {
                        done = TRUE;
                    }
                }
            }
            else if (textLength < maxLength)
            {
                outText[textLength++] = keys[key];
            }
            waitUntilKeyReleased(0);
            char previewText[9] = "        ";
            memcpy(previewText, outText, textLength);
            kprintf(previewText);
            VDP_drawTextBG(BG_B, previewText, 200 >> 3, (SCREEN_HEIGHT + 48 - 32) >> 3);
        }
        else if (getGameControllerButtonB())
        {
            waitUntilKeyReleased(0);
            break;
        }

        SPR_setFrame(keySprite, key);
        SPR_setPosition(keySprite, KEY_0_X + (col << 4), KEY_0_Y + (row << 4));
    }
    SPR_setVisibility(keySprite, HIDDEN);

    // scroll down
    while (scroll > 0)
    {
        scroll = scroll - max(1, scroll >> 3);
        VDP_setVerticalScroll(BG_B, scroll);
        videoLoop();
    }

    SPR_releaseSprite(keySprite);
    VDP_setHilightShadow(FALSE);
    videoLoop();
    return done;
}
