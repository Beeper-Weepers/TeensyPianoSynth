#ifndef _PlayManager_h_
#define _PlayManager_h_

class PlayManager {
  private:
    Bounce **buttons;
    AudioEffectEnvelope **envelopes;
    int sz;
    BinaryDisplay *disp;

  public:
    void setup(int size, const int inputs[], AudioEffectEnvelope *envSet[], BinaryDisplay *dis) {
      //Initialize arrays
      buttons = new Bounce*[size];
      
      sz = size;
      envelopes = envSet;

      //Setup of objects
      for (int i = 0; i < sz; i++) {
        //Setup envelopes
        envelopes[i]->hold(100);
        envelopes[i]->decay(800);
        envelopes[i]->sustain(0.0);
        
        //Instantiate new buttons
        buttons[i] = new Bounce();
        
        pinMode(inputs[i], INPUT);
        buttons[i]->attach(inputs[i]);
        buttons[i]->interval(5);
      }

      disp = dis;
    }

    void updatePatches() {
      
      for (int i = 0; i < sz; i++) {
        
        buttons[i]->update();
        if (buttons[i]->rose()) {
          envelopes[i]->noteOff();
        } else if (buttons[i]->fell()) {
          envelopes[i]->noteOn();
          disp->setValue(i + 1);
        }
        
      }
    }

    //Deconstructor
    ~PlayManager() {
      //Destruct all classes
      /*for (int i = 0; i < sz; i++) {
        delete buttons[i];
      }*/

      //Delete entire arrays
      delete[] buttons;
      delete[] envelopes;
    }
};

#endif
