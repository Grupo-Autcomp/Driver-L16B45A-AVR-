/*
 * File:   newmain.c
 * Author: BEV
 *
 * Created on 24 de Março de 2022, 11:24
 */


#include <xc.h>
#define F_CPU 4000000UL
#include <util/delay.h>


int mensagem(uint8_t data){
    
    //Ativar LE quando for receber mensagem (Low)
    //Desativar LE quando acabar (high) (ele lançará a mensagem)
    SPI0.DATA = data;

    while (!(SPI0.INTFLAGS & SPI_IF_bm))  /* waits until data is exchanged*/
    {
        if (SPI0.INTFLAGS & SPI_TXCIF_bm)
            PORTC.OUT &= 0x00; //ACENDENDO LED PARA TESTE
    }
    if (SPI0.INTFLAGS & SPI_TXCIF_bm)
        PORTC.OUT &= 0x00; //ACENDENDO LED PARA TESTE
    
    
    return SPI0.DATA;
}

int main(void) {
    
    uint8_t i = 0;
    
    do{
        i++;
        mensagem(i);
        _delay_ms(10000);
    }while(1);
    
    
    return 0;
}
