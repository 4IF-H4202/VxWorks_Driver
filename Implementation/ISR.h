
/*************************************************************************
							ISR  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//----------- Interface de la procédure <ISR> (fichier ISR.h) ------------
#ifndef _ISR
#define _ISR

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

#define NB_MS_PER_DAY 86400000
#define NB_MS_PER_HOUR 3600000
#define NB_MS_PER_MINUTE 60000

//------------------------------------------------------------------ Types


//------------------------------------------------------------------ Tâche

void monISR(void);
// Mode d'emploi :
//		Traite l'interruption envoyée par les périphériques-capteurs.
//		Consulte le message dans le registre matériel et le transmet au pilote afin de le faire remonter à l'utilisateur si demande.
// Contrat :
//		/


#endif
