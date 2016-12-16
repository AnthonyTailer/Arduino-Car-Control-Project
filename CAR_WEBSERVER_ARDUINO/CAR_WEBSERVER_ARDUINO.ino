const int GPIO2 = 13; //UP
const int GPIO0 = 12; //DOWN
const int GPIO3 = 11; //RIGHT
const int GPIO1 = 10; //LEFT

const int pin7 = 7;
const int pin6 = 6;
const int pin5 = 5;
const int pin4 = 4;
const int pin3 = 3;
const int pin2 = 2;
const int pin1 = 1;
const int pin0 = 0;

int gpio2, gpio0, gpio3, gpio1;

void stop_all(){
  digitalWrite(pin7, LOW);
  digitalWrite(pin6, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, LOW);
  digitalWrite(pin0, LOW);
}

void up(){
  digitalWrite(pin7, HIGH);
  digitalWrite(pin6, LOW);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin4, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin0, LOW);
}

void down(){
  digitalWrite(pin7, LOW);
  digitalWrite(pin6, HIGH);
  digitalWrite(pin5, LOW);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin1, LOW);
  digitalWrite(pin0, HIGH);
}

void left(){
  digitalWrite(pin7, HIGH);
  digitalWrite(pin6, LOW);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin4, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, LOW);
  digitalWrite(pin0, LOW);
}

void right(){
  digitalWrite(pin7, LOW);
  digitalWrite(pin6, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin1, HIGH);
  digitalWrite(pin0, LOW);
}

void setup(){
  pinMode(GPIO2, INPUT);
  pinMode(GPIO0, INPUT);
  pinMode(GPIO3, INPUT);
  pinMode(GPIO1, INPUT);

  pinMode(pin7, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin0, OUTPUT);
}

void loop(){
  gpio2 = digitalRead(GPIO2);
  gpio0 = digitalRead(GPIO0);
  gpio3 = digitalRead(GPIO3);
  gpio1 = digitalRead(GPIO1);
  
  if( gpio2 == HIGH ) //carro move para frente
    up();
  else if( gpio0 == HIGH ) //carro move para tras
    down();
  else if( gpio3 == HIGH ) //carro move para direita
    right();
  else if( gpio1 == HIGH ) //carro move para esquerda
    left();
  else
    stop_all();   
}

