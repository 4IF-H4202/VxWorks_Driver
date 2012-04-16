#include <tasklib.h>
#include "ISR.h"
#include "registre.h"
#include "stdio.h"

simulateurPeripherique(int numCapteur, int delaiEntreMessage, int nbBoucles)
// Mode d'emploi :
//		Simule le fonctionnement d'un périphérique-capteur #numCapteur envoyant des messages (entre 00 et 99) à intervalles réguliers (delaiEntreMessage tics).
// Contrat :
//		- 0 <= numCapteur < 100
//		- delaiEntreMessage en nombre de tics
{
	int i = 0;
	int j = 0;
	char numeroCapteur[3];
	char message[2];
	
	numeroCapteur[0] = numCapteur / 10 + 48;
	numeroCapteur[1] = numCapteur % 10 + 48;
	message[0] = '0';
	message[1] = '0';
	
	numeroCapteur[2] = '\0';
				
	for(j = 0; j < nbBoucles; j++)
	{		
		message[0] = 48 + i / 10;
		message[1] = 48 + i % 10;
		
		// Ecriture du message dans le registre :
		registre[0] = numeroCapteur[0];
		registre[1] = numeroCapteur[1];
		registre[2] = message[0];
		registre[3] = message[1];
		
		printf("<Periph n°%s>", numeroCapteur);
		printf("%s\n", message);
		// Lancement de l'IT (ici appel direct de l'ISR) :
		monISR();
		
		i++;
		if (i==100) { i = 0; }

		taskDelay(delaiEntreMessage); // Attente entre l'envoi de deux messages.
	}
}
