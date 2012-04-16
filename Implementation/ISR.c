
/*************************************************************************
                             ISR  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
*************************************************************************/

//---------- Réalisation de la procédure <ISR> (fichier ISR.c) -----------

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <time.h>
#include <stdlib.h>
#include "msgQLib.h"
#include "tickLib.h"

//------------------------------------------------------ Include personnel
#include "ISR.h"
#include "monPilote.h"
#include "tableCorrespondance.h"
#include "registre.h"

#define MAP
#ifdef MAP
	#include "stdio.h"
#endif
//----------------------------------------------------------------- PUBLIC

//---------------------------------------------------- Fonctions publiques

void monISR(void)
{
	int i;
	// Datation du message :
	// time_t date = time(NULL);
	char message[MAX_MSG_LENGTH];
	// char* pdate = ctime(&date);
	ULONG nbTicks = tickGet(); 
	
	// Conversion timestamp :
	nbTicks = nbTicks % NB_MS_PER_DAY;
	message[0] = 48 + (nbTicks / NB_MS_PER_HOUR) / 10; // Dizaine d'heures
	message[1] = '0' + (nbTicks / NB_MS_PER_HOUR) % 10; // Unité d'heures
	message[2] = ':';
	nbTicks = nbTicks % NB_MS_PER_HOUR;
	message[3] = '0' + (nbTicks / NB_MS_PER_MINUTE) / 10; // Dizaine de minutes
	message[4] = '0' + (nbTicks / NB_MS_PER_MINUTE) % 10; // Unités de minutes
	message[5] = ':';
	nbTicks = nbTicks % NB_MS_PER_MINUTE;
	message[6] = '0' + (nbTicks / 1000) / 10; // Dizaine de secondes
	message[7] = '0' + (nbTicks / 1000) % 10; // Unités de secondes
	message[8] = '-';
	nbTicks = nbTicks % 1000;
	message[9] = '0' + nbTicks / 100; // Centaine de ms
	nbTicks = nbTicks % 100;
	message[10] = '0' + nbTicks / 10; // Dizaine de ms
	message[11] = '0' + nbTicks % 10; // Unité de ms
	
	// Récupération du message dans le registre matériel (ici une var. globale):
	for (i = 0; i < 4; i++ )
	{
		message[12+i] = registre[i];
	}

	// Envoi du message dans la boîte aux lettres :
	//msgQShow(idBoiteAuxLettres, 1);
	msgQSend (idBoiteAuxLettres, (char*)&message, sizeof(message), WAIT_FOREVER,MSG_PRI_NORMAL);

	
	return;
	
}
