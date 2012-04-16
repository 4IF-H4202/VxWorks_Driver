
/*************************************************************************
                           Facteur  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
*************************************************************************/

//-------- Réalisation de la tâche <Facteur> (fichier facteur.c) ---------

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include "msgQLib.h"
#include <stdlib.h>
#include "semLib.h"
#include <stdio.h>

//------------------------------------------------------ Include personnel
#include "facteur.h"
#include "tableCorrespondance.h"
//----------------------------------------------------------------- PUBLIC

//---------------------------------------------------- Fonctions publiques

void facteur(void)
{
	char buffer[MAX_MSG_LENGTH];
	int statut;
	DEV* pointeurSDD;
	Message* message;
	int i, nbMessages;
	for (;;)
	{						
		// Attente d'un message :
		statut = msgQReceive (idBoiteAuxLettres, buffer, MAX_MSG_LENGTH, WAIT_FOREVER);

		if (statut == MAX_MSG_LENGTH)
		{
			TableCorrespondance* parcours=tableCorrespondance;
			pointeurSDD = NULL;
			
			/* Recherche du périph correspondant dans la table de correspondance */
			while ((parcours != NULL) && (pointeurSDD == NULL)) 
			{
				if ((buffer[MAX_MSG_LENGTH-4]==parcours->numCapteur[0]) && (buffer[MAX_MSG_LENGTH-3]==parcours->numCapteur[1]))
				{
					pointeurSDD = parcours->pointeurSDD;
				}else
				{
					parcours = parcours->suivant;
				}
			}	
			
			if (pointeurSDD == NULL) {
				printf("<Erreur> Facteur : Périphérique non reconnu.\n");
				
			}
			else {
			
				/* Copie du message dans la SDD, en début de liste. */
				
				// Mise dans la liste d'attente de la demande d'écriture :
				semTake(pointeurSDD->idSemNoRedacteur, WAIT_FOREVER);
				
				// Prise du jeton de consultation quand 0 lecteur :
				semTake(pointeurSDD->idSemNoLecteurs, WAIT_FOREVER);
				semGive(pointeurSDD->idSemNoLecteurs);
				
				message = (Message*)malloc(sizeof(Message));
				
				for (i=0;i<(MAX_MSG_LENGTH-4);i++)
				{
					message->date[i] = buffer[i];
				}
				message->donnee[0] = buffer[MAX_MSG_LENGTH-2];
				message->donnee[1] = buffer[MAX_MSG_LENGTH-1];
				
				message->suivant = pointeurSDD->debutListe;
				pointeurSDD->debutListe = message;
				
				pointeurSDD->nbMessage++;
				
				if (pointeurSDD->nbMessage > MAX_NB_MSG)
				{
					Message* msgCourant = pointeurSDD->debutListe;
					Message* aSupprimer;
					int iii, nbIteration = MAX_NB_MSG - 5 ;
					for (iii = 0; iii< nbIteration ; iii++)
					{
						msgCourant = msgCourant->suivant;					
					}
					aSupprimer = msgCourant-> suivant;
					while (msgCourant != NULL)
					{
						free(msgCourant);
						pointeurSDD->nbMessage--;
						msgCourant = aSupprimer;
						if (aSupprimer != NULL)
						{
							aSupprimer = aSupprimer->suivant;
						}
					}
				}
				
				// Retour du jeton :
				semGive(pointeurSDD->idSemNoRedacteur);
			}
		}
	}
}
