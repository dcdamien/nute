EESchema Schematic File Version 2  date 11/04/2011 22:13:25
LIBS:Atmel_kl
LIBS:Connectors_kl
LIBS:power
LIBS:Tittar_kl
LIBS:Power_kl
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "11 apr 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 6250 2500
Wire Wire Line
	6900 2600 6900 2800
Wire Wire Line
	6250 2600 6900 2600
Wire Wire Line
	6300 3200 6300 3300
Wire Wire Line
	6900 3200 6900 3300
Wire Wire Line
	3850 2400 3850 2250
Connection ~ 6350 2400
Wire Wire Line
	6350 2400 6350 2300
Wire Wire Line
	4550 2700 4550 2850
Wire Wire Line
	6250 2400 6450 2400
Wire Wire Line
	6350 1900 6350 1800
Wire Wire Line
	3850 2850 3850 3000
Wire Wire Line
	6250 2700 6300 2700
$Comp
L GND #PWR?
U 1 1 4DA34470
P 6300 3300
F 0 "#PWR?" H 6390 3280 30  0001 C CNN
F 1 "GND" H 6300 3220 30  0001 C CNN
	1    6300 3300
	1    0    0    -1  
$EndComp
NoConn ~ 4550 2500
$Comp
L GND #PWR5
U 1 1 4DA33E45
P 6900 3300
F 0 "#PWR5" H 6990 3280 30  0001 C CNN
F 1 "GND" H 6900 3220 30  0001 C CNN
	1    6900 3300
	1    0    0    -1  
$EndComp
$Comp
L GERCON GC1
U 1 1 4DA33DDF
P 6300 2950
F 0 "GC1" H 6300 2750 60  0000 C CNN
F 1 "GERCON" H 6300 3150 60  0000 C CNN
	1    6300 2950
	0    1    1    0   
$EndComp
NoConn ~ 4550 2400
NoConn ~ 4550 2600
$Comp
L +BATT #PWR1
U 1 1 4C585A57
P 3850 2250
F 0 "#PWR1" H 3850 2200 20  0001 C CNN
F 1 "+BATT" H 3910 2290 30  0000 C CNN
	1    3850 2250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR2
U 1 1 4C585A53
P 3850 3000
F 0 "#PWR2" H 3940 2980 30  0001 C CNN
F 1 "GND" H 3850 2920 30  0001 C CNN
	1    3850 3000
	1    0    0    -1  
$EndComp
$Comp
L BAT B1
U 1 1 4C585A4A
P 3850 2600
F 0 "B1" H 4000 2800 60  0000 C CNN
F 1 "BAT" H 3600 2800 60  0000 C CNN
	1    3850 2600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 4C585A02
P 4550 2850
F 0 "#PWR3" H 4640 2830 30  0001 C CNN
F 1 "GND" H 4550 2770 30  0001 C CNN
	1    4550 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 4C5859FD
P 6350 1800
F 0 "#PWR4" H 6440 1780 30  0001 C CNN
F 1 "GND" H 6350 1720 30  0001 C CNN
	1    6350 1800
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4C5859F3
P 6350 2100
F 0 "C1" H 6400 2200 50  0000 L CNN
F 1 "0.1u" H 6400 2000 50  0000 L CNN
	1    6350 2100
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR6
U 1 1 4C5859BF
P 6450 2400
F 0 "#PWR6" H 6450 2350 20  0001 C CNN
F 1 "+BATT" H 6510 2440 30  0000 C CNN
	1    6450 2400
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 4C585997
P 6900 3000
F 0 "D1" H 7000 3140 50  0000 C CNN
F 1 "LED" H 6820 3140 50  0000 C CNN
	1    6900 3000
	0    1    1    0   
$EndComp
$Comp
L ATTINY45 DD1
U 1 1 4C58597E
P 5400 2600
F 0 "DD1" H 4950 2950 60  0000 C CNN
F 1 "ATTINY45" H 5700 2950 60  0000 C CNN
	1    5400 2600
	1    0    0    -1  
$EndComp
$EndSCHEMATC
