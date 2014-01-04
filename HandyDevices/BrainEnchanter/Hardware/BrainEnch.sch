EESchema Schematic File Version 2
LIBS:Connectors_kl
LIBS:pcb_details
LIBS:power
LIBS:Power_kl
LIBS:st_kl
LIBS:Tittar_kl
LIBS:Transistors_kl
LIBS:OpAmp_kl
LIBS:BrainEnch-cache
EELAYER 27 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date "2 jan 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 1350 6700 0    60   Italic 12
Debug port
Text Notes 1250 5400 0    60   Italic 12
Programming
Text Notes 5050 700  0    60   Italic 12
CPU
Text Notes 8650 8800 0    60   Italic 12
Power
$Comp
L GND #PWR18
U 1 1 5149BCE1
P 3700 4200
F 0 "#PWR18" H 3790 4180 30  0001 C CNN
F 1 "GND" H 3700 4120 30  0001 C CNN
F 2 "" H 3700 4200 60  0001 C CNN
F 3 "" H 3700 4200 60  0001 C CNN
	1    3700 4200
	1    0    0    -1  
$EndComp
$Comp
L REFPOINT RP2
U 1 1 5149B6EB
P 14050 9750
F 0 "RP2" H 14750 9750 60  0000 C CNN
F 1 "REFPOINT" H 14400 9750 60  0000 C CNN
F 2 "" H 14050 9750 60  0001 C CNN
F 3 "" H 14050 9750 60  0001 C CNN
	1    14050 9750
	1    0    0    -1  
$EndComp
$Comp
L REFPOINT RP1
U 1 1 5149B6E8
P 14050 9500
F 0 "RP1" H 14750 9500 60  0000 C CNN
F 1 "REFPOINT" H 14400 9500 60  0000 C CNN
F 2 "" H 14050 9500 60  0001 C CNN
F 3 "" H 14050 9500 60  0001 C CNN
	1    14050 9500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR26
U 1 1 5149A586
P 1950 6150
F 0 "#PWR26" H 2040 6130 30  0001 C CNN
F 1 "GND" H 1950 6070 30  0001 C CNN
F 2 "" H 1950 6150 60  0001 C CNN
F 3 "" H 1950 6150 60  0001 C CNN
	1    1950 6150
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR25
U 1 1 5149A57E
P 1950 5950
F 0 "#PWR25" H 1950 5910 30  0001 C CNN
F 1 "+3.3V" H 2030 5980 30  0000 C CNN
F 2 "" H 1950 5950 60  0001 C CNN
F 3 "" H 1950 5950 60  0001 C CNN
	1    1950 5950
	1    0    0    -1  
$EndComp
Text Label 1950 5750 0    60   ~ 0
SWCLK
Text Label 1950 5850 0    60   ~ 0
SWDIO
Text Label 6650 2700 0    60   ~ 0
SWCLK
Text Label 6650 2600 0    60   ~ 0
SWDIO
$Comp
L GND #PWR22
U 1 1 5149A472
P 5050 4300
F 0 "#PWR22" H 5140 4280 30  0001 C CNN
F 1 "GND" H 5050 4220 30  0001 C CNN
F 2 "" H 5050 4300 60  0001 C CNN
F 3 "" H 5050 4300 60  0001 C CNN
	1    5050 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR17
U 1 1 5149A46C
P 3450 4200
F 0 "#PWR17" H 3540 4180 30  0001 C CNN
F 1 "GND" H 3450 4120 30  0001 C CNN
F 2 "" H 3450 4200 60  0001 C CNN
F 3 "" H 3450 4200 60  0001 C CNN
	1    3450 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR16
U 1 1 5149A469
P 2700 4200
F 0 "#PWR16" H 2790 4180 30  0001 C CNN
F 1 "GND" H 2700 4120 30  0001 C CNN
F 2 "" H 2700 4200 60  0001 C CNN
F 3 "" H 2700 4200 60  0001 C CNN
	1    2700 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR14
U 1 1 5149A467
P 2200 4200
F 0 "#PWR14" H 2290 4180 30  0001 C CNN
F 1 "GND" H 2200 4120 30  0001 C CNN
F 2 "" H 2200 4200 60  0001 C CNN
F 3 "" H 2200 4200 60  0001 C CNN
	1    2200 4200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR10
U 1 1 5149A44F
P 2650 3350
F 0 "#PWR10" H 2650 3310 30  0001 C CNN
F 1 "+3.3V" H 2730 3380 30  0000 C CNN
F 2 "" H 2650 3350 60  0001 C CNN
F 3 "" H 2650 3350 60  0001 C CNN
	1    2650 3350
	-1   0    0    1   
$EndComp
$Comp
L +3.3V #PWR5
U 1 1 5149A448
P 1900 3150
F 0 "#PWR5" H 1900 3110 30  0001 C CNN
F 1 "+3.3V" H 1980 3180 30  0000 C CNN
F 2 "" H 1900 3150 60  0001 C CNN
F 3 "" H 1900 3150 60  0001 C CNN
	1    1900 3150
	-1   0    0    1   
$EndComp
$Comp
L C C2
U 1 1 5149A42D
P 2200 3900
F 0 "C2" H 2100 3800 50  0000 L CNN
F 1 "0.1u" H 2100 4000 50  0000 L CNN
F 2 "CAP_0402" V 2300 3750 28  0000 C BNN
F 3 "" H 2200 3900 60  0001 C CNN
	1    2200 3900
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5149A385
P 2700 3900
F 0 "C4" H 2600 3800 50  0000 L CNN
F 1 "0.1u" H 2600 4000 50  0000 L CNN
F 2 "CAP_0402" V 2800 3750 28  0000 C BNN
F 3 "" H 2700 3900 60  0001 C CNN
	1    2700 3900
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5149A370
P 3700 3900
F 0 "C6" H 3600 3800 50  0000 L CNN
F 1 "1u" H 3600 4000 50  0000 L CNN
F 2 "CAP_0402" V 3800 3750 28  0000 C BNN
F 3 "" H 3700 3900 60  0001 C CNN
	1    3700 3900
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5149A36D
P 3450 3900
F 0 "C5" H 3350 3800 50  0000 L CNN
F 1 "10n" H 3350 4000 50  0000 L CNN
F 2 "CAP_0402" V 3550 3750 28  0000 C BNN
F 3 "" H 3450 3900 60  0001 C CNN
	1    3450 3900
	1    0    0    -1  
$EndComp
NoConn ~ 3800 3000
Text Label 6650 2200 0    60   ~ 0
UART_TX
$Comp
L GND #PWR32
U 1 1 5149A28E
P 1600 7300
F 0 "#PWR32" H 1690 7280 30  0001 C CNN
F 1 "GND" H 1600 7220 30  0001 C CNN
F 2 "" H 1600 7300 60  0001 C CNN
F 3 "" H 1600 7300 60  0001 C CNN
	1    1600 7300
	-1   0    0    -1  
$EndComp
$Comp
L ST_SWD XL2
U 1 1 51499E97
P 1500 5900
F 0 "XL2" H 1350 6200 60  0000 C CNN
F 1 "ST_SWD" H 1700 6200 60  0000 C CNN
F 2 "" H 1500 5900 60  0001 C CNN
F 3 "" H 1500 5900 60  0001 C CNN
	1    1500 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR13
U 1 1 525CF187
P 1950 4200
F 0 "#PWR13" H 2040 4180 30  0001 C CNN
F 1 "GND" H 1950 4120 30  0001 C CNN
F 2 "" H 1950 4200 60  0001 C CNN
F 3 "" H 1950 4200 60  0001 C CNN
	1    1950 4200
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 525CF18D
P 1950 3900
F 0 "C1" H 1850 3800 50  0000 L CNN
F 1 "10u" H 1850 4000 50  0000 L CNN
F 2 "CAP_0805" V 2050 3750 28  0000 C BNN
F 3 "" H 1950 3900 60  0001 C CNN
	1    1950 3900
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5265B644
P 7350 1300
F 0 "R3" V 7430 1150 50  0000 C CNN
F 1 "1k" V 7350 1300 50  0000 C CNN
F 2 "RES_0402" V 7430 1400 28  0000 C CNN
F 3 "" H 7350 1300 60  0001 C CNN
	1    7350 1300
	0    -1   -1   0   
$EndComp
$Comp
L +BATT #PWR2
U 1 1 5265B651
P 7700 1300
F 0 "#PWR2" H 7700 1260 30  0001 C CNN
F 1 "+BATT" H 7780 1330 30  0000 C CNN
F 2 "" H 7700 1300 60  0000 C CNN
F 3 "" H 7700 1300 60  0000 C CNN
	1    7700 1300
	1    0    0    -1  
$EndComp
$Comp
L BAT B1
U 1 1 52664780
P 4800 9950
F 0 "B1" H 4500 10050 60  0000 C CNN
F 1 "BAT" H 4500 10150 60  0000 C CNN
F 2 "" H 4800 9950 60  0001 C CNN
F 3 "" H 4800 9950 60  0001 C CNN
	1    4800 9950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR39
U 1 1 52664786
P 8150 9700
F 0 "#PWR39" H 8150 9660 30  0001 C CNN
F 1 "+3.3V" H 8230 9730 30  0000 C CNN
F 2 "" H 8150 9700 60  0001 C CNN
F 3 "" H 8150 9700 60  0001 C CNN
	1    8150 9700
	1    0    0    -1  
$EndComp
Text Label 6650 9700 0    60   ~ 0
Lout
$Comp
L +BATT #PWR38
U 1 1 5266478D
P 5750 9550
F 0 "#PWR38" H 5750 9510 30  0001 C CNN
F 1 "+BATT" H 5830 9580 30  0000 C CNN
F 2 "" H 5750 9550 60  0001 C CNN
F 3 "" H 5750 9550 60  0001 C CNN
	1    5750 9550
	0    -1   -1   0   
$EndComp
$Comp
L C C12
U 1 1 52664793
P 7800 9950
F 0 "C12" H 7850 10050 50  0000 L CNN
F 1 "0.1u" H 7750 9850 50  0000 L CNN
F 2 "" H 7800 9950 60  0001 C CNN
F 3 "" H 7800 9950 60  0001 C CNN
	1    7800 9950
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 52664799
P 8050 9950
F 0 "C13" H 8100 10050 50  0000 L CNN
F 1 "10u" H 8050 9850 50  0000 L CNN
F 2 "" H 8050 9950 60  0001 C CNN
F 3 "" H 8050 9950 60  0001 C CNN
	1    8050 9950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR44
U 1 1 5266479F
P 7800 10250
F 0 "#PWR44" H 7890 10230 30  0001 C CNN
F 1 "GND" H 7800 10170 30  0001 C CNN
F 2 "" H 7800 10250 60  0001 C CNN
F 3 "" H 7800 10250 60  0001 C CNN
	1    7800 10250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR45
U 1 1 526647A5
P 8050 10250
F 0 "#PWR45" H 8140 10230 30  0001 C CNN
F 1 "GND" H 8050 10170 30  0001 C CNN
F 2 "" H 8050 10250 60  0001 C CNN
F 3 "" H 8050 10250 60  0001 C CNN
	1    8050 10250
	1    0    0    -1  
$EndComp
$Comp
L D_SHOTTKY D1
U 1 1 526647AB
P 7100 9700
F 0 "D1" H 6950 9800 40  0000 C CNN
F 1 "BAT54WS" H 7200 9800 40  0000 C CNN
F 2 "" H 7100 9700 60  0001 C CNN
F 3 "" H 7100 9700 60  0001 C CNN
	1    7100 9700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR43
U 1 1 526647B1
P 6700 10250
F 0 "#PWR43" H 6790 10230 30  0001 C CNN
F 1 "GND" H 6700 10170 30  0001 C CNN
F 2 "" H 6700 10250 60  0001 C CNN
F 3 "" H 6700 10250 60  0001 C CNN
	1    6700 10250
	1    0    0    -1  
$EndComp
$Comp
L L L1
U 1 1 526647B7
P 6400 9700
F 0 "L1" V 6310 9610 40  0000 C CNN
F 1 "22uH" V 6300 9800 40  0000 C CNN
F 2 "" H 6400 9700 60  0001 C CNN
F 3 "" H 6400 9700 60  0001 C CNN
	1    6400 9700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR42
U 1 1 526647BD
P 6000 10250
F 0 "#PWR42" H 6090 10230 30  0001 C CNN
F 1 "GND" H 6000 10170 30  0001 C CNN
F 2 "" H 6000 10250 60  0001 C CNN
F 3 "" H 6000 10250 60  0001 C CNN
	1    6000 10250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR41
U 1 1 526647C3
P 5750 10250
F 0 "#PWR41" H 5840 10230 30  0001 C CNN
F 1 "GND" H 5750 10170 30  0001 C CNN
F 2 "" H 5750 10250 60  0001 C CNN
F 3 "" H 5750 10250 60  0001 C CNN
	1    5750 10250
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 526647C9
P 6000 9950
F 0 "C8" H 6050 10050 50  0000 L CNN
F 1 "10u" H 6000 9850 50  0000 L CNN
F 2 "" H 6000 9950 60  0001 C CNN
F 3 "" H 6000 9950 60  0001 C CNN
	1    6000 9950
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 526647CF
P 5750 9950
F 0 "C7" H 5800 10050 50  0000 L CNN
F 1 "0.1u" H 5700 9850 50  0000 L CNN
F 2 "" H 5750 9950 60  0001 C CNN
F 3 "" H 5750 9950 60  0001 C CNN
	1    5750 9950
	1    0    0    -1  
$EndComp
$Comp
L NCP1400 DA1
U 1 1 526647D5
P 7150 10050
F 0 "DA1" H 6950 10300 60  0000 C CNN
F 1 "NCP1400" H 7350 10300 60  0000 C CNN
F 2 "" H 7150 10050 60  0001 C CNN
F 3 "" H 7150 10050 60  0001 C CNN
	1    7150 10050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR40
U 1 1 526647DB
P 4800 10250
F 0 "#PWR40" H 4890 10230 30  0001 C CNN
F 1 "GND" H 4800 10170 30  0001 C CNN
F 2 "" H 4800 10250 60  0001 C CNN
F 3 "" H 4800 10250 60  0001 C CNN
	1    4800 10250
	1    0    0    -1  
$EndComp
$Comp
L BUZZER BZ1
U 1 1 52670A22
P 7100 7650
F 0 "BZ1" H 7300 7750 60  0000 C CNN
F 1 "BUZZER" H 7400 7550 60  0000 C CNN
F 2 "" H 7100 7650 60  0001 C CNN
F 3 "" H 7100 7650 60  0001 C CNN
	1    7100 7650
	0    -1   1    0   
$EndComp
Text Label 6350 7650 0    60   ~ 0
BuzzerOut
Text Label 5050 8000 0    60   ~ 0
Buzzer
$Comp
L R R1
U 1 1 52670A2A
P 5750 8000
F 0 "R1" V 5830 8000 50  0000 C CNN
F 1 "1k" V 5750 8000 50  0000 C CNN
F 2 "" H 5750 8000 60  0001 C CNN
F 3 "" H 5750 8000 60  0001 C CNN
	1    5750 8000
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR34
U 1 1 52670A30
P 6450 8300
F 0 "#PWR34" H 6540 8280 30  0001 C CNN
F 1 "GND" H 6450 8220 30  0001 C CNN
F 2 "" H 6450 8300 60  0001 C CNN
F 3 "" H 6450 8300 60  0001 C CNN
	1    6450 8300
	1    0    0    -1  
$EndComp
$Comp
L NPN Q1
U 1 1 52670A36
P 6400 8000
F 0 "Q1" H 6600 8050 60  0000 C CNN
F 1 "MMBT2222" H 6750 7950 60  0000 C CNN
F 2 "" H 6400 8000 60  0001 C CNN
F 3 "" H 6400 8000 60  0001 C CNN
	1    6400 8000
	1    0    0    -1  
$EndComp
Text Label 3350 1600 0    60   ~ 0
Buzzer
Text Label 6650 2300 0    60   ~ 0
UART_RX
Text Label 1850 7050 0    60   ~ 0
UART_TX
Text Label 1850 6950 0    60   ~ 0
UART_RX
$Comp
L CONN_3 XL1
U 1 1 526728AC
P 1400 7050
F 0 "XL1" V 1350 7050 40  0000 C CNN
F 1 "CONN_3" V 1450 7050 40  0000 C CNN
F 2 "~" H 1400 7050 60  0000 C CNN
F 3 "~" H 1400 7050 60  0000 C CNN
	1    1400 7050
	1    0    0    1   
$EndComp
Text Notes 4600 9250 0    60   ~ 0
1xAAA
$Comp
L +3.3V #PWR33
U 1 1 526D45BA
P 7600 7650
F 0 "#PWR33" H 7600 7610 30  0001 C CNN
F 1 "+3.3V" H 7680 7680 30  0000 C CNN
F 2 "" H 7600 7650 60  0000 C CNN
F 3 "" H 7600 7650 60  0000 C CNN
	1    7600 7650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR35
U 1 1 526D45C7
P 7450 8300
F 0 "#PWR35" H 7540 8280 30  0001 C CNN
F 1 "GND" H 7450 8220 30  0001 C CNN
F 2 "" H 7450 8300 60  0001 C CNN
F 3 "" H 7450 8300 60  0001 C CNN
	1    7450 8300
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 526D45CD
P 7450 8000
F 0 "C10" H 7350 7900 50  0000 L CNN
F 1 "10u" H 7350 8100 50  0000 L CNN
F 2 "CAP_0805" V 7550 7850 28  0000 C BNN
F 3 "" H 7450 8000 60  0001 C CNN
	1    7450 8000
	1    0    0    -1  
$EndComp
NoConn ~ 6450 2100
NoConn ~ 6450 2400
NoConn ~ 6450 2500
$Comp
L GND #PWR15
U 1 1 526E3E25
P 2450 4200
F 0 "#PWR15" H 2540 4180 30  0001 C CNN
F 1 "GND" H 2450 4120 30  0001 C CNN
F 2 "" H 2450 4200 60  0001 C CNN
F 3 "" H 2450 4200 60  0001 C CNN
	1    2450 4200
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 526E3E2B
P 2450 3900
F 0 "C3" H 2350 3800 50  0000 L CNN
F 1 "0.1u" H 2350 4000 50  0000 L CNN
F 2 "CAP_0402" V 2550 3750 28  0000 C BNN
F 3 "" H 2450 3900 60  0001 C CNN
	1    2450 3900
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR7
U 1 1 526E3E32
P 2400 3250
F 0 "#PWR7" H 2400 3210 30  0001 C CNN
F 1 "+3.3V" H 2480 3280 30  0000 C CNN
F 2 "" H 2400 3250 60  0001 C CNN
F 3 "" H 2400 3250 60  0001 C CNN
	1    2400 3250
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR30
U 1 1 5270301A
P 6250 7100
F 0 "#PWR30" H 6340 7080 30  0001 C CNN
F 1 "GND" H 6250 7020 30  0001 C CNN
F 2 "" H 6250 7100 60  0000 C CNN
F 3 "" H 6250 7100 60  0000 C CNN
	1    6250 7100
	1    0    0    -1  
$EndComp
$Comp
L BUTTON SW3
U 1 1 52703029
P 5850 6200
F 0 "SW3" H 5650 6350 50  0000 C CNN
F 1 "BUTTON" H 5950 6350 50  0000 C CNN
F 2 "~" H 5850 6200 60  0000 C CNN
F 3 "~" H 5850 6200 60  0000 C CNN
	1    5850 6200
	1    0    0    -1  
$EndComp
$Comp
L BUTTON SW4
U 1 1 52703038
P 5850 6550
F 0 "SW4" H 5650 6700 50  0000 C CNN
F 1 "BUTTON" H 5950 6700 50  0000 C CNN
F 2 "~" H 5850 6550 60  0000 C CNN
F 3 "~" H 5850 6550 60  0000 C CNN
	1    5850 6550
	1    0    0    -1  
$EndComp
$Comp
L BUTTON SW5
U 1 1 52703047
P 5850 6900
F 0 "SW5" H 5650 7050 50  0000 C CNN
F 1 "BUTTON" H 5950 7050 50  0000 C CNN
F 2 "~" H 5850 6900 60  0000 C CNN
F 3 "~" H 5850 6900 60  0000 C CNN
	1    5850 6900
	1    0    0    -1  
$EndComp
Text Label 5200 6200 0    60   ~ 0
BTN3
Text Label 5200 6550 0    60   ~ 0
BTN4
Text Label 5200 6900 0    60   ~ 0
BTN5
$Comp
L GND #PWR31
U 1 1 52704227
P 8350 7100
F 0 "#PWR31" H 8440 7080 30  0001 C CNN
F 1 "GND" H 8350 7020 30  0001 C CNN
F 2 "" H 8350 7100 60  0001 C CNN
F 3 "" H 8350 7100 60  0001 C CNN
	1    8350 7100
	0    -1   -1   0   
$EndComp
Text Notes 7400 6700 0    60   ~ 0
LCD
$Comp
L +3.3V #PWR27
U 1 1 5270422E
P 8500 6700
F 0 "#PWR27" H 8500 6660 30  0001 C CNN
F 1 "+3.3V" H 8580 6730 30  0000 C CNN
F 2 "" H 8500 6700 60  0001 C CNN
F 3 "" H 8500 6700 60  0001 C CNN
	1    8500 6700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR28
U 1 1 52704234
P 8350 6850
F 0 "#PWR28" H 8440 6830 30  0001 C CNN
F 1 "GND" H 8350 6770 30  0001 C CNN
F 2 "" H 8350 6850 60  0001 C CNN
F 3 "" H 8350 6850 60  0001 C CNN
	1    8350 6850
	0    -1   -1   0   
$EndComp
Text Label 9150 7000 0    60   ~ 0
LCD_BCKLT
Text Label 8400 6150 0    60   ~ 0
LCD_SCLK
Text Label 8400 6250 0    60   ~ 0
LCD_SDA
Text Label 8400 6350 0    60   ~ 0
LCD_XCS
Text Label 8400 6450 0    60   ~ 0
LCD_XRES
Text Label 3350 2500 0    60   ~ 0
LCD_SCLK
Text Label 3350 2300 0    60   ~ 0
LCD_SDA
Text Label 3350 2400 0    60   ~ 0
LCD_XRES
Text Label 3350 2600 0    60   ~ 0
LCD_XCS
Text Label 3350 2700 0    60   ~ 0
LCD_BCKLT
$Comp
L R R4
U 1 1 52704260
P 8750 7000
F 0 "R4" V 8830 6850 50  0000 C CNN
F 1 "51R" V 8750 7000 50  0000 C CNN
F 2 "RES_0603" V 8830 7100 28  0000 C CNN
F 3 "" H 8750 7000 60  0000 C CNN
	1    8750 7000
	0    -1   -1   0   
$EndComp
$Comp
L CONN_NOKIA_LCD10 XL3
U 1 1 52704267
P 8000 6500
F 0 "XL3" V 7700 6700 60  0000 C CNN
F 1 "CONN_NOKIA_LCD10" V 7700 6150 60  0000 C CNN
F 2 "" H 8000 6500 60  0000 C CNN
F 3 "" H 8000 6500 60  0000 C CNN
	1    8000 6500
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5270DB78
P 7050 3950
F 0 "C9" H 7100 4050 50  0000 L CNN
F 1 "6.8pF" H 7100 3850 50  0000 L CNN
F 2 "" H 7050 3950 60  0001 C CNN
F 3 "" H 7050 3950 60  0001 C CNN
	1    7050 3950
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 5270DB7E
P 7650 3950
F 0 "C11" H 7700 4050 50  0000 L CNN
F 1 "6.8pF" H 7700 3850 50  0000 L CNN
F 2 "" H 7650 3950 60  0001 C CNN
F 3 "" H 7650 3950 60  0001 C CNN
	1    7650 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR20
U 1 1 5270DB84
P 7050 4250
F 0 "#PWR20" H 7140 4230 30  0001 C CNN
F 1 "GND" H 7050 4170 30  0001 C CNN
F 2 "" H 7050 4250 60  0001 C CNN
F 3 "" H 7050 4250 60  0001 C CNN
	1    7050 4250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR21
U 1 1 5270DB8A
P 7650 4250
F 0 "#PWR21" H 7740 4230 30  0001 C CNN
F 1 "GND" H 7650 4170 30  0001 C CNN
F 2 "" H 7650 4250 60  0001 C CNN
F 3 "" H 7650 4250 60  0001 C CNN
	1    7650 4250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5270DB98
P 6800 3400
F 0 "R2" V 6880 3250 50  0000 C CNN
F 1 "200k*" V 6800 3400 50  0000 C CNN
F 2 "RES_0402" V 6880 3500 28  0000 C CNN
F 3 "~" H 6800 3400 60  0000 C CNN
	1    6800 3400
	0    -1   1    0   
$EndComp
$Comp
L GENERIC_8PIN DA4
U 2 1 52907BA4
P 12800 4050
F 0 "DA4" H 12850 4250 60  0000 C CNN
F 1 "MAX4453" H 13000 4350 50  0000 C CNN
F 2 "" H 12800 4050 60  0000 C CNN
F 3 "" H 12800 4050 60  0000 C CNN
	2    12800 4050
	-1   0    0    -1  
$EndComp
$Comp
L LM2703 DA2
U 1 1 52907BB8
P 10300 9850
F 0 "DA2" H 10200 10100 60  0000 C CNN
F 1 "LM2703" H 10300 9850 60  0000 C CNN
F 2 "~" H 10300 9850 60  0000 C CNN
F 3 "~" H 10300 9850 60  0000 C CNN
	1    10300 9850
	1    0    0    -1  
$EndComp
$Comp
L L L2
U 1 1 52907BC7
P 10300 9100
F 0 "L2" V 10200 8960 40  0000 C CNN
F 1 "10uH" V 10200 9100 40  0000 C CNN
F 2 "IND_0805" V 10360 9110 40  0000 C CNN
F 3 "~" H 10300 9100 60  0000 C CNN
	1    10300 9100
	0    1    1    0   
$EndComp
$Comp
L D_SHOTTKY D2
U 1 1 52907C0A
P 11050 9100
F 0 "D2" H 10900 9200 40  0000 C CNN
F 1 "BAT54WS" H 11150 9200 40  0000 C CNN
F 2 "" H 11050 9100 60  0001 C CNN
F 3 "" H 11050 9100 60  0001 C CNN
	1    11050 9100
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 52907C12
P 11550 9600
F 0 "R5" V 11630 9450 50  0000 C CNN
F 1 "81k" V 11550 9600 50  0000 C CNN
F 2 "RES_0603" V 11630 9700 28  0000 C CNN
F 3 "~" H 11550 9600 60  0000 C CNN
	1    11550 9600
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 52907C21
P 11550 10450
F 0 "R6" V 11630 10300 50  0000 C CNN
F 1 "10k" V 11550 10450 50  0000 C CNN
F 2 "RES_0603" V 11630 10550 28  0000 C CNN
F 3 "~" H 11550 10450 60  0000 C CNN
	1    11550 10450
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 52907C68
P 12100 9700
F 0 "C15" H 12000 9600 50  0000 L CNN
F 1 "1uF" H 12000 9800 50  0000 L CNN
F 2 "CAP_0603" V 12200 9550 28  0000 C BNN
F 3 "~" H 12100 9700 60  0000 C CNN
	1    12100 9700
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 52907CA9
P 9450 9800
F 0 "C14" H 9350 9700 50  0000 L CNN
F 1 "10uF" H 9350 9900 50  0000 L CNN
F 2 "CAP_0603" V 9550 9650 28  0000 C BNN
F 3 "~" H 9450 9800 60  0000 C CNN
	1    9450 9800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR50
U 1 1 52908A89
P 11550 10850
F 0 "#PWR50" H 11640 10830 30  0001 C CNN
F 1 "GND" H 11550 10770 30  0001 C CNN
F 2 "" H 11550 10850 60  0000 C CNN
F 3 "" H 11550 10850 60  0000 C CNN
	1    11550 10850
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR37
U 1 1 52908B2F
P 12750 9100
F 0 "#PWR37" H 12750 9060 30  0001 C CNN
F 1 "+12V" H 12830 9130 30  0000 C CNN
F 2 "" H 12750 9100 60  0000 C CNN
F 3 "" H 12750 9100 60  0000 C CNN
	1    12750 9100
	1    0    0    -1  
$EndComp
Text Label 9550 10100 0    60   ~ 0
12V_EN
Text Label 6650 2800 0    60   ~ 0
12V_EN
$Comp
L +3.3V #PWR36
U 1 1 52908FA5
P 9300 9100
F 0 "#PWR36" H 9300 9060 30  0001 C CNN
F 1 "+3.3V" H 9380 9130 30  0000 C CNN
F 2 "" H 9300 9100 60  0000 C CNN
F 3 "" H 9300 9100 60  0000 C CNN
	1    9300 9100
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR49
U 1 1 5290904E
P 10300 10600
F 0 "#PWR49" H 10390 10580 30  0001 C CNN
F 1 "GND" H 10300 10520 30  0001 C CNN
F 2 "" H 10300 10600 60  0000 C CNN
F 3 "" H 10300 10600 60  0000 C CNN
	1    10300 10600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR48
U 1 1 52909054
P 9450 10600
F 0 "#PWR48" H 9540 10580 30  0001 C CNN
F 1 "GND" H 9450 10520 30  0001 C CNN
F 2 "" H 9450 10600 60  0000 C CNN
F 3 "" H 9450 10600 60  0000 C CNN
	1    9450 10600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR46
U 1 1 52909187
P 12100 10250
F 0 "#PWR46" H 12190 10230 30  0001 C CNN
F 1 "GND" H 12100 10170 30  0001 C CNN
F 2 "" H 12100 10250 60  0000 C CNN
F 3 "" H 12100 10250 60  0000 C CNN
	1    12100 10250
	1    0    0    -1  
$EndComp
$Comp
L CP C16
U 1 1 52909357
P 12500 9700
F 0 "C16" H 12550 9800 50  0000 L CNN
F 1 "100uF 16V" H 12550 9600 50  0000 L CNN
F 2 "~" H 12500 9700 60  0000 C CNN
F 3 "~" H 12500 9700 60  0000 C CNN
	1    12500 9700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR47
U 1 1 52909499
P 12500 10250
F 0 "#PWR47" H 12590 10230 30  0001 C CNN
F 1 "GND" H 12500 10170 30  0001 C CNN
F 2 "" H 12500 10250 60  0000 C CNN
F 3 "" H 12500 10250 60  0000 C CNN
	1    12500 10250
	1    0    0    -1  
$EndComp
Text Label 14800 2550 0    60   ~ 0
BRAIN_C
Text Label 12700 2100 0    61   ~ 0
DAC
$Comp
L GENERIC_8PIN DA4
U 1 1 52909CF9
P 13800 2800
F 0 "DA4" H 13850 3000 60  0000 C CNN
F 1 "MAX4453" H 14000 3100 50  0000 C CNN
F 2 "" H 13800 2800 60  0000 C CNN
F 3 "" H 13800 2800 60  0000 C CNN
	1    13800 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 52909CFF
P 13700 3200
F 0 "#PWR6" H 13790 3180 30  0001 C CNN
F 1 "GND" H 13700 3120 30  0001 C CNN
F 2 "" H 13700 3200 60  0000 C CNN
F 3 "" H 13700 3200 60  0000 C CNN
	1    13700 3200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR3
U 1 1 52909D05
P 13700 2400
F 0 "#PWR3" H 13700 2360 30  0001 C CNN
F 1 "+3.3V" H 13780 2430 30  0000 C CNN
F 2 "" H 13700 2400 60  0000 C CNN
F 3 "" H 13700 2400 60  0000 C CNN
	1    13700 2400
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 52909D0B
P 14800 3450
F 0 "R12" V 14880 3300 50  0000 C CNN
F 1 "100R" V 14800 3450 50  0000 C CNN
F 2 "RES_0805" V 14880 3550 28  0000 C CNN
F 3 "" H 14800 3450 60  0000 C CNN
	1    14800 3450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR19
U 1 1 52909D11
P 14800 4200
F 0 "#PWR19" H 14890 4180 30  0001 C CNN
F 1 "GND" H 14800 4120 30  0001 C CNN
F 2 "" H 14800 4200 60  0000 C CNN
F 3 "" H 14800 4200 60  0000 C CNN
	1    14800 4200
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 52909D35
P 13050 2400
F 0 "R8" V 13130 2250 50  0000 C CNN
F 1 "20k" V 13050 2400 50  0000 C CNN
F 2 "RES_0603" V 13130 2500 28  0000 C CNN
F 3 "" H 13050 2400 60  0000 C CNN
	1    13050 2400
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 52909D3B
P 13050 3000
F 0 "R9" V 13130 2850 50  0000 C CNN
F 1 "4.7k" V 13050 3000 50  0000 C CNN
F 2 "RES_0603" V 13130 3100 28  0000 C CNN
F 3 "" H 13050 3000 60  0000 C CNN
	1    13050 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 52909D41
P 13050 3300
F 0 "#PWR9" H 13140 3280 30  0001 C CNN
F 1 "GND" H 13050 3220 30  0001 C CNN
F 2 "" H 13050 3300 60  0000 C CNN
F 3 "" H 13050 3300 60  0000 C CNN
	1    13050 3300
	1    0    0    -1  
$EndComp
Text Notes 13500 1750 0    79   Italic 0
Stabilizer
Text Label 14250 3100 0    60   ~ 0
CURR_SNS
$Comp
L TESTPOINT TP2
U 1 1 52909D4F
P 14300 2750
F 0 "TP2" H 14300 2900 60  0000 C CNN
F 1 "TESTPOINT" H 14275 2975 60  0001 C CNN
F 2 "" H 14300 2750 60  0000 C CNN
F 3 "" H 14300 2750 60  0000 C CNN
	1    14300 2750
	1    0    0    -1  
$EndComp
$Comp
L TESTPOINT TP1
U 1 1 52909D55
P 13050 1950
F 0 "TP1" H 13050 2100 60  0000 C CNN
F 1 "TESTPOINT" H 13025 2175 60  0001 C CNN
F 2 "" H 13050 1950 60  0000 C CNN
F 3 "" H 13050 1950 60  0000 C CNN
	1    13050 1950
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 52909D61
P 12700 2950
F 0 "C17" H 12600 2850 50  0000 L CNN
F 1 "0.1u" H 12600 3050 50  0000 L CNN
F 2 "CAP_0603" V 12800 2800 28  0000 C BNN
F 3 "~" H 12700 2950 60  0000 C CNN
	1    12700 2950
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR4
U 1 1 52909D67
P 12700 2600
F 0 "#PWR4" H 12700 2560 30  0001 C CNN
F 1 "+3.3V" H 12780 2630 30  0000 C CNN
F 2 "" H 12700 2600 60  0000 C CNN
F 3 "" H 12700 2600 60  0000 C CNN
	1    12700 2600
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR8
U 1 1 52909D6D
P 12700 3300
F 0 "#PWR8" H 12790 3280 30  0001 C CNN
F 1 "GND" H 12700 3220 30  0001 C CNN
F 2 "" H 12700 3300 60  0000 C CNN
F 3 "" H 12700 3300 60  0000 C CNN
	1    12700 3300
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR1
U 1 1 52909DB1
P 14800 1150
F 0 "#PWR1" H 14800 1110 30  0001 C CNN
F 1 "+12V" H 14880 1180 30  0000 C CNN
F 2 "" H 14800 1150 60  0000 C CNN
F 3 "" H 14800 1150 60  0000 C CNN
	1    14800 1150
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 52909DC0
P 14800 1550
F 0 "R11" V 14880 1400 50  0000 C CNN
F 1 "100R" V 14800 1550 50  0000 C CNN
F 2 "RES_0603" V 14880 1650 28  0000 C CNN
F 3 "~" H 14800 1550 60  0000 C CNN
	1    14800 1550
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 XL4
U 1 1 52909FF5
P 15000 2150
F 0 "XL4" V 14950 2150 40  0000 C CNN
F 1 "CONN_2" V 15050 2150 40  0000 C CNN
F 2 "~" H 15000 2150 60  0000 C CNN
F 3 "~" H 15000 2150 60  0000 C CNN
	1    15000 2150
	1    0    0    -1  
$EndComp
Text Label 6650 1700 0    60   ~ 0
DAC
Text Label 6700 1500 0    60   ~ 0
ADC
$Comp
L R R10
U 1 1 5290A43A
P 13800 4850
F 0 "R10" V 13880 4700 50  0000 C CNN
F 1 "1k" V 13800 4850 50  0000 C CNN
F 2 "RES_0603" V 13880 4950 28  0000 C CNN
F 3 "~" H 13800 4850 60  0000 C CNN
	1    13800 4850
	0    -1   -1   0   
$EndComp
$Comp
L R R7
U 1 1 5290A449
P 12350 4850
F 0 "R7" V 12430 4700 50  0000 C CNN
F 1 "6.8k" V 12350 4850 50  0000 C CNN
F 2 "RES_0603" V 12430 4950 28  0000 C CNN
F 3 "~" H 12350 4850 60  0000 C CNN
	1    12350 4850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR24
U 1 1 5290A458
P 14450 4850
F 0 "#PWR24" H 14540 4830 30  0001 C CNN
F 1 "GND" H 14450 4770 30  0001 C CNN
F 2 "" H 14450 4850 60  0000 C CNN
F 3 "" H 14450 4850 60  0000 C CNN
	1    14450 4850
	0    -1   -1   0   
$EndComp
Text Label 11550 4050 0    60   ~ 0
ADC
$Comp
L GND #PWR23
U 1 1 5290AA50
P 12900 4500
F 0 "#PWR23" H 12990 4480 30  0001 C CNN
F 1 "GND" H 12900 4420 30  0001 C CNN
F 2 "" H 12900 4500 60  0000 C CNN
F 3 "" H 12900 4500 60  0000 C CNN
	1    12900 4500
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR11
U 1 1 5290ABEF
P 12900 3600
F 0 "#PWR11" H 12900 3560 30  0001 C CNN
F 1 "+3.3V" H 12980 3630 30  0000 C CNN
F 2 "" H 12900 3600 60  0000 C CNN
F 3 "" H 12900 3600 60  0000 C CNN
	1    12900 3600
	0    -1   -1   0   
$EndComp
Text Label 14800 1900 0    60   ~ 0
BRAIN_A
$Comp
L BUTTON SW1
U 1 1 5290AE40
P 5850 5500
F 0 "SW1" H 5650 5650 50  0000 C CNN
F 1 "BUTTON" H 5950 5650 50  0000 C CNN
F 2 "~" H 5850 5500 60  0000 C CNN
F 3 "~" H 5850 5500 60  0000 C CNN
	1    5850 5500
	1    0    0    -1  
$EndComp
$Comp
L BUTTON SW2
U 1 1 5290AE46
P 5850 5850
F 0 "SW2" H 5650 6000 50  0000 C CNN
F 1 "BUTTON" H 5950 6000 50  0000 C CNN
F 2 "~" H 5850 5850 60  0000 C CNN
F 3 "~" H 5850 5850 60  0000 C CNN
	1    5850 5850
	1    0    0    -1  
$EndComp
Text Label 5200 5500 0    60   ~ 0
BTN1
Text Label 5200 5850 0    60   ~ 0
BTN2
Text Label 3350 1700 0    60   ~ 0
BTN1
Text Label 3350 1800 0    60   ~ 0
BTN2
Text Label 3350 1900 0    60   ~ 0
BTN3
Text Label 3350 2000 0    60   ~ 0
BTN4
Text Label 3350 2100 0    60   ~ 0
BTN5
$Comp
L STM32L151CXTX DD1
U 1 1 52909D3C
P 5100 2500
F 0 "DD1" H 4600 3850 60  0000 C CNN
F 1 "STM32L151CXTX" H 5250 3850 60  0000 C CNN
F 2 "~" H 5100 2500 60  0000 C CNN
F 3 "~" H 5100 2500 60  0000 C CNN
	1    5100 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 6150 1950 6050
Wire Wire Line
	1950 6050 1850 6050
Wire Wire Line
	1950 5750 1850 5750
Wire Wire Line
	6450 2600 6650 2600
Wire Wire Line
	3700 4100 3700 4200
Wire Wire Line
	2200 4100 2200 4200
Wire Wire Line
	6450 2200 6650 2200
Wire Wire Line
	1600 7150 1600 7300
Wire Wire Line
	2700 4100 2700 4200
Wire Wire Line
	3450 4100 3450 4200
Wire Wire Line
	6450 2700 6650 2700
Wire Wire Line
	1850 5850 1950 5850
Wire Wire Line
	1850 5950 1950 5950
Wire Wire Line
	1600 6950 1850 6950
Wire Wire Line
	1950 4100 1950 4200
Wire Wire Line
	7700 1300 7600 1300
Wire Wire Line
	6450 1300 7100 1300
Wire Wire Line
	6700 9700 6700 9950
Connection ~ 7800 9700
Wire Wire Line
	7800 9700 7800 9750
Wire Wire Line
	8050 10150 8050 10250
Connection ~ 7600 9950
Wire Wire Line
	7600 10050 7550 10050
Connection ~ 6700 9700
Wire Wire Line
	6700 10150 6700 10250
Connection ~ 6000 9700
Wire Wire Line
	5750 10150 5750 10250
Wire Wire Line
	6000 9700 6000 9750
Connection ~ 5750 9700
Wire Wire Line
	6000 10150 6000 10250
Wire Wire Line
	6600 9700 6900 9700
Wire Wire Line
	7600 9950 7550 9950
Connection ~ 7600 9700
Wire Wire Line
	7300 9700 8150 9700
Connection ~ 8050 9700
Wire Wire Line
	5750 9550 5750 9750
Wire Wire Line
	7600 9700 7600 10050
Wire Wire Line
	8050 9700 8050 9750
Wire Wire Line
	4800 10250 4800 10200
Connection ~ 6450 7650
Wire Wire Line
	6850 7650 6350 7650
Wire Wire Line
	6450 7800 6450 7650
Wire Wire Line
	5050 8000 5500 8000
Wire Wire Line
	7350 7650 7600 7650
Wire Wire Line
	6000 8000 6200 8000
Wire Wire Line
	6450 8200 6450 8300
Wire Wire Line
	3350 1600 3800 1600
Wire Notes Line
	4150 4900 4150 11200
Wire Notes Line
	4150 8600 16000 8600
Wire Wire Line
	6650 2300 6450 2300
Wire Wire Line
	1850 7050 1600 7050
Wire Wire Line
	4800 9700 6200 9700
Connection ~ 3450 3650
Connection ~ 3700 3650
Connection ~ 2700 3350
Wire Wire Line
	3800 3650 3400 3650
Wire Wire Line
	2650 3350 3800 3350
Wire Wire Line
	7450 8200 7450 8300
Wire Wire Line
	7450 7800 7450 7650
Connection ~ 7450 7650
Wire Wire Line
	4800 9700 4800 9750
Wire Wire Line
	3450 3700 3450 3650
Wire Wire Line
	3700 3700 3700 3650
Wire Wire Line
	2700 3700 2700 3350
Wire Wire Line
	2450 4100 2450 4200
Wire Wire Line
	2450 3700 2450 3250
Wire Wire Line
	2400 3250 3800 3250
Connection ~ 2450 3250
Wire Wire Line
	1900 3150 3800 3150
Wire Wire Line
	1950 3700 1950 3150
Connection ~ 1950 3150
Wire Wire Line
	2200 3700 2200 3150
Connection ~ 2200 3150
Wire Wire Line
	6250 5500 6250 7100
Wire Wire Line
	6250 6200 6150 6200
Wire Wire Line
	6150 6550 6250 6550
Connection ~ 6250 6550
Wire Wire Line
	6150 6900 6250 6900
Connection ~ 6250 6900
Wire Wire Line
	5550 6200 5200 6200
Wire Wire Line
	5550 6550 5200 6550
Wire Wire Line
	5550 6900 5200 6900
Wire Wire Line
	3800 2700 3350 2700
Wire Wire Line
	3800 2600 3350 2600
Wire Wire Line
	3800 2400 3350 2400
Wire Wire Line
	3800 2300 3350 2300
Wire Wire Line
	3800 2500 3350 2500
Wire Wire Line
	8400 6450 8300 6450
Wire Wire Line
	8400 6250 8300 6250
Wire Wire Line
	8350 7100 8300 7100
Wire Wire Line
	8350 6850 8300 6850
Wire Wire Line
	8350 6650 8300 6650
Wire Wire Line
	8350 6650 8350 6750
Wire Wire Line
	8350 6750 8300 6750
Wire Wire Line
	8350 6700 8500 6700
Connection ~ 8350 6700
Wire Wire Line
	8300 7000 8500 7000
Wire Wire Line
	8300 6150 8400 6150
Wire Wire Line
	8300 6350 8400 6350
Wire Wire Line
	9000 7000 9150 7000
Wire Wire Line
	7200 3650 7050 3650
Connection ~ 7650 3650
Connection ~ 7050 3650
Wire Wire Line
	7050 3400 7050 3750
Wire Wire Line
	7050 4150 7050 4250
Wire Wire Line
	7650 3300 7650 3750
Wire Wire Line
	7650 4150 7650 4250
Wire Wire Line
	7500 3650 7650 3650
Wire Wire Line
	6450 3300 7650 3300
Wire Wire Line
	6450 3400 6550 3400
Wire Wire Line
	11550 9850 11550 10200
Wire Wire Line
	7800 10150 7800 10250
Wire Wire Line
	11250 9100 12750 9100
Wire Wire Line
	10550 9550 10550 9100
Connection ~ 10550 9100
Wire Wire Line
	10050 9550 10050 9100
Connection ~ 10050 9100
Wire Wire Line
	9450 9600 9450 9100
Connection ~ 9450 9100
Wire Wire Line
	10500 9100 10850 9100
Wire Wire Line
	11550 10700 11550 10850
Wire Wire Line
	11550 9000 11550 9350
Connection ~ 11550 9100
Wire Wire Line
	10700 10100 11550 10100
Connection ~ 11550 10100
Connection ~ 12100 9100
Wire Wire Line
	9550 10100 9900 10100
Wire Wire Line
	6650 2800 6450 2800
Wire Wire Line
	9300 9100 10100 9100
Wire Wire Line
	9450 10600 9450 10000
Wire Wire Line
	10300 10600 10300 10250
Wire Wire Line
	12100 10250 12100 9900
Wire Wire Line
	12100 9500 12100 9100
Wire Wire Line
	12500 9100 12500 9500
Connection ~ 12500 9100
Wire Wire Line
	12500 10250 12500 9900
Wire Wire Line
	13500 2900 13350 2900
Wire Wire Line
	13350 2900 13350 3950
Wire Wire Line
	13700 3050 13700 3200
Wire Wire Line
	13700 2400 13700 2550
Wire Wire Line
	14100 2800 14550 2800
Wire Wire Line
	13350 3300 14200 3300
Wire Wire Line
	14200 3300 14200 3100
Wire Wire Line
	14200 3100 14800 3100
Connection ~ 14800 3100
Wire Wire Line
	14800 3700 14800 4200
Wire Wire Line
	14800 2250 14800 2650
Wire Wire Line
	13050 1950 13050 2150
Wire Wire Line
	13050 2650 13050 2750
Wire Wire Line
	13050 2700 13500 2700
Connection ~ 13050 2700
Wire Wire Line
	13050 3250 13050 3300
Connection ~ 13050 2100
Wire Wire Line
	14300 2800 14300 2750
Connection ~ 14300 2800
Wire Wire Line
	12700 2600 12700 2750
Wire Wire Line
	12700 3150 12700 3300
Wire Wire Line
	14800 1800 14800 2050
Wire Wire Line
	14800 1150 14800 1300
Wire Wire Line
	6650 1700 6450 1700
Wire Wire Line
	6700 1500 6450 1500
Wire Wire Line
	14050 4850 14450 4850
Wire Wire Line
	13350 4150 13350 4850
Wire Wire Line
	12600 4850 13550 4850
Wire Wire Line
	11900 3950 11900 4850
Wire Wire Line
	11900 4850 12100 4850
Connection ~ 13350 4850
Wire Wire Line
	13350 3950 13100 3950
Connection ~ 13350 3300
Connection ~ 11900 4050
Wire Wire Line
	13100 4150 13350 4150
Wire Wire Line
	12900 4500 12900 4300
Wire Wire Line
	12900 3800 12900 3600
Wire Wire Line
	12500 4050 11550 4050
Wire Wire Line
	12700 2100 13050 2100
Wire Wire Line
	6250 5500 6150 5500
Wire Wire Line
	6150 5850 6250 5850
Connection ~ 6250 5850
Wire Wire Line
	5550 5500 5200 5500
Wire Wire Line
	5550 5850 5200 5850
Connection ~ 6250 6200
Wire Wire Line
	3350 1700 3800 1700
Wire Wire Line
	3350 1800 3800 1800
Wire Wire Line
	3350 1900 3800 1900
Wire Wire Line
	3350 2000 3800 2000
Wire Wire Line
	3350 2100 3800 2100
Wire Wire Line
	4850 3950 4850 4100
Wire Wire Line
	4850 4100 5300 4100
Wire Wire Line
	5300 4100 5300 3950
Wire Wire Line
	5150 3950 5150 4100
Connection ~ 5150 4100
Wire Wire Line
	5050 3950 5050 4300
Connection ~ 5050 4100
Wire Wire Line
	4950 3950 4950 4100
Connection ~ 4950 4100
NoConn ~ 6450 1400
NoConn ~ 6450 1800
NoConn ~ 6450 1600
NoConn ~ 6450 1900
NoConn ~ 6450 2000
NoConn ~ 6450 2950
NoConn ~ 6450 3050
NoConn ~ 3800 1300
NoConn ~ 3800 1400
NoConn ~ 3800 1500
NoConn ~ 3800 2200
NoConn ~ 3800 2800
NoConn ~ 6450 3200
$Comp
L PWR_FLAG #FLG1
U 1 1 5290A99F
P 11550 9000
F 0 "#FLG1" H 11550 9270 30  0001 C CNN
F 1 "PWR_FLAG" H 11550 9230 30  0000 C CNN
F 2 "" H 11550 9000 60  0000 C CNN
F 3 "" H 11550 9000 60  0000 C CNN
	1    11550 9000
	1    0    0    -1  
$EndComp
Text Label 10600 9100 0    60   ~ 0
Lout12
$Comp
L HOLE_METALLED HOLE1
U 1 1 5290BE09
P 12800 6700
F 0 "HOLE1" H 12300 6650 60  0000 C CNN
F 1 "HOLE_METALLED" H 12250 6750 60  0000 C CNN
F 2 "" H 12800 6700 60  0000 C CNN
F 3 "" H 12800 6700 60  0000 C CNN
	1    12800 6700
	1    0    0    -1  
$EndComp
$Comp
L HOLE_METALLED HOLE2
U 1 1 5290BE0F
P 12800 6950
F 0 "HOLE2" H 12300 6900 60  0000 C CNN
F 1 "HOLE_METALLED" H 12250 7000 60  0000 C CNN
F 2 "" H 12800 6950 60  0000 C CNN
F 3 "" H 12800 6950 60  0000 C CNN
	1    12800 6950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR29
U 1 1 5290BE15
P 13150 7050
F 0 "#PWR29" H 13240 7030 30  0001 C CNN
F 1 "GND" H 13150 6970 30  0001 C CNN
F 2 "" H 13150 7050 60  0000 C CNN
F 3 "" H 13150 7050 60  0000 C CNN
	1    13150 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	13100 6700 13150 6700
Connection ~ 13150 6700
Wire Wire Line
	13100 6950 13150 6950
Connection ~ 13150 6950
Wire Wire Line
	13150 6700 13150 7050
Wire Wire Line
	3800 3500 3700 3500
Wire Wire Line
	3700 3500 3700 3350
Connection ~ 3700 3350
$Comp
L TESTPOINT TP3
U 1 1 52A81664
P 11900 3950
F 0 "TP3" H 11900 4100 60  0000 C CNN
F 1 "TESTPOINT" H 11875 4175 60  0001 C CNN
F 2 "" H 11900 3950 60  0000 C CNN
F 3 "" H 11900 3950 60  0000 C CNN
	1    11900 3950
	1    0    0    -1  
$EndComp
$Comp
L CRYSTAL XTAL1
U 1 1 52A81997
P 7350 3650
F 0 "XTAL1" H 7350 3925 60  0000 C CNN
F 1 "32768" H 7375 3850 60  0000 C CNN
F 2 "CRYSTAL" H 7375 3775 39  0000 C CNN
F 3 "~" H 7350 3650 60  0000 C CNN
	1    7350 3650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR12
U 1 1 5149A441
P 2950 3650
F 0 "#PWR12" H 2950 3610 30  0001 C CNN
F 1 "+3.3V" H 3030 3680 30  0000 C CNN
F 2 "" H 2950 3650 60  0001 C CNN
F 3 "" H 2950 3650 60  0001 C CNN
	1    2950 3650
	-1   0    0    1   
$EndComp
$Comp
L L L3
U 1 1 52A81A10
P 3200 3650
F 0 "L3" V 3100 3510 40  0000 C CNN
F 1 "10uH" V 3100 3650 40  0000 C CNN
F 2 "IND_0805" V 3260 3660 40  0000 C CNN
F 3 "~" H 3200 3650 60  0000 C CNN
	1    3200 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	2950 3650 3000 3650
Text Notes 11700 2950 0    60   ~ 0
R9: 1k -> 4.7k
$Comp
L 2N7002 Q2
U 1 1 52C57941
P 14750 2850
F 0 "Q2" H 14950 2900 60  0000 C CNN
F 1 "2N7002" H 15100 2800 60  0000 C CNN
F 2 "" H 14750 2850 60  0000 C CNN
F 3 "" H 14750 2850 60  0000 C CNN
	1    14750 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	14800 3200 14800 3050
Text Notes 15250 2550 0    60   ~ 0
BC848 replaced\nwith 2N7002 to\neliminate B-E\ncurrent
Text Notes 12100 5050 0    60   ~ 0
R7: 6.5k -> 6.8k
Text Notes 12800 9700 0    60   ~ 0
C16: Do not mount 
$EndSCHEMATC