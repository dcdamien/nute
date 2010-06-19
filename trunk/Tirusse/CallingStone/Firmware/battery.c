#include "battery.h"
#include "common.h"
#include "main.h"

void Battery_Task (void) {
    if (BAT_IS_CHARGING()) LED_ON();
    else LED_OFF();
}

FORCE_INLINE void BatteryInit(void) {
    BAT_CHRG_DDR  &= ~(1<<BAT_CHRG_P);
    BAT_CHRG_PORT |=  (1<<BAT_CHRG_P);
}