/*
 * File:   main.c
 * Author: 20190224
 *
 * Created on 30 de Setembro de 2021, 14:24
 */


#include "config.h"
#include <xc.h>
#include "delay.h"
#include "lcd.h"
#include "teclado.h"
#include "sensor.h"
#include "ihm.h"
#include "adc.h"
#include "eusart.h"
#include "fifo.h"

void main(void) 
{
    char estado = 0;
    char tecla;
    dispLCD_init();
    teclado_init();
    initEUSART(115200);
    
    struct SensorTemperatura_t sensor;
    sensor_init(-50,150);
    
    while( 1 )
    {
        if( rxStatusEUSART() )
        {
            tecla = rxEUSART();
            txEUSART(tecla);
        }
    }
    
    /*while (1)
    {        
        tecla = teclado();
        
        switch( estado )
        {        
            case 0: estado = 1;
                    break;
                        
            case 1: dispLCD(0,0,"  Temperatura    ");
                    delay(2000);
                    dispLCD_clr();
                    estado = 10;
                    break;
                    
            case 10: dispLCD(0,0," Temperatura max ");    
                     delay(2000);
                     dispLCD_clr();
                     estado = 15;
                     break;
                     
            case 15: dispLCD(0,0,"1:Inst   C:Manut");  
                     
                     dispLCD(1,0,"Temp:     C        ");
                     temperatura( &sensor );
                     dispLCD_num(1, 6, sensor.temp_C, 4 );
                     estado = 16;
                     break;
                     
            case 16: dispLCD_num(1, 6, sensor.temp_C, 4 );
                     if(sensor.temp_C > 100)
                     {
                         dispLCD_clr();
                         dispLCD(0, 0, "     ALERTA     ");
                         dispLCD(1, 0, "TEMPERATURA ALTA");
                         estado = 17;                 
                     }
            
                     if(sensor.temp_C < 20 )
                     {
                         dispLCD_clr();
                         dispLCD(0, 0, "     ALERTA     ");
                         dispLCD(1, 0, "TEMPERATURA BAIX");
                         estado = 18;                 
                     }
            
                     if(tecla == '1')
                     {  
                         dispLCD_clr();
                         estado = 20;
                     }    
                     if(tecla == 'C')
                     {    
                         dispLCD_clr();
                         estado = 100;
                     } 
                     break;        
                     
            case 17: temperatura( &sensor );
                     if(sensor.temp_C < 100)
                     {    
                         dispLCD_clr(); 
                         estado = 15;
                     }    
                     break;    
                     
            case 18: temperatura( &sensor );
                     if(sensor.temp_C > 20)
                     {   
                         dispLCD_clr(); 
                         estado = 15;
                     }    
                     break;          
                     
            case 20: dispLCD(0,0,"   Instalacao   ");
                     if(tecla == '*')
                     {    
                         dispLCD_clr();
                         estado = 15;
                     }    
                     break;
                     
            case 100:dispLCD(0,0,"   Manutencao   ");
                     if(tecla == '*')
                         estado = 15;
                     break;                                  
        }    
        
        temperatura( &sensor );
            
    }    
    
    
    
    return;
}*/

/*void main(void) 
{
    char str[] = "Tecla:         ";
    dispLCD_init();
    teclado_init();
    
    
    while(1)
    {
        
        str[9] = teclado();
        
        if(str[9] == 0)
           str[9] = ' ';    
        
        dispLCD(0,0, " WELCOME JUNGLE " );
        dispLCD(1,0,str);
    }*/
}

