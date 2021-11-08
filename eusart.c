/*
 * File:   eusart.c
 * Author: curtaeletronica
 *
 * Created on 2 de Outubro de 2019, 20:25
 * 
 * Objetivo: 
 *      Camada de Abstra��o de Hardware:
 *          Interface de comunica��o Serial EUSART
 *          EUSART = Enhanced Universal Synchronous Asynchronous Receiver Transmitter
 *                   Transmissor Receptor Ass�ncrono S�ncrono Universal Aprimorado
 * 
 * Pinos    |n�     |Conex�o
 *  RC6     |25     | TX
 *  RC7     |26     | RX
 * 
 */


//***************** Bibliotecas
#include <xc.h>
#include "config.h"
#include "delay.h"
#include "eusart.h"

struct eusartT eusart = { rxEUSART, rxStatusEUSART , rxErrorEUSART , rxResetErrorEUSART , txEUSART , txStatusEUSART , initEUSART, search};

//***************** Structs
typedef union 
{
    struct 
    {
        unsigned char LO;
        unsigned char HI;
    };
    struct
    {
        unsigned int u16;
    };
} SPBRbits_t;
extern volatile SPBRbits_t SPBRbits __at(0x099);



/****************** Fun��o rxEUSART
 * Entrada: -
 * Retorno: Dado.
 * Objetivo: Ler o valor recebido pelo canal de comunica��o serial.
 */
unsigned char rxEUSART( void )
{
    return( RCREG );
}


/****************** Fun��o rxStatusEUSART
 * Entrada: -
 * Retorno: 0 = dado n�o recebido.
 *          1 = dado recebido.
 * Objetivo: Verificar se algum dado foi recebido pelo canal de comunica��o.
 */
unsigned char rxStatusEUSART( void )
{
    return( PIR1bits.RCIF );
}


/****************** Fun��o rxErrorEUSART
 * Entrada: -
 * Retorno: 0 = sem erro.
 *          1 = Framing Error: Erro no pacote de dados.
 *          2 = Overrun Error: Dado recebido de forma sobreposta, ou seraming Error: Erro no pacote de dados.ja,
 *              um dado chegou antes do anterior ser lido.
 * Objetivo: Verificar se houve erro na recep��o de dados.
 */
unsigned char rxErrorEUSART( void )
{
    if( RCSTAbits.FERR )
        return( 1 );
    else if( RCSTAbits.OERR )
        return( 2 );
    else 
        return( 0 );
}


/****************** Procedimento rxResetErrorEUSART
 * Entrada: -
 * Retorno: -
 * Objetivo: Reinicializar/limpar os indicadores(flags) de erro.
 */
void rxResetErrorEUSART( void )
{
    if( RCSTAbits.FERR )
    {
        RCSTAbits.SPEN = 0;
        __delay_ms(100);
        RCSTAbits.SPEN = 1;
    }
    if( RCSTAbits.OERR )
    {
        RCSTAbits.CREN = 0;
        __delay_ms(100);
        RCSTAbits.CREN = 1;
    }
}



/****************** Procedimento txEUSART
 * Entrada: dado.
 * Retorno: -
 * Objetivo: Transmitir um dado pelo canal de comunica��o serial.
 */
void txEUSART( unsigned char d )
{
    TXREG = d;
}


/****************** Fun��o txEUSART
 * Entrada: -
 * Retorno: Indica��o de dado em transmiss�o.
 * Objetivo: Indicar que um dado est� sendo transmitido.
 */
unsigned char txStatusEUSART( void )
{
    return( !TXSTAbits.TRMT );
}


/****************** Procedimento initEUSAR
 * Entrada: -
 * Retorno: -
 * Objetivo: Inicializar perif�rico de comunica��o serial ass�ncrona.
 */
void initEUSART( unsigned long baudRate )
{
    INTCONbits.GIE = 0;
                            // Calcula valor para registradores que produzem
                            // a taxa de transmiss�o (Baud rate) de dados desejada.
    SPBRbits.u16 = (unsigned int)( (_XTAL_FREQ / (baudRate<<2)) - 1);

   // SPBRbits.u16 = baudRate;
    
    TXSTAbits.SYNC = 0;     // Modo ass�ncrono.
    BAUDCTLbits.BRG16 = 1;  // Gerador de BaudRate de 16 bits.
    TXSTAbits.BRGH = 1;     // Sele��o de alto BaudRate.
    
    RCSTAbits.SPEN = 1;     // Habilita pinos para TX e RX.
    TXSTAbits.TXEN = 1;     // Inicia transmiss�o.
    RCSTAbits.CREN = 1;     // Habilita recep��o.

    PIE1bits.RCIE = 1;
    PIE1bits.TXIE = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

int search (const char * x, const char * y)
{
    unsigned char contem = 0;
    unsigned char f;
    const char * aux;
    aux = y;
    do
    { f = *x++;
        if( f== *aux)
        {
           contem = 1;
           ++aux;
        }
        else if (contem)
        {
            aux = y;
            contem = 0;
        }
        if(!*aux)
        {
            contem = 1;
            break;
        }
    } 

    while(f);
    return(contem );
}    
