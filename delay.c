/*
 * File:   delay.c
 * Author: 20190224
 *
 * Created on 30 de Setembro de 2021, 14:20
 */


#include "config.h"
#include <xc.h>

void delay (unsigned int t)
{
    while( t )
    {
        --t;
        __delay_ms(1);
    }
}

