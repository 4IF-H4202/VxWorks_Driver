#include "monPilote.h"
#include "stdio.h"
#include <stdlib.h>

void simulateurApplication(int numAppli, int numCapteur, int delaiEntreMessage, int nbMessagesLus, int nbBoucles)
// Mode d'emploi :
//		Simule le fonctionnement d'une application #numAppli consultant le capteur nommé "pXX" (avec <XX> = numCapteur) à intervalles réguliers (delaiEntreMessage tics), et imprimant les messages recus à l'écran.
// Contrat :
//		- 0 <= numCapteur < 100
//		- delaiEntreMessage en nombre de tics
{
	int monFD, statut;
	char* buffer;
	char nomPeriph[4];
	int j;
	
	nomPeriph[0] = 'p';
	nomPeriph[1] = numCapteur / 10 + 48;
	nomPeriph[2] = numCapteur % 10 + 48;
	nomPeriph[3] = '\0';
	
	monFD = open(nomPeriph, O_RDONLY, 0);

	buffer = (char *)malloc((16*nbMessagesLus+1)*sizeof(char));
	
	printf("- Appli n°%d : Ouverture du FD du périphérique %s - Début de lecture\n", numAppli, nomPeriph);
				
	for(j = 0; j < nbBoucles; j++)
	{		
		statut = read(monFD, buffer, 16*nbMessagesLus+1);
		printf("- Appli n°%d : Message lu - %s \t(statut : %d)\n", numAppli, buffer, statut);
	}
	
	close(monFD);
	free(buffer);
	
	return;
}
