# Controle de LED Driver por SPI

O código exemplo demonstra como se comunicar com o LED Driver L16B45 por comunicação serial.
Feito em novembro/2021

## L16B45

LED Driver low cost de 16 bits para controle de displays por SPI. 
Esse driver tem a capacidade de transmitir dados para o próximo driver através do pino SDO. O componente também possui um Schmitt trigger em sua entrada, o que permite que sejam encadeados diversos drivers seguidos.

Clique para ver o [datasheet](http://www.utc-ic.com/uploadfile/2015/1126/20151126031436921.pdf). 

## O código

O código está em um loop onde liga uma saída por vez (OUT0 até OUT15) até que todas estejam ligadas e, então, reinicia ativando a saída OUT0 novamente.

Clique para o [datasheet do AVR128DA48](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/AVR128DA28-32-48-64-Data-Sheet-40002183C.pdf)
