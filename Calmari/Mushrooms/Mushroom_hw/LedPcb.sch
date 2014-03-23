EESchema Schematic File Version 2
LIBS:Connectors_kl
LIBS:Tittar_kl
LIBS:LedPcb-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "noname.sch"
Date "23 mar 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED_RGB Q1
U 1 1 532DF73F
P 4000 2400
F 0 "Q1" H 3800 2750 60  0000 C CNN
F 1 "LED_RGB" H 4150 2750 60  0000 C CNN
F 2 "~" H 4000 2400 60  0000 C CNN
F 3 "~" H 4000 2400 60  0000 C CNN
	1    4000 2400
	1    0    0    -1  
$EndComp
$Comp
L LED_RGB_WS2812B Q2
U 1 1 532DF74E
P 4000 3450
F 0 "Q2" H 3800 3800 60  0000 C CNN
F 1 "LED_RGB_WS2812B" H 4000 3700 60  0000 C CNN
F 2 "~" H 3950 3450 60  0000 C CNN
F 3 "~" H 3950 3450 60  0000 C CNN
	1    4000 3450
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 XL3
U 1 1 532ED359
P 5250 3550
F 0 "XL3" V 5200 3560 40  0000 C CNN
F 1 "CONN_1" V 5260 3570 40  0000 C CNN
F 2 "~" H 5250 3550 60  0000 C CNN
F 3 "~" H 5250 3550 60  0000 C CNN
	1    5250 3550
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 532ED3E6
P 4000 3850
F 0 "C1" V 3900 3700 50  0000 L CNN
F 1 "0.1u" V 3900 3950 50  0000 L CNN
F 2 "CAP_0603" V 4100 3700 28  0000 C BNN
F 3 "~" H 4000 3850 60  0000 C CNN
	1    4000 3850
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 XL1
U 1 1 532ED892
P 2600 2400
F 0 "XL1" V 2550 2400 40  0000 C CNN
F 1 "CONN_3" V 2650 2400 40  0000 C CNN
F 2 "~" H 2600 2400 60  0000 C CNN
F 3 "~" H 2600 2400 60  0000 C CNN
	1    2600 2400
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 XL2
U 1 1 532ED8A1
P 5250 2400
F 0 "XL2" V 5200 2400 40  0000 C CNN
F 1 "CONN_3" V 5300 2400 40  0000 C CNN
F 2 "~" H 5250 2400 60  0000 C CNN
F 3 "~" H 5250 2400 60  0000 C CNN
	1    5250 2400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4200 3850 4500 3850
Wire Wire Line
	4500 3850 4500 3550
Wire Wire Line
	4450 3550 5050 3550
Connection ~ 4500 3550
Wire Wire Line
	3800 3850 3500 3850
Wire Wire Line
	3500 3850 3500 3550
Wire Wire Line
	2950 3550 3550 3550
Wire Wire Line
	2800 2500 2800 2550
Wire Wire Line
	2800 2550 3600 2550
Wire Wire Line
	5050 2500 5050 2550
Wire Wire Line
	5050 2550 4400 2550
Connection ~ 3500 3550
Wire Wire Line
	4450 3350 4450 2950
Wire Wire Line
	4450 2950 3400 2950
Wire Wire Line
	3550 3350 3550 2850
Wire Wire Line
	3550 2850 4650 2850
Wire Wire Line
	3150 2250 3150 2400
Wire Wire Line
	3150 2400 2800 2400
Wire Wire Line
	2800 2300 3050 2300
Wire Wire Line
	3050 2300 3050 2350
Wire Wire Line
	3050 2350 3250 2350
Wire Wire Line
	3250 2350 3250 2400
Wire Wire Line
	3250 2400 3600 2400
Wire Wire Line
	3150 2250 3600 2250
Wire Wire Line
	3400 2950 3400 2400
Connection ~ 3400 2400
Wire Wire Line
	2950 3550 2950 2550
Connection ~ 2950 2550
Wire Wire Line
	4650 2850 4650 2550
Connection ~ 4650 2550
Wire Wire Line
	4400 2250 4900 2250
Wire Wire Line
	4900 2250 4900 2400
Wire Wire Line
	4900 2400 5050 2400
Wire Wire Line
	5050 2300 4800 2300
Wire Wire Line
	4400 2400 4800 2400
Wire Wire Line
	4800 2400 4800 2300
$EndSCHEMATC
