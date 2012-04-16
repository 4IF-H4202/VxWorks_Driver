
/*************************************************************************
							ISR  -  description
                             -------------------
    d�but                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//----------- Interface de la proc�dure <ISR> (fichier ISR.h) ------------
#ifndef _ISR
#define _ISR

//--------------------------------------------------- Interfaces utilis�es

//------------------------------------------------------------- Constantes

#define NB_MS_PER_DAY 86400000
#define NB_MS_PER_HOUR 3600000
#define NB_MS_PER_MINUTE 60000

//------------------------------------------------------------------ Types


//------------------------------------------------------------------ T�che

void monISR(void);
// Mode d'emploi :
//		Traite l'interruption envoy�e par les p�riph�riques-capteurs.
//		Consulte le message dans le registre mat�riel et le transmet au pilote afin de le faire remonter � l'utilisateur si demande.
// Contrat :
//		/


#endif
