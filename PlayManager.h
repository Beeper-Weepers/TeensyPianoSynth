class PlayManager {
  private:
    Bounce *buttons;
    AudioEffectEnvelope *envelopes;
    int sz;

  public:
    void setup(int size, int *inputs, AudioEffectEnvelope *freqsSet) {
      sz = size;
      buttons = inputs;
      envelopes = freqsSet;

      //Setup of objects
      for (int i = 0; i < sz; i++) {
        //Button setups
        buttons[i] = new Bounce();
        
        pinMode(waveform1Set[i], INPUT);
        buttons->attach(inputs[i]);
        buttons->interval(5);
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
};
