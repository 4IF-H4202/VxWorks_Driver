
/*************************************************************************
                         Simulateur  -  description
                             -------------------
    d�but                : 30 Sept. 2011
    copyright            : (C) 2011 par Nicolas PHAN & Benjamin PLANCHE
*************************************************************************/

//-------- R�alisation de la t�che <Simulateur> (fichier simulateur.c) ---

//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include syst�me
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

//------------------------------------------------------ Fonctions priv�es

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
		printf("\tN� du pilote : %d\n", numPilote);
		printf("Liste des p�riph�riques du syst�me :\n");
		iosDrvShow();
	}
	else { 
		printf("\tInstallation -> ERREUR\n");
		printf("\tN� de l'erreur : %d\n", numPilote);
		iosDrvShow();
		return -1;
	}
	
	return 0;
}

void test1_2()
{
	/* ------------------------------------------
		TEST #1.2 : Ajout du pilote d�ja install�
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
		TEST #2.1 : Ajout de p�riph�riques
	   ------------------------------------------ */
	 
	int numPeriph00, numPeriph01, numPeriph42;
	
	printf("------------------------------------------\n");
	printf("\tTEST #2.1 : Ajout de p�riph�riques\n");
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
		TEST #2.2 : Ajout de p�riph�riques d�ja pr�sents
	   ------------------------------------------ */
	// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	
	int numPeriph42;
	   
	printf("------------------------------------------\n");
	printf("\tTEST #2 : Ajout d'un p�riph�rique d�ja pr�sent\n");
	printf("------------------------------------------\n\n");   

	numPeriph42 = DevAdd("p42", "42");
	
	printf("\tR�-ajout du p�riph�rique \"p42\" - V�rification :\n");
	iosDevShow();
}

void test3_1()
{	
	/* ------------------------------------------
		TEST #3.1 : Suppression de p�riph�rique existant
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #2 : Suppression d'un p�riph�rique existant\n");
	printf("------------------------------------------\n\n");  
	   
	DevDel("p42");   
	printf("\tSuppression du p�riph�rique \"p42\" - V�rification :\n");
	iosDevShow(); 
}

void test3_2()
{
	/* ------------------------------------------
		TEST #3.2 : Suppression de p�riph�rique inexistant
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #2 : Suppression d'un p�riph�rique inexistant\n");
	printf("------------------------------------------\n\n");  
	   
	DevDel("p42");   
	printf("\tSuppression du p�riph�rique \"p42\" - V�rification :\n");
	iosDevShow(); 
}
	
	
void test4()
{	
	int statut, monFd00;
	char buffer[17];
	int i ;
	/* ------------------------------------------
		TEST #4 : R�ception d'un message p�riph�rique et lecture
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #4.1 : R�ception d'un message p�riph�rique et lecture\n");
	printf("------------------------------------------\n\n");  
	   
	registre[0] = '0';
	registre[1] = '0';
	registre[2] = '7';
	registre[3] = '3';
	monISR();
	
	printf("\t Message \"73\" envoy� par le p�riph�rique \"p00\".\n");
	monFd00 = open("p00", O_RDONLY,0);
	statut = read(monFd00, buffer, 17);
	printf("\t Message re�u par l'application : %s \t(statut : %d)\n", buffer, statut);
	printf("\t Re-lectures multiples de ce message :\n");
	
	for (i = 2; i < 10; i++)
	{
		statut = read(monFd00, buffer, 17);
		printf("\t\t - Lecture n�%d : %s \t(statut : %d)\n", i, buffer, statut);
	}
	
	close(monFd00);
}

void test4_2()
{	
	/* ------------------------------------------
		TEST #4.2 : Tentative de lecture sur un p�riph�rique silencieux
	   ------------------------------------------ */
	
	int statut, monFd01;
	char buffer[17];  
	printf("------------------------------------------\n");
	printf("\tTEST #4.2 : Tentative de lecture sur un p�riph�rique silencieux\n");
	printf("------------------------------------------\n\n");  
	
	printf("\t Tentative de lecture sur le p�riph�rique \"p01\", n'ayant jamais envoy� de message.\n");
	monFd01 = open("p01", O_RDONLY,0);
	statut = read(monFd01, buffer, 17);
	printf("\t Message re�u par l'application : %s \t(statut : %d)\n", buffer, statut);
	   
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
	
	printf("\t Tentative de lecture du dernier message \"73\" sur le p�riph�rique \"p00\", avec en entrer un buffer trop petit.\n");
	monFd00 = open("p00", O_RDONLY,0);
	statut = read(monFd00, buffer, 9);
	printf("\t Message re�u par l'application : %s \t(statut : %d)\n", buffer, statut);
	   
	close(monFd00); 
}	

void test4_4()
{	
	int statut, monFd00;
	char buffer[16*3+1];	   
	/* ------------------------------------------
		TEST #4.4 : Tentative de lecture de plusieurs messages simultan�s :
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #4.4 : Tentative de lecture de plusieurs messages simultan�s\n");
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
	
	printf("\t Message \"74\" envoy� par le p�riph�rique \"p00\".\n");
	printf("\t Message \"75\" envoy� par le p�riph�rique \"p00\".\n");
	printf("\t Lecture des 3 derniers messages envoy�s par ce p�riph�rique :\n");
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
		TEST #4.5 : Tentative de lecture de X messages simultan�s, X > nombre de messages sauvegardables par le pilote :
	   ------------------------------------------ */
	   
	   // XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	   
	printf("------------------------------------------\n");
	printf("\tTEST #4.5 : Tentative de lecture de X messages simultan�s, X > nombre de messages sauvegardables par le pilote\n");
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
	
	printf("\t Message \"74\" envoy� par le p�riph�rique \"p00\".\n");
	printf("\t Message \"75\" envoy� par le p�riph�rique \"p00\".\n");
	printf("\t Lecture des 3 derniers messages envoy�s par ce p�riph�rique :\n");
	monFd00 = open("p00", O_RDONLY,0);
	statut = read(monFd00, buffer, 16*3+1);
	printf("%s \t(statut : %d)\n", buffer, statut);
	   
	close(monFd00);
}	

void test5()
{	
	int idSimulPeriph, idSimulAppli;
	/* ------------------------------------------
		TEST #5 : Lecture & Ecriture simultan�es :
	   ------------------------------------------ */

	   
	printf("------------------------------------------\n");
	printf("\tTEST #5.1 : Lecture & Ecriture simultan�es (1 Periph�rique, 1 Lecteur)\n");
	printf("------------------------------------------\n\n");  

	
	printf("\t Lancement d'une t�che simulant un capteur d�livrant un message � intervalles r�guliers.\n");
	printf("\t Lancement d'une t�che simulant une application n�1 consultant ce p�riph�rique � intervalles r�guliers 2x plus rapides.\n");
	printf("\t R�sultat :\n");
	
	idSimulPeriph = taskSpawn("SimulateurPeripherique", 56, 0, 10000, (FUNCPTR)simulateurPeripherique, 0, 10, 10,0,0,0,0,0,0,0); // Lancement de la t�che Periph
	idSimulAppli = taskSpawn("SimulateurApplication", 91, 0, 10000, (FUNCPTR)simulateurApplication, 1, 0, 5, 1, 25,0,0,0,0,0); // Lancement de la t�che Appli
	taskDelay(50);
}

void test5_2()
{	
	int idSimulPeriph, idSimulAppli, idSimulAppli2, idSimulAppli3;
	/* ------------------------------------------
		TEST #5 : Lecture & Ecriture simultan�es :
	   ------------------------------------------ */
	   
	printf("------------------------------------------\n");
	printf("\tTEST #5.2 : Lecture & Ecriture simultan�es (1 Periph�rique, N Lecteurs)\n");
	printf("------------------------------------------\n\n");  

	
	printf("\t Lancement d'une t�che simulant un capteur d�livrant un message � intervalles r�guliers.\n");
	printf("\t Lancement d'une t�che simulant une application n�1 consultant ce p�riph�rique � intervalles r�guliers 2x plus rapides.\n");
	printf("\t Lancement d'une t�che simulant une application n�2 consultant ce p�riph�rique � intervalles r�guliers 0.5x plus rapides.\n");
	printf("\t Lancement d'une t�che simulant une application n�3 consultant ce p�riph�rique � intervalles r�guliers 5x plus rapides.\n");
	printf("\t R�sultat :\n");
	
	idSimulPeriph = taskSpawn("SimulateurPeriph�rique", 90, 0, 10000, (FUNCPTR)simulateurPeripherique, 0, 10, 10,0,0,0,0,0,0,0); // Lancement de la t�che Periph
	idSimulAppli = taskSpawn("SimulateurApplication1", 91, 0, 10000, (FUNCPTR)simulateurApplication, 1, 0, 5, 1, 30,0,0,0,0,0); // Lancement de la t�che Appli
	idSimulAppli2 = taskSpawn("SimulateurApplication2", 92, 0, 10000, (FUNCPTR)simulateurApplication, 1, 0, 20, 1, 30,0,0,0,0,0); // Lancement de la t�che Appli
	idSimulAppli3 = taskSpawn("SimulateurApplication3", 93, 0, 10000, (FUNCPTR)simulateurApplication, 1, 0, 2, 1, 30,0,0,0,0,0); // Lancement de la t�che Appli
	taskDelay(60);
}

//---------------------------------------------------- Fonctions publiques

void simulateur(void)
{


	// AJOUT DE PILOTE
	//		TEST #1.1 : Ajout du pilote
	test1();
	// 		TEST #1.2 : Ajout du pilote d�ja install�
	test1_2();
	

	// AJOUT DE PERIPHERIQUES
	//		TEST #2.1 : Ajout de p�riph�riques
	test2_1();
	//		TEST #2.2 : Ajout de p�riph�riques d�ja pr�sents XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	test2_2();
	
	
	// SUPPRESSION DE PERIPHERIQUES
	//		TEST #3.1 : Suppression de p�riph�rique existant
	test3_1();
	//		TEST #3.2 : Suppression de p�riph�rique inexistant
	test3_2();
	
	
	// LECTURE ET ECRITURES SIMPLES :
	//		TEST #4 : R�ception d'un message p�riph�rique et lecture
	test4();
	//		TEST #4.2 : Tentative de lecture sur un p�riph�rique silencieux
	test4_2();
	//		TEST #4.3 : Tentative de lecture avec un buffer de taille incorrecte
	test4_3();
	//		TEST #4.4 : Tentative de lecture de plusieurs messages simultan�s
	test4_4();
	//		TEST #4.5 : Tentative de lecture de X messages simultan�s, X > nombre de messages sauvegardables par le pilote
	test4_5();
	// 		TEST #4.6 : Lecture sur periph�rique non install� (?????????????????????????? Erreur g�r�e par VxWorks ??????????????????????????)
	
	
	// LECTURE ET ECRITURES MULTIPLES / MULTITACHES :
	//		TEST #5 : Lecture & Ecriture simultan�es (1 Periph�rique, 1 Lecteur) XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	test5();
	//		TEST #5.2 : Lecture & Ecriture simultan�es (1 Periph�rique, N Lecteurs) XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	test5_2();
	//		TEST #5.3 : Suppression d'un p�riph�rique alors que des applications sont en lecture dessus. XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	
	// SUPPRESSION DE PILOTE
	//		TEST #6 : Suppression d'un pilote existant XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	//		TEST #6.2 : Supression d'un pilote inexistant XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
}
