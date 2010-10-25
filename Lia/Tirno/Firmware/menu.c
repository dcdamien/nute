#include "menu.h"
#include "lcd110x.h"
#include "tirno.h"
#include <util/delay.h>
#include <avr/pgmspace.h>

// =============================== Defines =====================================
#define LIST_INDENT     12  // Indent of list

#define OPTIONS_COUNT   2
#define OPTIONS_TOP     2

// ============================= Global variables ==============================
prog_char Option0[] = "Переименовать";
prog_char Option1[] = "Состыковать  ";
prog_char *EOptions[] = {Option0, Option1};

uint8_t EIndx;
uint8_t CharIndx;   // Indx of choosen Char in string edited
enum State_t EState;

// ========================== Implementation ===================================
// ============================ States =========================================
void SetState(enum State_t AState) {
    LCD_Clear();
    EState = AState;
    switch(AState) {
        case StateList:
            DisplayList(0); // Display list of lockets
            break;

        case StateSearch:
            LCD_PrintString(0, 0, EL.L[EL.Indx].S, false);  // Print current locket name
            LCD_PrintString_P(0, 2, PSTR("dBm:"), false);
            LCD_PrintString_P(0, 7, PSTR("Список"), true);
            LCD_DrawGauge(4);
            break;

        case StateOptions:
            LCD_PrintString(0, 0, EL.L[EL.Indx].S, false);  // Print current locket name
            // Display pseudo-buttons
            LCD_PrintString_P(0,  7, PSTR("  Ok  "), true);
            LCD_PrintString_P(60, 7, PSTR("Отмена"), true);
            // Display options
            LCD_PrintString_P(0, OPTIONS_TOP,   EOptions[0], true);
            LCD_PrintString_P(0, OPTIONS_TOP+1, EOptions[1], false);
            EIndx = 0;  // Set current temporary indx
            break;

        case StateRename_ChoosePlace:
            LCD_GotoXY(0, 0);
            // Print current locket name with first letter highlighted
            LCD_DrawChar(EL.L[EL.Indx].S[0], true);
            LCD_PrintString(6, 0, &EL.L[EL.Indx].S[1], false);  

            // Display pseudo-buttons
            LCD_PrintString_P(0,  7, PSTR("Изменить"), true);
            LCD_PrintString_P(60, 7, PSTR("Готово"), true);
            EIndx = 0;
            CharIndx = 0;
            break;

        default: break;
    } // switch
}

// ============================== Events =======================================
void EVENT_KeyUp(void) {
    uint8_t FPlace;
    switch(EState) {
        case StateList: // Move down by the list
            if(EL.Indx > 0) EL.Indx--;
            if(EL.Indx < EL.TopIndx) {    // Top of screen, draw previous items
                LCD_Clear();
                DisplayList(EL.Indx-6);
            }
            else {
                LCD_PrintString(LIST_INDENT, (EL.Indx - EL.TopIndx +1), EL.L[EL.Indx+1].S, false);   // Unhighlight previous element
                LCD_PrintString(LIST_INDENT,  EL.Indx - EL.TopIndx    , EL.L[EL.Indx  ].S, true);    // Highlight current element
            }
            break;

        case StateOptions:  // Move down by the list
            if(EIndx > 0) EIndx--;
            LCD_PrintString_P(0, (OPTIONS_TOP + EIndx+1), EOptions[EIndx+1], false);  // Unhighlight previous element
            LCD_PrintString_P(0, (OPTIONS_TOP + EIndx  ), EOptions[EIndx  ], true);   // Highlight current element
            break;

        case StateRename_ChoosePlace:
            if(CharIndx > 0) {
                CharIndx--;
                FPlace = (CharIndx << 1) + (CharIndx << 2); // 6*a == 4*a + 2*a
                LCD_GotoXY(FPlace, 0);
                LCD_DrawChar(EL.L[EL.Indx].S[CharIndx], true);  // Highlight current char
                LCD_DrawChar(EL.L[EL.Indx].S[CharIndx+1], false); // Unhighlight previous char
            }
            break;

        default: break;
    } // switch
}
void EVENT_KeyDown(void) {
    uint8_t FPlace;
    switch(EState) {
        case StateList: // Move down by the list
            if(EL.Indx < LOCKET_COUNT-1) EL.Indx++;
            // Handle more than 7 lockets
            if(EL.Indx > (EL.TopIndx + 6)) {    // Bottom of screen, draw next items
                LCD_Clear();
                DisplayList(EL.Indx);
            }
            else {
                LCD_PrintString(LIST_INDENT, (EL.Indx - EL.TopIndx - 1), EL.L[EL.Indx-1].S, false);  // Unhighlight previous element
                LCD_PrintString(LIST_INDENT,  EL.Indx - EL.TopIndx     , EL.L[EL.Indx  ].S, true);   // Highlight current element
            }
            break;

        case StateOptions:  // Move down by the list
            if(EIndx < OPTIONS_COUNT-1) EIndx++;
            LCD_PrintString_P(0, (OPTIONS_TOP + EIndx-1), EOptions[EIndx-1], false);  // Unhighlight previous element
            LCD_PrintString_P(0, (OPTIONS_TOP + EIndx  ), EOptions[EIndx  ], true);   // Highlight current element
            break;

        case StateRename_ChoosePlace:
            if(CharIndx < LOCKET_NAME_L-1) {
                FPlace = (CharIndx << 1) + (CharIndx << 2); // 6*a == 4*a + 2*a
                LCD_GotoXY(FPlace, 0);
                LCD_DrawChar(EL.L[EL.Indx].S[CharIndx], false); // Unhighlight previous char
                CharIndx++;
                LCD_DrawChar(EL.L[EL.Indx].S[CharIndx], true); // Highlight current char
            }
            break;

        default: break;
    } // switch
}
void EVENT_KeyLeft(void) {
    switch(EState) {
        case StateList:
            // Blink button
            LCD_PrintString_P(0, 7, PSTR("     "), false);
            _delay_ms(150);
            LCD_PrintString_P(0, 7, PSTR("Поиск"), true);
            _delay_ms(200);
            SetState(StateSearch);
            break;

        case StateSearch:
            // Blink button
            LCD_PrintString_P(0, 7, PSTR("      "), false);
            _delay_ms(150);
            LCD_PrintString_P(0, 7, PSTR("Список"), true);
            _delay_ms(200);
            SetState(StateList);
            break;

        case StateOptions:
            // Blink button
            LCD_PrintString_P(0, 7, PSTR("      "), false);
            _delay_ms(150);
            LCD_PrintString_P(0, 7, PSTR("  Ok  "), true);
            _delay_ms(200);
            // Set state depending on option
            if(EIndx == 0) SetState(StateRename_ChoosePlace);
            else           SetState(StatePair);
            break;

        case StateRename_ChoosePlace:
            // Blink button
            LCD_PrintString_P(0, 7, PSTR("        "), false);
            _delay_ms(150);
            LCD_PrintString_P(0, 7, PSTR("Выбрать"), true);
            EState = StateRename_ChooseLetter;
            // Get choosen letter
            uint8_t Choosen = EL.L[EL.Indx].S[CharIndx];
            if((Choosen >= 'A') && (Choosen <= 'Z')) Choosen += 'a'-'A';    // Change to uppercase
            if((Choosen >= 'А') && (Choosen <= 'Я')) Choosen += 'а'-'А';    // Change to uppercase
            // Display alphabet
            LCD_GotoXY(0, 1);
            for(uint16_t c='а'; c<='р'; c++) LCD_DrawChar(c, (c == Choosen));
            LCD_GotoXY(0, 2);
            for(uint16_t c='с'; c<='я'; c++) LCD_DrawChar(c, (c == Choosen));
            LCD_GotoXY(0, 3);
            for(uint8_t c='a'; c<='r'; c++) LCD_DrawChar(c, (c == Choosen));
            LCD_GotoXY(0, 4);
            for(uint8_t c='s'; c<='z'; c++) LCD_DrawChar(c, (c == Choosen));
            LCD_GotoXY(0, 5);
            for(uint8_t c='('; c<='9'; c++) LCD_DrawChar(c, (c == Choosen));
            break;

        case StateRename_ChooseLetter:  // Choice done
            // Blink button
            LCD_PrintString_P(0, 7, PSTR("        "), false);
            _delay_ms(150);
            LCD_PrintString_P(0, 7, PSTR("Изменить"), true);
            EState = StateRename_ChoosePlace;
            // Get selected letter



            break;
        default: break;
    } // switch
}
void EVENT_KeyRight(void) {
    switch(EState) {
        case StateList:
            // Blink button
            LCD_PrintString_P(66, 7, PSTR("     "), false);
            _delay_ms(150);
            LCD_PrintString_P(66, 7, PSTR("Опции"), true);
            _delay_ms(200);
            // Display current item options
            SetState(StateOptions);
            break;
        case StateOptions:
            // Blink button
            LCD_PrintString_P(60, 7, PSTR("      "), false);
            _delay_ms(150);
            LCD_PrintString_P(60, 7, PSTR("Отмена"), true);
            _delay_ms(200);
            // Return to list
            SetState(StateList);
            break;

        case StateRename_ChoosePlace:
            // Blink button
            LCD_PrintString_P(60, 7, PSTR("      "), false);
            _delay_ms(150);
            LCD_PrintString_P(60, 7, PSTR("Готово"), true);
            _delay_ms(200);
            // Return to list
            SetState(StateList);
            break;

        default: break;
    } // switch
}

// ============================= Inner use =====================================
void DisplayList(uint8_t StartElement) {
    uint8_t i = StartElement;
    EL.TopIndx = StartElement;
    for(uint8_t y=0; y<LCD_STR_HEIGHT-1; y++) { // -1, because we need place for menu
        if(i >= LOCKET_COUNT) break;
        LCD_PrintUint(0, y, i+1);
        LCD_PrintString(LIST_INDENT, y, EL.L[i].S, (i==EL.Indx));
        i++;
    }
    // Display pseudo-buttons
    LCD_PrintString_P(0, 7, PSTR("Поиск"), true);
    LCD_PrintString_P(66, 7, PSTR("Опции"), true);
}
