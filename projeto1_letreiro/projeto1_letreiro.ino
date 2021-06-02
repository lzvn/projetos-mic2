//documentação da biblioteca LedControl: http://wayoda.github.io/LedControl/pages/software
//letras feitas com o site http://robojax.com/learn/arduino/8x8LED/

#include <LedControl.h>
#define DIN 2 //Pino DIN (DATA IN) do display
#define CLK 3 //Pino de clock do display
#define CS 4 //Pino CS do display
#define NM 1 //Número de displays conectados, neste protótipo, sempre será 1
#define PERIODO_MINIMO 25.0 //Periodo mínimo, ou seja, que define a velocidade máxima de deslizamento
#define LEITURA_PERIODO A0 //Porta usada na leitura do potenciometro

String frase; //Frase a ser mostrada no display
int periodo; //Valor do periodo que será usado na função letreiro (vide abaixo)
char sentido; //Sentido que a frase será mostrada

LedControl display1 = LedControl(DIN, CLK, CS, NM);


void letra(char l, int pos_ini);
//l é a letra que será mostrada no display e pos_ini é a posição inicial da da letra no display
void letreiro();



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("Digite qual a frase que deseja ser mostrada no display:");
  while(1)
  {
    Serial.flush();
    if(Serial.available())
    {
      String aux = " ";
      frase = Serial.readString();
      frase = String(" " + frase + " ");
      Serial.println(frase);
      break;
    }
  }
  
  Serial.println("Ajuste no potenciômetro a velocidade de deslizamento, sendo mostrada em quantas colunas o texto se move por segundo.");
  Serial.println("Esta velocidade é alterável durante o funcionamento por meio do ajuste do potenciômetro.");
  Serial.println("Envie qualquer caracter para terminar esta seleção.");  
  delay(2000);
  
  while(1)
  {
    Serial.flush();
    if(Serial.available())
    {
      //periodo = (Serial.readString()).toInt();
      Serial.readString();
      break;
    }
    else
    {
      periodo = (int) (( (1000.0 - PERIODO_MINIMO)/1023.0)*analogRead(LEITURA_PERIODO) + PERIODO_MINIMO ); 
      Serial.print(1000/periodo);
      Serial.println("posições por segundo");
    }
  }
  

  Serial.println("Digite l para que o texto seja mostrada da direita pra esquerda e d para o sentido contrário");
  while(1)
  {
    Serial.flush();
    if(Serial.available())
    {
      sentido = Serial.read();
      if(sentido == 'l' || sentido == 'L' || sentido == 'd' || sentido == 'D')
        {
          Serial.println("Operação iniciada com sucesso");
          break;
        }
     else
      Serial.println("Código invalido, tente novamente");
    }
  }

  display1.shutdown(0, false);
  display1.setIntensity(0, 8);
  display1.clearDisplay(0);

} //fim setup()

void loop() {
  // put your main code here, to run repeatedly:

  letreiro();


}//fim loop()

/////Letras simples
//PROGMEM const int A[] = {0x00, 0x, 0x, 0x, 0x, 0x, 0x, 0x};
PROGMEM const int A[] = {0x00, 0x1F, 0x3F, 0x6C, 0xCC, 0x6C, 0x3F, 0x1F};
PROGMEM const int B[] = {0x00, 0xFF, 0xFF, 0x99, 0x99, 0x99, 0x99, 0x66};
PROGMEM const int C[] = {0x00, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xC3, 0xC3};
PROGMEM const int D[] = {0x00, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0x66, 0x3C};
PROGMEM const int E[] = {0x00, 0xFF, 0xFF, 0xDB, 0xDB, 0xDB, 0xDB, 0xDB};
PROGMEM const int F[] = {0x00, 0xFF, 0xFF, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1};
PROGMEM const int G[] = {0x00, 0xFF, 0xFF, 0xC3, 0xDB, 0xDB, 0xDF, 0xDF};
PROGMEM const int H[] = {0x00, 0xFF, 0xFF, 0x18, 0x18, 0x18, 0xFF, 0xFF};
PROGMEM const int I[] = {0x00, 0x00, 0x00, 0x81, 0xFF, 0xFF, 0x81, 0x00};
PROGMEM const int J[] = {0x00, 0x0F, 0x0F, 0x83, 0xFF, 0xFF, 0x80, 0x00};
PROGMEM const int K[] = {0x00, 0xFF, 0xFF, 0x18, 0x7E, 0xE7, 0xC3, 0x81};
PROGMEM const int L[] = {0x00, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0x03, 0x03};
PROGMEM const int M[] = {0x00, 0xFF, 0xE0, 0x30, 0x0C, 0x30, 0xE0, 0xFF};
PROGMEM const int N[] = {0x00, 0xFF, 0xFF, 0x60, 0x3C, 0x06, 0xFF, 0xFF};
PROGMEM const int O[] = {0x00, 0xFF, 0xFF, 0xC3, 0xC3, 0xC3, 0xFF, 0xFF};
PROGMEM const int P[] = {0x00, 0xFF, 0xFF, 0xCC, 0xCC, 0xCC, 0xFC, 0xFC};
PROGMEM const int Q[] = {0x00, 0xFC, 0xFC, 0xCC, 0xCC, 0xCF, 0xFF, 0xFC};
PROGMEM const int R[] = {0x00, 0xFF, 0xFF, 0xCC, 0xCF, 0xCF, 0xFD, 0xFC};
PROGMEM const int S[] = {0x00, 0xFB, 0xFB, 0xDB, 0xDB, 0xDB, 0xDF, 0xDF};
PROGMEM const int T[] = {0x00, 0x00, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0};
PROGMEM const int U[] = {0x00, 0xFF, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFF};
PROGMEM const int V[] = {0x00, 0xF8, 0xFC, 0x06, 0x03, 0x06, 0xFC, 0xF8};
PROGMEM const int X[] = {0x00, 0xC3, 0xE7, 0x3C, 0x18, 0x3C, 0xE7, 0xC3};
PROGMEM const int W[] = {0x00, 0xFF, 0x07, 0x0C, 0x30, 0x0C, 0x07, 0xFF};
PROGMEM const int Y[] = {0x00, 0x00, 0xE0, 0x30, 0x1F, 0x1F, 0x30, 0xE0};
PROGMEM const int Z[] = {0x00, 0xC3, 0xC7, 0xCF, 0xDB, 0xF3, 0xE3, 0xC3};

//letras especiais e acentuadas
//PROGMEM const int A[] = {0x00, 0x, 0x, 0x, 0x, 0x, 0x, 0x};
PROGMEM const int cedilha[] = {0x00, 0xFC, 0xFC, 0xCD, 0xCF, 0xCF, 0xCC, 0xCC};
PROGMEM const int Atil[] = {0x00, 0xC7, 0x8A, 0x92, 0x52, 0x4A, 0xC7, 0x00};
PROGMEM const int Aagudo[] = {0x00, 0x07, 0x0A, 0x32, 0x52, 0x8A, 0x07, 0x00};
PROGMEM const int Acrase[] = {0x00, 0x07, 0x8A, 0x52, 0x32, 0x0A, 0x07, 0x00};
PROGMEM const int Acircumflexo[] = {0x00, 0x27, 0x4A, 0x92, 0x92, 0x4A, 0x27, 0x00};
PROGMEM const int Eagudo[] = {0x00, 0x1F, 0x35, 0x55, 0x95, 0x15, 0x00, 0x00};
PROGMEM const int Ecircumflexo[] = {0x00, 0x3F, 0x55, 0x95, 0x95, 0x55, 0x20, 0x00};
PROGMEM const int Iagudo[] = {0x00, 0x00, 0x00, 0x3F, 0x5F, 0x80, 0x00, 0x00};
PROGMEM const int Otil[] = {0x00, 0xC0, 0x9F, 0x91, 0x51, 0x5F, 0xC0, 0x00};
PROGMEM const int Oagudo[] = {0x00, 0x00, 0x1F, 0x31, 0x51, 0x9F, 0x00, 0x00};
PROGMEM const int Ocircumflexo[] = {0x00, 0x20, 0x5F, 0x91, 0x91, 0x5F, 0x20, 0x00};
PROGMEM const int Uagudo[] = {0x00, 0x00, 0x1F, 0x21, 0x41, 0x9F, 0x00, 0x00};

//números
//PROGMEM const int A[] = {0x00, 0x, 0x, 0x, 0x, 0x, 0x, 0x};
PROGMEM const int zero[] = {0x00, 0x3C, 0x46, 0x89, 0x91, 0x62, 0x3C, 0x00};
PROGMEM const int um[] = {0x00, 0x00, 0x00, 0x20, 0x40, 0xFF, 0x00, 0x00};
PROGMEM const int dois[] = {0x00, 0x23, 0x43, 0x85, 0x89, 0x51, 0x21, 0x00};
PROGMEM const int tres[] = {0x00, 0x00, 0x81, 0x91, 0xB1, 0xD2, 0x8C, 0x00};
PROGMEM const int quatro[] = {0x00, 0x08, 0x18, 0x28, 0x48, 0xFF, 0x08, 0x00};
PROGMEM const int cinco[] = {0x00, 0xF1, 0x91, 0x91, 0x91, 0x89, 0x86, 0x00};
PROGMEM const int seis[] = {0x00, 0x1C, 0x22, 0x51, 0x91, 0x91, 0x8E, 0x00};
PROGMEM const int sete[] = {0x00, 0x81, 0x82, 0x84, 0x88, 0xB0, 0xC0, 0x00};
PROGMEM const int oito[] = {0x00, 0x00, 0x6E, 0x91, 0x91, 0x6E, 0x00, 0x00};
PROGMEM const int nove[] = {0x00, 0x00, 0x63, 0x91, 0x91, 0x91, 0x7E, 0x00};

//espaço, pontos e outros
//PROGMEM const int A[] = {0x00, 0x, 0x, 0x, 0x, 0x, 0x, 0x};
PROGMEM const int espaco[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
PROGMEM const int exclamacao[] = {0x00, 0x00, 0x00, 0xFB, 0xFB, 0x00, 0x00, 0x00};
PROGMEM const int aspasduplas[] = {0x00, 0x00, 0x00, 0xE0, 0x00, 0xE0, 0x00, 0x00};
PROGMEM const int cifrao[] = {0x00, 0xFB, 0xFB, 0xDB, 0xFF, 0xDB, 0xDF, 0xDF};
PROGMEM const int porcento[] = {0x00, 0x61, 0x62, 0x04, 0x08, 0x10, 0x23, 0x43};
PROGMEM const int parentesis1[] = {0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x81, 0x81};//(
PROGMEM const int parentesis2[] = {0x00, 0x81, 0x81, 0x42, 0x3C, 0x00, 0x00, 0x00};//)
PROGMEM const int asterisco[] = {0x00, 0x00, 0x90, 0x60, 0xF0, 0x60, 0x90, 0x00};
PROGMEM const int ponto[] = {0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00};
PROGMEM const int virgula[] = {0x00, 0x00, 0x01, 0x02, 0x0C, 0x00, 0x00, 0x00};
PROGMEM const int mais[] = {0x00, 0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00};
PROGMEM const int traco[] = {0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00};
PROGMEM const int barra[] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x30};
PROGMEM const int doispontos[] = {0x00, 0x00, 0x00, 0xC3, 0xC3, 0x00, 0x00, 0x00};
PROGMEM const int igual[] = {0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00};



//Funções do letreiro
void letreiro()
{
  display1.clearDisplay(0);
  int tamanho = frase.length();
  int i = 0;
  int j = 0;

  if(sentido == 'l' || sentido == 'L')
    {
        for(i = 0; i<tamanho; i++)
          {
            for(j=0; j<8; j++)
              {		
                letra(frase[i], -j);
                if(i < tamanho-1)
                  letra(frase[i+1], 8 - j);

                periodo = (int) ( ( (1000.0 - PERIODO_MINIMO)/1023.0)*analogRead(LEITURA_PERIODO) + PERIODO_MINIMO);                 
                delay(periodo);   
              }
          } 
    }

    //testar o abaixo pra ver se funciona, que eu acho que não
  else if(sentido == 'd' || sentido == 'D')
    {
        for(i = tamanho-1; i>=0; i--)
          {
            for(j = 0; j<8; j++)
              {
                letra(frase[i], j);
                if(i>0)
                  letra(frase[i-1], j-8);

                periodo = (int) (( (1000.0 - PERIODO_MINIMO)/1023.0)*analogRead(LEITURA_PERIODO) + PERIODO_MINIMO );                 
                delay(periodo);  
              }
          }
    }
   
}//fim letreiro

void letra(char l, int pos_ini)
{
  int i = 0;
    switch(l)
    {
       //Letras simples (só maiúsculas, sendo que minúsculas são mostradas como maiúsculas)
      case 'A':
      case 'a':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, A[i]);
        }        
        break;

      case 'B':
      case 'b':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, B[i]);
        }           
        break;

      case 'C':
      case 'c':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, C[i]);
        }           
        break;
        
      case 'D':
      case 'd':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, D[i]);
        }           
        break;

      case 'E':
      case 'e':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, E[i]);
        }           
        break;
        
      case 'F':
      case 'f':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, F[i]);
        }           
        break;
      case 'G':
      case 'g':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, G[i]);
        }           
        break;
        
      case 'H':
      case 'h':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, H[i]);
        }           
        break;
        
      case 'I':
      case 'i':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, I[i]);
        }           
        break;
        
      case 'J':
      case 'j':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, J[i]);
        }           
        break;
        
      case 'K':
      case 'k':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, K[i]);
        }           
        break;
        
      case 'L':
      case 'l':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, L[i]);
        }           
        break;
        
      case 'M':
      case 'm':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, M[i]);
        }           
        break;
        
      case 'N':
      case 'n':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, N[i]);
        }           
        break;
        
      case 'O':
      case 'o':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, O[i]);
        }           
        break;
        
      case 'P':
      case 'p':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, P[i]);
        }           
        break;
        
      case 'Q':
      case 'q':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Q[i]);
        }           
        break;
        
      case 'R':
      case 'r':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, R[i]);
        }           
        break;
        
      case 'S':
      case 's':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, S[i]);
        }           
        break;
        
      case 'T':
      case 't':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, T[i]);
        }           
        break;
        
      case 'U':
      case 'u':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, U[i]);
        }           
        break;
        
      case 'V':
      case 'v':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, V[i]);
        }           
        break;
        
      case 'X':
      case 'x':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, X[i]);
        }           
        break;
        
      case 'W':
      case 'w':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, W[i]);
        }           
        break;
        
      case 'Y':
      case 'y':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Y[i]);
        }           
        break;
        
      case 'Z':
      case 'z':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Z[i]);
        }           
        break;

      //Letras especiais e com acentos

      case 'Ç':
      case 'ç':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, cedilha[i]);
        }           
        break;
        
        case 'Ã':
        case 'ã':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Atil[i]);
        }           
        break;

        case 'Á':
        case 'á':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Aagudo[i]);
        }           
        break;

        case 'À':
        case 'à':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Acrase[i]);
        }           
        break;

        case 'Â':
        case 'â':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Acircumflexo[i]);
        }           
        break;

        case 'É':
        case 'é':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Eagudo[i]);
        }           
        break;

        case 'Ê':
        case 'ê':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Ecircumflexo[i]);
        }           
        break;

        case 'Í':
        case 'í':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Iagudo[i]);
        }           
        break;

        case 'Õ':
        case 'õ':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Otil[i]);
        }           
        break;

        case 'Ó':
        case 'ó':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Oagudo[i]);
        }           
        break;

        case 'Ô':
        case 'ô':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Ocircumflexo[i]);
        }           
        break;

        case 'Ú':
        case 'ú':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, Uagudo[i]);
        }           
        break;


      //Números

      case '0':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, zero[i]);
        }           
        break;

        case '1':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, um[i]);
        }           
        break;

        case '2':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, dois[i]);
        }           
        break;

        case '3':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, tres[i]);
        }           
        break;

        case '4':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, quatro[i]);
        }           
        break;

        case '5':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, cinco[i]);
        }           
        break;

        case '6':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, seis[i]);
        }           
        break;

        case '7':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, sete[i]);
        }           
        break;

        case '8':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, oito[i]);
        }           
        break;

        case '9':
        for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, nove[i]);
        }           
        break;
        
      //Espaco, pontos e outros
      case ' ':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, espaco[i]);
        }        
        break;

        case '!':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, exclamacao[i]);
        }        
        break;

        case '"':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, aspasduplas[i]);
        }        
        break;

        case '$':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, cifrao[i]);
        }        
        break;

        case '%':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, porcento[i]);
        }        
        break;

        case '(':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, parentesis1[i]);
        }        
        break;

        case ')':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, parentesis2[i]);
        }        
        break;

        case '*':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, asterisco[i]);
        }        
        break;

        case '.':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, ponto[i]);
        }        
        break;

        case ',':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, virgula[i]);
        }        
        break;

        case '+':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, mais[i]);
        }        
        break;

        case '-':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, traco[i]);
        }        
        break;

        case '/':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, barra[i]);
        }        
        break;

        case ':':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, doispontos[i]);
        }        
        break;

        case '=':
         for(i = 0; i<8; i++)
        {
          if( (pos_ini+i)>=0 || (pos_ini+i) < 8)
            display1.setColumn(0, i+pos_ini, igual[i]);
        }        
        break;
        
       default:
        break;
    }
}//fim letra
