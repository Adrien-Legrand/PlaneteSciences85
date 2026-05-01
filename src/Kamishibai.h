/** @file Kamishibai.h
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

#ifndef Kamishibai_hpp
#define Kamishibai_hpp

#include "Arduino.h"
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include <PololuLedStrip.h>

#define VS1053_RESET  8
#define VS1053_CS     6
#define VS1053_DCS    7
#define VS1053_DREQ   2
#define CARDCS 9

#define BUTTON_PIN  4
#define R_PIN       3
#define G_PIN       10
#define B_PIN       5
#define STRIP_PIN   A0
#define LED_COUNT   20

class Kamishibai {
    public: 
        Kamishibai();
        void demarrer();
        void lumiereBleu();
        void lumiereRouge();
        void lumiereVert();
        void lumiere(uint8_t r, uint8_t g, uint8_t b);
        void arreterLumiere();
        void jouerSon(String fichier);
        void arreterSon();
        void attendreBouton();
        void volumeSon(uint8_t pourcent);
    private:
        Adafruit_VS1053_FilePlayer _player;
        PololuLedStrip<STRIP_PIN> _strip;
        rgb_color _colors[LED_COUNT];
        bool _started = false;

};

#endif // Kamishibai_hpp