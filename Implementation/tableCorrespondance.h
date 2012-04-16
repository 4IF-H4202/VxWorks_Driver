
/*************************************************************************
                        Table de correspondance  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//------------- Interface de <tableCorrespondance> (fichier tableCorrespondance.h) -------------
#ifndef _TABLECORRESPONDANCE
#define _TABLECORRESPONDANCE

//--------------------------------------------------- Interfaces utilisées

#include <iosLib.h> /* librairie pour les pilotes */
#include "msgQLib.h"
#include "semLib.h"

//------------------------------------------------------------- Constantes

// Déclaration des constantes pour la boîte aux lettres et les messages
#define MAX_MSG 10				/* Nombre maximal de messages sauvegardés pour un périphérique par le pilote. */
#define MSG_DATE_LENGTH 12		/* Longueur du champ Date dans le message traité par le pilote. */
#define MSG_USER_LENGTH 16 		/* Longueur du message transmis à l'utilisateur par le pilote - MSG_DATE_LENGTH+4 */
#define MAX_MSG_LENGTH 16 		/* Longueur du message transmis à la boite aux lettres - Contient la date, puis la donnée du message - MSG_DATE_LENGTH+4 */
#define MAX_NB_MSG 30			/* Nombre de messages maximum pour une liste chaînée */
MSG_Q_ID idBoiteAuxLettres;		/* ID de la boîte aux lettres */

//------------------------------------------------------------------ Types

typedef struct ElemMessage 		/* Structure d'un message dans la liste chainee */
{
	char donnee[2];				/* Teneur du message, transmis par le périphérique. */
	char date[MSG_DATE_LENGTH]; /* Du type "Www Mmm dd hh:mm:ss yyyy" */
	struct ElemMessage* suivant;
} Message;

typedef struct 					/* SDD VxWorks pour un périphérique-capteur */
{ 
	DEV_HDR donnees;			/* SDD standard */
	Message* debutListe; 		/* Début de la liste chaînée de message */
	SEM_ID idSemNoLecteurs;		/* ID du sémaphore FIFO destinés aux lecteurs sur ce périphérique */
	SEM_ID idSemNoRedacteur;	/* ID du sémaphore FIFO destiné au rédacteur */
	SEM_ID idSemNbLect;			/* ID du sémaphore NbLect destinés aux lecteurs sur ce périphérique */
	int nbLect;					/* Nombre de lecteurs en attente de lecture sur ce périphérique. */
	int nbMessage;				/* Nombre de messages dans la liste de messages du périphérique */
} DEV;

typedef struct ElementTable		/* Structure d'une table de correspondance entre le numéro du capteur et le pointeur vers la structure de donnée correspondante */
{
	char numCapteur[2];
	DEV* pointeurSDD;
	struct ElementTable* suivant;
} TableCorrespondance;


//----------------------------------------------------- Variables Globales

TableCorrespondance * tableCorrespondance; /* Table de correspondance entre le numéro du capteur et le pointeur vers la structure de donnée correspondante. */
SEM_ID idSemTableCorrespondance;/* ID du sémaphore protégeant la table de correspondance. */



#endif
