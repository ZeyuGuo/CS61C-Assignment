#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "lfsr.h"

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    return (x >> n) & 0x00000001;
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns 
    // 0 or 1)
    return -1;
}

void lfsr_calculate(uint16_t *reg) {
    /* YOUR CODE HERE */
    unsigned MSB = get_bit(*reg, 0) ^ get_bit(*reg, 2) ^ get_bit(*reg, 3) ^ get_bit(*reg, 5);
    *reg = *reg >> 1;
    *reg = (*reg & ~(1 << 15)) | (MSB << 15);
}


