#ifndef _PlayManager_h_
#define _PlayManager_h_

class PlayManager {
  private:
    Bounce **buttons;
    AudioEffectEnvelope *envelopes;
    int sz;

  public:
    void setup(int size, const int inputs[], AudioEffectEnvelope envSet[]) {
      //Initialize arrays
      buttons = new Bounce*[size];
      
      sz = size;
      envelopes = envSet;

      //Setup of objects
      for (int i = 0; i < sz; i++) {
        //Setup envelopes
        envelopes[i].hold(100);
        envelopes[i].decay(800);
        envelopes[i].sustain(0.0);
        
        //Instantiate new buttons
        buttons[i] = new Bounce();
        
        pinMode(inputs[i], INPUT);
        buttons[i]->attach(inputs[i]);
        buttons[i]->interval(5);
      }
    }

    void updatePatches() {
      for (int i = 0; i < sz; i++) {
        
        buttons[i]->update();
        if (buttons[i]->rose()) {
          envelopes[i].noteOn();
        } else if (buttons[i]->fell()) {
          envelopes[i].noteOff();
        }
        
      }
    }

    //Deconstructor
    ~PlayManager() {
      //Destruct all classes
      for (int i = 0; i < sz; i++) {
        delete buttons[i];
      }

      //Delete entire arrays
      delete[] buttons;
      delete[] envelopes;
    }
};

#endif
