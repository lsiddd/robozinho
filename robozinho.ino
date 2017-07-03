/* LIGHTNING LITTLE MARK VERSÃO 0.0.1
   AUTOR: LUCAS DE SOUSA PACHECO <LUCASSIDPACHECO@GMAIL.COM>
   MODIFICADO EM: 02/07/2017
*/

#define slinha1 3 // pino analógico
#define slinha2 4 //pino analógico
#define hcTrigg 7 // trigger do sensor ultrassônico
#define hcEcho 8 // echo do sensor ultrassônico

/*-- PINOS PWM PARA CONTROLE DO MOTORES --*/
#define m1Pin1 5 // In 1 do primeiro motor
#define m1Pin2 6 // In 2 do primeiro motor
#define m2Pin1 9 //Ind 1 segundo motor
#define m2Pin2 10 //Ind 2 segundo motor

/*-- INTERVALO DE CHAMADA DAS FUNÇÕES --*/
int slTime = 50; //milissegundos
int hcTime = 100; //milissegundos

/*-- VARIÁVEIS DE CONTROLE --*/
bool inimigo = 0;
bool linhaFrente = 0;
bool linhaTras = 0;
int linhaCalibre = 0;
int val1 = 0;
int val2 = 0;
// CONTROLE DO TEMPO
unsigned long lastSLinha = 0;
unsigned long currentLinha = 0;
unsigned long lastHC = 0;
unsigned long currentHC = 0;
long duration, distance;

/*-- FUNÇÕES DE STATUS --*/
void procuraInimigos () {
  //emite um pulso e calcula a distância em cm de objetos pŕoximos
  digitalWrite(hcTrigg, LOW);
  delayMicroseconds(5);
  digitalWrite(hcTrigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(hcTrigg, LOW);
  duration = pulseIn(hcEcho, HIGH);

  //converte a distância para cm
  distance = (duration / 2) / 29.1;

  if (distance < 30)
    inimigo = true;
  delay (50);
}

void procuraLinha () {
  val1 = analogRead (slinha1);
  val2 = analogRead (slinha2);

  if (val1 - linhaCalibre > 10) { //determinhar treshold ainda
    linhaFrente = 1;
    return;
  }
  if (val2 - linhaCalibre > 10) { //determinhar treshold ainda
    linhaTras = 1;
    return;
  }
  linhaFrente = 0;
  linhaTras = 0;
}

/*--- FUNÇÕES DE MOVIMENTO ---*/
void andaFrente (int pwd) {
  analogWrite (m1Pin1, pwd);
  digitalWrite(m1Pin2, LOW);
  analogWrite (m2Pin1, pwd);
  digitalWrite (m2Pin2, LOW);
}

void andaTras (int pwd) {
  analogWrite (m1Pin2, pwd);
  digitalWrite(m1Pin1, LOW);
  analogWrite (m2Pin2, pwd);
  digitalWrite (m2Pin1, LOW);
}

void gira (bool sentido) {
  //0 - horário
  //1 - anti-horário
  if (sentido) {
    analogWrite (m1Pin2, 100);//valor a ajustar
    digitalWrite(m1Pin1, LOW);
    analogWrite (m2Pin1, 100);//valor a ajustar
    digitalWrite (m2Pin2, LOW);
    return;
  }
  analogWrite (m1Pin1, 100);//valor a ajustar
  digitalWrite(m1Pin2, LOW);
  analogWrite (m2Pin2, 100);//valor a ajustar
  digitalWrite (m2Pin1, LOW);
}

/*--- FUNÇÕES DO ARDUINO ---*/
void setup () {
  //inicialização dos pinos
  pinMode (hcTrigg, OUTPUT);
  pinMode (hcEcho, INPUT);
  pinMode (m1Pin1, OUTPUT);
  pinMode (m1Pin2, OUTPUT);
  pinMode (m2Pin1, OUTPUT);
  pinMode (m2Pin2, OUTPUT);

  linhaCalibre = analogRead (slinha1);
  //espera inicial
  delay (5000);
}

void loop () {
  currentLinha = millis ();
  if (currentLinha - lastSLinha >= slTime) {
    procuraLinha ();
    lastSLinha = currentLinha;
  }

  currentHC = millis ();
  if (currentHC - lastHC >= hcTime) {
    procuraInimigos ();
    lastHC = currentHC;
  }

  if (inimigo)
    andaFrente (255);
  else if (linhaFrente)
    andaTras (255);
  else if (linhaTras)
    andaFrente(255);
  else
    gira (true);
}

