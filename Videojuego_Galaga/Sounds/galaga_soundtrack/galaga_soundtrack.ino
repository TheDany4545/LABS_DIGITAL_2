
// Credit:
// Midi to Arduino Converter
//     - Andy Tran (extramaster), 2015
// https://www.extramaster.net/tools/midiToArduino/
//
// Process:
// Midi -> Midi tracks -> Note mappings -> Frequency
//
// CC0

// Set this to be the pin that your buzzer resides in. (Note that you can only have one buzzer actively using the PWM signal at a time).
int tonePin = 2;
void setup() {

}

void midi() {

    tone(tonePin, 391, 351.5625);
    delay(390.625);
    tone(tonePin, 440, 234.375);
    delay(260.416666667);
    tone(tonePin, 523, 117.1875);
    delay(130.208333333);
    tone(tonePin, 493, 351.5625);
    delay(390.625);
    tone(tonePin, 391, 351.5625);
    delay(390.625);
    tone(tonePin, 523, 351.5625);
    delay(390.625);
    tone(tonePin, 587, 234.375);
    delay(260.416666667);
    tone(tonePin, 698, 117.1875);
    delay(130.208333333);
    tone(tonePin, 659, 351.5625);
    delay(390.625);
    tone(tonePin, 587, 351.5625);
    delay(390.625);
    tone(tonePin, 622, 351.5625);
    delay(390.625);
    tone(tonePin, 587, 234.375);
    delay(260.416666667);
    tone(tonePin, 523, 117.1875);
    delay(130.208333333);
    tone(tonePin, 466, 351.5625);
    delay(390.625);
    tone(tonePin, 622, 351.5625);
    delay(390.625);
    tone(tonePin, 932, 351.5625);
    delay(390.625);
    tone(tonePin, 783, 234.375);
    delay(260.416666667);
    tone(tonePin, 622, 117.1875);
    delay(130.208333333);
    tone(tonePin, 587, 351.5625);
    delay(390.625);
    tone(tonePin, 783, 234.375);
    delay(260.416666667);
    tone(tonePin, 659, 468.75);
    delay(520.833333333);

}

void loop() {
    // Play midi
    midi();
}
