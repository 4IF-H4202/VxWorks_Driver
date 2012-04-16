
/*************************************************************************
                         Simulateur  -  description
                             -------------------
    début                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
*************************************************************************/

//-------- Réalisation de la tâche <Simulateur> (fichier simulateur.c) ---

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
//#include <sysLib.h>
#include <time.h>
#include <stdio.h>
#include "taskLib.h"
//------------------------------------------------------ Include personnel

#include "simulateur.h"
#include "simulateurApplication.h"
#include "simulateurPeripherique.h"
#include "ISR.h"
#include "monPilote.h"
#include "registre.h"

//----------------------------------------------------------------- PUBLIC

//------------------------------------------------------ Fonctions privées

int test1()
{
	int numPilote;
	/* ------------------------------------------
		TEST #1.1 : Ajout du pilote
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #1 : Ajout du pilote\n");
	printf("------------------------------------------\n\n");
	
	numPilote = DrvInstall();
	if (numPilote != -1)
	{
		printf("\tInstallation -> OK\n");
		printf("\tN° du pilote : %d\n", numPilote);
		printf("Liste des périphériques du système :\n");
		iosDrvShow();
	}
	else { 
		printf("\tInstallation -> ERREUR\n");
		printf("\tN° de l'erreur : %d\n", numPilote);
		iosDrvShow();
		return -1;
	}
	
	return 0;
}

void test1_2()
{
	/* ------------------------------------------
		TEST #1.2 : Ajout du pilote déja installé
	   ------------------------------------------ */
	int numPilote;
	printf("------------------------------------------\n");
	printf("\tTEST #1.2 : Ajout du pilote alors que deja installe\n");
	printf("------------------------------------------\n\n");
	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	
	numPilote = DrvInstall();
	
}

void test2_1()
{   
	/* ------------------------------------------
		TEST #2.1 : Ajout de périphériques
	   ------------------------------------------ */
	 
	int numPeriph00, numPeriph01, numPeriph42;
	
	printf("------------------------------------------\n");
	printf("\tTEST #2.1 : Ajout de périphériques\n");
	printf("------------------------------------------\n\n");   
	
	numPeriph00 = DevAdd("p00", "00");
	numPeriph01 = DevAdd("p01", "01");
	numPeriph42 = DevAdd("p42", "42");
	
	printf("\tAjout des peripheriques \"p00\", \"p01\" et \"p42\" - Verification :\n");
	iosDevShow();
}

void test2_2()
{
	/* ------------------------------------------
		TEST #2.2 : Ajout de périphériques déja présents
	   ------------------------------------------ */
	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	
	int numPeriph42;
	   
	printf("------------------------------------------\n");
	printf("\tTEST #2 : Ajout d'un périphérique déja présent\n");
	printf("------------------------------------------\n\n");   

	numPeriph42 = DevAdd("p42", "42");
	
	printf("\tRé-ajout du périphérique \"p42\" - Vérification :\n");
	iosDevShow();
}

void test3_1()
{	
	/* ------------------------------------------
		TEST #3.1 : Suppression de périphérique existant
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #2 : Suppression d'un périphérique existant\n");
	printf("------------------------------------------\n\n");  
	   
	DevDel("p42");   
	printf("\tSuppression du périphérique \"p42\" - Vérification :\n");
	iosDevShow(); 
}

void test3_2()
{
	/* ------------------------------------------
		TEST #3.2 : Suppression de périphérique inexistant
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #2 : Suppression d'un périphérique inexistant\n");
	printf("------------------------------------------\n\n");  
	   
	DevDel("p42");   
	printf("\tSuppression du périphérique \"p42\" - Vérification :\n");
	iosDevShow(); 
}
	
	
void test4()
{	
	int statut, monFd00;
	char buffer[17];
	int i ;
	/* ------------------------------------------
		TEST #4 : Réception d'un message périphérique et lecture
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #4.1 : Réception d'un message périphérique et lecture\n");
	printf("------------------------------------------\n\n");  
	   
	registre[0] = '0';
	registre[1] = '0';
	registre[2] = '7';
	registre[3] = '3';
	monISR();
	
	printf("\t Message \"73\" envoyé par le périphérique \"p00\".\n");
	monFd00 = open("p00", O_RDONLY,0);
	statut = read(monFd00, buffer, 17);
	printf("\t Message reçu par l'application : %s \t(statut : %d)\n", buffer, statut);
	printf("\t Re-lectures multiples de ce message :\n");
	
	for (i = 2; i < 10; i++)
	{
		statut = read(monFd00, buffer, 17);
		printf("\t\t - Lecture n°%d : %s \t(statut : %d)\n", i, buffer, statut);
	}
	
	close(monFd00);
}

void test4_2()
{	
	/* ------------------------------------------
		TEST #4.2 : Tentative de lecture sur un périphérique silencieux
	   ------------------------------------------ */
	
	int statut, monFd01;
	char buffer[17];  
	printf("------------------------------------------\n");
	printf("\tTEST #4.2 : Tentative de lecture sur un périphérique silencieux\n");
	printf("------------------------------------------\n\n");  
	
	printf("\t Tentative de lecture sur le périphérique \"p01\", n'ayant jamais envoyé de message.\n");
	monFd01 = open("p01", O_RDONLY,0);
	statut = read(monFd01, buffer, 17);
	printf("\t Message reçu par l'application : %s \t(statut : %d)\n", buffer, statut);
	   
	close(monFd01);
}	   


void test4_3()
{	
	int statut, monFd00;
	char buffer[9];	
	/* ------------------------------------------
		TEST #4.3 : Tentative de lecture avec un buffer de taille incorrecte :
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #4.3 : Tentative de lecture avec un buffer de taille incorrecte\n");
	printf("------------------------------------------\n\n");  
	
	printf("\t Tentative de lecture du dernier message \"73\" sur le périphérique \"p00\", avec en entrer un buffer trop petit.\n");
	monFd00 = open("p00", O_RDONLY,0);
	statut = read(monFd00, buffer, 9);
	printf("\t Message reçu par l'application : %s \t(statut : %d)\n", buffer, statut);
	   
	close(monFd00); 
}	

void test4_4()
{	
	int statut, monFd00;
	char buffer[16*3+1];	   
	/* ------------------------------------------
		TEST #4.4 : Tentative de lecture de plusieurs messages simultanés :
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #4.4 : Tentative de lecture de plusieurs messages simultanés\n");
	printf("------------------------------------------\n\n");  
	
	registre[0] = '0';
	registre[1] = '0';
	registre[2] = '7';
	registre[3] = '4';
	monISR();
	registre[0] = '0';
	registre[1] = '0';
	registre[2] = '7';
	registre[3] = '5';
	monISR();
	
	printf("\t Message \"74\" envoyé par le périphérique \"p00\".\n");
	printf("\t Message \"75\" envoyé par le périphérique \"p00\".\n");
	printf("\t Lecture des 3 derniers messages envoyés par ce périphérique :\n");
	monFd00 = open("p00", O_RDONLY,0);
	statut = read(monFd00, buffer, 16*3+1);
	printf("%s \t(statut : %d)\n", buffer, statut);
	   
	close(monFd00); 
}
	   
	  
void test4_5()
{	
	int statut, monFd00;
	char buffer[16*3+1];	  
	/* ------------------------------------------
		TEST #4.5 : Tentative de lecture de X messages simultanés, X > nombre de messages sauvegardables par le pilote :
	   ------------------------------------------ */
	   
	   // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	   
	printf("------------------------------------------\n");
	printf("\tTEST #4.5 : Tentative de lecture de X messages simultanés, X > nombre de messages sauvegardables par le pilote\n");
	printf("------------------------------------------\n\n");  
	
	registre[0] = '0';
	registre[1] = '0';
	registre[2] = '7';
	registre[3] = '4';
	monISR();
	registre[0] = '0';
	registre[1] = '0';
	registre[2] = '7';
	registre[3] = '5';
	monISR();
	
	printf("\t Message \"74\" envoyé par le périphérique \"p00\".\n");
	printf("\t Message \"75\" envoyé par le périphérique \"p00\".\n");
	printf("\t Lecture des 3 derniers messages envoyés par ce périphérique :\n");
	monFd00 = open("p00", O_RDONLY,0);
	statut = read(monFd00, buffer, 16*3+1);
	printf("%s \t(statut : %d)\n", buffer, statut);
	   
	close(monFd00);
}	

void test5()
{	
	int idSimulPeriph, idSimulAppli;
	/* ------------------------------------------
		TEST #5 : Lecture & Ecriture simultanées :
	   ------------------------------------------ */

	   
	printf("------------------------------------------\n");
	printf("\tTEST #5.1 : Lecture & Ecriture simultanées (1 Periphérique, 1 Lecteur)\n");
	printf("------------------------------------------\n\n");  

	
	printf("\t Lancement d'une tâche simulant un capteur délivrant un message à intervalles réguliers.\n");
	printf("\t Lancement d'une tâche simulant une application n°1 consultant ce périphérique à intervalles réguliers 2x plus rapides.\n");
	printf("\t Résultat :\n");
	
	idSimulPeriph = taskSpawn("SimulateurPeripherique", 56, 0, 10000, (FUNCPTR)simulateurPeripherique, 0, 10, 10,0,0,0,0,0,0,0); // Lancement de la tâche Periph
	idSimulAppli = taskSpawn("SimulateurApplication", 91, 0, 10000, (FUNCPTR)simulateurApplication, 1, 0, 5, 1, 25,0,0,0,0,0); // Lancement de la tâche Appli
	taskDelay(50);
}

void test5_2()
{	
	int idSimulPeriph, idSimulAppli, idSimulAppli2, idSimulAppli3;
	/* ------------------------------------------
		TEST #5 : Lecture & Ecriture simultanées :
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #5.2 : Lecture & Ecriture simultanées (1 Periphérique, N Lecteurs)\n");
	printf("------------------------------------------\n\n");  

	
	printf("\t Lancement d'une tâche simulant un capteur délivrant un message à intervalles réguliers.\n");
	printf("\t Lancement d'une tâche simulant une application n°1 consultant ce périphérique à intervalles réguliers 2x plus rapides.\n");
	printf("\t Lancement d'une tâche simulant une application n°2 consultant ce périphérique à intervalles réguliers 0.5x plus rapides.\n");
	printf("\t Lancement d'une tâche simulant une application n°3 consultant ce périphérique à intervalles réguliers 5x plus rapides.\n");
	printf("\t Résultat :\n");
	
	idSimulPeriph = taskSpawn("SimulateurPeriphérique", 90, 0, 10000, (FUNCPTR)simulateurPeripherique, 0, 10, 10,0,0,0,0,0,0,0); // Lancement de la tâche Periph
	idSimulAppli = taskSpawn("SimulateurApplication1", 91, 0, 10000, (FUNCPTR)simulateurApplication, 1, 0, 5, 1, 30,0,0,0,0,0); // Lancement de la tâche Appli
	idSimulAppli2 = taskSpawn("SimulateurApplication2", 92, 0, 10000, (FUNCPTR)simulateurApplication, 1, 0, 20, 1, 30,0,0,0,0,0); // Lancement de la tâche Appli
	idSimulAppli3 = taskSpawn("SimulateurApplication3", 93, 0, 10000, (FUNCPTR)simulateurApplication, 1, 0, 2, 1, 30,0,0,0,0,0); // Lancement de la tâche Appli
	taskDelay(60);
}

//---------------------------------------------------- Fonctions publiques

void simulateur(void)
{


	// AJOUT DE PILOTE
	//		TEST #1.1 : Ajout du pilote
	test1();
	// 		TEST #1.2 : Ajout du pilote déja installé
	test1_2();
	

	// AJOUT DE PERIPHERIQUES
	//		TEST #2.1 : Ajout de périphériques
	test2_1();
	//		TEST #2.2 : Ajout de périphériques déja présents XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	test2_2();
	
	
	// SUPPRESSION DE PERIPHERIQUES
	//		TEST #3.1 : Suppression de périphérique existant
	test3_1();
	//		TEST #3.2 : Suppression de périphérique inexistant
	test3_2();
	
	
	// LECTURE ET ECRITURES SIMPLES :
	//		TEST #4 : Réception d'un message périphérique et lecture
	test4();
	//		TEST #4.2 : Tentative de lecture sur un périphérique silencieux
	test4_2();
	//		TEST #4.3 : Tentative de lecture avec un buffer de taille incorrecte
	test4_3();
	//		TEST #4.4 : Tentative de lecture de plusieurs messages simultanés
	test4_4();
	//		TEST #4.5 : Tentative de lecture de X messages simultanés, X > nombre de messages sauvegardables par le pilote
	test4_5();
	// 		TEST #4.6 : Lecture sur periphérique non installé (?????????????????????????? Erreur gérée par VxWorks ??????????????????????????)
	
	
	// LECTURE ET ECRITURES MULTIPLES / MULTITACHES :
	//		TEST #5 : Lecture & Ecriture simultanées (1 Periphérique, 1 Lecteur) XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	test5();
	//		TEST #5.2 : Lecture & Ecriture simultanées (1 Periphérique, N Lecteurs) XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	test5_2();
	//		TEST #5.3 : Suppression d'un périphérique alors que des applications sont en lecture dessus. XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	
	// SUPPRESSION DE PILOTE
	//		TEST #6 : Suppression d'un pilote existant XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	//		TEST #6.2 : Supression d'un pilote inexistant XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
}
