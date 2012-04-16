
/*************************************************************************
                        Simulateur  -  description
                             -------------------
    d�but                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
 *************************************************************************/

//------- Interface de la t�che <Simulateur> (fichier simulateur.h) ------
#ifndef _SIMULATEUR
#define _SIMULATEUR

//--------------------------------------------------- Interfaces utilis�es


//------------------------------------------------------------- Constantes

#define  PRIORITY_SIMULATEUR 120 /* Priorit� de la t�che Simulateur */

//------------------------------------------------------------------ Types


//------------------------------------------------------------------ T�che

void simulateur(void);
// Mode d'emploi :
//		Simule l'utilisation du pilote MonPilote, � des fins de tests.
//		Cette fonction simule 3 acteurs :
//			- Les p�riph�riques physiques, en rempla�ant les registres mat�riels par des variables globales.
//			- Les utilisateurs d�sirant consulter les messages envoy�s par les p�riph�riques.
//			- L'administrateur, charg� de l'installation et d�sinstallation du pilote et des p�riph�riques.
//		Teste � travers diverses proc�dures les cas de bords relev�s dans la sp�cification du pilote.
// Contrat :
//		/




#endif
