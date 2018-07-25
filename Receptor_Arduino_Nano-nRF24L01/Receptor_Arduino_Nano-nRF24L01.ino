  /*      Codigo para el receptor
 *       Arduino NANO
 *       Pierre C.J.
 *       correo:nuoor.market@gmail.com
 *       @nuoortechnology
*/


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// en nuestro caso tenemos el "ce" conectado en la entrada 8  y "csn" en la entrada 9 
//del arduino pero si las colocaste en otras entradas solo debes cambiar los valores

RF24 radio(10, 9); // (ce , csn)
const byte direccion[6] = "00001";

byte led1=5;
byte led2=6;
byte led3=7;
byte led4=8;

int valor_ejey=0;
int valor_ejex=0;

struct Lectura {
  int ejeY;
  int ejeX;
};

Lectura a ;

void setup() {

  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(0,direccion);
  radio.startListening();
}

void loop(){
   while ( radio.available() ) {
   radio.read(&a, sizeof(Lectura));
   
   valor_ejey=a.ejeY;
   valor_ejex=a.ejeX;
   
   Serial.print("Valor en el eje Y : ");
   Serial.println(valor_ejey);
   Serial.print("Valor en el eje X : ");
   Serial.println(valor_ejex);

   if (valor_ejey>220 && valor_ejex<130 && valor_ejex>100){
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
   
   }
    if (valor_ejey<35 && valor_ejex<130 && valor_ejex>100){
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
     
   }   
   if (valor_ejex>220 && valor_ejey<130 &&valor_ejey>100){
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,LOW);
   }
   if (valor_ejex<35 && valor_ejey<130 && valor_ejey>100){
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,HIGH);
     
    }
   }
}


