#define LED 14 // pin D1 del nodeMCU
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <LiquidCrystal_I2C.h>                         //PRIMERAMENTE INCLUIMOS LAS LIBRERIAS NECESARIAS, DEPENDIENDO DE LOS ELEMENTOS A UTILIZAR
#include <Wire.h>                                     //EN ESTE CASO UTILIZAREMOS UNA PANTALLA LCD, UN MANDO Y UN RECEPTOR INFRARROJO

LiquidCrystal_I2C lcd(0x3f, 16, 2);// si no funciona la LCD probar con 0x27, en lugar de 0x3f

unsigned long claves[21] = {0xFFA25D,0xFF629D, 0xFFE21D, 0xFF22DD, 0xFF02FD,
0xFFC23D, 0xFFE01F,0xFFA857,0xFF906F,0xFF6897, 0xFF9867, 0xFFB04F, 0xFF30CF,
0xFF18E7, 0xFF7A85, 0xFF10EF, 0xFF38C7, 0xFF5AA5, 0xFF42BD, 0xFF4AB5,0xFF52AD};

String valor[21] = {"ON/OFF", "MODE", "VolOFF", "PLAY/PAUSE", "PREV", ":",
".", "-", "+", "0", "LOOP", "U/SD", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

int RECV_PIN = 0; // pin 0 es el D3 del Node

IRrecv irrecv(RECV_PIN); // Crea objeto de ’irrecv’
decode_results results; // Crea objeto de ’decode_results’


void escribeLCD(String t) {
      lcd.clear(); // Limpia el LCD
      int n = t.length();
      
      if(t!="") {
        if(n>16){
          lcd.setCursor(0,0);
          lcd.print(t.substring(0,16));
          lcd.setCursor(0,1);
          lcd.print(t.substring(16,n));
          
          }
          else{
          lcd.setCursor(0,0); // Coloca cursor en fila 0
          lcd.print(t); // Muestra cadena
          }
        }
       else {
          lcd.setCursor(0,1); // Coloca cursor en fila 1
          lcd.print( "----Rebote--"); // Muestra mensaje rebote
      }
      delay(200); // Retardo para evitar rebote
}

String getValor(unsigned long c) {
        byte i;
        i=0;
        while( (i<21) && (claves[i]!=c) ) {
                i++;
        }
        if (i==21) return String("");
        else return String(valor[i]);
}


// Lee pulsaciones del mando hasta que se pulsa "U/SD"
String t;
String leerHastaRetorno() {
         bool b = false;
         String r="", s;
         t ="";
         while(!b) {
                 if (irrecv.decode(&results)) { // Si alguna señal
                         // Lee el código pulsado y envía a programa python
                         s = getValor(results.value);
                         t = t + s;
                         escribeLCD(t);  
                         if(s!="U/SD") {
                                  // Enviar identificador pulsado a python
                                  if(s=="LOOP") r = r + String(":");
                                  else r = r + s;
                 } else {
                         b = true; // completada cadena
                 }
                 irrecv.resume(); // Recibir el siguiente valor
                 }
                 // Necesario para evitar el problema del "Soft WDT reset"
                 // caused by watchdog timer.
                 delay(1); //
                 }
         return String(r);
}
         
String leerLinea() {
         // Espera hasta que haya algo que leer
         // BUCLE TOTALMENTE NECESARIO
         while(Serial.available() < 1) {
                   delay(1);
         }
         return Serial.readStringUntil('\n'); // Recibe info hasta ’\n’
}

void setup() {
        
        Serial.begin(115200);
        irrecv.enableIRIn(); // Inicializa el receptor
        pinMode(LED, OUTPUT); // LED como salida
        Wire.begin(5, 4);  //AQUI PONGO LOS PINES LOS CUALES VOY A CONECTAR LA LCD.
        lcd.setBacklight(HIGH); //Use predefined PINS consts
        lcd.begin(16,2);
        lcd.home();
        lcd.setCursor(0,1); // Situa el cursor en 2ª Fila
        lcd.print("ORDINARIO 2"); // Muestra mensaje inicial
}

void loop() {
     String s; // (s), VA SIENDO EL VALOR QUE VA RECIBIENDO EL NODE TRAS PULSAR CADA BOTON DEL MANDO. 
     String r = ""; 
    
          
        if (irrecv.decode(&results)) { // Si alguna señal recibida
          
            
                // enciende el LED
                digitalWrite(LED, HIGH);

                //LEE EL CODIGO PULSADO
                s = leerHastaRetorno();
               
               //ENVÍO A PROGRAMA PHYTON
                Serial.println( s );
                
                // Recibir respuesta
                r = leerLinea(); // recibe info hasta ’\n’
                escribeLCD(r);
                delay(4000);
               
                // Envía lo recibido terminado en "\n"
                Serial.println( r ); // devolver respuesta

                // apaga el LED0
                digitalWrite(LED, LOW);
         }
    }



  

 


