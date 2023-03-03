/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include <xc.h>
#define F_CPU 4000000UL
#include <util/delay.h>


uint16_t i = 0x01;
uint8_t var;
uint8_t tar;
uint8_t first_time=0x01;

int mensagem(uint8_t data){
    
    //Ativar LE quando for receber mensagem (Low)
    //Desativar LE quando acabar (high) (ele lançará a mensagem)
    SPI0.DATA = data;

    while (!(SPI0.INTFLAGS & SPI_IF_bm))  //Espera mandar data
    {
        if (SPI0.INTFLAGS & SPI_TXCIF_bm)
            PORTC.OUT &= 0x00; //ACENDENDO LED PARA TESTE
    }
   /* if (SPI0.INTFLAGS & SPI_TXCIF_bm)
        PORTC.OUT &= 0x00; //ACENDENDO LED PARA TESTE*/
    
    
    return SPI0.DATA;
}

void slaveSelect(void)
{
    //PORTC.OUT |= PIN4_bm; // jogando OE' pra 1
    PORTA.OUT &= ~PIN7_bm; // Setando valor do pino SS LOW
}

void slaveDeselect(void)
{
    PORTA.OUT |= PIN7_bm; // Setando valor do pino SS HIGH
}

int main(void)
{
    
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    PORTC.OUT &= ~PIN5_bm;//jogando LE pra 0
   
    //PORTC.OUT &= ~PIN4_bm; // jogando OE' pra 0

    do{
        //i++;
        if(first_time == 0)
            i=i*2+1;
        //PORTC.OUT &= ~PIN5_bm;//jogando LE pra 0
        var = (i & 0x00ff);
        tar = (i>>8);
        slaveSelect();
        mensagem(var);
        mensagem(tar);
        slaveDeselect();
        PORTC.OUT |= PIN5_bm; //jogando LE pra 1
        PORTC.OUT &= ~PIN5_bm;//jogando LE pra 0
        /* _delay_ms(1);
        PORTC.OUT |= PIN5_bm; //jogando LE pra 1
        _delay_ms(1);
        PORTC.OUT &= ~PIN5_bm;//jogando LE pra 0
        _delay_ms(1);
        PORTC.OUT &= ~PIN4_bm; // jogando OE' pra 0*/
        _delay_ms(150);

      
         
        if(first_time==1)
           first_time = 0;
         
        if (i == 0xffff){
            i = 0x01;
            first_time = 1;
        }

    }while(1);


     return 0;
}
/**
    End of File
*/