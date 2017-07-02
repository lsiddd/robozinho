/* RELÂMPAGO MARQUINHOS VERSÃO 0.0.1
 * AUTOR: LUCAS DE SOUSA PACHECO
 * MODIFICADO EM: 02/07/2017
 */

 #define slinha 3 // pino analógico
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
 bool linha = 0;
 // CONTROLE DO TEMPO
 unsigned long lastSLinha = 0;
 unsigned long lastHC = 0;

 void procuraInimigos (){
  
 }

 void procuraLinha (){
  
 }

 void setup (){
  //inicialização dos pinos
  pinMode (hcTrigg, OUTPUT);
  pinMode (hcEcho, INPUT);
  pinMode (m1Pin1, OUTPUT);
  pinMode (m1Pin2, OUTPUT);
  pinMode (m2Pin1, OUTPUT);
  pinMode (m2Pin2, OUTPUT);

  //espera inicial
  delay (5000);
 }

 void loop (){
  if (millis() - lastSLinha >= slTime)
    procuraLinha ();  

  if (millis() - lastHC >= hcTime)
    procuraInimigos ();  
 }

