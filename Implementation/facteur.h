
/*************************************************************************
						   Facteur  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//--------- Interface de la tâche <Facteur> (fichier facteur.h) ----------
#ifndef _FACTEUR
#define _FACTEUR


//--------------------------------------------------- Interfaces utilisées


//------------------------------------------------------------- Constantes

#define PRIORITY_FACTEUR 50		/* Priorité de la tâche Facteur */

//------------------------------------------------------------------ Types


//------------------------------------------------------------------ Tâche

void facteur(void);
// Mode d'emploi :
//		Appartenant au pilote, traite les messages des périphériques mis dans la boîte aux lettres du pilote par l'ISR, et les redistribue aux SDD correspondant au pilote-envoyeur.
// Contrat :
//		- Boîte aux lettres initialisée


#endif