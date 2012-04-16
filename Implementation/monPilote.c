
/*************************************************************************
                          MonPilote  -  description
                             -------------------
    d�but                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
*************************************************************************/

//------- R�alisation du module <monPilote> (fichier monPilote.c) --------

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include syst�me
#include <stdlib.h>
#include "stdio.h"
#include <string.h>
#include "taskLib.h"
#include "sysLib.h"
#include "tickLib.h"
//------------------------------------------------------ Include personnel
#include "monPilote.h"
#include "facteur.h"
#include "tableCorrespondance.h"
//----------------------------------------------------------------- PUBLIC

//------------------------------------------------------ Variables priv�es

int idFacteur = 0; /* ID de la t�che Facteur */

//---------------------------------------------------- Variables publiques

drvNumber = -1; 
nbrePeriph = 0;
	
//------------------------------------------------------ Fonctions priv�es

/* D�clarations et impl�mentation des 7 primitives monCreat, monRemove, monOpen, monClose, monRead, monWrite, monIOCtl : */

int monRead(DEV* desc, char * buff, int length) 
// Contrats :
//	- length doit valoir (X*MSG_USER_LENGTH)+1, avec X nombre de messages demand� par l'utilisateur.
{		
	int nbLecteurPrec;
	int nombreMessage = length / MSG_USER_LENGTH;
	Message* pMessage;
	int i,j;
	
	// Erreur - buffer de taille incorrecte :
	if (length % MSG_USER_LENGTH != 1) { return ERROR_BUFFER_SIZE; }


	// Protection par s�maphore type 'Lecteurs/Redacteur' des messages du p�riph�riques :
	
	if (desc == NULL) { return ERROR_DEV_DEL; }
	
	pMessage = desc->debutListe;
	
	// Attente en cas de modification du message (r�dacteur ayant la main) :
	semTake(desc->idSemNoRedacteur, WAIT_SEM_FIFO_LECT);
	
	if (desc == NULL) {
		 semGive(desc->idSemNoRedacteur);
		 return ERROR_DEV_DEL;
	}
	
	// Incr�mentation du nombre de lecteurs sur ce buffer :
	semTake(desc->idSemNbLect, WAIT_SEM_NB_LECT);
	if (desc == NULL) {
		semGive(desc->idSemNbLect);
		semGive(desc->idSemNoRedacteur);
		return ERROR_DEV_DEL;
	}
	
	nbLecteurPrec = desc->nbLect++;
	
	semGive(desc->idSemNbLect);
	
	if (nbLecteurPrec == 0) // S'il s'agit du seul lecteur actuellement :
	{
		// Prise du jeton s�maphore pr�venant d'une lecture en cours :
		semTake(desc->idSemNoLecteurs, WAIT_SEM_MESSAGES);
	}
			
	// Redonne potentiellement la main au r�dacteur pour qu'il s'inscrive dans la "liste d'attente" :
	semGive(desc->idSemNoRedacteur);
	
	// Lecture :
	 
	for (i = 0; i < nombreMessage; i++)
	{
		if (pMessage == NULL) { break;}
		
		// Copie de la date du message courant :
		for (j = 0; j < (MAX_MSG_LENGTH-4); j++)
		{
			buff[i*MSG_USER_LENGTH+j] = pMessage->date[j];
		}
		// S�parateur :
		buff[i*MSG_USER_LENGTH+MAX_MSG_LENGTH-4] = '|';
		// Copie de la donn�e du message courant :
		buff[i*MSG_USER_LENGTH+MAX_MSG_LENGTH-3] = pMessage->donnee[0];
		buff[i*MSG_USER_LENGTH+MAX_MSG_LENGTH-2] = pMessage->donnee[1];
		// S�parateur :
		buff[i*MSG_USER_LENGTH+MAX_MSG_LENGTH-1] = '\n';
		
		
		// Passage au message suivant :
		pMessage = pMessage->suivant;
	}
	
	buff[nombreMessage*MSG_USER_LENGTH] = '\o';
	
	semTake(desc->idSemNbLect, WAIT_SEM_NB_LECT);
	if (desc == NULL) {
		semGive(desc->idSemNoLecteurs);
		return ERROR_DEV_DEL;
	}
	
	nbLecteurPrec = desc->nbLect--;
	
	semGive(desc->idSemNbLect);
	
	if (nbLecteurPrec == 1) // S'il s'agit du dernier lecteur sur ce p�riph�rique :
	{
		// Nous rendons le jeton pr�venant d'une lecture en cours :
		semGive(desc->idSemNoLecteurs);
	}
	
	return i;

}

int monOpen(DEV * desc, char * remainder, int mode)
{
	if (*remainder!='\0')
	{
		return ERROR;
	}
	else
	{
		return ((int) desc) ;
	}
}

int monClose(DEV * desc, char * name)
{
	return 0;
}	

//---------------------------------------------------- Fonctions publiques

int DrvInstall()
{
	int statut;
	if (drvNumber==-1)
	{
		drvNumber = iosDrvInstall ( NULL, NULL, &monOpen, &monClose, &monRead, NULL, NULL) ;
		idSemTableCorrespondance = semMCreate(SEM_Q_PRIORITY); // Initialisation de la table de correspondance
		idBoiteAuxLettres = msgQCreate(MAX_MSG, MAX_MSG_LENGTH, MSG_Q_FIFO); // Initialisation de la boite aux lettres
		// Initialisation de l'horodateur :
		sysAuxClkEnable();
		statut = sysAuxClkRateSet(NB_TICKS_PER_SECOND);
		if (statut != OK) { printf("<Erreur> Horloge secondaire invalide\n"); return -1;}
		tickSet(0);
		
		idFacteur = taskSpawn("Facteur", PRIORITY_FACTEUR, 0, 10000, (FUNCPTR)facteur, 0,0,0,0,0,0,0,0,0,0); // Lancement de la t�che Facteur
	}
	return drvNumber;
}	

int DevAdd(char * name,char numCapteur[2])
{
	DEV * desc = (DEV *)malloc(sizeof(DEV));
	
	if (drvNumber != -1) // Si driver install� :
	{
		// Ajout du p�riph�rique dans la table de correspondance
		semTake(idSemTableCorrespondance, WAIT_FOREVER);
		if (tableCorrespondance==NULL)
		{
			tableCorrespondance = (TableCorrespondance*)malloc(sizeof(TableCorrespondance));
			tableCorrespondance->numCapteur[0]=numCapteur[0];
			tableCorrespondance->numCapteur[1]=numCapteur[1];
			tableCorrespondance->pointeurSDD=desc;
			tableCorrespondance->suivant=NULL;
		}
		else
		{
			TableCorrespondance * nouvelleTete=(TableCorrespondance*)malloc(sizeof(TableCorrespondance));
			nouvelleTete->numCapteur[0]=numCapteur[0];
			nouvelleTete->numCapteur[1]=numCapteur[1];
			nouvelleTete->pointeurSDD=desc;
			nouvelleTete->suivant=tableCorrespondance;
			tableCorrespondance=nouvelleTete;
		}
		
		semGive(idSemTableCorrespondance);
		
		// Initialisation de la SDD du p�riph�riques :
		// Initialisation des s�maphores :
		desc->idSemNoLecteurs = semMCreate(SEM_Q_FIFO);
		desc->idSemNoRedacteur = semMCreate(SEM_Q_FIFO);
		desc->idSemNbLect = semMCreate(SEM_Q_FIFO);
		desc->nbLect = 0;
		desc->debutListe = NULL;
		desc->nbMessage = 0;
		
		iosDevAdd ((DEV_HDR *)desc, name, drvNumber);
		return ++nbrePeriph ;
	}
	else // Driver non install�
		return -1;
}

int DevDel(char * name)
{
	char* suite [1];
	DEV_HDR * pDevHdr; /* structure pour le p�riph�rique */
	Message* precedent;
	Message* courantMessage;
	/* Suppression de la liste des p�riph�riques : */
	pDevHdr = iosDevFind(name,suite);/* recherche du p�riph�rique */
	if ((pDevHdr!= NULL) && (*suite[0]=='\0'))
	{		
		TableCorrespondance* courant;
		
		/* Suppression de l'occurrence dans la table de correspondance : */
		semTake(idSemTableCorrespondance, WAIT_FOREVER);
		courant = tableCorrespondance;
		if ((courant!= NULL) && (&(courant->pointeurSDD->donnees) == pDevHdr))
		{
			tableCorrespondance = courant->suivant;
			// Destruction des s�maphores :
			semDelete(courant->pointeurSDD->idSemNoLecteurs);
			semDelete(courant->pointeurSDD->idSemNoRedacteur);
			semDelete(courant->pointeurSDD->idSemNbLect);
			free(courant);
		}
		else if (courant != NULL)
		{
			while ((courant->suivant != NULL) && (&(courant->suivant->pointeurSDD->donnees) != pDevHdr))
			{
				courant = courant->suivant;
			}
			if (courant->suivant != NULL)
			{
				TableCorrespondance* delete = courant->suivant;
				courant = courant->suivant->suivant;
				
				// Destruction des s�maphores :
				semDelete(delete->pointeurSDD->idSemNoLecteurs);
				semDelete(delete->pointeurSDD->idSemNoRedacteur);
				semDelete(delete->pointeurSDD->idSemNbLect);
				
				// Destruction des listes de message.
				precedent = delete->pointeurSDD->debutListe;
				if (precedent != NULL)
				{					 
					courantMessage = delete->pointeurSDD->debutListe->suivant;
					if (courant == NULL)
					{
						free(precedent);
					}else
					{
						while (courant != NULL)
						{
							free(precedent);
							precedent = courantMessage;
							courantMessage = courantMessage->suivant;
						}
						free(precedent);
					}
				}

				free(delete);
			}
			else
			{
				semGive(idSemTableCorrespondance);
				return ERROR_NOT_IN_TABLE;
			}
		}
		else
		{
			semGive(idSemTableCorrespondance);
			return ERROR_NOT_IN_TABLE;
		}
		
		semGive(idSemTableCorrespondance);
		
		iosDevDelete( pDevHdr );
		free(pDevHdr);
	}
	return 0;
}

int DrvRemove()
{
	/* Suppression de la table des correspondance : */
	TableCorrespondance* delete;
	int ret;/* num�ro du pilote */
	
	while (tableCorrespondance!= NULL){
		delete = tableCorrespondance;
		tableCorrespondance = tableCorrespondance->suivant;
		free(delete);
	}
	semDelete(idSemTableCorrespondance);
	
	/* Suppression de la tache Facteur : */
	taskDelete(idFacteur);
	msgQDelete(idBoiteAuxLettres);
	
	/* Suppression du pilote : */
	
	if (drvNumber != -1)
	{ 
		ret = iosDrvRemove( drvNumber,FALSE) ;
		drvNumber = -1 ;
	}
	return ret ;
}
