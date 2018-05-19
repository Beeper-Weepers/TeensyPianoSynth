#ifndef _BinaryDisplay_h_
#define _BinaryDisplay_h_

class BinaryDisplay {
  private:
    const int *pins;
    uint8_t sz;
    
    boolean on;
    uint64_t startOn;
    int left; //time left in milliseconds
    
  public:
    void setup(uint8_t arraySize, const int pinArray[]) {
      pins = pinArray;
      sz = arraySize;
      on = false;

      //Setup LEDs
      for (int i = 0; i < arraySize; i++) {
        pinMode(pins[i], OUTPUT);
      }
    }

    void setValue(int value) {
      
      int bitBin;
      for (int i = 0; i < sz; i++) {
        bitBin = 1 << i;
        digitalWrite(pins[i], (value & bitBin) >> i);
      }

      on = true;
      startOn = millis();
      left = 10 * 1000;
    }

    void updateLEDs() {
      if (on && left < (int) (millis() - startOn)) {
        on = false;
        //Reset lights
        for (int i = 0; i < sz; i++) {
          digitalWrite(pins[i], 0);
        }
      }
    }
};

#endif
