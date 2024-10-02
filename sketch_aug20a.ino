#include <Servo.h>
#include <Dabble.h>  // Inclua a biblioteca do Dabble

// Definindo pinos
const int trigPin = 9;  // Pino Trigger do sensor ultrassônico
const int echoPin = 10; // Pino Echo do sensor ultrassônico
const int motorPin1 = 5; // Pino de controle do motor (L298N - IN1)
const int motorPin2 = 6; // Pino de controle do motor (L298N - IN2)
const int motorEnablePin = 3; // Pino de Enable do motor (L298N - ENA)
Servo servoLeme; // Servo para o leme
Servo servoBoia; // Servo para a boia
int distancia = 0; // Variável para armazenar a distância medida pelo sensor ultrassônico

// Variáveis de controle
bool motorLigado = false;
bool motorFrente = false;

void setup() {
  // Inicializando comunicação serial para o módulo Bluetooth
  Serial.begin(9600);

  // Inicializando Dabble
  Dabble.begin(9600);  // Comunicação serial com o Dabble

  // Inicializando pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inicializando pinos do motor
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorEnablePin, OUTPUT);

  // Inicializando servos
  servoLeme.attach(11); // Pino do servo leme
  servoBoia.attach(12); // Pino do servo boia

  // Inicializa com motor desligado
  desligarMotor();
}

void loop() {
  Dabble.processInput();  // Processa a entrada do Dabble

  // Verifica distância com o sensor ultrassônico
  distancia = medirDistancia();

  // Se a distância for menor que 30 cm, o motor é desligado
  if (distancia < 30 && motorLigado) {
    desligarMotor();
  }

  // Verifica os comandos do Gamepad do Dabble
  if (GamePad.isPressed(UP_ARROW)) {
    ligarMotorFrente();
  }
  
  if (GamePad.isPressed(DOWN_ARROW)) {
    ligarMotorRe();
  }

  if (GamePad.isPressed(LEFT_ARROW)) {
    servoLeme.write(135);  // Vira o leme para a esquerda
  }
  
  if (GamePad.isPressed(RIGHT_ARROW)) {
    servoLeme.write(45);  // Vira o leme para a direita
  }

  if (GamePad.isPressed(SWITCH_1)) {
    servoBoia.write(90);   // Lança a boia
    delay(1000);           // Espera 1 segundo
    servoBoia.write(0);    // Volta à posição original
  }

  if (GamePad.isPressed(SWITCH_2)) {
    desligarMotor();       // Desliga o motor
  }
}

// Função para ligar o motor em frente
void ligarMotorFrente() {
  motorLigado = true;
  motorFrente = true;
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(motorEnablePin, 255); // Velocidade máxima
}

// Função para ligar o motor em ré
void ligarMotorRe() {
  motorLigado = true;
  motorFrente = false;
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(motorEnablePin, 255); // Velocidade máxima
}

// Função para desligar o motor
void desligarMotor() {
  motorLigado = false;
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(motorEnablePin, 0); // Motor desligado
}

// Função para medir a distância com o sensor ultrassônico
int medirDistancia() {
  long duracao;
  int distancia;

  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2; // Convertendo tempo em distância

  return distancia;
}
