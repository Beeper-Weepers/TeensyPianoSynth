class BinaryDisplay {
  private:
    int *pins;
    uint8_t *tempPinValues;
    int sz;
    
  public:
    void setup(int *pinArray, int arraySize) {
      //Allocate memory dynamically
      tempPinValues = (uint8_t*) malloc(arraySize * sizeof(uint8_t));
      
      pins = pinArray;
      sz = arraySize;
    }

    void setValue(int value) {
      //Clear temp value array
      for (int i = 0; i < sz; i++) { tempPinValues[0] = LOW; }

      //Fill temp array with binary values
      int j;
      while (value > 0) {
        tempPinValues[j++] = value % 2;
        value /= 2;
      }

      //Read temp array into pins
      for (int i = 0; i < sz; i++) {
        digitalWrite(pins[i], tempPinValues[i]);
      }
    }
};

