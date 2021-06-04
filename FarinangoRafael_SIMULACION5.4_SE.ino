/*
 *CAPITULO V: FUNCIONES ESPECIFICAS
 *CODIGO 22: CAMBIO DE CONFIGURACION DE ARDUINO X WDT
 *OBJETIVO: CAMBIAR LA CONFIGURACION DE LA COMUNICACION SERIAL Y TIMER 2 EN UN REINICIO DE PROGRAMA(wdt, sistema de reinicio por software)
 *NOMBRE: RAFAEL FARINANGO
 *FUNCIONES: wdt_disable()  deshabilita el WDT
 *           wdt_enable()   habilita la funcion
 *           tiempos        WDTO_15MS, WDT0_500MS,.....WDT0_8S
 *           Librearia      avr/wdt.h
 *           wdt_reset()    resetea al contador
 */

#include<avr/wdt.h>     // librería wdt
#include <EEPROM.h>     // librería EEPROM
#include <MsTimer2.h>   // librería Timer2
int j;                  // varaible de cambio de configuración
void setup() {
    
    attachInterrupt(0,on,LOW);     // habilita interrupcion 0
    MsTimer2::set(9000, conteo);   // timer 2 a 9s period
    j=EEPROM.read(0);              // lectura de dato desde EEPROM
     if(j==1){                     // condición de configuración 
       MsTimer2::start();          // habilita timer
       Serial.begin(19200);        // cx serial 
        }
     else{
       Serial.begin(9600);         // cx serial a diferente velocidad
        wdt_disable();             // deshabilita wdt
        MsTimer2::stop();          // para el timer
        }
   Serial.println("INICIO");       // mensaje
}
void loop() {
  Serial.println(j);               // envía el estado de variable
  delay(200);
}
void on(){                         // interrupción
    MsTimer2::start();             // inicia Timer 2
    j=1-j;                         // cambia de estado para nuevo reset
    EEPROM.update(0,j);            // actualiza valor de variable
    if(j==0)                       // condición de config
    MsTimer2::stop();              // detiene timer
     
  }
void conteo(){                     // rutina de timer
    Serial.println("timer");       // mensaje
    if(j==1){                      // condición de funcionamiento
         wdt_enable(WDTO_1S);      // reinicio de sistema
        }
  }


//#include <avr/wdt.h>
//#include <EEPROM.h>
//#include <MsTimer2.h>
//
//int j;        //variable de cambio de config
//
//
//void setup() {
//  attachInterrupt(0, on, LOW);    //habilita la interrupt 0 (pin 2)
//  MsTimer2::set(9000, conteo);    //timer2 a 9s periodo
//  j = EEPROM.read(0);             //lectura de dato desde la eeprom
//  if(j == 1){
//    MsTimer2::start();            //habilita el timer2
//    Serial.begin(19200);          //inicia comunicacion serial
//  }
//  else{
//    Serial.begin(9600);           //comunicacion serial a dif vel
//    wdt_disable();                //deshabilita wdt
//    MsTimer2::stop();             //detiene el timer
//  }
//  Serial.println("INICIO");
//}
//
//
//void loop() {
//  Serial.println(j);              //envia el estado de la variable
//  delay(200);
//}
//
//
//void on(){                        //interrupcion
//  MsTimer2::start();              //inicia timer2
//  j = 1-j;                        //cambio de estado para nuevo reset
//  EEPROM.update(0,j);             //actualizacion de valor de variable
//  if(j == 0){
//    MsTimer2::stop();
//  }
//}
//
//
//void conteo(){
//  Serial.println("Timer");  
//  if(j == 1){
//    wdt_enable(WDTO_1S);          //reinicio del sistema
//  }
//}
