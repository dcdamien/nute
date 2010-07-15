// ======================== Lume IO defins ==========================
// ********** Defines ************
// Keys
#define KEY_MODE_PORT	PORTB
#define KEY_MODE_DDR	DDRB
#define KEY_MODE_PIN	PINB
#define KEY_MODE_P		PB6

#define KEY_PLUS_PORT	PORTB
#define KEY_PLUS_DDR	DDRB
#define KEY_PLUS_PIN	PINB
#define KEY_PLUS_P		PB7

#define KEY_MINUS_PORT	PORTB
#define KEY_MINUS_DDR	DDRB
#define KEY_MINUS_PIN	PINB
#define KEY_MINUS_P		PB5

// Hours
#define h01PORT	PORTA
#define h01P	PA1
#define h02PORT	PORTB
#define h02P	PB1
#define h03PORT	PORTB
#define h03P	PB3
#define h04PORT	PORTD
#define h04P	PD0
#define h05PORT	PORTD
#define h05P	PD2
#define h06PORT	PORTD
#define h06P	PD5
#define h07PORT	PORTD
#define h07P	PD7
#define h08PORT	PORTC
#define h08P	PC1
#define h09PORT	PORTC
#define h09P	PC3
#define h10PORT	PORTC
#define h10P	PC5
#define h11PORT	PORTA
#define h11P	PA6
#define h12PORT	PORTA
#define h12P	PA3

// Minutes
#define m01PORT	PORTA
#define m01P	PA2
#define m02PORT	PORTB
#define m02P	PB0
#define m03PORT	PORTB
#define m03P	PB2
#define m04PORT	PORTB
#define m04P	PB4
#define m05PORT	PORTD
#define m05P	PD1
#define m06PORT	PORTD
#define m06P	PD4
#define m07PORT	PORTD
#define m07P	PD6
#define m08PORT	PORTC
#define m08P	PC0
#define m09PORT	PORTC
#define m09P	PC2
#define m10PORT	PORTC
#define m10P	PC4
#define m11PORT	PORTA
#define m11P	PA7
#define m12PORT	PORTA
#define m12P	PA5

// ===== Pseudo-functions ======
#define KEY_MODE_DOWN	bit_is_clear (KEY_MODE_PIN, KEY_MODE_P)
#define KEY_PLUS_DOWN	bit_is_clear (KEY_PLUS_PIN, KEY_PLUS_P)
#define KEY_MINUS_DOWN	bit_is_clear (KEY_MINUS_PIN, KEY_MINUS_P)


// ==== function prototypes ====
void KeysInit (void);
void MinuteSwitch (const uint8_t AMin, const uint8_t AOn);
void HourSwitch (const uint8_t AHour, const uint8_t AOn);
void FadeAll (void);

