#ifndef _BinaryDisplay_h_
#define _BinaryDisplay_h_

class BinaryDisplay {
  private:
    const int *pins;
    int sz;
    
  public:
    void setup(int arraySize, const int pinArray[]) {
      pins = pinArray;
      sz = arraySize;
    }

    void setValue(int value) {
      
      int bitBin;
      for (int i = 0; i < sz; i++) {
        bitBin = 1 << i;
        digitalWrite(i, (value & bitBin) >> i);
      }
      
    }
};

#endif
