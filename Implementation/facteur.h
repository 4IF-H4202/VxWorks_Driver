
/*************************************************************************
						   Facteur  -  description
                             -------------------
    d�but                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//--------- Interface de la t�che <Facteur> (fichier facteur.h) ----------
#ifndef _FACTEUR
#define _FACTEUR


//--------------------------------------------------- Interfaces utilis�es


//------------------------------------------------------------- Constantes

#define PRIORITY_FACTEUR 50		/* Priorit� de la t�che Facteur */

//------------------------------------------------------------------ Types


//------------------------------------------------------------------ T�che

void facteur(void);
// Mode d'emploi :
//		Appartenant au pilote, traite les messages des p�riph�riques mis dans la bo�te aux lettres du pilote par l'ISR, et les redistribue aux SDD correspondant au pilote-envoyeur.
// Contrat :
//		- Bo�te aux lettres initialis�e


#endif