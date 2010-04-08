
// prototypes
void LEDKeyInit (void);

// Constants
#define LED_PORT    PORTC
#define LED_DDR     DDRC
#define LED_GREEN   PC7
#define LED_RED     PC6

//#define BTN_PORT    PORTD
//#define BTN_PIN     PIND
//#define BTN_DDR     DDRD
//#define BTN2        PD6
//#define BTN1        PD7

// Pseudo functions
#define LED_RED_ON( )       LED_PORT |=  (1<<LED_RED)
#define LED_RED_OFF( )      LED_PORT &= ~(1<<LED_RED)
#define LED_RED_TOGGLE( )   LED_PORT ^=  (1<<LED_RED)

#define LED_GREEN_ON( )     LED_PORT |=  (1<<LED_GREEN)
#define LED_GREEN_OFF( )    LED_PORT &= ~(1<<LED_GREEN)
#define LED_GREEN_TOGGLE( ) LED_PORT ^=  (1<<LED_GREEN)

//#define BTN2_IS_DOWN( ) bit_is_clear (BTN_PIN, BTN2)
//#define BTN1_IS_DOWN( ) bit_is_clear (BTN_PIN, BTN1)