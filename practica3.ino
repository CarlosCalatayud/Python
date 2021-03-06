#include <Keypad_I2C.h>
#include <Keypad.h>        // GDY120705
// la librería comunica el nodeMCU (o arduino) con 
// dispositivos que usan el protocolo I2C/TWI
#include <Wire.h> 
#define I2CADDR 0x20

const byte ROWS = 4; // Cuatro filas
const byte COLS = 4; // Cuatro columnas
// Define los simbolos de los botones del keypad
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte colPins[COLS] = {3, 2, 1, 0}; // Conecta a los pinouts de la fila del keypad
byte rowPins[ROWS] = {7, 6, 5, 4}; // Conecta a los pinouts de la columna del keypad

// Inicializa una instancia de la clase Keypad_I2C
Keypad_I2C customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 

void setup(){
  customKeypad.begin( ); // GDY120705
  Serial.begin(115200);
}

String pulsa;
String op = "";
String letras="ABCD";
String numeros="0123456789";

void loop(){
  if (op.length()==0){
    Serial.println( "Pulsa una tecla del keypad: \n **Para modo numérico. \n ##Para modo carácter. \n Si está en modo numérico pulse del 0 al 9 y si está en modo carácter pulse A, B, C o D." );

  }
  pulsa=leerTeclaKeypad();
  if (pulsa=="*"){
    op+="*";
  }
  if (pulsa=="#"){
    op+="#";
  }
  if (op=="**" || op=="##"){
    if (op=="**"){
      if (pulsa == "*"){
        Serial.println("Modo numérico activado");
      }
      soloNumeros();
    }
    
    if (op=="##"){
      if (pulsa == "#"){
        Serial.println("Modo carácter");
      }
      soloLetras();
    }
  }
  if (op.length()>2){
      op = "";
    }
}


String soloLetras(){
  int i;
  for (i=0;i<4;i++){
    if (pulsa==String(letras[i])){
      Serial.println(pulsa);
    }
  }
}

String soloNumeros(){
  int i;
  for (i=0;i<10;i++){
    if (pulsa==String(numeros[i])){
      Serial.println(pulsa);
    }
  }
}

char leerTeclaKeypad() {
  char customKey = customKeypad.getKey();

  while (customKey == NO_KEY) {
    customKey = customKeypad.getKey();
    delay(10);
  }
  return customKey;
}
