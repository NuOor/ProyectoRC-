/*      Codigo para el transimsor 
 *       Arduino UNO
 *       Pierre C.J.
 *       correo:nuoor.market@gmail.com
 *       @nuoortechnology
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// en nuestro caso tenemos el "ce" conectado en la entrada 8  y "csn" en la entrada 9 
//del arduino pero si las colocaste en otras entradas solo debes cambiar los valores

RF24 radio(8, 9); // (ce , csn)
const byte direccion[6] = "00001";//esta sera la direccion para que se puedan      
                                            //comunicar los arduinos, debe ser la misma en ambos
struct Lectura {
  int ejeY;
  int ejeX;
};

Lectura a;//damos una instancia de variable "a" y luego llamar a los miembros del struct

void setup() {
    radio.begin();
    radio.openWritingPipe(direccion);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening();
}


void loop(){
  
  a.ejeY = map(analogRead(0),0,1023,0,255);//lectura del joystick en el eje x 
  a.ejeX = map(analogRead(1),0,1023,0,255);//lectura del joystick en el eje y
  
  radio.write(&a, sizeof(Lectura));
}

