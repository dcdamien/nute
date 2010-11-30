/* 
 * File:   main.c
 * Author: Kreyl Laurelindo
 *
 * Created on 29 Ноябрь 2010 г., 19:48
 */

#include "main.h"
#include "touch_qt_config.h"
#include "touch_api.h"
#include <avr/interrupt.h>

/* flag set by timer ISR when it's time to measure touch */
static volatile uint8_t time_to_measure_touch = 0u;

/* current time, set by timer ISR */
static volatile uint16_t current_time_ms_touch = 0u;
/* Timer period in msec. */
uint16_t qt_measurement_period_msec = 25u;

int main(void) {
    GeneralInit();
    /*status flags to indicate the re-burst for library*/
    uint16_t status_flag = 0u;
    uint16_t burst_flag = 0u;

    sei();

    while(1) {
        if(time_to_measure_touch) {
            time_to_measure_touch = false;
            do {
                //  one time measure touch sensors
                status_flag = qt_measure_sensors(current_time_ms_touch);
                burst_flag  = status_flag & QTLIB_BURST_AGAIN;
            } while (burst_flag);
        } // if(time_to_measure_touch)

        if(SensorIsTouched(0)) PumpOn(0);
        else PumpOff(0);
    } // while(1)
}

FORCE_INLINE void GeneralInit(void) {
    QTouchInit();

    // Pumps
    PUMP_DDR |= (1<<PUMP1P)|(1<<PUMP2P)|(1<<PUMP3P)|(1<<PUMP4P);
    //
}

// Pumps
void PumpOn(enum pump_t APump) {
    switch (APump) {
        case Pump1: PUMP_PORT |= (1<<PUMP1P);
        case Pump2: PUMP_PORT |= (1<<PUMP2P);
        case Pump3: PUMP_PORT |= (1<<PUMP3P);
        case Pump4: PUMP_PORT |= (1<<PUMP4P);
    }
}
void PumpOff(enum pump_t APump) {
    switch (APump) {
        case Pump1: PUMP_PORT &= ~(1<<PUMP1P);
        case Pump2: PUMP_PORT &= ~(1<<PUMP2P);
        case Pump3: PUMP_PORT &= ~(1<<PUMP3P);
        case Pump4: PUMP_PORT &= ~(1<<PUMP4P);
    }
}

// QTouch
void QTouchInit(void) {
    // Configure the Sensors as keys
    qt_enable_key( CHANNEL_0, AKS_GROUP_1, 10u, HYST_6_25 );
    qt_enable_key( CHANNEL_1, AKS_GROUP_1, 10u, HYST_6_25 );
    qt_enable_key( CHANNEL_2, AKS_GROUP_1, 10u, HYST_6_25 );
    qt_enable_key( CHANNEL_3, AKS_GROUP_1, 10u, HYST_6_25 );

    //  Set the parameters like recalibration threshold, Max_On_Duration etc in this function by the user
    /*  This will be modified by the user to different values   */
    qt_config_data.qt_di              = DEF_QT_DI;
    qt_config_data.qt_neg_drift_rate  = DEF_QT_NEG_DRIFT_RATE;
    qt_config_data.qt_pos_drift_rate  = DEF_QT_POS_DRIFT_RATE;
    qt_config_data.qt_max_on_duration = DEF_QT_MAX_ON_DURATION;
    qt_config_data.qt_drift_hold_time = DEF_QT_DRIFT_HOLD_TIME;
    qt_config_data.qt_recal_threshold = DEF_QT_RECAL_THRESHOLD;
    qt_config_data.qt_pos_recal_delay = DEF_QT_POS_RECAL_DELAY;

    qt_init_sensing();  // initialise touch sensing

    // configure timer ISR to fire regularly
    /*  set timer compare value (how often timer ISR will fire) */
    OCR1A = ( TICKS_PER_MS * qt_measurement_period_msec);
    /*  enable timer ISR */
    TIMSK |= (1u << OCIE1A);
    /*  timer prescaler = system clock / 8  */
    TCCR1B |= (1u << CS11);
    /*  timer mode = CTC (count up to compare value, then reset)    */
    TCCR1B |= (1u << WGM12);


    /*  Address to pass address of user functions   */
    /*  This function is called after the library has made capacitive measurements,
    *   but before it has processed them. The user can use this hook to apply filter
    *   functions to the measured signal values.(Possibly to fix sensor layout faults)    */
    qt_filter_callback = 0;

}

FORCE_INLINE bool SensorIsTouched(uint8_t ASensor) {
    return (qt_measure_data.qt_touch_status.sensor_states[0] & (1<<(ASensor)));
}


ISR(TIMER1_COMPA_vect) {
    /*  set flag: it's time to measure touch    */
    time_to_measure_touch = 1u;

    /*  update the current time */
    current_time_ms_touch += qt_measurement_period_msec;
}


