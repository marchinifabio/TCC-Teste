/* 
 * File:   fifo.h
 * Author: 21193665
 *
 * Created on 27 de Outubro de 2021, 16:42
 */

#ifndef FIFO_H
#define	FIFO_H

void fifo_inserir( unsigned char d );
unsigned char fifo_retirar( void );
unsigned char fifo_tam( void );
void fifo_init( void );

#endif

