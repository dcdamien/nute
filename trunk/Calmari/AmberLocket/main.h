// ******************* Includes ************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdbool.h>

// Types
enum Mode_t {Up, Down};

struct Chnl_t {
    uint8_t PWM;
    enum Mode_t Mode;
    uint16_t Timer, Delay;
    volatile uint8_t *FOCR;
};

// ************** Functions prototypes *****************
void GeneralInit(void);
void HandleCh(struct Chnl_t* ACh);

// ******************* Constants ***********************
#define START1  0
#define START2  128

// Timings
#define QuickDelay   7
#define SlowDelay    27
#define StepOver     40
