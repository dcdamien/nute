EESchema Schematic File Version 2  date 29/05/2010 13:17:11
LIBS:Connectors_kl
LIBS:power
LIBS:Sensors
LIBS:Tittar_kl
LIBS:touch_sens-cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title "noname.sch"
Date "29 may 2010"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_1 XL3
U 1 1 4C00DB88
P 7000 2450
F 0 "XL3" V 6950 2460 40  0000 C CNN
F 1 "CONN_1" V 7010 2470 40  0000 C CNN
	1    7000 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2450 5700 2450
Connection ~ 6200 2550
Wire Wire Line
	6200 2300 6200 2550
Wire Wire Line
	5800 2950 5700 2950
Connection ~ 6000 2550
Wire Wire Line
	6000 2750 6000 2550
Connection ~ 5900 2450
Wire Wire Line
	5900 2450 5900 2400
Wire Wire Line
	4750 2950 4650 2950
Wire Wire Line
	4650 2950 4650 2900
Wire Wire Line
	4550 2450 4750 2450
Wire Wire Line
	3850 2450 4050 2450
Wire Wire Line
	4650 2500 4650 2450
Connection ~ 4650 2450
Wire Wire Line
	5200 3300 5200 3400
Wire Wire Line
	5900 1900 5900 1800
Wire Wire Line
	5700 2550 6350 2550
Wire Wire Line
	6000 3150 6000 3400
Wire Wire Line
	5800 3400 5800 2750
Wire Wire Line
	5800 2750 5700 2750
Connection ~ 5800 2950
Wire Wire Line
	6350 3100 6450 3100
Connection ~ 6350 3100
Wire Wire Line
	6350 2750 6350 3400
$Comp
L CONN_2 XL2
U 1 1 4C00DB6C
P 6550 2650
F 0 "XL2" V 6500 2650 40  0000 C CNN
F 1 "CONN_2" V 6600 2650 40  0000 C CNN
	1    6550 2650
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG2
U 1 1 4C00C02F
P 6450 3100
F 0 "#FLG2" H 6450 3370 30  0001 C CNN
F 1 "PWR_FLAG" H 6450 3330 30  0000 C CNN
	1    6450 3100
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG1
U 1 1 4C00BFD8
P 6200 2300
F 0 "#FLG1" H 6200 2570 30  0001 C CNN
F 1 "PWR_FLAG" H 6200 2530 30  0000 C CNN
	1    6200 2300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 4C00BF6D
P 5900 1800
F 0 "#PWR3" H 5990 1780 30  0001 C CNN
F 1 "GND" H 5900 1720 30  0001 C CNN
	1    5900 1800
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4C00BF66
P 5900 2150
F 0 "R2" V 5980 2150 50  0000 C CNN
F 1 "10k" V 5900 2150 50  0000 C CNN
	1    5900 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 4C00BF59
P 6350 3400
F 0 "#PWR5" H 6440 3380 30  0001 C CNN
F 1 "GND" H 6350 3320 30  0001 C CNN
	1    6350 3400
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 4C00BF36
P 6000 2950
F 0 "C2" H 6050 3050 50  0000 L CNN
F 1 "0.1u" H 6050 2850 50  0000 L CNN
	1    6000 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 4C00BF21
P 6000 3400
F 0 "#PWR4" H 6090 3380 30  0001 C CNN
F 1 "GND" H 6000 3320 30  0001 C CNN
	1    6000 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 4C00BF19
P 5800 3400
F 0 "#PWR2" H 5890 3380 30  0001 C CNN
F 1 "GND" H 5800 3320 30  0001 C CNN
	1    5800 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 4C00BF12
P 5200 3400
F 0 "#PWR1" H 5290 3380 30  0001 C CNN
F 1 "GND" H 5200 3320 30  0001 C CNN
	1    5200 3400
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4C00BEFD
P 4650 2700
F 0 "C1" H 4700 2800 50  0000 L CNN
F 1 "10n" H 4700 2600 50  0000 L CNN
	1    4650 2700
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4C00BEF0
P 4300 2450
F 0 "R1" V 4380 2450 50  0000 C CNN
F 1 "10k" V 4300 2450 50  0000 C CNN
	1    4300 2450
	0    1    1    0   
$EndComp
$Comp
L CON1 XL1
U 1 1 4C00BEDF
P 3700 2450
F 0 "XL1" H 3700 2600 60  0000 C CNN
F 1 "CON1" H 3700 2300 60  0000 C CNN
	1    3700 2450
	1    0    0    -1  
$EndComp
$Comp
L QT100A DA1
U 1 1 4C00BEB0
P 5200 2750
F 0 "DA1" H 5000 3200 60  0000 C CNN
F 1 "QT100A" H 5400 3200 60  0000 C CNN
	1    5200 2750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
