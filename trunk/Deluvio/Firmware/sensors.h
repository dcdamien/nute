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

#define QTOUCH_STUDIO_MASKS 1
#define NUMBER_OF_PORTS     1
#define SNS1                B
#define SNSK1               B


void QTouchInit(void);
bool SensorIsTouched(uint8_t ASensor);

void Task_Sensors(void);


#endif	/* SENSORS_H */

