#ifndef _PlayManager_h_
#define _PlayManager_h_

class PlayManager {
  private:
    //Bounce **buttons;
    const int powerPins[];
    const int inputPins[];
    AudioEffectEnvelope **envelopes;
    int powerSz;
    int inputSz;
    int envelopeSz;

  public:
    void setup(int powSz, int inpSz, int envSz, const int powPins[], const int inpPins[], AudioEffectEnvelope *envSet[]) {
      //Initialize arrays
      inputPins = inpPins;
      powerPins = powPins;
      
      powerSz = powSz;
      inputSz = inpSz;
      envelopeSz = envSz;
      
      envelopes = envSet;

      //Setup of pins
      for (int i = 0; i < inpSz; i++) {
        pinMode(inputs[i], INPUT_PULLDOWN);
      }

      //Setup of envelope objects
      for (int i = 0; i < powSz; i++) {
        for (int j = 0; j < inpSz; j++) {
          envelopes[i * j]->hold(100);
          envelopes[i * j]->decay(800);
          envelopes[i * j]->sustain(0.1);
        }
      }
    }

    void updatePatches() {
      
      for (int i = 0; i < powerSz; i++) {
        digitalWrite(powerPins[i], HIGH);
        delay(5);
        
        for (int j = 0; j < inputSz; j++) {
            if (digitalRead(pins[j])) {
              if (!envelopes[i * j]->isActive()) {
                envelopes[i * j]->noteOn();
              }
            } else if (envelopes[i * j]->isActive()) {
              envelopes[i * j]->noteOff();
            }
        }
        
        digitalWrite(powerPins[i], LOW);
      }
    }

    //Deconstructor
    ~PlayManager() {
      delete[] envelopes;
    }
};

#endif
