
/*************************************************************************
						  monPilote  -  description
                             -------------------
    d�but                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//--------- Interface du module <monPilote> (fichier monPilote.h) --------
#ifndef _MON_PILOTE
#define _MON_PILOTE

//--------------------------------------------------- Interfaces utilis�es

#include <iosLib.h> /* librairie pour les pilotes */

//------------------------------------------------------------- Constantes

// D�claration des constantes de retour d'erreur :
#define ERROR_NOT_IN_TABLE -10 	/* Erreur en cas de p�riph�rique non retrouv� dans la table de correspondance. */
#define ERROR_DEV_DEL -20		/* Erreur en cas de p�riph�riques d�sinstall� entre temps. */
#define ERROR_DEV_NOT_FOUND -30 /* Erreur lorsque l'utilisateur cherche un p�riph�rique qui n'existe pas. */
#define ERROR_BUFFER_SIZE -40 	/* Erreur renvoy�e en cas de passage de buffer de taille incorrecte lors d'un read() */


// D�claration des constantes pour les s�maphores :
#define WAIT_SEM_FIFO_LECT -1	/* Temps d'attente max. (en tic) par les lecteurs sur le s�maphore FIFO */
#define WAIT_SEM_NB_LECT -1		/* Temps d'attente max. (en tic) par les lecteurs sur le s�maphore Nb_Lect */
#define WAIT_SEM_MESSAGES -1	/* Temps d'attente max. (en tic) par les lecteurs et r�dacteurs sur le s�maphore Messages */

// D�claration des constantes pour l'horodateur :
#define NB_TICKS_PER_SECOND 1000	/* Fr�quence de l'horodateur */

//----------------------------------------------------- Variables globales

int drvNumber;					/* Num�ro du driver sur le syst�me. */
int nbrePeriph;					/* Nombre de p�riph�riques install�s pour ce pilote. */
int timestampStart;				/* Timestamp � l'installation du syst�me, pour passer d'un horodatage relatif en absolu */

//---------------------------------------------------- Fonctions publiques

int DrvInstall(); 				/* Primitive d�installation du pilote */
// Mode d'emploi :
//		Installe le pilote sur le syst�me (s'il n'�tait pas encore install�), et retourne son num�ro ou un code d'erreur.
// Contrat :
//		/

int DrvRemove(); 				/* Primitive de d�sinstallation du pilote */
// Mode d'emploi :
//		D�sinstalle le pilote sur le syst�me, et retourne le code d'erreur adapt�.
// Contrat :
//		- Les p�riph�riques restants ne sont pas d�sinstall�s.

int DevAdd(char * name, char numCapteur[2]); /* Primitive d�ajout d'un p�riph�rique */
// Mode d'emploi :
//		Ajoute un p�riph�rique � ceux trait�s par le pilote, et retourne le nombre actuel de p�riph�riques li�s, ou un code d'erreur.
// Contrat :
//		/

int DevDel(char * name); 		/* Primitive de suppression d'un p�riph�rique */
// Mode d'emploi :
//		D�sinstalle le pilote sur le syst�me, et retourne un code de retour.
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
