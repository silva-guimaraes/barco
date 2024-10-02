// Definição dos pinos
const int enA = 9;    // Pino de PWM para controlar a velocidade do motor
const int in1 = 8;    // Pino IN1 da ponte H
const int in2 = 7;    // Pino IN2 da ponte H

void setup() {
  // Configura os pinos como saída
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Inicia o motor parado
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0); // Velocidade 0
}

void loop() {
  // Gira o motor para frente
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 255); // Velocidade do motor (0-255)

  delay(2000); // Gira por 2 segundos

  // Para o motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  
  delay(1000); // Pausa de 1 segundo

  // Gira o motor para trás
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 255); // Velocidade do motor (0-255)

  delay(2000); // Gira por 2 segundos

  // Para o motor novamente
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);

  delay(1000); // Pausa de 1 segundo
}
