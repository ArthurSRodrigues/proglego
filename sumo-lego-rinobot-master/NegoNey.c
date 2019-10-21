#pragma config(Sensor, S1,     0,               sensorSONAR)
#pragma config(Sensor, S2,     1,              sensorSONAR)
#pragma config(Sensor, S3,     2,              sensorSONAR)
#pragma config(Sensor, S4,     3,            sensorI2CHiTechnicAccel)
#pragma config(Motor,  motorA,          A,             tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          E,             tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          D,             tmotorNXT, PIDControl, reversed, encoder)
//*!!Code aumtoatialcly generated by 'ROBOTC' configuration wizard               !!*//

float kVelocidade = 2.07;

#include "includes/configurarVariaveis.h"
#include "includes/configuracaoManual.h"
#include "includes/atualizarDisplay.h"
#include "visao/filtroMediaMovel.h"
#include "visao/tratamentoSensores.h"
#include "includes/monitoramento.h"
#include "movimentacao/3Motores.h"
#include "estrategias/NegoNey.h"

task AtualizarSensores();
task SimularSensores();
bool simular = false;

task main()
{
	bPlaySounds = true;
	UnmuteSound();
	nVolume = 2;
	setBluetoothOn();
	btConnect(1, "NXT");
	clearDebugStream();

	ConfigurarVariaveis();
	Esperar = GerarMenu(Esperar5s, 2);
	EstrategiaSelecionada = GerarMenu(Estrategias, NumEstrategias);
	AcelerometroCair = GerarMenu(MenuAcelerometro, 2);
	PressioneStart();

	ClearTimer(T1);

	//StartTask(Monitoramento);
	StartTask(AtualizarDisplay);
	StartTask(AtualizarSensores);
	if(simular){
		StartTask(SimularSensores);
	}
	StartTask(TratarSensores);

	if(Esperar){
		FuncaoEsperar();
	}

	//StartTask(medirTempo);

	iniciarEstrategia();

	StartTask(Movimentacao);

	while(true){}
}

//==============================FUNCOES===================================================


task AtualizarSensores(){
	while(true){
		FiltrarSensor(SonarEsquerdo, simular);
		FiltrarSensor(SonarDireito, simular);
		FiltrarSensor(SonarCentro, simular);
		ProcessarAcelerometro();
	}
}

task SimularSensores(){
	int min = 50;
	int max = 150;

	srand(nSysTime);

	while(true)
	{
		if(nNxtButtonPressed == BotaoLaranja){
			NovoValor = 255;
		}
		else{
			NovoValor = 80;
		}
		//NovoValor = (rand() % (max-min)) + min;
		//wait1Msec(77);
	}
}
