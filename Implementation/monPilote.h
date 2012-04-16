
/*************************************************************************
						  monPilote  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//--------- Interface du module <monPilote> (fichier monPilote.h) --------
#ifndef _MON_PILOTE
#define _MON_PILOTE

//--------------------------------------------------- Interfaces utilisées

#include <iosLib.h> /* librairie pour les pilotes */

//------------------------------------------------------------- Constantes

// Déclaration des constantes de retour d'erreur :
#define ERROR_NOT_IN_TABLE -10 	/* Erreur en cas de périphérique non retrouvé dans la table de correspondance. */
#define ERROR_DEV_DEL -20		/* Erreur en cas de périphériques désinstallé entre temps. */
#define ERROR_DEV_NOT_FOUND -30 /* Erreur lorsque l'utilisateur cherche un périphérique qui n'existe pas. */
#define ERROR_BUFFER_SIZE -40 	/* Erreur renvoyée en cas de passage de buffer de taille incorrecte lors d'un read() */


// Déclaration des constantes pour les sémaphores :
#define WAIT_SEM_FIFO_LECT -1	/* Temps d'attente max. (en tic) par les lecteurs sur le sémaphore FIFO */
#define WAIT_SEM_NB_LECT -1		/* Temps d'attente max. (en tic) par les lecteurs sur le sémaphore Nb_Lect */
#define WAIT_SEM_MESSAGES -1	/* Temps d'attente max. (en tic) par les lecteurs et rédacteurs sur le sémaphore Messages */

// Déclaration des constantes pour l'horodateur :
#define NB_TICKS_PER_SECOND 1000	/* Fréquence de l'horodateur */

//----------------------------------------------------- Variables globales

int drvNumber;					/* Numéro du driver sur le système. */
int nbrePeriph;					/* Nombre de périphériques installés pour ce pilote. */
int timestampStart;				/* Timestamp à l'installation du système, pour passer d'un horodatage relatif en absolu */

//---------------------------------------------------- Fonctions publiques

int DrvInstall(); 				/* Primitive d’installation du pilote */
// Mode d'emploi :
//		Installe le pilote sur le système (s'il n'était pas encore installé), et retourne son numéro ou un code d'erreur.
// Contrat :
//		/

int DrvRemove(); 				/* Primitive de désinstallation du pilote */
// Mode d'emploi :
//		Désinstalle le pilote sur le système, et retourne le code d'erreur adapté.
// Contrat :
//		- Les périphériques restants ne sont pas désinstallés.

int DevAdd(char * name, char numCapteur[2]); /* Primitive d’ajout d'un périphérique */
// Mode d'emploi :
//		Ajoute un périphérique à ceux traités par le pilote, et retourne le nombre actuel de périphériques liés, ou un code d'erreur.
// Contrat :
//		/

int DevDel(char * name); 		/* Primitive de suppression d'un périphérique */
// Mode d'emploi :
//		Désinstalle le pilote sur le système, et retourne un code de retour.
// Contrat :
//		/

int DrvConfig(); 				/* Primitive de configuration */
// Mode d'emploi :
//		XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Contrat :
//		/

int InfoDrv(); 					/* Primitive de test */
// Mode d'emploi :
//		XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// Contrat :
//		/

#endif
