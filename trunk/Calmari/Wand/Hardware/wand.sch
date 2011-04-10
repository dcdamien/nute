EESchema Schematic File Version 2  date 26/12/2009 23:42:41
LIBS:power,D:/SVN/Token/TokenSmartCard/Hardware/trunk/KiCadLibs/Tittar_kl,D:/SVN/Token/TokenSmartCard/Hardware/trunk/KiCadLibs/Power_kl,D:/SVN/Token/TokenSmartCard/Hardware/trunk/KiCadLibs/pcb_details,D:/SVN/Token/TokenSmartCard/Hardware/trunk/KiCadLibs/Connectors_kl,D:/SVN/Token/TokenSmartCard/Hardware/trunk/KiCadLibs/Atmel_kl,.\wand.cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title ""
Date "1 dec 2009"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 4950 2250
NoConn ~ 3250 1950
Connection ~ 1600 5450
Wire Wire Line
	1600 5450 1700 5450
Connection ~ 9500 4550
Wire Wire Line
	7950 4550 9550 4550
Connection ~ 9500 3950
Wire Wire Line
	9500 4000 9500 3950
Connection ~ 3000 5050
Wire Wire Line
	3400 4950 3400 5050
Wire Wire Line
	3400 5050 3000 5050
Wire Wire Line
	3000 4950 3000 5100
Wire Wire Line
	1600 5350 1600 5550
Connection ~ 7200 4550
Wire Wire Line
	7050 4550 7350 4550
Connection ~ 6900 4350
Wire Wire Line
	6900 4650 6900 4350
Connection ~ 10150 4550
Wire Wire Line
	10150 4150 10150 4650
Wire Wire Line
	9150 3950 9150 4000
Wire Wire Line
	8550 4450 8550 4500
Wire Wire Line
	8550 3950 8550 4050
Wire Wire Line
	7950 3950 7950 4350
Wire Wire Line
	7650 4750 7650 4800
Wire Wire Line
	7200 4550 7200 4600
Wire Wire Line
	1950 3950 2100 3950
Wire Wire Line
	4950 1950 5050 1950
Wire Wire Line
	4950 2150 5050 2150
Wire Wire Line
	3250 2250 3250 2400
Wire Wire Line
	5050 2050 4950 2050
Wire Wire Line
	1350 3950 1350 4200
Wire Wire Line
	7200 5100 7200 5150
Wire Wire Line
	7300 4350 7300 3950
Wire Wire Line
	7300 3950 7450 3950
Connection ~ 7300 4350
Wire Wire Line
	8050 3950 7850 3950
Connection ~ 7950 3950
Wire Wire Line
	8650 3950 8450 3950
Connection ~ 8550 3950
Wire Wire Line
	9150 4400 9150 4500
Connection ~ 9150 3950
Wire Wire Line
	10150 5150 10150 5200
Wire Wire Line
	6800 4350 7350 4350
Wire Wire Line
	6900 5050 6900 5150
Wire Wire Line
	1600 4900 1800 4900
Wire Wire Line
	3000 4400 3000 4550
Wire Wire Line
	3000 4450 3400 4450
Wire Wire Line
	3400 4450 3400 4550
Connection ~ 3000 4450
Wire Wire Line
	10050 4550 10150 4550
Wire Wire Line
	10150 3950 9050 3950
Wire Wire Line
	9500 4550 9500 4400
Wire Wire Line
	1700 4800 1700 4900
Connection ~ 1700 4900
$Comp
L PWR_FLAG #FLG01
U 1 1 4B14D4E6
P 1700 5450
F 0 "#FLG01" H 1700 5720 30  0001 C CNN
F 1 "PWR_FLAG" H 1700 5680 30  0000 C CNN
	1    1700 5450
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 4B14D4E0
P 1700 4800
F 0 "#FLG02" H 1700 5070 30  0001 C CNN
F 1 "PWR_FLAG" H 1700 5030 30  0000 C CNN
	1    1700 4800
	1    0    0    -1  
$EndComp
$Comp
L CONN_1 XL5
U 1 1 4B14D4B4
P 1400 5350
F 0 "XL5" V 1350 5360 40  0000 C CNN
F 1 "CONN_1" V 1410 5370 40  0000 C CNN
	1    1400 5350
	-1   0    0    1   
$EndComp
$Comp
L CONN_1 XL4
U 1 1 4B14D4A0
P 1400 4900
F 0 "XL4" V 1350 4910 40  0000 C CNN
F 1 "CONN_1" V 1410 4920 40  0000 C CNN
	1    1400 4900
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 4B0C5B41
P 9800 4550
F 0 "R3" V 9880 4550 50  0000 C CNN
F 1 "1k" V 9800 4550 50  0000 C CNN
	1    9800 4550
	0    1    1    0   
$EndComp
$Comp
L Zener D2
U 1 1 4B0C5B0E
P 9500 4200
F 0 "D2" H 9500 4300 40  0000 C CNN
F 1 "Zener 20V" H 9500 4100 40  0000 C CNN
	1    9500 4200
	0    -1   -1   0   
$EndComp
$Comp
L VCC #PWR03
U 1 1 4B086905
P 3000 4400
F 0 "#PWR03" H 3000 4450 30  0001 C CNN
F 1 "VCC" H 3070 4430 30  0000 C CNN
	1    3000 4400
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR04
U 1 1 4B086900
P 3000 5100
F 0 "#PWR04" H 3090 5080 30  0001 C CNN
F 1 "GND" H 3000 5020 30  0001 C CNN
	1    3000 5100
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 4B0868F6
P 3400 4750
F 0 "C2" H 3450 4850 50  0000 L CNN
F 1 "0.1" H 3450 4650 50  0000 L CNN
	1    3400 4750
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 4B0868F1
P 3000 4750
F 0 "C1" H 3050 4850 50  0000 L CNN
F 1 "10u" H 3050 4650 50  0000 L CNN
	1    3000 4750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR05
U 1 1 4B0868EC
P 1800 4900
F 0 "#PWR05" H 1800 4950 30  0001 C CNN
F 1 "VCC" H 1870 4930 30  0000 C CNN
	1    1800 4900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 4B0868E9
P 1600 5550
F 0 "#PWR06" H 1690 5530 30  0001 C CNN
F 1 "GND" H 1600 5470 30  0001 C CNN
	1    1600 5550
	1    0    0    -1  
$EndComp
NoConn ~ 3250 2050
NoConn ~ 3250 2150
Text Label 7050 4550 0    60   ~ 0
PWM
$Comp
L GND #PWR07
U 1 1 4B086796
P 6900 5150
F 0 "#PWR07" H 6990 5130 30  0001 C CNN
F 1 "GND" H 6900 5070 30  0001 C CNN
	1    6900 5150
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 4B086790
P 6900 4850
F 0 "C3" H 6950 4950 50  0000 L CNN
F 1 "10u" H 6950 4750 50  0000 L CNN
	1    6900 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 4B086763
P 10150 5200
F 0 "#PWR08" H 10240 5180 30  0001 C CNN
F 1 "GND" H 10150 5120 30  0001 C CNN
	1    10150 5200
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4B086757
P 10150 4900
F 0 "R2" V 10230 4900 50  0000 C CNN
F 1 "6R8" V 10150 4900 50  0000 C CNN
	1    10150 4900
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 XL3
U 1 1 4B08674C
P 10350 4050
F 0 "XL3" V 10300 4050 40  0000 C CNN
F 1 "CONN_2" V 10400 4050 40  0000 C CNN
	1    10350 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 4B086735
P 9150 4500
F 0 "#PWR09" H 9240 4480 30  0001 C CNN
F 1 "GND" H 9150 4420 30  0001 C CNN
	1    9150 4500
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 4B08672C
P 9150 4200
F 0 "C5" H 9200 4300 50  0000 L CNN
F 1 "10u" H 9200 4100 50  0000 L CNN
	1    9150 4200
	1    0    0    -1  
$EndComp
$Comp
L D_Shottky D1
U 1 1 4B086722
P 8850 3950
F 0 "D1" H 8850 4050 40  0000 C CNN
F 1 "BAT254" H 8850 3850 40  0000 C CNN
	1    8850 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 4B086717
P 8550 4500
F 0 "#PWR010" H 8640 4480 30  0001 C CNN
F 1 "GND" H 8550 4420 30  0001 C CNN
	1    8550 4500
	1    0    0    -1  
$EndComp
$Comp
L L L2
U 1 1 4B086710
P 8550 4250
F 0 "L2" V 8460 4160 40  0000 C CNN
F 1 "100uH" V 8450 4350 40  0000 C CNN
	1    8550 4250
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 4B0866E7
P 8250 3950
F 0 "C4" H 8300 4050 50  0000 L CNN
F 1 "10u" H 8300 3850 50  0000 L CNN
	1    8250 3950
	0    1    1    0   
$EndComp
$Comp
L L L1
U 1 1 4B0866BB
P 7650 3950
F 0 "L1" V 7560 3860 40  0000 C CNN
F 1 "100uH" V 7550 4050 40  0000 C CNN
	1    7650 3950
	0    1    1    0   
$EndComp
$Comp
L GND #PWR011
U 1 1 4B0866A5
P 7200 5150
F 0 "#PWR011" H 7290 5130 30  0001 C CNN
F 1 "GND" H 7200 5070 30  0001 C CNN
	1    7200 5150
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 4B08669F
P 7200 4850
F 0 "R1" V 7280 4850 50  0000 C CNN
F 1 "100k" V 7200 4850 50  0000 C CNN
	1    7200 4850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR012
U 1 1 4B086674
P 6800 4350
F 0 "#PWR012" H 6800 4400 30  0001 C CNN
F 1 "VCC" H 6870 4380 30  0000 C CNN
	1    6800 4350
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR013
U 1 1 4B08651A
P 7650 4800
F 0 "#PWR013" H 7740 4780 30  0001 C CNN
F 1 "GND" H 7650 4720 30  0001 C CNN
	1    7650 4800
	1    0    0    -1  
$EndComp
$Comp
L LM3410 DA1
U 1 1 4B086511
P 7650 4400
F 0 "DA1" H 7500 4700 60  0000 C CNN
F 1 "LM3410" H 7650 4600 60  0000 C CNN
	1    7650 4400
	1    0    0    -1  
$EndComp
Text Label 2100 3950 0    60   ~ 0
PB2
$Comp
L GND #PWR014
U 1 1 4B0861CD
P 1350 4200
F 0 "#PWR014" H 1440 4180 30  0001 C CNN
F 1 "GND" H 1350 4120 30  0001 C CNN
	1    1350 4200
	1    0    0    -1  
$EndComp
$Comp
L PUSHBUTTON SW1
U 1 1 4B0861C2
P 1650 3950
F 0 "SW1" H 1800 4060 50  0000 C CNN
F 1 "PUSHBUTTON" H 1650 3870 50  0000 C CNN
	1    1650 3950
	1    0    0    -1  
$EndComp
Text Label 5050 2150 0    60   ~ 0
PWM
Text Label 5050 2050 0    60   ~ 0
PB2
$Comp
L VCC #PWR015
U 1 1 4B086120
P 5050 1950
F 0 "#PWR015" H 5050 2000 30  0001 C CNN
F 1 "VCC" H 5120 1980 30  0000 C CNN
	1    5050 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 4B086116
P 3250 2400
F 0 "#PWR016" H 3340 2380 30  0001 C CNN
F 1 "GND" H 3250 2320 30  0001 C CNN
	1    3250 2400
	1    0    0    -1  
$EndComp
$Comp
L ATTINY45 DD1
U 1 1 4B0860E4
P 4100 2150
F 0 "DD1" H 3650 2500 60  0000 C CNN
F 1 "ATTINY45" H 4400 2500 60  0000 C CNN
	1    4100 2150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
