/* CAN Rx */
#define F_CPU (4000000L)
#include <avr/io.h>
#include <util/delay.h>
#include "can_api.h"

ISR(CAN_INT_vect)
{
    // Reset CANPAGE (A necessary step; don't worry about it
    CANPAGE = 0x00;
    uint8_t msg = CANMSG;

    if (msg == 0x11){
      PORTB ^= _BV(PB7);
      _delay_ms(200);
      PORTB ^= _BV(PB7);
      //PORTB &= ~_BV(PB6);
    }
    // msg now contains the first byte of the CAN message.
    // Repeat this call to receive the other bytes.

    // Set the chip to wait for another message.
    CAN_Rx(0, IDT_GLOBAL, IDT_GLOBAL_L, IDM_single);
}

int main (void) {
    // Initialize CAN
    DDRB |= _BV(PB7);
    DDRD |= _BV(PD0);
    CAN_init(0, 0);

    // Tell the CAN system to wait for a message.
    CAN_Rx(0, IDT_GLOBAL, IDT_GLOBAL_L, IDM_single);

    while(1) {
      PORTD ^= _BV(PD0);
      _delay_ms(500);
      PORTD ^= _BV(PD0);
      _delay_ms(500);
        // Wait indefinitely for a message to come.
    }
}
