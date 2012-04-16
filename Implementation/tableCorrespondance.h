
/*************************************************************************
                        Table de correspondance  -  description
                             -------------------
    d�but                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//------------- Interface de <tableCorrespondance> (fichier tableCorrespondance.h) -------------
#ifndef _TABLECORRESPONDANCE
#define _TABLECORRESPONDANCE

//--------------------------------------------------- Interfaces utilis�es

#include <iosLib.h> /* librairie pour les pilotes */
#include "msgQLib.h"
#include "semLib.h"

//------------------------------------------------------------- Constantes

// D�claration des constantes pour la bo�te aux lettres et les messages
#define MAX_MSG 10				/* Nombre maximal de messages sauvegard�s pour un p�riph�rique par le pilote. */
#define MSG_DATE_LENGTH 12		/* Longueur du champ Date dans le message trait� par le pilote. */
#define MSG_USER_LENGTH 16 		/* Longueur du message transmis � l'utilisateur par le pilote - MSG_DATE_LENGTH+4 */
#define MAX_MSG_LENGTH 16 		/* Longueur du message transmis � la boite aux lettres - Contient la date, puis la donn�e du message - MSG_DATE_LENGTH+4 */
#define MAX_NB_MSG 30			/* Nombre de messages maximum pour une liste cha�n�e */
MSG_Q_ID idBoiteAuxLettres;		/* ID de la bo�te aux lettres */

//------------------------------------------------------------------ Types

typedef struct ElemMessage 		/* Structure d'un message dans la liste chainee */
{
	char donnee[2];				/* Teneur du message, transmis par le p�riph�rique. */
	char date[MSG_DATE_LENGTH]; /* Du type "Www Mmm dd hh:mm:ss yyyy" */
	struct ElemMessage* suivant;
} Message;

typedef struct 					/* SDD VxWorks pour un p�riph�rique-capteur */
{ 
	DEV_HDR donnees;			/* SDD standard */
	Message* debutListe; 		/* D�but de la liste cha�n�e de message */
	SEM_ID idSemNoLecteurs;		/* ID du s�maphore FIFO destin�s aux lecteurs sur ce p�riph�rique */
	SEM_ID idSemNoRedacteur;	/* ID du s�maphore FIFO destin� au r�dacteur */
	SEM_ID idSemNbLect;			/* ID du s�maphore NbLect destin�s aux lecteurs sur ce p�riph�rique */
	int nbLect;					/* Nombre de lecteurs en attente de lecture sur ce p�riph�rique. */
	int nbMessage;				/* Nombre de messages dans la liste de messages du p�riph�rique */
} DEV;

typedef struct ElementTable		/* Structure d'une table de correspondance entre le num�ro du capteur et le pointeur vers la structure de donn�e correspondante */
{
	char numCapteur[2];
	DEV* pointeurSDD;
	struct ElementTable* suivant;
} TableCorrespondance;


//----------------------------------------------------- Variables Globales

TableCorrespondance * tableCorrespondance; /* Table de correspondance entre le num�ro du capteur et le pointeur vers la structure de donn�e correspondante. */
SEM_ID idSemTableCorrespondance;/* ID du s�maphore prot�geant la table de correspondance. */



#endif
