
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
int tonePin = 11;
void setup() {

}

void midi() {

    tone(tonePin, 493, 200.89275);
    delay(223.214166667);
    tone(tonePin, 587, 306.919479167);
    delay(341.021643519);
    tone(tonePin, 554, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 523, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 493, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 466, 200.89275);
    delay(223.214166667);
    tone(tonePin, 440, 200.89275);
    delay(223.214166667);
    tone(tonePin, 415, 200.89275);
    delay(223.214166667);
    tone(tonePin, 391, 200.89275);
    delay(223.214166667);
    tone(tonePin, 369, 200.89275);
    delay(223.214166667);
    tone(tonePin, 349, 200.89275);
    delay(223.214166667);
    tone(tonePin, 329, 401.7855);
    delay(446.428333333);
    tone(tonePin, 391, 401.7855);
    delay(446.428333333);
    tone(tonePin, 277, 200.89275);
    delay(223.214166667);
    tone(tonePin, 329, 200.89275);
    delay(223.214166667);
    tone(tonePin, 233, 401.7855);
    delay(446.428333333);
    tone(tonePin, 195, 401.7855);
    delay(446.428333333);
    tone(tonePin, 174, 200.89275);
    delay(223.214166667);
    tone(tonePin, 164, 200.89275);
    delay(223.214166667);
    tone(tonePin, 174, 401.7855);
    delay(446.428333333);
    tone(tonePin, 195, 401.7855);
    delay(446.428333333);
    tone(tonePin, 164, 200.89275);
    delay(223.214166667);
    tone(tonePin, 174, 200.89275);
    delay(223.214166667);
    tone(tonePin, 195, 200.89275);
    delay(223.214166667);
    tone(tonePin, 164, 200.89275);
    delay(223.214166667);
    tone(tonePin, 174, 200.89275);
    delay(223.214166667);
    tone(tonePin, 195, 200.89275);
    delay(223.214166667);
    tone(tonePin, 220, 200.89275);
    delay(223.214166667);
    tone(tonePin, 261, 602.67825);
    delay(669.6425);
    tone(tonePin, 195, 200.89275);
    delay(223.214166667);
    tone(tonePin, 207, 200.89275);
    delay(223.214166667);
    tone(tonePin, 261, 200.89275);
    delay(223.214166667);
    tone(tonePin, 293, 200.89275);
    delay(223.214166667);
    tone(tonePin, 391, 401.7855);
    delay(446.428333333);
    tone(tonePin, 349, 401.7855);
    delay(446.428333333);
    tone(tonePin, 261, 200.89275);
    delay(223.214166667);
    tone(tonePin, 293, 200.89275);
    delay(223.214166667);
    tone(tonePin, 329, 803.571);
    delay(892.856666667);
    tone(tonePin, 391, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 369, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 349, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 329, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 349, 200.89275);
    delay(223.214166667);
    tone(tonePin, 391, 200.89275);
    delay(223.214166667);
    tone(tonePin, 493, 200.89275);
    delay(223.214166667);
    tone(tonePin, 587, 401.7855);
    delay(446.428333333);
    tone(tonePin, 493, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 329, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 293, 401.7855);
    delay(446.428333333);
    tone(tonePin, 277, 909.597729167);
    delay(1010.66414352);
    tone(tonePin, 415, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 440, 200.89275);
    delay(223.214166667);
    tone(tonePin, 466, 200.89275);
    delay(223.214166667);
    tone(tonePin, 415, 200.89275);
    delay(223.214166667);
    tone(tonePin, 698, 200.89275);
    delay(223.214166667);
    tone(tonePin, 554, 200.89275);
    delay(223.214166667);
    tone(tonePin, 659, 803.571);
    delay(892.856666667);
    tone(tonePin, 587, 200.89275);
    delay(223.214166667);
    tone(tonePin, 659, 200.89275);
    delay(223.214166667);
    tone(tonePin, 698, 200.89275);
    delay(223.214166667);
    tone(tonePin, 554, 200.89275);
    delay(223.214166667);
    tone(tonePin, 587, 200.89275);
    delay(223.214166667);
    tone(tonePin, 698, 200.89275);
    delay(223.214166667);
    tone(tonePin, 880, 200.89275);
    delay(223.214166667);
    tone(tonePin, 1046, 200.89275);
    delay(223.214166667);
    tone(tonePin, 1567, 1004.46375);
    delay(1116.07083333);
    tone(tonePin, 1046, 200.89275);
    delay(223.214166667);
    tone(tonePin, 1864, 401.7855);
    delay(446.428333333);
    tone(tonePin, 1661, 401.7855);
    delay(446.428333333);
    tone(tonePin, 1567, 200.89275);
    delay(223.214166667);
    tone(tonePin, 1396, 200.89275);
    delay(223.214166667);
    tone(tonePin, 1318, 401.7855);
    delay(446.428333333);
    tone(tonePin, 1174, 200.89275);
    delay(223.214166667);
    tone(tonePin, 1108, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 932, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 880, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 783, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 698, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 659, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 587, 401.7855);
    delay(446.428333333);
    tone(tonePin, 554, 401.7855);
    delay(446.428333333);
    tone(tonePin, 587, 200.89275);
    delay(223.214166667);
    tone(tonePin, 659, 200.89275);
    delay(223.214166667);
    tone(tonePin, 783, 200.89275);
    delay(223.214166667);
    tone(tonePin, 739, 200.89275);
    delay(223.214166667);
    tone(tonePin, 698, 401.7855);
    delay(446.428333333);
    tone(tonePin, 440, 200.89275);
    delay(223.214166667);
    tone(tonePin, 523, 200.89275);
    delay(223.214166667);
    tone(tonePin, 622, 401.7855);
    delay(446.428333333);
    tone(tonePin, 783, 1205.3565);
    delay(1339.285);
    tone(tonePin, 587, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 554, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 523, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 493, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 523, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 659, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 783, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 987, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 1174, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 1108, 94.8660208333);
    delay(105.406689815);
    tone(tonePin, 987, 106.026729167);
    delay(117.807476852);
    tone(tonePin, 1046, 898.437020833);
    delay(998.263356481);

}

void loop() {
    // Play midi
    midi();
}
