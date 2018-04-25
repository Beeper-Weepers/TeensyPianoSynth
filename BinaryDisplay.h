class BinaryDisplay {
  private:
    int *pins;
    int sz;
    
  public:
    void setup(int *pinArray, int arraySize) {
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
