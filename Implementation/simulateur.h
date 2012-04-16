
/*************************************************************************
                        Simulateur  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//------- Interface de la tâche <Simulateur> (fichier simulateur.h) ------
#ifndef _SIMULATEUR
#define _SIMULATEUR

//--------------------------------------------------- Interfaces utilisées


//------------------------------------------------------------- Constantes

#define  PRIORITY_SIMULATEUR 120 /* Priorité de la tâche Simulateur */

//------------------------------------------------------------------ Types


//------------------------------------------------------------------ Tâche

void simulateur(void);
// Mode d'emploi :
//		Simule l'utilisation du pilote MonPilote, à des fins de tests.
//		Cette fonction simule 3 acteurs :
//			- Les périphériques physiques, en remplaçant les registres matériels par des variables globales.
//			- Les utilisateurs désirant consulter les messages envoyés par les périphériques.
//			- L'administrateur, chargé de l'installation et désinstallation du pilote et des périphériques.
//		Teste à travers diverses procédures les cas de bords relevés dans la spécification du pilote.
// Contrat :
//		/




#endif
