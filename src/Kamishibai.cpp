/** @file Kamishibai.cpp
 *
 * @brief A library for Arduino boards that reads angles from AS5047 and AS5147 sensors.
 * 		  Also support configuration of the sensor parameters.
 *
 * @par
 * COPYRIGHT NOTICE: MIT License
 *
 * 	Copyright (c) 2026 Planète Sciences Vendée
 *
 * 	Permission is hereby granted, free of charge, to any person obtaining a copy
 * 	of this software and associated documentation files (the "Software"), to deal
 * 	in the Software without restriction, including without limitation the rights
 * 	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * 	copies of the Software, and to permit persons to whom the Software is
 * 	furnished to do so, subject to the following conditions:
 *
 * 	The above copyright notice and this permission notice shall be included in all
 * 	copies or substantial portions of the Software.
 *
 * 	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * 	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * 	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * 	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * 	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * 	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * 	SOFTWARE.
 *
*/

#include "Kamishibai.h"

Kamishibai::Kamishibai() : _player(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS), _strip()
{
}

void Kamishibai::demarrer() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);
    if (!this->_started) {
        this->_started = true;
        Serial.begin(9600);
        Serial.println("--- Planète Sciences Vendée ---");
        Serial.println("[Kamishibai] Démarrage...");
        Serial.print("[Kamishibai] Module Audio : ");
        if (!_player.begin())
        {
            Serial.println("[Kamishibai] ERREUR !");
            while (1);
        }
        Serial.println("[Kamishibai] OK !");

        Serial.print("[Kamishibai] Module SD : ");
        if (!SD.begin(CARDCS))
        {
            Serial.println("[Kamishibai] ERREUR !");
            while (1) ;
        }
        Serial.println("[Kamishibai] OK !");
        this->volumeSon(50);

        if (! _player.useInterrupt(VS1053_FILEPLAYER_PIN_INT)) {
            Serial.println(F("DREQ : ERREUR"));
        }  
    }
}

void Kamishibai::jouerSon(String fichier) {
    if (!_player.stopped()) {
        arreterSon();
    }
    _volumeSon(_volume);
    Serial.print("[Kamishibai] Lecture du fichier ");
    Serial.print(fichier);
    Serial.println(" ...");
    this->_player.startPlayingFile(fichier.c_str());
}

void Kamishibai::arreterSon() {
    Serial.println("[Kamishibai] Arrêt de la lecture du son !");
    this->_player.stopPlaying();
    _volumeSon(0);
}

void Kamishibai::volumeSon(uint8_t pourcent) {
    Serial.print("[Kamishibai] Volume sonore réglé à ");
    Serial.print(pourcent);
    Serial.println("%.");
    _volume = pourcent;
    _volumeSon(_volume);
}

void Kamishibai::_volumeSon(uint8_t pourcent) {
    pourcent = pourcent > 100 ? 100 : pourcent;
    pourcent = pourcent < 0 ? 0 : pourcent;
    uint8_t volume = map(pourcent, 0, 100, 105, 0);
    this->_player.setVolume(volume, volume);
};

void Kamishibai::lumiereBleu() {
    lumiereCouleur(0, 0, 255);
}

void Kamishibai::lumiereVert() {
    lumiereCouleur(0, 255, 0);
}

void Kamishibai::lumiereRouge() {
    lumiereCouleur(255, 0, 0);
}

void Kamishibai::lumiereCouleur(uint8_t r, uint8_t g, uint8_t b) {
    analogWrite(R_PIN, r);
    analogWrite(B_PIN, g);
    analogWrite(G_PIN, b);

    rgb_color color;
    color.red = r;
    color.green = g;
    color.blue = b;

    for(uint16_t i = 0; i < LED_COUNT; i++)
    {
        _colors[i] = color;
    }
    _strip.write(_colors, LED_COUNT);
}

void Kamishibai::arreterLumiere() {
    lumiereCouleur(0, 0, 0);
}

void Kamishibai::attendreBouton() {
    while (!digitalRead(BUTTON_PIN)) {
        delay(100);
    }
    while (digitalRead(BUTTON_PIN)) {
        delay(100);
    }
}

Kamishibai module;