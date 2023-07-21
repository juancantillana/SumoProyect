#include <Button.h>

const int US_del_trig=2; //pin trigger de ultrasónico 
const int US_del_echo=3; //pin echo de ultrasónico

const int IR_del=4; //pin infrarojo delantero

const int IR_tras=13; //pin infrarojo trasero

const int Mot_izq_1=5; //pin motor izq
const int Mot_izq_2=6; //pin 2 motor izq

int Mot_der_1=10; //pin motor der
int Mot_der_2=11; //pin 2 motor der

long dist_US_del=1000; //inicialización de distancia de sensor

int IR_del_val=0; //inicialización sensores infrarojos
int IR_tras_val=0;


int state_button=false; //booleano de estado de botón
//const int pin_boton= ;

Button button1(7); //Objeto botón pin 7

void setup() {
  //boton
  button1.begin();
  //Ultrasonicos
  pinMode(US_del_trig,OUTPUT);
  pinMode(US_del_echo,INPUT);
  //Infrarojos
  pinMode(IR_del,INPUT);
  pinMode(IR_tras,INPUT);
  //Motores
  pinMode(Mot_izq_1,OUTPUT);
  pinMode(Mot_izq_2,OUTPUT);
  pinMode(Mot_der_1,OUTPUT);
  pinMode(Mot_der_2,OUTPUT);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //SI se apreta el botón, se cambia el estado del botón y hay un delay de 5 seg.
  if (button1.toggled()&&button1.read() == Button::PRESSED) {
    state_button=!state_button;
    delay(5000);
  }
  //Si el esatdo del botón es verdadero (fue apretado)
	if (state_button) {
    // Se calcula la distancia del ultrasónico y el valor de los IR
      dist_US_del=dist_US(US_del_trig,US_del_echo);
      IR_del_val=digitalRead(IR_del);
      IR_tras_val=digitalRead(IR_tras);
      
    if(IR_tras_val==0){
      Mover(200,200); //Si el sensor trasero detecta blanco, se avanza
      
    }
    else if(IR_del_val==0){
      Mover(-200,-200); //Si el sensor delantero detecta blanco, se retrocede
      
     }
    else if(dist_US_del<=25&&dist_US_del>2){
      Mover(220,220); //Si hay un enemigo en un rango de 2 a 25cm, se avanza atacando

    }
    else{
      Mover(-160,160); //Si los sensores no detectan nada, se gira.
 
    }
      
  }
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2; //Funcion para convertir microsegundos a centímetros para el US
}

long dist_US(int trigger, int echo) {
  long duration, cm;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm; //Función que calcula la distancia en centímetros del sensor ultrasónico
}

void Mover(int MOTizq,int MOTder){ //Función que hace mover los motores izquierdo y derecho a una valocidad pqm entre -255 a 255
  if (MOTizq<0){
    analogWrite(Mot_izq_1,0);
    analogWrite(Mot_izq_2,-MOTizq);
  } else {
    analogWrite(Mot_izq_1,MOTizq);
    analogWrite(Mot_izq_2,0);   
  }
  if (MOTder<0){
    analogWrite(Mot_der_1,0);
    analogWrite(Mot_der_2,-MOTder);
  } else {
    analogWrite(Mot_der_1,MOTder);
    analogWrite(Mot_der_2,0);   
  }
}
