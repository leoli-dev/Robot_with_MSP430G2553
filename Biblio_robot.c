/*
*  Bibliothèque de fonctions utilisables pour piloter le robot          *
*                                                                       *
*/

#include <msp430.h>


void Arret_Robot();

  
/*.............................................................................*/
/* Fonction  permettant d'initialiser le timer avec deux sortie PWM            */
/* sur les voies P2.2 et P2.4 						       */
/* Le robot est configuré en mode arrêté, il ne peut pas bouger tant que l'on  */
/* n'exécute pas la fonction Demarrer_Robot()				       */
/* Cette fonction initialise aussi les lignes P2.1 et P2.5 qui déterminent le  */
/* sens de rotation des moteurs                                                */
/*.............................................................................*/ 
void Init_Robot()
{
    P2DIR |= BIT2 | BIT4;                //P2.2 et P2.4 (PWM moteurs) en sortie
    P2SEL |= BIT2 | BIT4;                // sortie PWM sur P2.2 et P2.4 (moteurs)
    P2SEL2 &= ~(BIT2|BIT4);              // selection fonction TA1.1 TA1.2
    P2DIR |= (BIT1 | BIT5);              // 0,1,2 output : CS, MAphase, MBphase(sens du moteur A, sens du monteur B)
    TA1CTL = TASSEL_2 | MC_1;            // select TimerA source SMCLK, set mode to up-counting
    TA1CCR0 = 200;                       // periode du signal PWM
    Arret_Robot();
    
}

/*............................................................................*/
/* Fonction  permettant de choisir le sens de fonctionnement des moteurs      */
/*  Il y a quatre possibilités permettant d'avancer, reculer, tourner à       */
/*  gauche ou à droite.                                                       */
/*............................................................................*/

void Choix_direction(unsigned char sens)
{
  switch (sens)
	{
        //avancer
	case 0:
        P2OUT &= ~BIT1;
        P2OUT |= BIT5;
        break;
        
        //reculer
        case 1:
        P2OUT |= BIT1;                      
  	P2OUT &= ~BIT5;  
        break;
        
        //tourner a gauche
        case 2:
        P2OUT |= BIT1;
        P2OUT |= BIT5;
        break;
        
        //tourner a droite
        case 3:
        P2OUT &= ~BIT1;
        P2OUT &= ~BIT5;
        break;
        
	default:
	break;
	}
}

/*............................................................................*/
/* Fonction  permettant de définir la vitesse des moteurs                     */
/*  Pour compenser les disparités des moteurs il faut envoyer deux vitesses   */
/*  gauche et droite. Les valeurs doivent être comprises entre 0 et 200       */
/*............................................................................*/
void Vitesse_moteurs(unsigned int vit_gauche, unsigned int vit_droite)
{
  TA1CCR1 = vit_gauche;                      // rapport cyclique moteur A
  TA1CCR2 = vit_droite;                      // rapport cyclique moteur B
}

/*............................................................................*/
/* Fonction  permettant d'arrêter la rotation des roues du robot              */
/*............................................................................*/


void Arret_Robot()
{
  TA1CCTL1 = OUTMOD_0;                 // select timer compare mode
  TA1CCTL2 = OUTMOD_0;                 // select timer compare mode
}


/*............................................................................*/
/* Fonction  permettant de démarrer la rotation des roues du robot            */
/* La rotation ne sera effective que si la fonction Vitesse_moteurs()         */
/* a été utilisée avec des paramètres corrects.                               */
/*............................................................................*/


void Demarrer_robot()
{
  TA1CCTL1 = OUTMOD_7;                 // select timer compare mode
  TA1CCTL2 = OUTMOD_7;                 // select timer compare mode
}


/*............................................................................*/
/* Fonction  de temporisation permettant de faire une pause de N millisecondes*/
/* Cette temporisation est calibrée pour une fréquence de travail de 1MHz     */
/*............................................................................*/

void tempo( unsigned int ms)
{
  unsigned int i=0;
  for (i=0;i<ms;i++)  {
    __delay_cycles(1000); }
  
}



/*............................................................................*/
/*                     Fonction pour deplacer                                 */
/*............................................................................*/
void robot_avancer(unsigned int ms, unsigned int vit)
{
    Choix_direction(0);
    Vitesse_moteurs(vit, vit);
    Demarrer_robot();    
    tempo(ms);    
    Arret_Robot();
}


void robot_reculer(unsigned int ms, unsigned int vit)
{
    Choix_direction(1);
    Vitesse_moteurs(vit, vit);
    Demarrer_robot();
    tempo(ms);
    Arret_Robot();     
}

void robot_gauche_2_roues(unsigned int ms, unsigned int vit)
{
    Choix_direction(2);
    Vitesse_moteurs(vit, vit);
    Demarrer_robot();
    tempo(ms);
    Arret_Robot();      
}

void robot_droite_2_roues(unsigned int ms, unsigned int vit)
{
    Choix_direction(3);
    Vitesse_moteurs(vit, vit);
    Demarrer_robot();    
    tempo(ms);
    Arret_Robot();
}

void robot_gauche_1_roue(unsigned int ms, unsigned int vit)
{
    Choix_direction(0);
    Vitesse_moteurs(vit-30, vit);
    Demarrer_robot();
    tempo(ms);
    Arret_Robot();      
}

void robot_droite_1_roue(unsigned int ms, unsigned int vit)
{
    Choix_direction(0);
    Vitesse_moteurs(vit, vit-30);
    Demarrer_robot();
    tempo(ms);
    Arret_Robot();      
}