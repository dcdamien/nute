// ======================== Lume IO unit ==========================
#include "LumeIO.h"

// ======================= Implementation =========================
void MinuteSwitch (const uint8_t AMin, const uint8_t AOn) {
	if (!AMin) return;
	switch (AMin) {
		case  1:	if (AOn) m01PORT &= ~(1<<m01P); else m01PORT |= (1<<m01P); break;
		case  2:	if (AOn) m02PORT &= ~(1<<m02P); else m02PORT |= (1<<m02P); break;
		case  3:	if (AOn) m03PORT &= ~(1<<m03P); else m03PORT |= (1<<m03P); break;
		case  4:	if (AOn) m04PORT &= ~(1<<m04P); else m04PORT |= (1<<m04P); break;
		case  5:	if (AOn) m05PORT &= ~(1<<m05P); else m05PORT |= (1<<m05P); break;
		case  6:	if (AOn) m06PORT &= ~(1<<m06P); else m06PORT |= (1<<m06P); break;
		case  7:	if (AOn) m07PORT &= ~(1<<m07P); else m07PORT |= (1<<m07P); break;
		case  8:	if (AOn) m08PORT &= ~(1<<m08P); else m08PORT |= (1<<m08P); break;
		case  9:	if (AOn) m09PORT &= ~(1<<m09P); else m09PORT |= (1<<m09P); break;
		case 10:	if (AOn) m10PORT &= ~(1<<m10P); else m10PORT |= (1<<m10P); break;
		case 11:	if (AOn) m11PORT &= ~(1<<m11P); else m11PORT |= (1<<m11P); break;
		case 12:	if (AOn) m12PORT &= ~(1<<m12P); else m12PORT |= (1<<m12P); break;
	}
}

void HourSwitch (const uint8_t AHour, const uint8_t AOn) { 
	if (!AHour) return;
	switch (AHour) {
		case  1:	if (AOn) h01PORT &= ~(1<<h01P); else h01PORT |= (1<<h01P); break;
		case  2:	if (AOn) h02PORT &= ~(1<<h02P); else h02PORT |= (1<<h02P); break;
		case  3:	if (AOn) h03PORT &= ~(1<<h03P); else h03PORT |= (1<<h03P); break;
		case  4:	if (AOn) h04PORT &= ~(1<<h04P); else h04PORT |= (1<<h04P); break;
		case  5:	if (AOn) h05PORT &= ~(1<<h05P); else h05PORT |= (1<<h05P); break;
		case  6:	if (AOn) h06PORT &= ~(1<<h06P); else h06PORT |= (1<<h06P); break;
		case  7:	if (AOn) h07PORT &= ~(1<<h07P); else h07PORT |= (1<<h07P); break;
		case  8:	if (AOn) h08PORT &= ~(1<<h08P); else h08PORT |= (1<<h08P); break;
		case  9:	if (AOn) h09PORT &= ~(1<<h09P); else h09PORT |= (1<<h09P); break;
		case 10:	if (AOn) h10PORT &= ~(1<<h10P); else h10PORT |= (1<<h10P); break;
		case 11:	if (AOn) h11PORT &= ~(1<<h11P); else h11PORT |= (1<<h11P); break;
		case 12:	if (AOn) h12PORT &= ~(1<<h12P); else h12PORT |= (1<<h12P); break;
	}
}

void KeysInit (void) {
	WaitForRelease = false;
	KEY_MODE_DDR	&= ~(1<<KEY_MODE_P);
	KEY_MODE_PORT	|=  (1<<KEY_MODE_P);
	KEY_PLUS_DDR	&= ~(1<<KEY_PLUS_P);
	KEY_PLUS_PORT	|=  (1<<KEY_PLUS_P);
	KEY_MINUS_DDR	&= ~(1<<KEY_MINUS_P);
	KEY_MINUS_PORT	|=  (1<<KEY_MINUS_P);
}

void FadeAll (void) {
	h01PORT |= (1<<h01P);
	h02PORT |= (1<<h02P);
	h03PORT |= (1<<h03P);
	h04PORT |= (1<<h04P);
	h05PORT |= (1<<h05P);
	h06PORT |= (1<<h06P);
	h07PORT |= (1<<h07P);
    h08PORT |= (1<<h08P);
    h09PORT |= (1<<h09P);
    h10PORT |= (1<<h10P);
    h11PORT |= (1<<h11P);
    h12PORT |= (1<<h12P);
    
	m01PORT |= (1<<m01P);
	m02PORT |= (1<<m02P);
	m03PORT |= (1<<m03P);
	m04PORT |= (1<<m04P);
	m05PORT |= (1<<m05P);
	m06PORT |= (1<<m06P);
	m07PORT |= (1<<m07P);
	m08PORT |= (1<<m08P);
	m09PORT |= (1<<m09P);
	m10PORT |= (1<<m10P);
	m11PORT |= (1<<m11P);
    m12PORT |= (1<<m12P);
}
    