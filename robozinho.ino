/* LIGHTNING LITTLE MARK VERSÃO 0.0.1
   AUTOR: LUCAS DE SOUSA PACHECO <LUCASSIDPACHECO@GMAIL.COM>
   MODIFICADO EM: 02/07/2017
*/

/*-- PINOS DOS SENSORES --*/
#define slinha 3 // pino analógico
#define hcTrigg 7 // digital - trigger do sensor ultrassônico
#define hcEcho 8 // digital - echo do sensor ultrassônico

/*-- PINOS PWM PARA CONTROLE DO MOTORES --*/
#define m1Pin1 5 // In 1 do primeiro motor
#define m1Pin2 6 // In 2 do primeiro motor
#define m2Pin1 10 //Ind 1 segundo motor
#define m2Pin2 9 //Ind 2 segundo motor

/*-- INTERVALO DE CHAMADA DAS FUNÇÕES --*/
int slTime = 50; //milissegundos
int hcTime = 100; //milissegundos

/*-- VARIÁVEIS DE CONTROLE --*/
bool inimigo = 0;
bool linha = 0;
int linhaCalibre = 0;
int val = 0;
// CONTROLE DO TEMPO
unsigned long lastSLinha = 0;
unsigned long lastHC = 0;
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
  distance = (duration / 2) / 29.1;//converte a distância para cm

  if (distance < 30){
    inimigo = true;
    return;
  }
  inimigo = false;
}

void procuraLinha () {
  val = analogRead (slinha);

  if (val - linhaCalibre > 50) { //determinhar treshold ainda
    linha = 1;
    return;
  }
  linha = 0;
}

/*--- FUNÇÕES DE MOVIMENTO ---*/
void andaTras (int pwd) {
  analogWrite (m1Pin1, pwd);
  digitalWrite(m1Pin2, LOW);
  analogWrite (m2Pin1, pwd);
  digitalWrite (m2Pin2, LOW);
}

void andaFrente (int pwd) {
  analogWrite (m1Pin2, pwd);
  digitalWrite(m1Pin1, LOW);
  analogWrite (m2Pin2, pwd);
  digitalWrite (m2Pin1, LOW);
}

void gira () {
  analogWrite (m1Pin1, 100);//valor a ajustar
  digitalWrite(m1Pin2, LOW);
  digitalWrite (m2Pin1, LOW);
  analogWrite (m2Pin2, 255);//valor a ajustar
}

void desliga (){
  digitalWrite(m1Pin1, LOW);
  digitalWrite(m1Pin2, LOW);
  digitalWrite(m2Pin1, LOW);
  digitalWrite(m2Pin2, LOW);
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

  linhaCalibre = analogRead (slinha);

  Serial.begin(9600);
  //espera inicial
  //retirado para debugar
  //delay (5000);
}

void loop () {
  if (millis() - lastSLinha >= slTime)
    procuraLinha ();

  if (millis() - lastHC >= hcTime)
    procuraInimigos ();
    
  if (inimigo && linha)
    andaFrente(255);
  else if (linha){
    andaTras(100);
    delay(400);
  }
  else if(inimigo){
    andaFrente(255);
  }
  // a procura de inimigos ainda tá meio bugada
  else{
    gira();
    delay(200);
    andaFrente(100);
  }
}
