/*
    Kamishibai - Planète Sciences Vendée

    Description :
        - Personnaliser le programme ci-dessous pour jouer des musiques et changer la couleur du bandeau LED
          après chaque activation du bouton poussoir.
*/


#include <Kamishibai.h>

void setup() {
    Demarrer();
}

void loop() {
    // Allumer le bandeau LED en rouge
    LumiereRouge();
    // Aussi disponible avec LumiereVert, LumiereBleu

    // Met en pause le programme jusqu'à activation du bouton poussoir :
    AttendreBouton();

    // Gérer le volume sonore entre 0 et 100%
    VolumeSon(75);

    // Jouer un fichier de musique stockée sur la carte SD
    // Le fichier doit contenir au maximum 8 caractères et doit terminer par .mp3
    JouerSon("son1.mp3");
    LumiereBleu();
    AttendreBouton();

    LumiereVert();
    AttendreBouton();

    // On peut jouer autant de sons que l'on veut.
    JouerSon("son2.mp3");
    AttendreBouton();

    // Allumer le bandeau LED avec une couleur personnalisée
    // On passe les intensités lumineures entre 0 et 255
    // ROUGE, VERT, BLEU
    LumiereCouleur(255,255,255);
    ArreterSon();
    AttendreBouton();

    ArreterLumiere();
    AttendreBouton();
    
    // A la fin du programme : on retourne au début.
}