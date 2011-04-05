#include "mdl_inputs.h"
#include "delay_util.h"

Inputs_t Inputs;

void Inputs_t::Init(void) {
    
}

void Inputs_t::Check() {
    if (!Delay.Elapsed(&Timer, DELAY_CHECK)) return;
}