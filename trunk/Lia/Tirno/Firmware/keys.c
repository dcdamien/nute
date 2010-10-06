#include "keys.h"
#include <stdbool.h>
#include "delay_util.h"

struct {
    bool KeyDownPressed:1;
    bool KeyUpPressed:1;
    bool KeyRightPressed:1;
    bool KeyLeftPressed:1;
    uint16_t Timer;
} EKeys;

void Keys_Task(void) {
    if(!DelayElapsed(&EKeys.Timer, 250)) return;

    if(KEY_DOWN_PRESSED() && !EKeys.KeyDownPressed) {
        EKeys.KeyDownPressed = true;
        EVENT_KeyDown();
    }
    else if(!KEY_DOWN_PRESSED() && EKeys.KeyDownPressed) EKeys.KeyDownPressed = false;
}

void KeysInit(void) {
    // Init ports
    KEYS_DDR  &= ~((1<<KEY_UP)|(1<<KEY_DOWN)|(1<<KEY_RIGHT)|(1<<KEY_LEFT));
    KEYS_PORT |=  ((1<<KEY_UP)|(1<<KEY_DOWN)|(1<<KEY_RIGHT)|(1<<KEY_LEFT));
    // Init variables
    EKeys.KeyDownPressed = false;
    EKeys.KeyUpPressed = false;
    EKeys.KeyLeftPressed = false;
    EKeys.KeyRightPressed = false;
    DelayReset(&EKeys.Timer);
}

