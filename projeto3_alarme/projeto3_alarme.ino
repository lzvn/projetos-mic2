#include <Wire.h> //necessária para a comunicaçao serial com o rtc
#include <RTClib.h> //biblioteca do rtc

//pinos
#define JANELAS_PIR 13
#define PORTA_PIR 12
#define CORREDOR_PIR 10
#define ALARME 8 //pino do alarme

// estado 'a' representa que o sistema está em alerta e em 's' representa que ele está seguro
char estado = 's';
  
String senha;
unsigned short int horario_inicio;
unsigned short int horario_fim;
String log_alarme;
short unsigned int ativo;
RTC_DS1307 rtc;

void rotina();
void alarme();
void atualizar_hora();
void alt_horario_func();
void alterar_senha();

void setup() {
	Serial.begin(9600);

	pinMode(JANELAS_PIR, INPUT);
	pinMode(PORTA_PIR, INPUT_PULLUP);
	pinMode(CORREDOR_PIR, INPUT_PULLUP);
	pinMode(ALARME, OUTPUT);

	rtc.begin();
	  if(!rtc.isrunning())
		Serial.println("RTC não funcionando");

	Serial.println("Digite uma senha de 4 caracteres para ativar e desativar os alarmes: ");
	while(1) 
	{
		if(Serial.available()) 
		{
			senha = Serial.readString();
      
			if(senha.length() < 4) 
			{
				Serial.println("A senha deve ter pelo menos 4 caracteres. Por favor, digite-a novamente.");
			} 
			else 
			{
				break;
			}
		}
	}
  
	alt_horario_func();
	atualizar_hora();
	Serial.println("Sistema iniciado");
}

void loop() {
	DateTime now = rtc.now();
	unsigned short int hora_atual = 60*( now.hour() ) + now.minute();
	unsigned short int hora_alarme[2];
	if(horario_inicio < horario_fim) 
	{
		if( hora_atual >= horario_inicio && hora_atual <= horario_fim && ativo != 1) 
		{
			ativo = 1;
			Serial.println("Sistema ativado");
		} 
		else if (hora_atual <= horario_inicio && hora_atual >= horario_fim && ativo != 0)
		{
			ativo = 0;
			Serial.println("Sistema desativado");
		}
	}
	else if(horario_inicio > horario_fim)
	{
		if( hora_atual <= horario_inicio && hora_atual >= horario_fim && ativo != 1)
		{
			ativo = 1;
			Serial.println("Sistema ativado");
		}
		else if (hora_atual >= horario_inicio && hora_atual <= horario_fim && ativo != 0)
		{
			ativo = 0;
			Serial.println("Sistema desativado");
		}
	}

  

	if(Serial.available())
	{
		String aux = Serial.readString();

		if(senha.equals(aux))
		{
			Serial.println("Digite o codigo da opcao que deseja:");
			Serial.println("01 - Atualizar a hora do sistema");
			Serial.println("02 - Alterar o horario de funcionamento do sistema");
			Serial.println("03 - Alterar a senha");
			Serial.println("04 - Sair deste menu");
			int opcao = 0;

			while(1)
			{
				if(Serial.available())
				{
					opcao = (Serial.readString()).toInt();
					if(opcao >0 && opcao < 5)
						break;
					else
						Serial.println("Codigo invalido. Por favor, digite novamente");
				}
			}
			switch(opcao)
			{
				case 1:
					atualizar_hora();
					break;
				case 2:
					alt_horario_func();
					break;
				case 3:
					alterar_senha();
					break;
				default:
					break;
			}
		}
	} //Fim if serial available 

	if(ativo)
	{
		rotina();
		hora_alarme[0] = now.hour();
		hora_alarme[1] = now.minute();
		int i;
		while(estado == 'a')
		{
			alarme(1);
			Serial.println("Para encerrar o alarme e verificar o log, digite a senha");
			if(Serial.available())
			{
				String aux = Serial.readString();
				if(senha.equals(aux))
				{
					estado = 's';
					alarme(0);
					Serial.println(log_alarme);
					Serial.print("A invasao ocorreu em ");
					Serial.print(hora_alarme[0]);
					Serial.print(":");
					Serial.println(hora_alarme[1]);
				}
			}
		}
	}//Fim if ativo

 } //fim loop

//funções

void rotina()
{
	if(digitalRead(JANELAS_PIR))
	{
		estado = 'a';
		log_alarme = "Invasao por uma das janelas";
		return;
	}
	if(!digitalRead(PORTA_PIR))
	{
		estado = 'a';
		log_alarme = "Invasao pela porta de entrada";
		return;
	}
	if(!digitalRead(CORREDOR_PIR))
	{
		estado = 'a';
		log_alarme = "Houve uma invasao não vista em uma das entradas e que foi verificada pela passagem pelo corredor";
		return;
	}
}

void alarme(int ativar)
{
	if(ativar)
		tone(ALARME, 5000, 200);
	else
		digitalWrite(ALARME, LOW);
}

void atualizar_hora()
{
	String hora;
	Serial.println("Digite a hora atual, no padrão 00:00");
	Serial.println("Incluindo zeros para números menores que 10 e sem espaços (ex. 04:45)");
	while(1)
	{
		if(Serial.available())
		{
			hora = Serial.readString();
			if(hora.length() != 5)
				Serial.println("Ocorreu um erro, horário fora do formato padrão. Por favor, digite novamente");
			else
			break;
		}
	}
	rtc.adjust(DateTime(0, 0, 0, (hora.substring(0, 2)).toInt(), (hora.substring(3, 5)).toInt(), 30));
}




void alt_horario_func()
{
	String hora;
	unsigned int horas;
	unsigned int minutos;
	Serial.println("Digite a hora em que o sistema de alarme será ativado, no padrão 00:00");
	Serial.println("Incluindo zeros para números menores que 10 e sem espaços (ex. 04:45)");
	while(1)
	{
		if(Serial.available())
		{
			hora = Serial.readString();
			Serial.println(hora);
			if(hora.length() != 5)
			Serial.println("Ocorreu um erro, horário fora do formato padrão. Por favor, digite novamente");
			else
			{
				horas = (hora.substring(0,2)).toInt();
				minutos = (hora.substring(3,5)).toInt();

				if(horas < 0 || horas > 23)
					Serial.println("A hora deve ser um valor entre 0 e 23. Por favor, digite novamente");
				else if(minutos <0 || minutos > 59)
					Serial.println("Os minutos devem ser um valor entre 0 e 59. Por favor, digite novamente");
				else
					break;
			}
		}
	}
	horario_inicio = 60*horas + minutos;

	Serial.println("Digite a hora em que o sistema de alarme será desativado, encerrando o intervalo de funcionamento, no padrão 00:00");
	Serial.println("Incluindo zeros para números menores que 10 e sem espaços (ex. 04:45)");
	while(1)
	{
		if(Serial.available())
		{
			hora = Serial.readString();
			Serial.println(hora);
			if(hora.length() != 5) 
			{
				Serial.println("Ocorreu um erro, horário fora do formato padrão. Por favor, digite novamente");
			}
			else
			{
				horas = (hora.substring(0,2)).toInt();
				minutos = (hora.substring(3,5)).toInt();

				if(horas < 0 || horas > 23)
					Serial.println("A hora deve ser um valor entre 0 e 23. Por favor, digite novamente");
				else if(minutos <0 || minutos > 59)
					Serial.println("Os minutos devem ser um valor entre 0 e 59. Por favor, digite novamente");
				else
					break;
			}
		}
	}
	horario_fim = 60*horas + minutos; 
}

void alterar_senha()
{
	Serial.println("Por favor, digite a sua senha novamente:");

	while(1)
	{
		if(Serial.available())
		{
			String aux = Serial.readString();

			if(senha.equals(aux))
			{
				Serial.println("Digite a nova senha: ");
				while(1)
				{
					if(Serial.available())
					{
						senha = Serial.readString();

						if(senha.length() < 4)
						{
							Serial.println("A senha deve ter pelo menos 4 caracteres. Por favor, digite-a novamente.");
						}
						else
						{
							Serial.println("Senha alterada com sucesso");
							break;
						}
					}
				}
				break;
			}
			else
			{
				Serial.println("Senha incorreta, tente novamente");
			}
		}
	}
}
