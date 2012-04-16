#include "stdio.h"
#include "monPilote.h"
#include "taskLib.h"
#include "simulateur.h"
#include "ISR.h"
#include "registre.h"

int main(void)
{
	
	
//	int numPilote = DrvInstall();
//	if (numPilote == -1) { return -1; }
//	{
//	int numPeriph42 = DevAdd("p42", "42");
//	int numPeriph66 = DevAdd("p66", "66");
//	int numPeriph00 = DevAdd("p00", "00");
//	int monFd42;
//	int monFd66;
//	char buffer[150];
//	iosDevShow();
//	DevDel("p00");
//	iosDevShow();
//
//	
//	registre[0] = '4';
//	registre[1] = '2';
//	registre[2] = '7';
//	registre[3] = '3';
//	monISR();
//	
//	monFd42 = open("p42", O_RDONLY,0);
//	monFd66 = open("p66", O_RDONLY,0);
//	read(monFd42, buffer, 17);
//	printf(buffer);
//	
//	DevDel("p42");
//	DevDel("p66");
//	DrvRemove();
//	message
//	}
	
	simulateur();
	return 1;
}

/*
int main(void)
{
	int numPilote = -1;
	int idSimulateur = -1;
	numPilote = DrvInstall();
	
	if (numPilote != -1) {
		int numPeriph = DevAdd("monPeriph", "42");
		int monFd = open("monPeriph", O_RDONLY,0);
		
		iosDevShow();
		DevDel("monPeriph");
	}else
		printf("Erreur... ;\n");
	printf("%d \n",numPilote);
	iosDrvShow();
	
	idSimulateur = taskSpawn("Simulateur", PRIORITY_SIMULATEUR, 0, 10000, (FUNCPTR)simulateur, 0,0,0,0,0,0,0,0,0,0);
			
	
	DrvRemove();
	iosDrvShow();
	
	taskDelete(idSimulateur);
	
	return 10;
}
*/
