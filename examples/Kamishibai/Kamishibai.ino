#include <Kamishibai.h>

Kamishibai module;

void setup() {
    module.demarrer();
}

void loop() {
    module.lumiere(255, 255, 255);
    module.attendreBouton();

    module.jouerSon("track001.mp3");
    module.volumeSon(75);
    module.lumiere(240, 255, 240);

    module.attendreBouton();

    module.arreterSon();
    module.arreterLumiere();
}