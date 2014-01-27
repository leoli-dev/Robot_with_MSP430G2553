#include "Biblio_robot.h"
#include "msp430.h"
#include "adc.h"
#include "Fonction_trajectoire.h"
#define BUTTON BIT3

unsigned int seuilDistanceInfrarouge = 650;
unsigned int seuilSwitchON = 900;

// seuil par default
unsigned int seuilBlancDetecteurA = 890;
unsigned int seuilBlancDetecteurB = 850;

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  // Initialisation
  P1DIR &= ~(BIT0|BIT1|BIT2|BIT4|BIT5);   // P1.0, P1.1, P1.2, P1.4, P1.5  input
  P1DIR |= BIT6; // P1.6 output
  P1OUT &= ~BIT6; // mettre P1.6 a 0
  P2DIR &= ~(BIT0 | BIT3); // P2.0, P2.3 input
  Init_Robot();
  
  //enable interrupt of button
  P1IE |= BUTTON; // P1.3 interrupt enabled
  P1IFG &= ~BUTTON; // P1.3 IFG cleared
  __enable_interrupt(); // enable all interrupts
  
  //loop
  while(1){
        // clignoter le LED vert
        P1OUT |= BIT6;
        tempo(250);
        P1OUT &= ~BIT6;
        tempo(250);
  }  
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    // allumer le LED vert
    P1OUT |= BIT6;
    // un tempo pour attendre laisser la main
    tempo(800);
    // eteindre le LED vert
    P1OUT &= ~BIT6;
    // lire l'etat de switch
    init_ADC_P1_1();
    int etat_P1_1 = ReadAdc();
    init_ADC_P1_2();
    int etat_P1_2 = ReadAdc();
    
    // "00":HOPITAL
    if(etat_P1_1 < seuilSwitchON && etat_P1_2 < seuilSwitchON){
        // 1: sortir la maison( environ 3.5cm )
        Aller_Tout_Droit_Avec_OptoCoupleur(7, seuilDistanceInfrarouge);
        // 2: chercher la ligne
        Chercher_La_Ligne_90(seuilBlancDetecteurA, seuilBlancDetecteurB);       
        // 3: avancer ( environ 25cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(47, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 4: passer la 1ere intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);          
        // 5: avancer ( environ 68cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(115, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);        
        // 6: passer la 2eme intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);  
        // 7: avancer ( environ 18cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(32, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 8: tourner a gauche
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB); 
        // 9: avancer ( environ 11cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(20, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB); 
        // 10: passer la 3eme intersection T
        Traverser_La_Intersection_T_4(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB); 
        // 11: avancer ( environ 30cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(54, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 12: tourner a droite pour entrer la 4eme intersection T
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 13: avancer ( environ 7cm)
        Aller_Tout_Droit_Avec_DetecteurLigne(13, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 14: tourner a gauche pour corriger l'angle
        Tourner_A_Droite_Avec_OptoCoupleur(1);
        // 15: attendre un peu
        tempo(500);
        // 16: avancer pouer enter l'hopital ( environ 21.5cm )
        Aller_Tout_Droit_Avec_OptoCoupleur(37, seuilDistanceInfrarouge);
        // 17: attendre 5s
        Clignoter_LED_Vert(5);
        // 18: reculer ( environ 20cm )
        Reculer_Tout_Droit_Avec_OptoCoupleur(34, seuilDistanceInfrarouge);
        // 19: attendre un peu
        tempo(500);
        // 20: chercher la ligne
        Chercher_La_Ligne_360(seuilBlancDetecteurA, seuilBlancDetecteurB);  
        // 21: avancer ( environ 2cm)
        Aller_Tout_Droit_Avec_DetecteurLigne(3, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 22: repasser la 4eme intersection T
        Traverser_La_Intersection_T_6(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 23: avancer ( environ 20cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(39, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 24: tourner a gauche
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 25: avancer ( environ 90cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(160, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 26: tourner a gauche
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 27: avancer ( environ 18cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(32, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);                                    
        // 28: passer la 5eme intersection T
        Traverser_La_Intersection_T_4(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 29: avancer ( environ 56cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(99, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);        
        // 30: repasser par la 1ere intersection T
        Traverser_La_Intersection_T_6(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 31: avancer ( environ 25cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(45, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 32: rentrer a la maison
        Aller_Tout_Droit_Avec_OptoCoupleur(24, seuilDistanceInfrarouge);
        // 33: attendre un peu
        tempo(500);
        // 34: tourner 180 degree
        Tourner_A_Droite_Avec_OptoCoupleur(24);
    }
    
    // "01":BOULANGERIE
    if(etat_P1_1 < seuilSwitchON && etat_P1_2 >= seuilSwitchON){
        // 1: sortir la maison( environ 3.5cm )
        Aller_Tout_Droit_Avec_OptoCoupleur(7, seuilDistanceInfrarouge);
        // 2: chercher la ligne
        Chercher_La_Ligne_90(seuilBlancDetecteurA, seuilBlancDetecteurB);       
        // 3: avancer ( environ 25cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(47, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 4: passer la 1ere intersection T( tourner a gauche )
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 5: avancer ( environ 54cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(96, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 6: tourner a gauche pour entrer la 2eme intersection T
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 7: avancer ( environ 11cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(19, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 8: avancer pouer enter la Boulangerie ( environ 21.5cm )
        Aller_Tout_Droit_Avec_OptoCoupleur(37, seuilDistanceInfrarouge);
        // 9: attendre 5s
        Clignoter_LED_Vert(5);
        // 10: reculer ( environ 20cm )
        Reculer_Tout_Droit_Avec_OptoCoupleur(34, seuilDistanceInfrarouge);
        // 11: attendre un peu
        tempo(500);
        // 12: chercher la ligne
        Chercher_La_Ligne_360(seuilBlancDetecteurA, seuilBlancDetecteurB); 
        // 13: avancer ( environ 4cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(7, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 14: repasser la 2eme intersection T
        Traverser_La_Intersection_T_5(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 15: avancer ( environ 18cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(32, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 16: tourner a droite
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 17: avancer ( environ 90cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(160, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 18: tourner a droite
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 19: avancer ( environ 20cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(39, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 20: passer la 3eme intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 21: avancer ( environ 30cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(54, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 22: passer la 4eme intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 23: avancer ( environ 11cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(20, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB); 
        // 24: tourner a droite
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 25: avancer ( environ 18cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(32, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 26: passer la 5eme intersection T
        Traverser_La_Intersection_T_4(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 27: avancer ( environ 68cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(115, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB); 
        // 28: repasser la 1ere intersection T
        Traverser_La_Intersection_T_4(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 29: avancer ( environ 25cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(45, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 30: rentrer a la maison
        Aller_Tout_Droit_Avec_OptoCoupleur(24, seuilDistanceInfrarouge);
        // 31: attendre un peu
        tempo(500);
        // 32: tourner 180 degree
        Tourner_A_Droite_Avec_OptoCoupleur(24);
    }
    
    // "10":POSTE
    if(etat_P1_1 >= seuilSwitchON && etat_P1_2 < seuilSwitchON){
        // 1: sortir la maison( environ 3.5cm )
        Aller_Tout_Droit_Avec_OptoCoupleur(7, seuilDistanceInfrarouge);
        // 2: chercher la ligne
        Chercher_La_Ligne_90(seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 3: avancer ( environ 25cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(47, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 4: passer la 1ere intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 5: avancer ( environ 68cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(115, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 6: passer la 2eme intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 7: avancer ( environ 18cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(32, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 8: tourner a gauche
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 9: avancer ( environ 11cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(20, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 10: tourner a droite pour entrer la 3eme intersection T
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 11: avancer ( environ 54cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(95, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);        
        // 12: avancer pouer enter la Poste ( environ 21.5cm )
        Aller_Tout_Droit_Avec_OptoCoupleur(37, seuilDistanceInfrarouge);                
        // 13: attendre 5s
        Clignoter_LED_Vert(5);
        // 14: reculer ( environ 20cm )
        Reculer_Tout_Droit_Avec_OptoCoupleur(34, seuilDistanceInfrarouge);
        // 15: attendre un peu
        tempo(500);
        // 16: chercher la ligne
        Chercher_La_Ligne_360(seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 17: avancer ( environ 45cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(80, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 18: repasser la 3eme intersection T
        Traverser_La_Intersection_T_6(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 19: avancer ( environ 30cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(54, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 20: passer la 4eme intersection T
        Traverser_La_Intersection_T_4(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 21: avancer ( environ 20cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(39, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 22: tourner a gauche
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 23: avancer ( environ 90cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(160, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 24: tourner a gauche
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 25: avancer ( environ 18cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(32, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 26: passer la 5eme intersection T
        Traverser_La_Intersection_T_4(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 27: avancer ( environ 56cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(99, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 28: repasser par la 1ere intersection T
        Traverser_La_Intersection_T_6(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 29: avancer ( environ 25cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(45, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 30: rentrer a la maison
        Aller_Tout_Droit_Avec_OptoCoupleur(24, seuilDistanceInfrarouge);
        // 31: attendre un peu
        tempo(500);
        // 32: tourner 180 degree
        Tourner_A_Droite_Avec_OptoCoupleur(24);
    }
    
    // "11":BANQUE
    if(etat_P1_1 >= seuilSwitchON && etat_P1_2 >= seuilSwitchON){
        // 1: sortir la maison( environ 3.5cm )
        Aller_Tout_Droit_Avec_OptoCoupleur(7, seuilDistanceInfrarouge);
        // 2: chercher la ligne
        Chercher_La_Ligne_90(seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 3: avancer ( environ 25cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(47, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 4: passer la 1ere intersection T( tourner a gauche )
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 5: avancer ( environ 54cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(96, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 6: passer la 2eme intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 7: avancer ( environ 18cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(32, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 8: tourner a droite
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 9: avancer ( environ 90cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(160, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 10: tourner a droite
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 11: avancer ( environ 20cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(39, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 12: passer la 3eme intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 13: avancer ( environ 30cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(54, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 14: passer la 4eme intersection T
        Traverser_La_Intersection_T_2(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 15: avancer ( environ 11cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(20, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 16: tourner a droite
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 17: avancer ( environ 18cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(32, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 18: tourner a droite pour entrer la 5eme intersection T
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 19: avancer ( environ 23cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(41, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 20: tourner a gauche
        Tourner_A_Gauche_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 21: avancer ( environ 19cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(33, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);        
        // 22: avancer pouer enter la Banque ( environ 21.5cm )
        Aller_Tout_Droit_Avec_OptoCoupleur(37, seuilDistanceInfrarouge);
        // 23: attendre 5s
        Clignoter_LED_Vert(5);
        // 24: reculer ( environ 20cm )
        Reculer_Tout_Droit_Avec_OptoCoupleur(34, seuilDistanceInfrarouge);
        // 25: attendre un peu
        tempo(500);        
        // 26: chercher la ligne
        Chercher_La_Ligne_360(seuilBlancDetecteurA, seuilBlancDetecteurB);        
        // 27: avancer ( environ 12cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(21, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);       
        // 28: tourner a droite
        Tourner_A_Droite_Avec_DetecteurLigne(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 29: avancer ( environ 23cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(41, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 30: repasser la 5eme intersection T ( tourner a droite )
        Traverser_La_Intersection_T_6(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 31: avancer ( environ 68cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(115, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 32: repasser la 1ere intersection T
        Traverser_La_Intersection_T_4(seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 33: avancer ( environ 25cm )
        Aller_Tout_Droit_Avec_DetecteurLigne(45, seuilDistanceInfrarouge, seuilBlancDetecteurA, seuilBlancDetecteurB);
        // 34: rentrer a la maison
        Aller_Tout_Droit_Avec_OptoCoupleur(24, seuilDistanceInfrarouge);
        // 35: attendre un peu
        tempo(500);
        // 36: tourner 180 degree
        Tourner_A_Droite_Avec_OptoCoupleur(24);
    }

    P1IFG &= ~BUTTON; // P1.3 IFG cleared
    // the interrupt vector will be called
    // when P1.3 goes from HitoLow as well as
    // LowtoHigh
}
