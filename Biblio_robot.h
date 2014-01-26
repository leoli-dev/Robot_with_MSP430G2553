

/*
*  Bibliothèque de fonctions utilisables pour piloter le robot          *
*                                                                       *
*/



  
void Init_Robot();

void Choix_direction(unsigned char sens);

void Vitesse_moteurs(unsigned int vit_gauche, unsigned int vit_droite);

void Arret_robot();

void Demarrer_robot();

void tempo( unsigned int ms);


void robot_avancer(unsigned int ms, unsigned int vit);
void robot_reculer(unsigned int ms, unsigned int vit);
void robot_gauche_2_roues(unsigned int ms, unsigned int vit);
void robot_droite_2_roues(unsigned int ms, unsigned int vit);
void robot_gauche_1_roue(unsigned int ms, unsigned int vit);
void robot_droite_1_roue(unsigned int ms, unsigned int vit);