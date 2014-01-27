#include "Biblio_robot.h"
#include "msp430.h"
#include "adc.h"
#include "Fonction_trajectoire.h"


void Detecter_Obstacle(int seuilDistanceInfrarouge){
    int distance;
    while(1){
		init_ADC_Infrarouge();
		distance = ReadAdc();
		if(distance < seuilDistanceInfrarouge){
		  break;
		}else{
		  tempo(500);
		}
	}
}

void Aller_Tout_Droit_Avec_DetecteurLigne(int pasDemande, int seuilDistanceInfrarouge, int seuilBlancDetecteurA, int seuilBlancDetecteurB){
    int etatGaucheAvant;
    int etatGaucheApres;
    int pasDejaBouge = 0;
	int ligne_dct_A;
	int ligne_dct_B;
	// lire l'etats de la roue a gauche(Avant bouger)
	if((P2IN & BIT0)==BIT0){
		  etatGaucheAvant = 1;
	}else{
		  etatGaucheAvant = 0;
	}
    while(pasDejaBouge < pasDemande){
		// detecter des obstacle
		  Detecter_Obstacle(seuilDistanceInfrarouge);
		  // lire les etats des detecteurs
		  init_ADC_LigneDetecteurA();
		  ligne_dct_A = ReadAdc();
		  init_ADC_LigneDetecteurB();
		  ligne_dct_B = ReadAdc();
		  // les cas differents
		  if(ligne_dct_A > seuilBlancDetecteurA && ligne_dct_B > seuilBlancDetecteurB){
				// Avancer le robot
				robot_avancer(20, 150);
		  }else{
				// corriger			
				if(ligne_dct_A <= seuilBlancDetecteurA){
					robot_gauche_1_roue(20, 150);
				}else{
					robot_droite_1_roue(20, 150);
				}               
		  }
        // lire l'etats de la roue a gauche(Apres bouger)
        if((P2IN & BIT0)==BIT0){
            etatGaucheApres = 1;
        }else{
            etatGaucheApres = 0;
        }
        // Comparer l'etat avant et l'etat apres
        if(etatGaucheAvant != etatGaucheApres){
            pasDejaBouge++;
        }
        // mettre etatGaucheApres dans etatGaucheAvant pour la prochaine fois
        etatGaucheAvant = etatGaucheApres;
    }
}

void Aller_Tout_Droit_Avec_OptoCoupleur(int pasDemande, int seuilDistanceInfrarouge){
	int etatGaucheAvant;
    int etatGaucheApres;
    int pasDejaBouge = 0;
	// lire l'etats de la roue a gauche(Avant bouger)
	if((P2IN & BIT0)==BIT0){
		  etatGaucheAvant = 1;
	}else{
		  etatGaucheAvant = 0;
	}
	while(pasDejaBouge < pasDemande){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// Avancer le robot
		robot_avancer(20, 150);
		// lire l'etats de la roue a gauche(Apres bouger)
		if((P2IN & BIT0)==BIT0){
			  etatGaucheApres = 1;
		  }else{
			  etatGaucheApres = 0;
		 }
		// Comparer l'etat avant et l'etat apres
		if(etatGaucheAvant != etatGaucheApres){
			 pasDejaBouge++;
		}
		// mettre etatGaucheApres dans etatGaucheAvant pour la prochaine fois
		etatGaucheAvant = etatGaucheApres;	  
	}
}
                         
void Reculer_Tout_Droit_Avec_OptoCoupleur(int pasDemande, int seuilDistanceInfrarouge){
	int etatGaucheAvant;
    int etatGaucheApres;
    int pasDejaBouge = 0;
	// lire l'etats de la roue a gauche(Avant bouger)
	if((P2IN & BIT0)==BIT0){
		  etatGaucheAvant = 1;
	}else{
		  etatGaucheAvant = 0;
	}
	while(pasDejaBouge < pasDemande){
		// Avancer le robot
		robot_reculer(20, 150);
		// lire l'etats de la roue a gauche(Apres bouger)
		if((P2IN & BIT0)==BIT0){
			  etatGaucheApres = 1;
		  }else{
			  etatGaucheApres = 0;
		 }
		// Comparer l'etat avant et l'etat apres
		if(etatGaucheAvant != etatGaucheApres){
			 pasDejaBouge++;
		}
		// mettre etatGaucheApres dans etatGaucheAvant pour la prochaine fois
		etatGaucheAvant = etatGaucheApres;	  
	}
}

void Tourner_A_Gauche_Avec_OptoCoupleur(int pasDemande){
    int etatGaucheAvant;
    int etatGaucheApres;
    int pasDejaBouge = 0;
	// lire l'etats de la roue a gauche(Avant bouger)
	if((P2IN & BIT0)==BIT0){
		  etatGaucheAvant = 1;
	}else{
		  etatGaucheAvant = 0;
	}
    while(pasDejaBouge < pasDemande){
		// Avancer le robot
		robot_gauche_2_roues(20, 80);
		// lire l'etats de la roue a gauche(Apres bouger)
		if((P2IN & BIT0)==BIT0){
			  etatGaucheApres = 1;
		  }else{
			  etatGaucheApres = 0;
		 }
		// Comparer l'etat avant et l'etat apres
		if(etatGaucheAvant != etatGaucheApres){
			  pasDejaBouge++;
		}
		// mettre etatGaucheApres dans etatGaucheAvant pour la prochaine fois
		etatGaucheAvant = etatGaucheApres;
    }
}

void Tourner_A_Droite_Avec_OptoCoupleur(int pasDemande){
    int etatGaucheAvant;
    int etatGaucheApres;
    int pasDejaBouge = 0;
	// lire l'etats de la roue a gauche(Avant bouger)
	if((P2IN & BIT0)==BIT0){
		  etatGaucheAvant = 1;
	}else{
		  etatGaucheAvant = 0;
	}
    while(pasDejaBouge < pasDemande){
		// Avancer le robot
		robot_droite_2_roues(20, 80);
		// lire l'etats de la roue a gauche(Apres bouger)
		if((P2IN & BIT0)==BIT0){
			  etatGaucheApres = 1;
		  }else{
			  etatGaucheApres = 0;
		 }
		// Comparer l'etat avant et l'etat apres
		if(etatGaucheAvant != etatGaucheApres){
			  pasDejaBouge++;
		}
		// mettre etatGaucheApres dans etatGaucheAvant pour la prochaine fois
		etatGaucheAvant = etatGaucheApres;
    }
}

void Tourner_A_Gauche_Avec_DetecteurLigne(int seuilDistanceInfrarouge, int seuilBlancDetecteurA, int seuilBlancDetecteurB){
	int ligne_dct_A;
    int ligne_dct_B;
	// etape 1: mettre le detecteur a droite sur la ligne
	while(1){
		robot_gauche_1_roue(10, 100);
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B <= seuilBlancDetecteurB){
			break;
		}
	}
	// etape 2: avancer pour toucher la ligne
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A > seuilBlancDetecteurA){
			// Avancer le robot
			robot_avancer(20, 100);
		}else{
			// Apres toucher la ligne, finir cette etape
			break;
		}
	}
	// etape 3: avancer pour passer la ligne
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA){
			// Avancer le robot
			robot_avancer(20, 100);
		}else{
			// Apres passer la ligne, finir cette etape
			break;
		}
	}        
	// etape 4: avancer un peu (plus que 3.5cm, et moins que 4cm)
	Aller_Tout_Droit_Avec_OptoCoupleur(7, seuilDistanceInfrarouge); 
        // etape 5: attendre un peu
        tempo(500);     
	// etape 6: tourner jusqu'a toucher la ligne
	while(1){
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A > seuilBlancDetecteurA){
			// Avancer le robot
			robot_gauche_2_roues(20, 100);
		}else{
			// Apres toucher la ligne, finir cette etape
			break;
		}
	}
	// etape 7: tourner pour passer la ligne
	while(1){
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA){
			// Avancer le robot
			robot_gauche_2_roues(20, 100);
		}else{
			// Apres passer la ligne, finir cette etape
			break;
		}
	}
}

void Tourner_A_Droite_Avec_DetecteurLigne(int seuilDistanceInfrarouge, int seuilBlancDetecteurA, int seuilBlancDetecteurB){
	int ligne_dct_A;
    int ligne_dct_B;
	// etape 1: mettre le detecteur a gauche sur la ligne
	while(1){
		robot_droite_1_roue(10, 100);
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA){
			break;
		}
	}
	// etape 2: avancer pour toucher la ligne
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B > seuilBlancDetecteurB){
			// Avancer le robot
			robot_avancer(20, 100);
		}else{
			// Apres toucher la ligne, finir cette etape
			break;
		}
	}
	// etape 3: avancer pour passer la ligne
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B <= seuilBlancDetecteurB){
			// Avancer le robot
			robot_avancer(20, 100);
		}else{
			// Apres passer la ligne, finir cette etape
			break;
		}
	}
	// etape 4: avancer un peu (plus que 3.5cm, et moins que 4cm)
	Aller_Tout_Droit_Avec_OptoCoupleur(7, seuilDistanceInfrarouge);
        // etape 5: attendre un peu
        tempo(500); 
	// etape 6: tourner jusqu'a toucher la ligne
	while(1){
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B > seuilBlancDetecteurB){
			// Avancer le robot
			robot_droite_2_roues(20, 100);
		}else{
			// Apres toucher la ligne, finir cette etape
			break;
		}
	}
	// etape 7: tourner pour passer la ligne
	while(1){
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B <= seuilBlancDetecteurB){
			// Avancer le robot
			robot_droite_2_roues(20, 100);
		}else{
			// Apres passer la ligne, finir cette etape
			break;
		}
	}
}

void Traverser_La_Intersection_T_2(int seuilDistanceInfrarouge, int seuilBlancDetecteurA, int seuilBlancDetecteurB){
	int ligne_dct_A;
	int ligne_dct_B;
	// etape 1: mettre le detecteur a droite sur la ligne
	while(1){
		robot_gauche_1_roue(10, 100);
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B <= seuilBlancDetecteurB){
			break;
		}
	}
	// etape 2: avancer pour toucher la ligne
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A > seuilBlancDetecteurA){
			// Avancer le robot
			robot_avancer(20, 100);
		}else{
			// Apres toucher la ligne, finir cette etape
			break;
		}
	}
	// etape 3: avancer pour passer la ligne
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA){
			// Avancer le robot
			robot_avancer(20, 100);
		}else{
			// Apres passer la ligne, finir cette etape
			break;
		}
	}
    // etape 4: mettre le detecteur a gauche sur la ligne
	while(1){
		robot_droite_1_roue(10, 100);
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA){
			break;
		}
	}
}

void Traverser_La_Intersection_T_4(int seuilDistanceInfrarouge, int seuilBlancDetecteurA, int seuilBlancDetecteurB){
	int ligne_dct_A;
    int ligne_dct_B;
	// etape 1: mettre le detecteur a gauche sur la ligne
	while(1){
		robot_droite_1_roue(10, 100);
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA){
			break;
		}
	}
	// etape 2: avancer pour toucher la ligne
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B > seuilBlancDetecteurB){
			// Avancer le robot
			robot_avancer(20, 100);
		}else{
			// Apres toucher la ligne, finir cette etape
			break;
		}
	}
	// etape 3: avancer pour passer la ligne
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B <= seuilBlancDetecteurB){
			// Avancer le robot
			robot_avancer(20, 100);
		}else{
			// Apres passer la ligne, finir cette etape
			break;
		}
	}
    // etape 4: mettre le detecteur a droite sur la ligne
	while(1){
		robot_gauche_1_roue(10, 100);
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B <= seuilBlancDetecteurB){
			break;
		}
	}	
}

void Traverser_La_Intersection_T_5(int seuilDistanceInfrarouge, int seuilBlancDetecteurA, int seuilBlancDetecteurB){
	int ligne_dct_A;
	int ligne_dct_B;
	// etape 1: avancer pour toucher les lignes
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire les etats des detecteurs lignes
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA && ligne_dct_B <= seuilBlancDetecteurB){
			// Apres toucher les lignes, finir cette etape
			break;
		}else{
			// Avancer le robot
			robot_avancer(20, 100);
		}
	}
	// etape 2: avancer pour passer les lignes
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire les etats des detecteurs lignes
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_A > seuilBlancDetecteurA && ligne_dct_B > seuilBlancDetecteurB){
			// Apres passer la ligne, finir cette etape
			break;			
		}else{
			// Avancer le robot
			robot_avancer(20, 100);
		}
	}
	// etape 3: avancer un peu (plus que 3.5cm, et moins que 4cm)
	Aller_Tout_Droit_Avec_OptoCoupleur(7, seuilDistanceInfrarouge);
        // etape 4: attendre un peu
        tempo(500);
	// etape 5: tourner jusqu'a toucher la ligne a gauche
	while(1){
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A > seuilBlancDetecteurA){
			// Avancer le robot
			robot_gauche_2_roues(20, 100);
		}else{
			// Apres toucher la ligne, finir cette etape
			break;
		}
	}
	// etape 6: tourner pour passer la ligne a gauche
	while(1){
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA){
			// Avancer le robot
			robot_gauche_2_roues(20, 100);
		}else{
			// Apres passer la ligne, finir cette etape
			break;
		}
	}
}

void Traverser_La_Intersection_T_6(int seuilDistanceInfrarouge, int seuilBlancDetecteurA, int seuilBlancDetecteurB){
	int ligne_dct_A;
	int ligne_dct_B;
	// etape 1: avancer pour toucher les lignes
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire les etats des detecteurs lignes
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_A <= seuilBlancDetecteurA && ligne_dct_B <= seuilBlancDetecteurB){
			// Apres toucher les lignes, finir cette etape
			break;
		}else{
			// Avancer le robot
			robot_avancer(20, 100);
		}
	}
	// etape 2: avancer pour passer les lignes
	while(1){
		// detecter des obstacle
		Detecter_Obstacle(seuilDistanceInfrarouge);
		// lire les etats des detecteurs lignes
		init_ADC_LigneDetecteurA();
		ligne_dct_A = ReadAdc();
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_A > seuilBlancDetecteurA && ligne_dct_B > seuilBlancDetecteurB){
			// Apres passer la ligne, finir cette etape
			break;			
		}else{
			// Avancer le robot
			robot_avancer(20, 100);
		}
	}
	// etape 3: avancer un peu (plus que 3.5cm, et moins que 4cm)
	Aller_Tout_Droit_Avec_OptoCoupleur(7, seuilDistanceInfrarouge);
        // etape 4: attendre un peu
        tempo(500);
	// etape 5: tourner jusqu'a toucher la ligne a droite
	while(1){
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B > seuilBlancDetecteurB){
			// Avancer le robot
			robot_droite_2_roues(20, 100);
		}else{
			// Apres toucher la ligne, finir cette etape
			break;
		}
	}
	// etape 6: tourner pour passer la ligne a droite
	while(1){
		// lire l'etat de detecteur ligne
		init_ADC_LigneDetecteurB();
		ligne_dct_B = ReadAdc();
		if(ligne_dct_B <= seuilBlancDetecteurB){
			// Avancer le robot
			robot_droite_2_roues(20, 100);
		}else{
			// Apres passer la ligne, finir cette etape
			break;
		}
	}
}

void Chercher_La_Ligne_90(int seuilBlancDetecteurA, int seuilBlancDetecteurB){
	// attendre un peu
	tempo(500);
	int ligne_dct_A;
    int ligne_dct_B;
	// lire l'etat de detecteur ligne
	init_ADC_LigneDetecteurA();
	ligne_dct_A = ReadAdc();
        init_ADC_LigneDetecteurB();
	ligne_dct_B = ReadAdc();
        //Si une des detecteurs est sur la ligne
        if(ligne_dct_A <= seuilBlancDetecteurA || ligne_dct_B <= seuilBlancDetecteurB){
            // Si le detecteur a gauche est sur la ligne
            if(ligne_dct_A <= seuilBlancDetecteurA){
              while(1){
                  robot_gauche_2_roues(20, 80);
                  init_ADC_LigneDetecteurA();
                  ligne_dct_A = ReadAdc();
                  // Si le detcteur a gauche sort la ligne, s'arretera.
                  if(ligne_dct_A > seuilBlancDetecteurA){
                        break;
                  }
              }
            }else{
                // Si le detecteur a droite est sur la ligne
                while(1){
                     robot_droite_2_roues(20, 80);
                     init_ADC_LigneDetecteurB();
                     ligne_dct_B = ReadAdc();
                     // Si le detecteur a droite sort la ligne, s'arretera.
                     if(ligne_dct_B > seuilBlancDetecteurB){
                        break;
                     }
                }
            }
        }else{
            // Si les deux detecteurs ne sont pas sur la ligne			
			int end_loop = 0;
			int etatGaucheAvant;
			int etatGaucheApres;
			int pasDejaBouge = 0;
			// lire l'etats de la roue a gauche(Avant bouger)
			if((P2IN & BIT0)==BIT0){
				  etatGaucheAvant = 1;
			}else{
				  etatGaucheAvant = 0;
			}
			// tourner a gauche: 7 pas
			for(pasDejaBouge=0;pasDejaBouge<7;){
				// si end_loop = 1, sortir cette etape
				if(end_loop == 1){
					break;
				}
				// Tourner le robot
				robot_gauche_2_roues(20, 80);
				// relire les etats
				init_ADC_LigneDetecteurA();
				ligne_dct_A = ReadAdc();
				init_ADC_LigneDetecteurB();
				ligne_dct_B = ReadAdc();
				// Si le detecteur a gauche est sur la ligne
				if(ligne_dct_A <= seuilBlancDetecteurA){
					while(1){
						robot_gauche_2_roues(20, 80);
						init_ADC_LigneDetecteurA();
						ligne_dct_A = ReadAdc();
						// Si le detcteur a gauche sort la ligne, s'arretera.
						if(ligne_dct_A > seuilBlancDetecteurA){
							end_loop = 1;
							break;
						}
						
					}
				}
				// Si le detecteur a droite est sur la ligne
				if(ligne_dct_B <= seuilBlancDetecteurB){
					while(1){
						robot_droite_2_roues(20, 80);
						init_ADC_LigneDetecteurB();
						ligne_dct_B = ReadAdc();
						// Si le detecteur a droite sort la ligne, s'arretera.
						if(ligne_dct_B > seuilBlancDetecteurB){
							end_loop = 1;
							break;
						}
					}
				}
				// lire l'etats de la roue a gauche(Apres bouger)
				if((P2IN & BIT0)==BIT0){
					  etatGaucheApres = 1;
				  }else{
					  etatGaucheApres = 0;
				 }
				// Comparer l'etat avant et l'etat apres
				if(etatGaucheAvant != etatGaucheApres){
					  pasDejaBouge++;
				}
				// mettre etatGaucheApres dans etatGaucheAvant pour la prochaine fois
				etatGaucheAvant = etatGaucheApres;
			}
			// attendre un peu
                        tempo(500);
			// tourner a droite: 12 pas
			for(pasDejaBouge=0;pasDejaBouge<12;){
				// si end_loop = 1, sortir cette etape
				if(end_loop == 1){
					break;
				}
				// Tourner le robot
				robot_droite_2_roues(20, 80);
				// relire l'etat de la roue a droite
				init_ADC_LigneDetecteurB();
				ligne_dct_B = ReadAdc();
				// Si le detecteur a droite est sur la ligne
				if(ligne_dct_B <= seuilBlancDetecteurB){
					while(1){
						robot_droite_2_roues(20, 80);
						init_ADC_LigneDetecteurB();
						ligne_dct_B = ReadAdc();
						// Si le detecteur a droite sort la ligne, s'arretera.
						if(ligne_dct_B > seuilBlancDetecteurB){
							end_loop = 1;
							break;
						}
					}
				}
				// lire l'etats de la roue a gauche(Apres bouger)
				if((P2IN & BIT0)==BIT0){
					  etatGaucheApres = 1;
				  }else{
					  etatGaucheApres = 0;
				 }
				// Comparer l'etat avant et l'etat apres
				if(etatGaucheAvant != etatGaucheApres){
					  pasDejaBouge++;
				}
				// mettre etatGaucheApres dans etatGaucheAvant pour la prochaine fois
				etatGaucheAvant = etatGaucheApres;
			}
        }  	
}

void Chercher_La_Ligne_360(int seuilBlancDetecteurA, int seuilBlancDetecteurB){
	int ligne_dct_A;
        int ligne_dct_B;
        // lire l'etat de detecteur ligne
	init_ADC_LigneDetecteurA();
	ligne_dct_A = ReadAdc();
        init_ADC_LigneDetecteurB();
	ligne_dct_B = ReadAdc();
        //Si une des detecteurs est sur la ligne
        if(ligne_dct_A <= seuilBlancDetecteurA || ligne_dct_B <= seuilBlancDetecteurB){
            // Si le detecteur a gauche est sur la ligne
            if(ligne_dct_A <= seuilBlancDetecteurA){
              while(1){
                  robot_gauche_2_roues(10, 50);
                  init_ADC_LigneDetecteurA();
                  ligne_dct_A = ReadAdc();
                  // Si le detcteur a gauche sort la ligne, s'arretera.
                  if(ligne_dct_A > seuilBlancDetecteurA){
                        break;
                  }
              }
            }else{
                // Si le detecteur a droite est sur la ligne
                while(1){
                     robot_droite_2_roues(10, 50);
                     init_ADC_LigneDetecteurB();
                     ligne_dct_B = ReadAdc();
                     // Si le detecteur a droite sort la ligne, s'arretera.
                     if(ligne_dct_B > seuilBlancDetecteurB){
                        break;
                     }
                }
            }
        }else{
            // Si les deux detecteurs ne sont pas sur la ligne
            while(1){
                int end_loop = 0;
                robot_gauche_2_roues(10, 100);
                // relire les etats
                init_ADC_LigneDetecteurA();
                ligne_dct_A = ReadAdc();
                init_ADC_LigneDetecteurB();
                ligne_dct_B = ReadAdc();
                // Si le detecteur a gauche est sur la ligne
                if(ligne_dct_A <= seuilBlancDetecteurA){
                  while(1){
                      robot_gauche_2_roues(10, 50);
                      init_ADC_LigneDetecteurA();
                      ligne_dct_A = ReadAdc();
                      // Si le detcteur a gauche sort la ligne, s'arretera.
                      if(ligne_dct_A > seuilBlancDetecteurA){
                            end_loop = 1;
                            break;
                      }
                      
                  }
                }
                // Si le detecteur a droite est sur la ligne
                if(ligne_dct_B <= seuilBlancDetecteurB){
                    while(1){
                         robot_droite_2_roues(10, 50);
                         init_ADC_LigneDetecteurB();
                         ligne_dct_B = ReadAdc();
                         // Si le detecteur a droite sort la ligne, s'arretera.
                         if(ligne_dct_B > seuilBlancDetecteurB){
                            end_loop = 1;
                            break;
                         }
                    }
                }
                // Sortir la boucle
                if(end_loop == 1){
                    break;
                }
            } 
        }  
}

void Clignoter_LED_Vert(int s){
    int i;
    for(i=0;i<s;i++){
        P1OUT |= BIT6;
        tempo(750);
        P1OUT &= ~BIT6;
        tempo(250);
    }
}