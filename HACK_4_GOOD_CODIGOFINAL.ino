#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // TX, RX

int led=13;        // Led 13 del Arduino
int BluetoothData=20; // Dato que se recibe de la aplicación
byte n = 0;
unsigned long ahora, antes;
int referencia = 0;

int sound=A0;   // Entrada del microfono

int MIC = 0;           // Lectura del microfono

boolean llaveA = false;
boolean llaveB = false;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  while(!Serial) {}
  
  pinMode(led,OUTPUT);
  pinMode(sound, INPUT);

 // Recoge el valor medido normal en una sala cuando no hay perturbaciones
 // Espera 2 segundos desde que se enciende
  referencia = DetectarPico();
  //Serial.print("La referencia es:  ");
  //Serial.println(referencia);
  //delay(5000);
}

void loop() {


     MIC = analogRead(sound);
     Serial.println(MIC);

  // Si el sonido del MIC supera 5 más que el del sonido ambiente se manda una señal a la APP
     if(MIC>=referencia+7){  
      //for(int i =0; i<=1; i++){
      mySerial.print(1);
       
      //}
      
      digitalWrite(led,HIGH);
      delay(2000);
      n++;
      digitalWrite(led,LOW);
      }  
      
}


int DetectarPico(){

// Detecta el pico maximo de sonido producido en un  intervalo de 5 segundos
  int lectura;
  int pico=0;
  
  antes = millis();
  ahora = millis();


  // Busca el valor mas alto de todos durante 2 segundos
  while(ahora-antes<=3000){
  
    ahora = millis();
    MIC = analogRead(sound);
    Serial.println(MIC); 
  //  delay(100);
    lectura = MIC;
   
   if(lectura >= pico){ pico =  lectura;}    
    }
    return pico;
  }
