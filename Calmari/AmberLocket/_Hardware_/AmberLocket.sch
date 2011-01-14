EESchema Schematic File Version 2  date 11/01/2011 20:12:04
LIBS:Atmel_kl
LIBS:power
LIBS:Tittar_kl
EELAYER 43  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "11 jan 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	6650 3100 6650 3250
Wire Wire Line
	6000 2700 6100 2700
Wire Wire Line
	3600 2700 3700 2700
Wire Wire Line
	6150 2050 6150 1950
Wire Wire Line
	6000 2500 6350 2500
Wire Wire Line
	4300 3000 4300 2800
Wire Wire Line
	6150 2500 6150 2450
Connection ~ 6150 2500
Wire Wire Line
	3600 3100 3600 3250
Wire Wire Line
	4200 2700 4300 2700
Wire Wire Line
	6600 2700 6650 2700
$Comp
L GND #PWR?
U 1 1 4D2C8F41
P 3600 3250
F 0 "#PWR?" H 3690 3230 30  0001 C CNN
F 1 "GND" H 3600 3170 30  0001 C CNN
	1    3600 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4D2C8F3E
P 6650 3250
F 0 "#PWR?" H 6740 3230 30  0001 C CNN
F 1 "GND" H 6650 3170 30  0001 C CNN
	1    6650 3250
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 4D2C8F35
P 3950 2700
F 0 "R?" V 4030 2700 50  0000 C CNN
F 1 "22" V 3950 2700 50  0000 C CNN
	1    3950 2700
	0    1    1    0   
$EndComp
$Comp
L R R?
U 1 1 4D2C8F2E
P 6350 2700
F 0 "R?" V 6430 2700 50  0000 C CNN
F 1 "22" V 6350 2700 50  0000 C CNN
	1    6350 2700
	0    1    1    0   
$EndComp
$Comp
L LED D?
U 1 1 4D2C8F1F
P 3600 2900
F 0 "D?" H 3700 3040 50  0000 C CNN
F 1 "LED" H 3520 3040 50  0000 C CNN
	1    3600 2900
	0    1    1    0   
$EndComp
$Comp
L LED D?
U 1 1 4D2C8F0E
P 6650 2900
F 0 "D?" H 6750 3040 50  0000 C CNN
F 1 "LED" H 6570 3040 50  0000 C CNN
	1    6650 2900
	0    1    1    0   
$EndComp
NoConn ~ 6000 2600
NoConn ~ 6000 2800
NoConn ~ 4300 2600
NoConn ~ 4300 2500
$Comp
L GND #PWR?
U 1 1 4D2C8E9F
P 6150 1950
F 0 "#PWR?" H 6240 1930 30  0001 C CNN
F 1 "GND" H 6150 1870 30  0001 C CNN
	1    6150 1950
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 4D2C8E9A
P 6150 2250
F 0 "C?" H 6200 2350 50  0000 L CNN
F 1 "C" H 6200 2150 50  0000 L CNN
	1    6150 2250
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR?
U 1 1 4D2C8E7C
P 6350 2500
F 0 "#PWR?" H 6350 2460 30  0001 C CNN
F 1 "+BATT" H 6430 2530 30  0000 C CNN
	1    6350 2500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 4D2C8E70
P 4300 3000
F 0 "#PWR?" H 4390 2980 30  0001 C CNN
F 1 "GND" H 4300 2920 30  0001 C CNN
	1    4300 3000
	1    0    0    -1  
$EndComp
$Comp
L ATTINY45 DD?
U 1 1 4D2C8E60
P 5150 2700
F 0 "DD?" H 4700 3050 60  0000 C CNN
F 1 "ATTINY45" H 5450 3050 60  0000 C CNN
	1    5150 2700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
