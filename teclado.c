/*
 * File:   teclado.c
 * Author: 20190224
 *
 * Created on 30 de Setembro de 2021, 14:23
 */


#include "lcd.h"
#include "config.h"
#include <xc.h>

#define L0 PORTBbits.RB0 
#define L1 PORTBbits.RB1
#define L2 PORTBbits.RB2 
#define L3 PORTBbits.RB3
#define C0 PORTBbits.RB4 
#define C1 PORTBbits.RB5
#define C2 PORTBbits.RB6
#define C3 PORTBbits.RB7
#define MASK 0x10

char tabela[4][4] = {{'1', '2' , '3' , 'A'},
                     {'4', '5' , '6' , 'B'},
                     {'7', '8' , '9' , 'C'},
                     {'*', '0' , '#' , 'D'}};

void teclado_init( void )
{
    ANSELH = 0;
    TRISB = 0xF0;
    PORTB = 0x00;
}

char teclado (void)
{
    char tecla = 0;
    char col, lin;
    
    for(lin=0; lin<4; lin++) //linha
    {    
        PORTB = 0x01<<lin;
        for(col=0; col<4; col++) 
        { 
            if(PORTB & MASK<<col) 
                tecla = tabela[lin][col];
        }
    }
    
    return(tecla);     
}
