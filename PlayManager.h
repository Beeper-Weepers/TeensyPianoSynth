class PlayManager {
  private:
    Bounce **buttons;
    AudioEffectEnvelope **envelopes;
    int sz;

  public:
    void setup(int size, int inputs[], AudioEffectEnvelope* freqsSet[]) {
      //Initialize arrays
      buttons = new Bounce*[size];
      envelopes = new AudioEffectEnvelope*[size];
      
      sz = size;
      envelopes = freqsSet;

      //Setup of objects
      for (int i = 0; i < sz; i++) {
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
          envelopes[i]->noteOn();
        } else if (buttons[i]->fell()) {
          envelopes[i]->noteOff();
        }
        
      }
    }

    //Deconstructor
    ~PlayManager() {
      //Destruct all classes
      for (int i = 0; i < sz; i++) {
        delete buttons[i];
        delete envelopes[i];
      }

      //Delete entire arrays
      delete[] buttons;
      delete[] envelopes;
    }
};
