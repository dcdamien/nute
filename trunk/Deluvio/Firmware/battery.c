#include "battery.h"
#include "common.h"
#include "util/atomic.h"

uint16_t BatteryADCValue;

// ============================= Implementation ================================
void BatteryMeasure(void) {
    BatteryADCValue = 0;
    ADC_REF_ENABLE();
    ADC_START_MEASUREMENT();    // First fake measurement
    while(!ADC_MEASUREMENT_COMPLETED());
    for(uint8_t i=0; i<BAT_NUMBER_OF_MEASURES; i++) {
        ADC_START_MEASUREMENT();
        while(!ADC_MEASUREMENT_COMPLETED());
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            BatteryADCValue += ADC;
        }
    } // for
    ADC_REF_DISABLE();
    ADC_DISABLE();
    // divide result
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        BatteryADCValue >>= BAT_POWER_OF_MEASURES;
    }
}