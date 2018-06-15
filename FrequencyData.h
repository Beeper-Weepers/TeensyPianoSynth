#ifndef _FrequencyData_h_
#define _FrequencyData_h_


//Setup note definitions for octaves 2 - 4

#define NOTE_E2   82.41
#define NOTE_F2   87.31
#define NOTE_Fs2  92.50
#define NOTE_G2   98.00
#define NOTE_Gs2 103.82
#define NOTE_A2  110.00
#define NOTE_As2 116.54
#define NOTE_B2  123.47
#define NOTE_C3  130.81
#define NOTE_Cs3 138.59
#define NOTE_D3  146.83
#define NOTE_Ds3 155.56
#define NOTE_E3  164.81
#define NOTE_F3  174.61
#define NOTE_Fs3 185.00
#define NOTE_G3  196.00
#define NOTE_Gs3 207.65
#define NOTE_A3  220.00
#define NOTE_As3 233.08
#define NOTE_B3  246.94
#define NOTE_C4  261.63
#define NOTE_Cs4 277.18
#define NOTE_D4  293.66
#define NOTE_Ds4 311.13
#define NOTE_E4  329.63
#define NOTE_F4  349.23
#define NOTE_Fs4 369.99
#define NOTE_G4  392.00
#define NOTE_Gs4 415.30
#define NOTE_A4  440.00
#define NOTE_As4 466.16
#define NOTE_B4  493.88
#define NOTE_C5  523.25

//Frequencies for keys
#define scaleCount 2
const float cMajor[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };
const float cHarmonicMinor[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_Fs4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };
const float* scales[] = { cMajor, cHarmonicMinor };


#endif
