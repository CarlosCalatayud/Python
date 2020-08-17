
// Display 5161AS
const int A = 12; // D6
const int B = 14; // D5
const int C = 2; // D4
const int D = 5; // D1
const int E = 4; // D2
const int F = 13; // D7
const int G = 15; // D8
const int DP = 0; // el punto, de momento no se usa

void setup() {
  pinMode(A, OUTPUT);  // Asignación de las salidas digitales
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  Serial.begin(115200); 
}

String leerLinea() {
  // Espera hasta que haya algo que leer
  while(Serial.available() < 1) {
    delay(1);
  }
  return Serial.readStringUntil('\n'); // Recibe info hasta '\n'
}
 
void display (int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(A,a);   //Se reciben 7 variables y se asignan
  digitalWrite(B,b);   //a cada una de las salidas
  digitalWrite(C,c);
  digitalWrite(D,d);
  digitalWrite(E,e);
  digitalWrite(F,f);
  digitalWrite(G,g);
}
 
// Dependiendo de cada dígito, se envía a la función display
// los estados (0 y 1) a cada uno de los segmentos
void loop() {
  String r = "";
  r = leerLinea();
  Serial.println(r);
  if (r[0]=='0') {
    display (1,1,1,1,1,1,0); //escribe 0
  } else if (r[0]=='1') {
    display (0,1,1,0,0,0,0); //escribe 1
  } else if (r[0]=='2') {
    display (1,1,0,1,1,0,1); //escribe 2
  } else if (r[0]=='3') {
    display (1,1,1,1,0,0,1); //escribe 3
  } else if (r[0]=='4') {
    display (0,1,1,0,0,1,1); //escribe 4
  } else if (r[0]=='5') {
    display (1,0,1,1,0,1,1); //escribe 5
  } else if (r[0]=='6') {
    display (1,0,1,1,1,1,1); //escribe 6
  } else if (r[0]=='7') {
    display (1,1,1,0,0,0,0); //escribe 7
  } else if (r[0]=='8') {
    display (1,1,1,1,1,1,1); //escribe 8
   } else if (r[0]=='9') {
    display (1,1,1,0,0,1,1); //escribe 9
   } else {
    display (0,0,0,0,0,0,0); //borra display
  }
}
