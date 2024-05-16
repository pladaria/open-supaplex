#include <stdint.h>
#include "genesis.h"

void initializeControllers(void)
{
}

int8_t getGameControllerX(void)
{
    u16 joy1 = JOY_readJoypad(JOY_1);
    if (joy1 & BUTTON_LEFT) {
        return -1;
    }
    if (joy1 & BUTTON_RIGHT) {
        return 1;
    }
    return 0;
}

int8_t getGameControllerY(void)
{
    u16 joy1 = JOY_readJoypad(JOY_1);
    if (joy1 & BUTTON_UP) {
        return -1;
    }
    if (joy1 & BUTTON_DOWN) {
        return 1;
    }
    return 0;
}

uint8_t getGameControllerButtonA(void)
{
    u16 joy1 = JOY_readJoypad(JOY_1);
    return (joy1 & BUTTON_A) != 0;
}

uint8_t getGameControllerButtonB(void)
{
    u16 joy1 = JOY_readJoypad(JOY_1);
    return (joy1 & BUTTON_B) != 0;
}

uint8_t getGameControllerButtonX(void)
{
    return 0;
}

uint8_t getGameControllerButtonY(void)
{
    return 0;
}

uint8_t getGameControllerButtonBack(void)
{
    return 0;
}

uint8_t getGameControllerButtonStart(void)
{
    u16 joy1 = JOY_readJoypad(JOY_1);
    return (joy1 & BUTTON_START) != 0;
}

uint8_t getGameControllerButtonLeftShoulder(void)
{
    return 0;
}

uint8_t getGameControllerButtonRightShoulder(void)
{
    return 0;
}

uint8_t isAnyGameControllerButtonPressed(void)
{
    JOY_update();
    return JOY_readJoypad(JOY_1) != 0;
}

uint8_t getGameControllerConfirmButton(void)
{
    return 0;
}

uint8_t getGameControllerCancelButton(void)
{
    return 0;
}

void gameControllerEmulateMouse(float *x, float *y, uint8_t *leftButton, uint8_t *rightButton)
{
    u16 joy1 = JOY_readJoypad(JOY_1);
    if (joy1 & BUTTON_LEFT)
    {
        *x = -1.0;
    }
    else if (joy1 & BUTTON_RIGHT)
    {
        *x = 1.0;
    }
    else
    {
        *x = 0.0;
    }
    if (joy1 & BUTTON_UP)
    {
        *y = -1.0;
    }
    else if (joy1 & BUTTON_DOWN)
    {
        *y = 1.0;
    }
    else
    {
        *y = 0.0;
    }
    *leftButton = (joy1 & BUTTON_A) != 0;
    *rightButton = (joy1 & BUTTON_B) != 0;
}
