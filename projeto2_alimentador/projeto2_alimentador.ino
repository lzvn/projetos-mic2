#include <Wire.h> //necessária para a comunicaçao serial com o rtc
#include <RTClib.h> //biblioteca do rtc

#define PINO_ABRIR 5  //pino que controla o motor para abrir a saída de ração, com PINO_FECHAR em baixo
#define PINO_FECHAR 6 //pino que controla o motor para fechar a saída de ração, com PINO_ABRIR em baixo
#define PINO_ENABLE 7 //pino do enable A da ponte H l298n
#define T_OP 200 //tempo para abrir ou fechar a saída de ração

long unsigned int intervalo = 0; //intervalo de tempo escolhido pelo usuário para a reposição da ração
long unsigned int tempo = 0; //tempo decorrido desde a última reposição
int tempo_racao = 500;
int estado_motor = 'f'; //estado do motor, sendo 'f' fechdo e 'a' aberto
RTC_DS1307 rtc;

void abrir_motor();
void fechar_motor();

void setup() {
  // put your setup code here, to run once:

  pinMode(PINO_ABRIR, OUTPUT);
  pinMode(PINO_FECHAR, OUTPUT);
  pinMode(PINO_ENABLE, OUTPUT);
  digitalWrite(PINO_ENABLE, HIGH);

  Serial.begin(9600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
   rtc.adjust(DateTime(0, 0, 0, 0, 0, 0));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

   //rtc.begin();
  //rtc.isrunning();
   //rtc.adjust(DateTime(0, 0, 0, 0, 0, 0));
  int i = 0;
  int hora;
  int minuto;
  int aux = 0;

  while(i <2)
  {
    Serial.flush( );
    if(i == 0 && aux==0)
    {
      Serial.println("Digite quantas horas deseja ter intervalo de tempo para reposição da ração: ");
      aux = 1;
    }
    else if(i == 1 && aux==0)
    {
      Serial.println("Digite quantos minutos deseja ter intervalo de tempo para reposição da ração: ");
      aux = 1;
    }
      
    if(Serial.available())
    {
      aux = 0;
      if(i == 0)
        hora = (Serial.readString()).toInt();
      else if(i == 1)
        minuto = (Serial.readString()).toInt();
     if( (hora>=0) || (minuto>=0 && minuto<60) )    
      i++;
     else
      Serial.println("Ocorreu um erro. Por favor, digite novamente.\n");
    }
  }

  intervalo = 60*hora + minuto;
  
  Serial.print("O intervalo foi ajustado para ");
  Serial.print(hora);
  Serial.print(" horas e ");
  Serial.print(minuto);
  Serial.println(" minutos");
  Serial.print("Total de ");
  Serial.print(intervalo);
  Serial.println(" minutos");

Serial.println("Operação iniciada com sucesso");
delay(2000);
rtc.adjust(DateTime(0, 0, 0, 0, 0, 0)); //A função ajusta a data na ordem: ano, mes, dia, hora, minuto, segundo

}///////Fim de setup


void loop() {
  // put your main code here, to run repeatedly:
DateTime now = rtc.now();


//lembrar de testar pra ver se tem que faze a conversão da saída de now.hour

tempo = 60*(now.hour()) + now.minute();
Serial.print("tempo decorrido: ");
Serial.print(now.hour());
Serial.print(":");
Serial.print(now.minute());
Serial.print(":");
Serial.println(now.second());
Serial.print("Total de ");
Serial.print(tempo);
Serial.println(" minutos");
delay(1000);

//testar o código do motor
if(tempo == intervalo)
{
  abrir_motor();
  delay(tempo_racao);  
  fechar_motor();
  rtc.adjust(DateTime(0, 0, 0, 0, 0, 0)); //Reseta a hora para facilitar a contagem do tempo
  tempo = 0;
}


}//////////Fim de loop

void abrir_motor()
{
  if(estado_motor == 'a')
    return;
  else
    {
      estado_motor = 'a';
      analogWrite(PINO_ABRIR, 255);
      analogWrite(PINO_FECHAR, 0);
      delay(T_OP);
      analogWrite(PINO_ABRIR, 0);
      analogWrite(PINO_FECHAR, 0);
    }
    
}

void fechar_motor()
{
  if(estado_motor == 'f')
    return;
  else
    {
      estado_motor = 'f';
      analogWrite(PINO_ABRIR, 0);
      analogWrite(PINO_FECHAR, 255);
      delay(T_OP);
      analogWrite(PINO_ABRIR, 0);
      analogWrite(PINO_FECHAR, 0);
    }  
}     
