EESchema Schematic File Version 2
LIBS:Candle4-cache
EELAYER 27 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date "22 feb 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 9100 2800 0    60   ~ 0
CC_GDO0
Entry Wire Line
	9450 2800 9550 2900
$Comp
L TESTPOINT TP2
U 1 1 4E47AFD0
P 9050 2800
F 0 "TP2" V 9050 3000 60  0000 C CNN
F 1 "TESTPOINT" H 9025 3025 60  0001 C CNN
F 2 "" H 9050 2800 60  0001 C CNN
F 3 "" H 9050 2800 60  0001 C CNN
	1    9050 2800
	0    -1   -1   0   
$EndComp
NoConn ~ 7750 2400
NoConn ~ 7750 3400
NoConn ~ 7750 3700
NoConn ~ 7750 3850
NoConn ~ 7750 3950
NoConn ~ 7750 4100
NoConn ~ 7750 4200
NoConn ~ 7750 4300
NoConn ~ 5250 3300
NoConn ~ 5250 3200
NoConn ~ 5250 3100
NoConn ~ 5250 3000
NoConn ~ 5250 2700
NoConn ~ 5250 2500
NoConn ~ 5250 2400
$Comp
L GND #PWR01
U 1 1 4E47AC97
P 5200 5100
F 0 "#PWR01" H 5290 5080 30  0001 C CNN
F 1 "GND" H 5200 5020 30  0001 C CNN
F 2 "" H 5200 5100 60  0001 C CNN
F 3 "" H 5200 5100 60  0001 C CNN
	1    5200 5100
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 4E47AC96
P 5200 4800
F 0 "C5" H 5150 4900 50  0000 L CNN
F 1 "1u" H 5150 4700 50  0000 L CNN
F 2 "" H 5200 4800 60  0001 C CNN
F 3 "" H 5200 4800 60  0001 C CNN
	1    5200 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR02
U 1 1 4E47AA61
P 12200 4200
F 0 "#PWR02" H 12200 4160 30  0001 C CNN
F 1 "+3.3V" H 12280 4230 30  0000 C CNN
F 2 "" H 12200 4200 60  0001 C CNN
F 3 "" H 12200 4200 60  0001 C CNN
	1    12200 4200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR03
U 1 1 4E47AA5D
P 12500 4100
F 0 "#PWR03" H 12500 4060 30  0001 C CNN
F 1 "+3.3V" H 12580 4130 30  0000 C CNN
F 2 "" H 12500 4100 60  0001 C CNN
F 3 "" H 12500 4100 60  0001 C CNN
	1    12500 4100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR04
U 1 1 4E47AA57
P 12750 4000
F 0 "#PWR04" H 12750 3960 30  0001 C CNN
F 1 "+3.3V" H 12830 4030 30  0000 C CNN
F 2 "" H 12750 4000 60  0001 C CNN
F 3 "" H 12750 4000 60  0001 C CNN
	1    12750 4000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR05
U 1 1 4E47AA52
P 13000 3900
F 0 "#PWR05" H 13000 3860 30  0001 C CNN
F 1 "+3.3V" H 13080 3930 30  0000 C CNN
F 2 "" H 13000 3900 60  0001 C CNN
F 3 "" H 13000 3900 60  0001 C CNN
	1    13000 3900
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR06
U 1 1 4E47AA4B
P 13300 3800
F 0 "#PWR06" H 13300 3760 30  0001 C CNN
F 1 "+3.3V" H 13380 3830 30  0000 C CNN
F 2 "" H 13300 3800 60  0001 C CNN
F 3 "" H 13300 3800 60  0001 C CNN
	1    13300 3800
	1    0    0    -1  
$EndComp
Text Label 7850 3500 0    60   ~ 0
SWDIO
Text Label 7850 3600 0    60   ~ 0
SWCLK
$Comp
L +3.3V #PWR07
U 1 1 4E45917B
P 2450 2700
F 0 "#PWR07" H 2450 2660 30  0001 C CNN
F 1 "+3.3V" H 2530 2730 30  0000 C CNN
F 2 "" H 2450 2700 60  0001 C CNN
F 3 "" H 2450 2700 60  0001 C CNN
	1    2450 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 4E45917A
P 2450 2850
F 0 "#PWR08" H 2540 2830 30  0001 C CNN
F 1 "GND" H 2450 2770 30  0001 C CNN
F 2 "" H 2450 2850 60  0001 C CNN
F 3 "" H 2450 2850 60  0001 C CNN
	1    2450 2850
	1    0    0    -1  
$EndComp
$Comp
L ST_SWD XL1
U 1 1 4E459179
P 1950 2650
F 0 "XL1" H 1800 2950 60  0000 C CNN
F 1 "ST_SWD" H 2150 2950 60  0000 C CNN
F 2 "" H 1950 2650 60  0001 C CNN
F 3 "" H 1950 2650 60  0001 C CNN
	1    1950 2650
	1    0    0    -1  
$EndComp
Text Label 2400 2500 0    60   ~ 0
SWCLK
Text Label 2400 2600 0    60   ~ 0
SWDIO
Text Notes 1100 2700 0    60   ~ 0
Programming
Text Label 11950 3500 0    60   ~ 0
Ant2
$Comp
L C C3
U 1 1 4E37BB86
P 4700 4800
F 0 "C3" H 4650 4900 50  0000 L CNN
F 1 "0.1u" H 4650 4700 50  0000 L CNN
F 2 "" H 4700 4800 60  0001 C CNN
F 3 "" H 4700 4800 60  0001 C CNN
	1    4700 4800
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 4E37BB85
P 4950 4800
F 0 "C4" H 4900 4900 50  0000 L CNN
F 1 "0.1u" H 4900 4700 50  0000 L CNN
F 2 "" H 4950 4800 60  0001 C CNN
F 3 "" H 4950 4800 60  0001 C CNN
	1    4950 4800
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 4E37BB80
P 4450 4800
F 0 "C2" H 4400 4900 50  0000 L CNN
F 1 "0.1u" H 4400 4700 50  0000 L CNN
F 2 "" H 4450 4800 60  0001 C CNN
F 3 "" H 4450 4800 60  0001 C CNN
	1    4450 4800
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR09
U 1 1 4E37BB3B
P 4900 4550
F 0 "#PWR09" H 4900 4510 30  0001 C CNN
F 1 "+3.3V" H 4980 4580 30  0000 C CNN
F 2 "" H 4900 4550 60  0001 C CNN
F 3 "" H 4900 4550 60  0001 C CNN
	1    4900 4550
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR010
U 1 1 4E37BB36
P 4650 4250
F 0 "#PWR010" H 4650 4210 30  0001 C CNN
F 1 "+3.3V" H 4730 4280 30  0000 C CNN
F 2 "" H 4650 4250 60  0001 C CNN
F 3 "" H 4650 4250 60  0001 C CNN
	1    4650 4250
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR011
U 1 1 4E37BB32
P 4400 4150
F 0 "#PWR011" H 4400 4110 30  0001 C CNN
F 1 "+3.3V" H 4480 4180 30  0000 C CNN
F 2 "" H 4400 4150 60  0001 C CNN
F 3 "" H 4400 4150 60  0001 C CNN
	1    4400 4150
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR012
U 1 1 4E37BB2C
P 4150 4050
F 0 "#PWR012" H 4150 4010 30  0001 C CNN
F 1 "+3.3V" H 4230 4080 30  0000 C CNN
F 2 "" H 4150 4050 60  0001 C CNN
F 3 "" H 4150 4050 60  0001 C CNN
	1    4150 4050
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR013
U 1 1 4E37BB15
P 4950 5100
F 0 "#PWR013" H 5040 5080 30  0001 C CNN
F 1 "GND" H 4950 5020 30  0001 C CNN
F 2 "" H 4950 5100 60  0001 C CNN
F 3 "" H 4950 5100 60  0001 C CNN
	1    4950 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 4E37BB13
P 4700 5100
F 0 "#PWR014" H 4790 5080 30  0001 C CNN
F 1 "GND" H 4700 5020 30  0001 C CNN
F 2 "" H 4700 5100 60  0001 C CNN
F 3 "" H 4700 5100 60  0001 C CNN
	1    4700 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 4E37BB11
P 4450 5100
F 0 "#PWR015" H 4540 5080 30  0001 C CNN
F 1 "GND" H 4450 5020 30  0001 C CNN
F 2 "" H 4450 5100 60  0001 C CNN
F 3 "" H 4450 5100 60  0001 C CNN
	1    4450 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 4E37BB0E
P 4200 5100
F 0 "#PWR016" H 4290 5080 30  0001 C CNN
F 1 "GND" H 4200 5020 30  0001 C CNN
F 2 "" H 4200 5100 60  0001 C CNN
F 3 "" H 4200 5100 60  0001 C CNN
	1    4200 5100
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4E37BAEC
P 4200 4800
F 0 "C1" H 4150 4900 50  0000 L CNN
F 1 "0.1u" H 4150 4700 50  0000 L CNN
F 2 "" H 4200 4800 60  0001 C CNN
F 3 "" H 4200 4800 60  0001 C CNN
	1    4200 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 4E37BA12
P 6000 5100
F 0 "#PWR017" H 6000 5100 30  0001 C CNN
F 1 "GND" H 6000 5030 30  0001 C CNN
F 2 "" H 6000 5100 60  0001 C CNN
F 3 "" H 6000 5100 60  0001 C CNN
	1    6000 5100
	1    0    0    -1  
$EndComp
Text Label 11950 3300 0    60   ~ 0
Ant1
Text Notes 9000 3250 0    60   ~ 0
Debug\nUART
$Comp
L GND #PWR018
U 1 1 4DC3BA39
P 8650 3350
F 0 "#PWR018" H 8740 3330 30  0001 C CNN
F 1 "GND" H 8650 3270 30  0001 C CNN
F 2 "" H 8650 3350 60  0001 C CNN
F 3 "" H 8650 3350 60  0001 C CNN
	1    8650 3350
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 XL4
U 1 1 4DC3BA27
P 8850 3200
F 0 "XL4" V 8800 3200 40  0000 C CNN
F 1 "CONN_2" V 8900 3200 40  0000 C CNN
F 2 "" H 8850 3200 60  0001 C CNN
F 3 "" H 8850 3200 60  0001 C CNN
	1    8850 3200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR019
U 1 1 4BE7DE56
P 13550 3700
F 0 "#PWR019" H 13550 3660 30  0001 C CNN
F 1 "+3.3V" H 13630 3730 30  0000 C CNN
F 2 "" H 13550 3700 60  0001 C CNN
F 3 "" H 13550 3700 60  0001 C CNN
	1    13550 3700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 4BE7DE21
P 13500 5100
F 0 "#PWR020" H 13590 5080 30  0001 C CNN
F 1 "GND" H 13500 5020 30  0001 C CNN
F 2 "" H 13500 5100 60  0001 C CNN
F 3 "" H 13500 5100 60  0001 C CNN
	1    13500 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 4BE7DE1D
P 13250 5100
F 0 "#PWR021" H 13340 5080 30  0001 C CNN
F 1 "GND" H 13250 5020 30  0001 C CNN
F 2 "" H 13250 5100 60  0001 C CNN
F 3 "" H 13250 5100 60  0001 C CNN
	1    13250 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 4BE7DE18
P 12950 5100
F 0 "#PWR022" H 13040 5080 30  0001 C CNN
F 1 "GND" H 12950 5020 30  0001 C CNN
F 2 "" H 12950 5100 60  0001 C CNN
F 3 "" H 12950 5100 60  0001 C CNN
	1    12950 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 4BE7DE14
P 12700 5100
F 0 "#PWR023" H 12790 5080 30  0001 C CNN
F 1 "GND" H 12700 5020 30  0001 C CNN
F 2 "" H 12700 5100 60  0001 C CNN
F 3 "" H 12700 5100 60  0001 C CNN
	1    12700 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 4BE7DE10
P 12450 5100
F 0 "#PWR024" H 12540 5080 30  0001 C CNN
F 1 "GND" H 12450 5020 30  0001 C CNN
F 2 "" H 12450 5100 60  0001 C CNN
F 3 "" H 12450 5100 60  0001 C CNN
	1    12450 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 4BE7DE0C
P 12150 5100
F 0 "#PWR025" H 12240 5080 30  0001 C CNN
F 1 "GND" H 12150 5020 30  0001 C CNN
F 2 "" H 12150 5100 60  0001 C CNN
F 3 "" H 12150 5100 60  0001 C CNN
	1    12150 5100
	1    0    0    -1  
$EndComp
$Comp
L C C22
U 1 1 4BE7DDFD
P 13500 4800
F 0 "C22" H 13550 4900 50  0000 L CNN
F 1 "220pF" H 13550 4700 50  0000 L CNN
F 2 "" H 13500 4800 60  0001 C CNN
F 3 "" H 13500 4800 60  0001 C CNN
	1    13500 4800
	1    0    0    -1  
$EndComp
$Comp
L C C20
U 1 1 4BE7DDE3
P 13250 4500
F 0 "C20" H 13300 4600 50  0000 L CNN
F 1 "0.1u" H 13300 4400 50  0000 L CNN
F 2 "" H 13250 4500 60  0001 C CNN
F 3 "" H 13250 4500 60  0001 C CNN
	1    13250 4500
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 4BE7DDCA
P 12950 4800
F 0 "C18" H 13000 4900 50  0000 L CNN
F 1 "220pF" H 13000 4700 50  0000 L CNN
F 2 "" H 12950 4800 60  0001 C CNN
F 3 "" H 12950 4800 60  0001 C CNN
	1    12950 4800
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 4BE7DD9D
P 12700 4500
F 0 "C17" H 12750 4600 50  0000 L CNN
F 1 "0.1u" H 12750 4400 50  0000 L CNN
F 2 "" H 12700 4500 60  0001 C CNN
F 3 "" H 12700 4500 60  0001 C CNN
	1    12700 4500
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 4BE7DD83
P 12450 4800
F 0 "C14" H 12500 4900 50  0000 L CNN
F 1 "0.1u" H 12500 4700 50  0000 L CNN
F 2 "" H 12450 4800 60  0001 C CNN
F 3 "" H 12450 4800 60  0001 C CNN
	1    12450 4800
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 4BE7DD5E
P 12150 4500
F 0 "C13" H 12200 4600 50  0000 L CNN
F 1 "220pF" H 12200 4400 50  0000 L CNN
F 2 "" H 12150 4500 60  0001 C CNN
F 3 "" H 12150 4500 60  0001 C CNN
	1    12150 4500
	1    0    0    -1  
$EndComp
NoConn ~ 10450 3900
Entry Wire Line
	9850 3700 9950 3800
Entry Wire Line
	9850 3500 9950 3600
Entry Wire Line
	9850 3400 9950 3500
Entry Wire Line
	9850 3300 9950 3400
Entry Wire Line
	9850 3200 9950 3300
Text Label 10000 3400 0    60   ~ 0
CC_MOSI
Text Label 10000 3500 0    60   ~ 0
CC_MISO
Text Label 10000 3300 0    60   ~ 0
CC_SCK
Text Label 10000 3600 0    60   ~ 0
CC_CS
Text Label 10000 3800 0    60   ~ 0
CC_GDO0
$Comp
L GND #PWR026
U 1 1 4BE7DA14
P 11850 5100
F 0 "#PWR026" H 11940 5080 30  0001 C CNN
F 1 "GND" H 11850 5020 30  0001 C CNN
F 2 "" H 11850 5100 60  0001 C CNN
F 3 "" H 11850 5100 60  0001 C CNN
	1    11850 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 4BE7DA05
P 11150 5100
F 0 "#PWR027" H 11240 5080 30  0001 C CNN
F 1 "GND" H 11150 5020 30  0001 C CNN
F 2 "" H 11150 5100 60  0001 C CNN
F 3 "" H 11150 5100 60  0001 C CNN
	1    11150 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 4BE7DA00
P 10400 5100
F 0 "#PWR028" H 10490 5080 30  0001 C CNN
F 1 "GND" H 10400 5020 30  0001 C CNN
F 2 "" H 10400 5100 60  0001 C CNN
F 3 "" H 10400 5100 60  0001 C CNN
	1    10400 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 4BE7D9F9
P 10100 5100
F 0 "#PWR029" H 10190 5080 30  0001 C CNN
F 1 "GND" H 10100 5020 30  0001 C CNN
F 2 "" H 10100 5100 60  0001 C CNN
F 3 "" H 10100 5100 60  0001 C CNN
	1    10100 5100
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4BE7D9B0
P 10400 4800
F 0 "R5" V 10480 4800 50  0000 C CNN
F 1 "56k" V 10400 4800 50  0000 C CNN
F 2 "" H 10400 4800 60  0001 C CNN
F 3 "" H 10400 4800 60  0001 C CNN
	1    10400 4800
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 4BE7D9A3
P 10100 4750
F 0 "C12" H 10150 4850 50  0000 L CNN
F 1 "0.1u" H 10150 4650 50  0000 L CNN
F 2 "" H 10100 4750 60  0001 C CNN
F 3 "" H 10100 4750 60  0001 C CNN
	1    10100 4750
	1    0    0    -1  
$EndComp
$Comp
L CC2500 DD2
U 1 1 4BE7D8B1
P 11150 4000
F 0 "DD2" H 10750 4850 60  0000 C CNN
F 1 "CC2500" H 11450 4850 60  0000 C CNN
F 2 "" H 11150 4000 60  0001 C CNN
F 3 "" H 11150 4000 60  0001 C CNN
	1    11150 4000
	1    0    0    -1  
$EndComp
Entry Wire Line
	8400 2600 8500 2700
Entry Wire Line
	8400 2700 8500 2800
Entry Wire Line
	8400 2500 8500 2600
Entry Wire Line
	8400 2900 8500 3000
Entry Wire Line
	8400 2800 8500 2900
Text Label 7850 2600 0    60   ~ 0
CC_GDO0
Text Label 7850 2500 0    60   ~ 0
CC_CS
Text Label 7850 2700 0    60   ~ 0
CC_SCK
Text Label 7850 2800 0    60   ~ 0
CC_MISO
Text Label 7850 2900 0    60   ~ 0
CC_MOSI
$Comp
L BUTTON SW1
U 1 1 51E14794
P 1950 5800
F 0 "SW1" H 1750 5950 50  0000 C CNN
F 1 "BUTTON" H 2050 5950 50  0000 C CNN
F 2 "~" H 1950 5800 60  0000 C CNN
F 3 "~" H 1950 5800 60  0000 C CNN
	1    1950 5800
	1    0    0    -1  
$EndComp
$Comp
L BUTTON SW2
U 1 1 51E147A3
P 1950 6400
F 0 "SW2" H 1750 6550 50  0000 C CNN
F 1 "BUTTON" H 2050 6550 50  0000 C CNN
F 2 "~" H 1950 6400 60  0000 C CNN
F 3 "~" H 1950 6400 60  0000 C CNN
	1    1950 6400
	1    0    0    -1  
$EndComp
$Comp
L BUTTON SW3
U 1 1 51E147B2
P 1950 7000
F 0 "SW3" H 1750 7150 50  0000 C CNN
F 1 "BUTTON" H 2050 7150 50  0000 C CNN
F 2 "~" H 1950 7000 60  0000 C CNN
F 3 "~" H 1950 7000 60  0000 C CNN
	1    1950 7000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 51E147C1
P 1500 8500
F 0 "#PWR030" H 1590 8480 30  0001 C CNN
F 1 "GND" H 1500 8420 30  0001 C CNN
F 2 "" H 1500 8500 60  0000 C CNN
F 3 "" H 1500 8500 60  0000 C CNN
	1    1500 8500
	1    0    0    -1  
$EndComp
Text Label 1950 7300 0    60   ~ 0
WKUP
Text Label 2500 5600 0    60   ~ 0
BTN_UP
Text Label 2500 6200 0    60   ~ 0
BTN_DOWN
Text Label 2500 6800 0    60   ~ 0
BTN_TX
$Comp
L LED_RGB Q1
U 1 1 51E14C2F
P 13950 7150
F 0 "Q1" H 13750 7500 60  0000 C CNN
F 1 "LED_RGB" H 14100 7500 60  0000 C CNN
F 2 "~" H 13950 7150 60  0000 C CNN
F 3 "~" H 13950 7150 60  0000 C CNN
	1    13950 7150
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 XL6
U 1 1 51E14C4D
P 13150 7150
F 0 "XL6" V 13100 7150 40  0000 C CNN
F 1 "CONN_3" V 13200 7150 40  0000 C CNN
F 2 "" H 13150 7150 60  0000 C CNN
F 3 "" H 13150 7150 60  0000 C CNN
	1    13150 7150
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 XL7
U 1 1 51E14C5C
P 14750 7150
F 0 "XL7" V 14700 7150 40  0000 C CNN
F 1 "CONN_3" V 14800 7150 40  0000 C CNN
F 2 "" H 14750 7150 60  0000 C CNN
F 3 "" H 14750 7150 60  0000 C CNN
	1    14750 7150
	-1   0    0    -1  
$EndComp
$Comp
L CONN_3 XL5
U 1 1 51E14C6B
P 12850 7150
F 0 "XL5" V 12800 7150 40  0000 C CNN
F 1 "CONN_3" V 12900 7150 40  0000 C CNN
F 2 "" H 12850 7150 60  0000 C CNN
F 3 "" H 12850 7150 60  0000 C CNN
	1    12850 7150
	-1   0    0    -1  
$EndComp
$Comp
L CONN_3 XL8
U 1 1 51E14C7A
P 15050 7150
F 0 "XL8" V 15000 7150 40  0000 C CNN
F 1 "CONN_3" V 15100 7150 40  0000 C CNN
F 2 "" H 15050 7150 60  0000 C CNN
F 3 "" H 15050 7150 60  0000 C CNN
	1    15050 7150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR031
U 1 1 51E14C89
P 15300 7400
F 0 "#PWR031" H 15390 7380 30  0001 C CNN
F 1 "GND" H 15300 7320 30  0001 C CNN
F 2 "" H 15300 7400 60  0000 C CNN
F 3 "" H 15300 7400 60  0000 C CNN
	1    15300 7400
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 51E15201
P 12100 7150
F 0 "R7" V 12180 7000 50  0000 C CNN
F 1 "51R" V 12100 7150 50  0000 C CNN
F 2 "RES_0603" V 12180 7250 28  0000 C CNN
F 3 "~" H 12100 7150 60  0000 C CNN
	1    12100 7150
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 51E15210
P 12100 7350
F 0 "R8" V 12180 7200 50  0000 C CNN
F 1 "51R" V 12100 7350 50  0000 C CNN
F 2 "RES_0603" V 12180 7450 28  0000 C CNN
F 3 "~" H 12100 7350 60  0000 C CNN
	1    12100 7350
	0    -1   -1   0   
$EndComp
$Comp
L R R6
U 1 1 51E1521F
P 12100 6950
F 0 "R6" V 12180 6800 50  0000 C CNN
F 1 "51R" V 12100 6950 50  0000 C CNN
F 2 "RES_0603" V 12180 7050 28  0000 C CNN
F 3 "~" H 12100 6950 60  0000 C CNN
	1    12100 6950
	0    -1   -1   0   
$EndComp
Text Label 11500 6950 0    60   ~ 0
LED_R
Text Label 11500 7150 0    60   ~ 0
LED_G
Text Label 11500 7350 0    60   ~ 0
LED_B
Text Notes 13600 6550 0    60   ~ 0
Additional PCB
Text Label 4700 2800 0    60   ~ 0
BTN_UP
Text Label 4700 2900 0    60   ~ 0
BTN_DOWN
Text Label 7850 2300 0    60   ~ 0
BTN_TX
$Comp
L STM32F100C4 DD1
U 1 1 51E1945E
P 6500 3400
F 0 "DD1" H 5750 4750 60  0000 C CNN
F 1 "STM32F100C4" H 6400 4750 60  0000 C CNN
F 2 "~" H 6500 3400 60  0000 C CNN
F 3 "~" H 6500 3400 60  0000 C CNN
	1    6500 3400
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL_H XTAL1
U 1 1 51E1A3DF
P 9600 4550
F 0 "XTAL1" H 9550 4850 60  0000 C CNN
F 1 "27MHz" H 9600 4750 60  0000 C CNN
F 2 "03225" H 9625 4675 39  0000 C CNN
F 3 "" H 9600 4550 60  0001 C CNN
	1    9600 4550
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 51E1A3E5
P 9850 4800
F 0 "C11" H 9750 4700 50  0000 L CNN
F 1 "10pF" H 9750 4900 50  0000 L CNN
F 2 "CAP_0402" V 9950 4650 28  0000 C BNN
F 3 "" H 9850 4800 60  0001 C CNN
	1    9850 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 51E1A3EB
P 9850 5100
F 0 "#PWR032" H 9940 5080 30  0001 C CNN
F 1 "GND" H 9850 5020 30  0001 C CNN
F 2 "" H 9850 5100 60  0001 C CNN
F 3 "" H 9850 5100 60  0001 C CNN
	1    9850 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR033
U 1 1 51E1A3F1
P 9350 5100
F 0 "#PWR033" H 9440 5080 30  0001 C CNN
F 1 "GND" H 9350 5020 30  0001 C CNN
F 2 "" H 9350 5100 60  0001 C CNN
F 3 "" H 9350 5100 60  0001 C CNN
	1    9350 5100
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 51E1A3F7
P 9350 4800
F 0 "C10" H 9250 4700 50  0000 L CNN
F 1 "10pF" H 9250 4900 50  0000 L CNN
F 2 "CAP_0402" V 9450 4650 28  0000 C BNN
F 3 "" H 9350 4800 60  0001 C CNN
	1    9350 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 51E1A3FD
P 9600 5100
F 0 "#PWR034" H 9690 5080 30  0001 C CNN
F 1 "GND" H 9600 5020 30  0001 C CNN
F 2 "" H 9600 5100 60  0001 C CNN
F 3 "" H 9600 5100 60  0001 C CNN
	1    9600 5100
	1    0    0    -1  
$EndComp
Text Label 4850 2200 0    60   ~ 0
LED_R
Text Label 4850 2300 0    60   ~ 0
LED_G
Text Label 4850 2600 0    60   ~ 0
LED_B
NoConn ~ 5250 3500
NoConn ~ 5250 3600
NoConn ~ 5250 3700
$Comp
L TESTPOINT TP1
U 1 1 51E1A697
P 5100 3900
F 0 "TP1" V 5100 4100 60  0000 C CNN
F 1 "TESTPOINT" H 5075 4125 60  0001 C CNN
F 2 "" H 5100 3900 60  0001 C CNN
F 3 "" H 5100 3900 60  0001 C CNN
	1    5100 3900
	0    -1   -1   0   
$EndComp
$Comp
L C C15
U 1 1 51E1A8E8
P 12700 2550
F 0 "C15" V 12950 2700 50  0000 L CNN
F 1 "100pF" V 12850 2550 50  0000 L CNN
F 2 "CAP_0402" V 12800 2400 28  0000 C BNN
F 3 "~" H 12700 2550 60  0000 C CNN
	1    12700 2550
	0    -1   -1   0   
$EndComp
$Comp
L C C16
U 1 1 51E1A936
P 12700 2950
F 0 "C16" V 12950 3100 50  0000 L CNN
F 1 "100pF" V 12850 2950 50  0000 L CNN
F 2 "CAP_0402" V 12800 2800 28  0000 C BNN
F 3 "~" H 12700 2950 60  0000 C CNN
	1    12700 2950
	0    -1   -1   0   
$EndComp
$Comp
L C C19
U 1 1 51E1A93E
P 13000 3250
F 0 "C19" H 12900 3150 50  0000 L CNN
F 1 "1pF" H 12900 3350 50  0000 L CNN
F 2 "CAP_0402" V 13100 3100 28  0000 C BNN
F 3 "~" H 13000 3250 60  0000 C CNN
	1    13000 3250
	1    0    0    -1  
$EndComp
$Comp
L L L2
U 1 1 51E1A94D
P 13000 2200
F 0 "L2" V 12900 2060 40  0000 C CNN
F 1 "1.2nH" V 12900 2200 40  0000 C CNN
F 2 "IND_0402" V 13060 2210 40  0000 C CNN
F 3 "~" H 13000 2200 60  0000 C CNN
	1    13000 2200
	1    0    0    -1  
$EndComp
$Comp
L C C21
U 1 1 51E1A95A
P 13300 2550
F 0 "C21" V 13550 2500 50  0000 L CNN
F 1 "1pF" V 13450 2450 50  0000 L CNN
F 2 "CAP_0402" V 13400 2400 28  0000 C BNN
F 3 "~" H 13300 2550 60  0000 C CNN
	1    13300 2550
	0    -1   -1   0   
$EndComp
$Comp
L L L3
U 1 1 51E1A976
P 13300 2950
F 0 "L3" V 13200 2810 40  0000 C CNN
F 1 "1.2nH" V 13200 2950 40  0000 C CNN
F 2 "IND_0402" V 13360 2960 40  0000 C CNN
F 3 "~" H 13300 2950 60  0000 C CNN
	1    13300 2950
	0    1    1    0   
$EndComp
$Comp
L GND #PWR035
U 1 1 51E1A999
P 13000 1900
F 0 "#PWR035" H 13090 1880 30  0001 C CNN
F 1 "GND" H 13000 1820 30  0001 C CNN
F 2 "" H 13000 1900 60  0000 C CNN
F 3 "" H 13000 1900 60  0000 C CNN
	1    13000 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR036
U 1 1 51E1A9A8
P 13000 3550
F 0 "#PWR036" H 13090 3530 30  0001 C CNN
F 1 "GND" H 13000 3470 30  0001 C CNN
F 2 "" H 13000 3550 60  0000 C CNN
F 3 "" H 13000 3550 60  0000 C CNN
	1    13000 3550
	1    0    0    -1  
$EndComp
$Comp
L C C23
U 1 1 51E1B0C3
P 13800 3050
F 0 "C23" H 13700 2950 50  0000 L CNN
F 1 "1.8pF" H 13700 3150 50  0000 L CNN
F 2 "CAP_0402" V 13900 2900 28  0000 C BNN
F 3 "~" H 13800 3050 60  0000 C CNN
	1    13800 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 51E1B0C9
P 13800 3350
F 0 "#PWR037" H 13890 3330 30  0001 C CNN
F 1 "GND" H 13800 3270 30  0001 C CNN
F 2 "" H 13800 3350 60  0000 C CNN
F 3 "" H 13800 3350 60  0000 C CNN
	1    13800 3350
	1    0    0    -1  
$EndComp
$Comp
L L L4
U 1 1 51E1B0D0
P 14100 2750
F 0 "L4" V 14000 2610 40  0000 C CNN
F 1 "1.2nH" V 14000 2750 40  0000 C CNN
F 2 "IND_0402" V 14160 2760 40  0000 C CNN
F 3 "~" H 14100 2750 60  0000 C CNN
	1    14100 2750
	0    1    1    0   
$EndComp
$Comp
L C C24
U 1 1 51E1B0D6
P 14400 3050
F 0 "C24" H 14300 2950 50  0000 L CNN
F 1 "1.5pF" H 14300 3150 50  0000 L CNN
F 2 "CAP_0402" V 14500 2900 28  0000 C BNN
F 3 "~" H 14400 3050 60  0000 C CNN
	1    14400 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR038
U 1 1 51E1B0DC
P 14400 3350
F 0 "#PWR038" H 14490 3330 30  0001 C CNN
F 1 "GND" H 14400 3270 30  0001 C CNN
F 2 "" H 14400 3350 60  0000 C CNN
F 3 "" H 14400 3350 60  0000 C CNN
	1    14400 3350
	1    0    0    -1  
$EndComp
$Comp
L ANT_GENERAL ANT1
U 1 1 51E1B112
P 15150 2800
F 0 "ANT1" H 14850 3050 60  0000 C CNN
F 1 "ANT_GENERAL" H 15050 2950 60  0000 C CNN
F 2 "" H 15150 2800 60  0000 C CNN
F 3 "" H 15150 2800 60  0000 C CNN
	1    15150 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 51E1B11F
P 14700 2950
F 0 "#PWR039" H 14790 2930 30  0001 C CNN
F 1 "GND" H 14700 2870 30  0001 C CNN
F 2 "" H 14700 2950 60  0000 C CNN
F 3 "" H 14700 2950 60  0000 C CNN
	1    14700 2950
	1    0    0    -1  
$EndComp
NoConn ~ 5250 3400
$Comp
L CONN_1 XL2
U 1 1 54EA2249
P 5150 8250
F 0 "XL2" V 5100 8260 40  0000 C CNN
F 1 "CONN_1" V 5160 8270 40  0000 C CNN
F 2 "~" H 5150 8250 60  0000 C CNN
F 3 "~" H 5150 8250 60  0000 C CNN
	1    5150 8250
	-1   0    0    1   
$EndComp
$Comp
L CONN_1 XL3
U 1 1 54EA24A3
P 5150 8800
F 0 "XL3" V 5100 8810 40  0000 C CNN
F 1 "CONN_1" V 5160 8820 40  0000 C CNN
F 2 "~" H 5150 8800 60  0000 C CNN
F 3 "~" H 5150 8800 60  0000 C CNN
	1    5150 8800
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR040
U 1 1 54EA24B2
P 5700 8950
F 0 "#PWR040" H 5790 8930 30  0001 C CNN
F 1 "GND" H 5700 8870 30  0001 C CNN
F 2 "~" H 5700 8950 60  0000 C CNN
F 3 "~" H 5700 8950 60  0000 C CNN
	1    5700 8950
	1    0    0    -1  
$EndComp
$Comp
L NCP1400 DA1
U 1 1 54EA259E
P 7900 8700
F 0 "DA1" H 7700 8950 60  0000 C CNN
F 1 "NCP1400" H 8100 8950 60  0000 C CNN
F 2 "~" H 7900 8700 60  0000 C CNN
F 3 "~" H 7900 8700 60  0000 C CNN
	1    7900 8700
	1    0    0    -1  
$EndComp
$Comp
L L L1
U 1 1 54EA25AD
P 7050 8250
F 0 "L1" V 6950 8110 40  0000 C CNN
F 1 "22uH" V 6950 8250 40  0000 C CNN
F 2 "~" V 7110 8260 40  0000 C CNN
F 3 "~" H 7050 8250 60  0000 C CNN
	1    7050 8250
	0    1    1    0   
$EndComp
$Comp
L C C7
U 1 1 54EA269A
P 6550 8550
F 0 "C7" H 6450 8450 50  0000 L CNN
F 1 "10u" H 6600 8650 50  0000 L CNN
F 2 "CAP_0603" V 6650 8400 28  0000 C BNN
F 3 "~" H 6550 8550 60  0000 C CNN
	1    6550 8550
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 54EA26A9
P 6150 8550
F 0 "C6" H 6050 8450 50  0000 L CNN
F 1 "0.1u" H 5950 8650 50  0000 L CNN
F 2 "CAP_0603" V 6250 8400 28  0000 C BNN
F 3 "~" H 6150 8550 60  0000 C CNN
	1    6150 8550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR041
U 1 1 54EA2927
P 6150 8950
F 0 "#PWR041" H 6240 8930 30  0001 C CNN
F 1 "GND" H 6150 8870 30  0001 C CNN
F 2 "~" H 6150 8950 60  0000 C CNN
F 3 "~" H 6150 8950 60  0000 C CNN
	1    6150 8950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR042
U 1 1 54EA2936
P 6550 8950
F 0 "#PWR042" H 6640 8930 30  0001 C CNN
F 1 "GND" H 6550 8870 30  0001 C CNN
F 2 "~" H 6550 8950 60  0000 C CNN
F 3 "~" H 6550 8950 60  0000 C CNN
	1    6550 8950
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG043
U 1 1 54EA2AEC
P 5500 8150
F 0 "#FLG043" H 5500 8420 30  0001 C CNN
F 1 "PWR_FLAG" H 5500 8380 30  0000 C CNN
F 2 "~" H 5500 8150 60  0000 C CNN
F 3 "~" H 5500 8150 60  0000 C CNN
	1    5500 8150
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG044
U 1 1 54EA2AFB
P 5500 8700
F 0 "#FLG044" H 5500 8970 30  0001 C CNN
F 1 "PWR_FLAG" H 5500 8930 30  0000 C CNN
F 2 "~" H 5500 8700 60  0000 C CNN
F 3 "~" H 5500 8700 60  0000 C CNN
	1    5500 8700
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 54EA2DFE
P 8800 8550
F 0 "C8" H 8700 8450 50  0000 L CNN
F 1 "0.1u" H 8600 8650 50  0000 L CNN
F 2 "CAP_0603" V 8900 8400 28  0000 C BNN
F 3 "~" H 8800 8550 60  0000 C CNN
	1    8800 8550
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 54EA2E0D
P 9200 8550
F 0 "C9" H 9100 8450 50  0000 L CNN
F 1 "10u" H 9250 8650 50  0000 L CNN
F 2 "CAP_0603" V 9300 8400 28  0000 C BNN
F 3 "~" H 9200 8550 60  0000 C CNN
	1    9200 8550
	1    0    0    -1  
$EndComp
$Comp
L D_SHOTTKY D1
U 1 1 54EA2E1C
P 7900 8250
F 0 "D1" H 7750 8350 40  0000 C CNN
F 1 "BAT54WS" H 8000 8350 40  0000 C CNN
F 2 "~" H 7900 8250 60  0000 C CNN
F 3 "~" H 7900 8250 60  0000 C CNN
	1    7900 8250
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR045
U 1 1 54EA2FE6
P 9600 8250
F 0 "#PWR045" H 9600 8210 30  0001 C CNN
F 1 "+3.3V" H 9680 8280 30  0000 C CNN
F 2 "~" H 9600 8250 60  0000 C CNN
F 3 "~" H 9600 8250 60  0000 C CNN
	1    9600 8250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR046
U 1 1 54EA3449
P 8800 8950
F 0 "#PWR046" H 8890 8930 30  0001 C CNN
F 1 "GND" H 8800 8870 30  0001 C CNN
F 2 "~" H 8800 8950 60  0000 C CNN
F 3 "~" H 8800 8950 60  0000 C CNN
	1    8800 8950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR047
U 1 1 54EA3458
P 9200 8950
F 0 "#PWR047" H 9290 8930 30  0001 C CNN
F 1 "GND" H 9200 8870 30  0001 C CNN
F 2 "~" H 9200 8950 60  0000 C CNN
F 3 "~" H 9200 8950 60  0000 C CNN
	1    9200 8950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 54EA3716
P 7350 8950
F 0 "#PWR048" H 7440 8930 30  0001 C CNN
F 1 "GND" H 7350 8870 30  0001 C CNN
F 2 "~" H 7350 8950 60  0000 C CNN
F 3 "~" H 7350 8950 60  0000 C CNN
	1    7350 8950
	1    0    0    -1  
$EndComp
Text Label 7850 2200 0    60   ~ 0
WKUP
$Comp
L R R1
U 1 1 54EA39C9
P 1500 7900
F 0 "R1" V 1580 7750 50  0000 C CNN
F 1 "30k" V 1500 7900 50  0000 C CNN
F 2 "RES_0603" V 1580 8000 28  0000 C CNN
F 3 "~" H 1500 7900 60  0000 C CNN
	1    1500 7900
	1    0    0    -1  
$EndComp
Wire Bus Line
	9550 2500 9550 2950
Connection ~ 5200 4550
Wire Wire Line
	5200 4600 5200 4550
Wire Wire Line
	5200 5000 5200 5100
Wire Wire Line
	4650 4250 5250 4250
Wire Wire Line
	4150 4050 5250 4050
Connection ~ 12150 4200
Wire Wire Line
	11800 4200 12200 4200
Connection ~ 12700 4000
Wire Wire Line
	11800 4000 12750 4000
Connection ~ 13250 3800
Wire Wire Line
	11800 3800 13300 3800
Wire Wire Line
	12150 4200 12150 4300
Wire Wire Line
	12700 4000 12700 4300
Wire Wire Line
	13250 3800 13250 4300
Wire Wire Line
	7750 2200 7850 2200
Wire Bus Line
	8500 2500 8500 3050
Wire Wire Line
	7850 3500 7750 3500
Wire Wire Line
	7750 3600 7850 3600
Wire Wire Line
	2300 2500 2400 2500
Wire Wire Line
	2300 2700 2450 2700
Wire Wire Line
	2300 2800 2450 2800
Wire Wire Line
	2450 2800 2450 2850
Wire Wire Line
	2400 2600 2300 2600
Wire Wire Line
	11800 3500 12500 3500
Connection ~ 6200 4950
Wire Wire Line
	6200 4850 6200 4950
Connection ~ 6000 4950
Wire Wire Line
	6450 4950 6450 4850
Wire Wire Line
	6000 4950 6450 4950
Wire Wire Line
	4950 5000 4950 5100
Wire Wire Line
	4450 5000 4450 5100
Connection ~ 4450 4150
Wire Wire Line
	4200 4050 4200 4600
Wire Wire Line
	4700 4250 4700 4600
Wire Wire Line
	4950 4400 4950 4600
Wire Wire Line
	8650 3300 8650 3350
Wire Wire Line
	13250 4700 13250 5100
Wire Wire Line
	12700 4700 12700 5100
Wire Wire Line
	12150 4700 12150 5100
Wire Wire Line
	10450 4400 10100 4400
Wire Wire Line
	10100 4400 10100 4550
Wire Wire Line
	10400 5050 10400 5100
Connection ~ 11850 4500
Wire Wire Line
	11800 4500 11850 4500
Wire Wire Line
	8400 2800 7750 2800
Wire Wire Line
	8400 2500 7750 2500
Wire Wire Line
	7750 2700 8400 2700
Wire Wire Line
	8400 2600 7750 2600
Wire Wire Line
	7750 2900 8400 2900
Wire Wire Line
	11800 4400 11850 4400
Wire Wire Line
	11850 4400 11850 5100
Wire Wire Line
	11150 4950 11150 5100
Wire Wire Line
	10100 4950 10100 5100
Wire Wire Line
	10400 4550 10400 4500
Wire Wire Line
	10400 4500 10450 4500
Wire Wire Line
	10450 3300 9950 3300
Wire Wire Line
	9950 3400 10450 3400
Wire Wire Line
	10450 3500 9950 3500
Wire Wire Line
	9950 3600 10450 3600
Wire Wire Line
	10450 3800 9950 3800
Wire Wire Line
	12450 5000 12450 5100
Wire Wire Line
	12950 5000 12950 5100
Wire Wire Line
	13500 5100 13500 5000
Connection ~ 4950 4550
Wire Wire Line
	4450 4150 4450 4600
Connection ~ 4200 4050
Connection ~ 4700 4250
Wire Wire Line
	4200 5000 4200 5100
Wire Wire Line
	4700 5000 4700 5100
Wire Wire Line
	6000 4850 6000 5100
Wire Wire Line
	6300 4850 6300 4950
Connection ~ 6300 4950
Wire Wire Line
	6100 4850 6100 4950
Connection ~ 6100 4950
Wire Bus Line
	8500 2500 9850 2500
Wire Bus Line
	9850 2500 9850 3800
Wire Wire Line
	11800 3300 12300 3300
Wire Wire Line
	8650 3100 7750 3100
Wire Wire Line
	7850 2300 7750 2300
Wire Wire Line
	13500 3700 13500 4600
Wire Wire Line
	12950 3900 12950 4600
Wire Wire Line
	12450 4100 12450 4600
Wire Wire Line
	11800 3700 13550 3700
Connection ~ 13500 3700
Wire Wire Line
	11800 3900 13000 3900
Connection ~ 12950 3900
Wire Wire Line
	11800 4100 12500 4100
Connection ~ 12450 4100
Wire Wire Line
	4400 4150 5250 4150
Wire Wire Line
	4900 4550 5250 4550
Wire Wire Line
	4950 4400 5250 4400
Wire Wire Line
	9450 2800 9050 2800
Wire Wire Line
	1650 5800 1500 5800
Wire Wire Line
	1500 6400 1650 6400
Connection ~ 1500 6400
Wire Wire Line
	1650 7000 1500 7000
Connection ~ 1500 7000
Wire Wire Line
	1500 7300 1950 7300
Wire Wire Line
	2250 5800 2650 5800
Wire Wire Line
	2250 6400 2650 6400
Wire Wire Line
	2250 7000 2650 7000
Wire Wire Line
	15300 7050 15300 7400
Wire Wire Line
	15300 7250 15250 7250
Wire Wire Line
	15250 7150 15300 7150
Connection ~ 15300 7250
Wire Wire Line
	15250 7050 15300 7050
Connection ~ 15300 7150
Wire Wire Line
	14350 7150 14550 7150
Wire Wire Line
	14550 7050 14450 7050
Wire Wire Line
	14450 7050 14450 7000
Wire Wire Line
	14450 7000 14350 7000
Wire Wire Line
	14350 7300 14450 7300
Wire Wire Line
	14450 7300 14450 7250
Wire Wire Line
	14450 7250 14550 7250
Wire Wire Line
	13350 7150 13550 7150
Wire Wire Line
	13550 7000 13450 7000
Wire Wire Line
	13450 7000 13450 7050
Wire Wire Line
	13450 7050 13350 7050
Wire Wire Line
	13350 7250 13450 7250
Wire Wire Line
	13450 7250 13450 7300
Wire Wire Line
	13450 7300 13550 7300
Wire Wire Line
	12350 7150 12650 7150
Wire Wire Line
	12650 7050 12500 7050
Wire Wire Line
	12500 7050 12500 6950
Wire Wire Line
	12500 6950 12350 6950
Wire Wire Line
	12350 7350 12500 7350
Wire Wire Line
	12500 7350 12500 7250
Wire Wire Line
	12500 7250 12650 7250
Wire Wire Line
	11500 7350 11850 7350
Wire Wire Line
	11850 7150 11500 7150
Wire Wire Line
	11500 6950 11850 6950
Wire Notes Line
	13000 6600 14900 6600
Wire Notes Line
	14900 7600 13000 7600
Wire Notes Line
	13000 7600 13000 6600
Wire Notes Line
	14900 6600 14900 7600
Wire Wire Line
	4700 2900 5250 2900
Wire Wire Line
	5250 2800 4700 2800
Wire Wire Line
	9850 4200 9850 4600
Wire Wire Line
	9850 4200 10450 4200
Wire Wire Line
	10450 4100 9350 4100
Wire Wire Line
	9350 4100 9350 4600
Wire Wire Line
	9850 5000 9850 5100
Connection ~ 9850 4550
Wire Wire Line
	9450 4550 9350 4550
Connection ~ 9350 4550
Wire Wire Line
	9350 5000 9350 5100
Wire Wire Line
	9600 4700 9600 5100
Wire Wire Line
	9750 4550 9850 4550
Wire Wire Line
	5250 3900 5100 3900
Wire Wire Line
	13000 3550 13000 3450
Wire Wire Line
	13000 3050 13000 2950
Wire Wire Line
	12900 2950 13100 2950
Connection ~ 13000 2950
Wire Wire Line
	12900 2550 13100 2550
Wire Wire Line
	13000 2400 13000 2550
Connection ~ 13000 2550
Wire Wire Line
	13000 2000 13000 1900
Wire Wire Line
	12500 3500 12500 2950
Wire Wire Line
	12300 3300 12300 2550
Wire Wire Line
	12300 2550 12500 2550
Wire Wire Line
	13800 3350 13800 3250
Wire Wire Line
	14400 3350 14400 3250
Wire Wire Line
	14700 2950 14700 2850
Wire Wire Line
	14300 2750 14700 2750
Wire Wire Line
	14400 2850 14400 2750
Connection ~ 14400 2750
Wire Wire Line
	13500 2550 13500 2950
Wire Wire Line
	13500 2750 13900 2750
Connection ~ 13500 2750
Wire Wire Line
	13800 2850 13800 2750
Connection ~ 13800 2750
Wire Wire Line
	5350 8250 6850 8250
Wire Wire Line
	5350 8800 5700 8800
Wire Wire Line
	7250 8250 7700 8250
Wire Wire Line
	6150 8350 6150 8250
Connection ~ 6150 8250
Wire Wire Line
	6550 8350 6550 8250
Connection ~ 6550 8250
Wire Wire Line
	6150 8750 6150 8950
Wire Wire Line
	6550 8750 6550 8950
Wire Wire Line
	5500 8150 5500 8250
Connection ~ 5500 8250
Wire Wire Line
	5500 8700 5500 8800
Connection ~ 5500 8800
Wire Wire Line
	5700 8800 5700 8950
Wire Wire Line
	7450 8600 7450 8250
Connection ~ 7450 8250
Wire Wire Line
	8100 8250 9600 8250
Wire Wire Line
	8800 8350 8800 8250
Connection ~ 8800 8250
Wire Wire Line
	9200 8350 9200 8250
Connection ~ 9200 8250
Wire Wire Line
	8300 8600 8350 8600
Wire Wire Line
	8350 8250 8350 8700
Connection ~ 8350 8250
Wire Wire Line
	8350 8700 8300 8700
Connection ~ 8350 8600
Wire Wire Line
	8800 8750 8800 8950
Wire Wire Line
	9200 8750 9200 8950
Wire Wire Line
	7450 8800 7350 8800
Wire Wire Line
	7350 8800 7350 8950
Wire Wire Line
	1500 8150 1500 8500
Connection ~ 1500 7300
Text Label 5750 8250 0    60   ~ 0
BATT
Text Label 7400 8250 0    60   ~ 0
Lout
$Comp
L R R2
U 1 1 54EA4103
P 2900 5800
F 0 "R2" V 2980 5650 50  0000 C CNN
F 1 "4k7" V 2900 5800 50  0000 C CNN
F 2 "RES_0603" V 2980 5900 28  0000 C CNN
F 3 "~" H 2900 5800 60  0000 C CNN
	1    2900 5800
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR049
U 1 1 54EA4112
P 3400 5800
F 0 "#PWR049" H 3400 5760 30  0001 C CNN
F 1 "+3.3V" H 3480 5830 30  0000 C CNN
F 2 "~" H 3400 5800 60  0000 C CNN
F 3 "~" H 3400 5800 60  0000 C CNN
	1    3400 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5800 2400 5600
Connection ~ 2400 5800
$Comp
L +3.3V #PWR050
U 1 1 54EA4481
P 3400 6400
F 0 "#PWR050" H 3400 6360 30  0001 C CNN
F 1 "+3.3V" H 3480 6430 30  0000 C CNN
F 2 "~" H 3400 6400 60  0000 C CNN
F 3 "~" H 3400 6400 60  0000 C CNN
	1    3400 6400
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 54EA4490
P 2900 6400
F 0 "R3" V 2980 6250 50  0000 C CNN
F 1 "4k7" V 2900 6400 50  0000 C CNN
F 2 "RES_0603" V 2980 6500 28  0000 C CNN
F 3 "~" H 2900 6400 60  0000 C CNN
	1    2900 6400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3150 6400 3400 6400
Wire Wire Line
	2500 6200 2400 6200
Wire Wire Line
	2400 6200 2400 6400
Connection ~ 2400 6400
Wire Wire Line
	3150 5800 3400 5800
$Comp
L R R4
U 1 1 54EA4822
P 2900 7000
F 0 "R4" V 2980 6850 50  0000 C CNN
F 1 "4k7" V 2900 7000 50  0000 C CNN
F 2 "RES_0603" V 2980 7100 28  0000 C CNN
F 3 "~" H 2900 7000 60  0000 C CNN
	1    2900 7000
	0    -1   -1   0   
$EndComp
$Comp
L +3.3V #PWR051
U 1 1 54EA4831
P 3400 7000
F 0 "#PWR051" H 3400 6960 30  0001 C CNN
F 1 "+3.3V" H 3480 7030 30  0000 C CNN
F 2 "~" H 3400 7000 60  0000 C CNN
F 3 "~" H 3400 7000 60  0000 C CNN
	1    3400 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 7000 3400 7000
Wire Wire Line
	2400 7000 2400 6800
Wire Wire Line
	2400 6800 2500 6800
Connection ~ 2400 7000
Wire Wire Line
	2400 5600 2500 5600
Wire Wire Line
	1500 5800 1500 7650
Text Notes 4550 8300 0    60   ~ 0
+BATTERY
Text Notes 4550 8800 0    60   ~ 0
-BATTERY
NoConn ~ 7750 3000
NoConn ~ 7750 3200
NoConn ~ 7750 3300
Wire Wire Line
	4850 2200 5250 2200
Wire Wire Line
	5250 2300 4850 2300
Wire Wire Line
	4850 2600 5250 2600
$EndSCHEMATC
