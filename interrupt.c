/*
 * File:   interrupt.c
 * Author: 20190224
 *
 * Created on 30 de Setembro de 2021, 14:22
 */


#include <xc.h>

#include "adc.h"


void __interrupt() isr(void)
{
    if( PIR1bits.ADIF )
    {
        PIR1bits.ADIF = 0;
        ADC_int();
    }
}

