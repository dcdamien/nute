/* 
 * File:   sensors.h
 * Author: Kreyl Laurelindo
 *
 * Created on 30 ������ 2010 �., 15:43
 */

#ifndef SENSORS_H
#define	SENSORS_H

#include <stdbool.h>
#include <inttypes.h>

// ================================= Defines ===================================
// Ports & pins
#define QTOUCH_STUDIO_MASKS 1
#define NUMBER_OF_PORTS     1
#define SNS1                B
#define SNSK1               B

// Measurement period in msec.
#define QT_MEASUREMENT_PERIOD   25

// ================================ Prototypes =================================
void QTouchInit(void);
bool SensorIsTouched(uint8_t ASensor);

void Task_Sensors(void);

void EVENT_KeyDown(void);
void EVENT_KeyUp(void);
void EVENT_KeyMenu(void);
void EVENT_KeyAqua(void);
//void EVENT_KeyAquaDepressed(void);


#endif	/* SENSORS_H */

