#ifndef _PlayManager_h_
#define _PlayManager_h_

class PlayManager {
  private:
    //Bounce **buttons;
    
    const int *powerPins;
    const int *inputPins;

    float *notes;
    
    AudioEffectEnvelope **envelopes;
    AudioSynthWaveform **waveforms;

    int *noteIndicies;
    int *original;
    
    int powerSz;
    int inputSz;
    int envelopeSz;

  public:
    //Constructor
    void setup(int powSz, int inpSz, const int envSz, const int powPins[], int inpPins[], AudioEffectEnvelope *envSet[], AudioSynthWaveform *waveSet[], float nts[]) {
      //Initialize arrays
      inputPins = inpPins;
      powerPins = powPins;
      envelopes = envSet;
      waveforms = waveSet;
      noteIndicies = new int[envSz];
      original = new int[envSz];
      notes = nts;

      //Initialize original array
      for (int i = 0; i < envSz; i++) {
        original[i] = i;
      }

      //Initialize sizes
      powerSz = powSz;
      inputSz = inpSz;
      envelopeSz = envSz;

      //Setup of pins
      for (int i = 0; i < inpSz; i++) {
        pinMode(inputPins[i], INPUT_PULLDOWN);
      }
      for (int i = 0; i < powSz; i++) {
        pinMode(powerPins[i], OUTPUT);
      }

      //Setup of envelope objects
      for (int i = 0; i < envelopeSz; i++) {
          envelopes[i]->hold(100);
          envelopes[i]->decay(800);
          envelopes[i]->sustain(0.1);
      }
    }

    //Helper function: finds the position of a noteIndex in the envelope
    int8_t findInEnvelopes(int value) {
      for (int i = 0; i < envelopeSz; i++) {
        if (value == noteIndicies[i]) {
          return i;
        }
      }
      return -1;
    }

    //Helper function: swaps to envelope indicies
    void swapEnvelopes(int in1, int in2) {
      int n2 = noteIndicies[in2];
      AudioEffectEnvelope* e2 = envelopes[in2];
      int o2 = original[in2];

      noteIndicies[in2] = noteIndicies[in1];
      envelopes[in2] = envelopes[in1];
      original[in2] = original[in1];

      noteIndicies[in1] = n2;
      envelopes[in1] = e2;
      original[in1] = o2;
    }

    //Helper function: adds new traits to the head and pushes everything else down
    void envelopeAdd(int noteInd) {

      //Store last values in temp
      //int tempN = noteIndicies[0];
      AudioEffectEnvelope* tempE = envelopes[0];
      int tempO = original[0];
      
      //Push down
      for (int i = 0; i < envelopeSz - 1; i++) {
        noteIndicies[i] = noteIndicies[i+1];
        envelopes[i] = envelopes[i+1];
        original[i] = original[i+1];
      }

      //Put last values up as new head
      //noteIndicies[envelopeSz - 1] = tempN;
      envelopes[envelopeSz - 1] = tempE;
      original[envelopeSz - 1] = tempO;
      
      //Assign new value to the head 
      int wavPos = original[envelopeSz - 1] * 2;
      waveforms[wavPos]->frequency(notes[noteInd]);
      waveforms[wavPos + 1]->frequency(notes[noteInd] / 2.0);
      noteIndicies[envelopeSz - 1] = noteInd;
    }

    //Helper function: moves a envelope from one place to the head and bumps everything else down
    void envelopeBump(int index) {
      //Store index values in temp
      int tempN = noteIndicies[index];
      AudioEffectEnvelope* tempE = envelopes[index];
      int tempO = original[index];
      
      //Push down
      for (int i = index; i < envelopeSz - 1; i++) {
        noteIndicies[i] = noteIndicies[i+1];
        envelopes[i] = envelopes[i+1];
        original[i] = original[i+1];
      }

      //Put index up as new head
      noteIndicies[envelopeSz - 1] = tempN;
      envelopes[envelopeSz - 1] = tempE;
      original[envelopeSz - 1] = tempO;
    }

    //Main loop
    void updatePatches() {

      int indx, pos;
      
      for (int i = 0; i < powerSz; i++) {
        //Run power to key lane
        digitalWrite(powerPins[i], HIGH);
        delay(5);

        //Check inputs in lane
        for (int j = 0; j < inputSz; j++) {
            indx = i * inputSz + j;

            pos = findInEnvelopes(indx);
            //New key pressed
            if (digitalRead(inputPins[j])) {
              
              //Add to list
              if (pos == -1) {
                  envelopeAdd(indx);
                  envelopes[envelopeSz - 1]->noteOn();
              }
              //Bump up in list
              else {
                if (envelopes[pos]->state < 1 || envelopes[pos]->state > 5) {
                  envelopeBump(pos);
                  pos = envelopeSz - 1;
                  envelopes[pos]->noteOn();
                }
              }
              
            }
            //Old key released
            else if (pos != -1 && envelopes[pos]->state >= 1 && envelopes[pos]->state <= 5) {
                envelopes[pos]->noteOff();
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
