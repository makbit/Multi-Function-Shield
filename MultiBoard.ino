//////////////////////////////////////////////////////////////////////////////////////
//  Multi-function shield for Arduino UNO R3                                        //
//  Sample sketch that demonstates most features of this shield.                    //
//                                                                                  //
//  Author: K.Max  (c) 2015         http://makbit.com                               //
//////////////////////////////////////////////////////////////////////////////////////
#include <IRremote.h>
#include <IRremoteInt.h>

//////////////////////////////////////////////////////////////////////////////////////
#define ON             LOW
#define OFF            HIGH

#define LED1            13
#define LED2            12
#define LED3            11
#define LED4            10

#define KEY1            A1
#define KEY2            A2
#define KEY3            A3
#define TEMPRT_PIN      A4
#define POT_PIN         A0
#define IRED_PIN        2
#define BEEP_PIN        3
#define LATCH_PIN       4
#define CLOCK_PIN       7
#define DATA_PIN        8

//////////////////////////////////////////////////////////////////////////////////////
#define BUT_POWER             0xe318261b
#define BUT_MODE              0x00511dbb
#define BUT_SOUND             0xee886d7f
#define BUT_PLAY              0x52a3d41f
#define BUT_PREV              0xd7e84b1b
#define BUT_NEXT              0x20fe4dbb
#define BUT_MINUS             0xa3c8eddb
#define BUT_PLUS              0xe5cfbd7f
#define BUT_EQ                0xf076c13b
#define BUT_0                 0xc101e57b
#define BUT_1                 0x9716be3f
#define BUT_2                 0x3d9ae3f7
#define BUT_3                 0x6182021b
#define BUT_4                 0x8c22657b
#define BUT_5                 0x488f3cbb
#define BUT_6                 0x0449e79f
#define BUT_7                 0x32c6fdf7
#define BUT_8                 0x1bc0157b
#define BUT_9                 0x3ec3fc1b
#define BUT_REWIND            0x97483bfb
#define BUT_USD               0xf0c41643

//////////////////////////////////////////////////////////////////////////////////////
// 7-Segment LED byte maps for numbers 0 to 9, 
// 'A', 'b', 'C', 'd', 'E', 'F', '.', 'H', 'J', 'L',
// 'P', 'q', 'U', 'o', '°', '_', '-', '=', '?', ' '
const byte SEGMENT_MAP[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
                            0x77,0x7C,0x39,0x5E,0x79,0x71,0x80,0x76,0x0E,0x38,
                            0x73,0x67,0x3E,0x5C,0x63,0x08,0x40,0x48,0x53,0x00};
                            
// Byte maps to select digit 1 to 4
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

//////////////////////////////////////////////////////////////////////////////////////

IRrecv IR(IRED_PIN);
decode_results results;
//////////////////////////////////////////////////////////////////////////////////////
void setup()
{
    // put your setup code here, to run once:
    analogReference(INTERNAL);

    pinMode(KEY1,       INPUT);
    pinMode(KEY2,       INPUT);
    pinMode(KEY3,       INPUT);
    pinMode(POT_PIN,    INPUT);
    pinMode(TEMPRT_PIN, INPUT);

    pinMode(LATCH_PIN,  OUTPUT);
    pinMode(CLOCK_PIN,  OUTPUT);
    pinMode(DATA_PIN,   OUTPUT);
    pinMode(LED1,       OUTPUT);
    pinMode(LED2,       OUTPUT);
    pinMode(LED3,       OUTPUT);
    pinMode(LED4,       OUTPUT);
    pinMode(BEEP_PIN,   OUTPUT);

    digitalWrite(BEEP_PIN, OFF);
    digitalWrite(LED1,     OFF);
    digitalWrite(LED2,     OFF);
    digitalWrite(LED3,     OFF);
    digitalWrite(LED4,     OFF);

    pinMode(MOTOR_LEFT_FRWD, OUTPUT);
    pinMode(MOTOR_LEFT_BKWD, OUTPUT);
    pinMode(MOTOR_RIGHT_FRWD, OUTPUT);
    pinMode(MOTOR_RIGHT_BKWD, OUTPUT);

    IR.enableIRIn();
}


//////////////////////////////////////////////////////////////////////////////////////
void loop()
{
    int nTemprt = 0;

    // LM35 is connected to A4
    float t = (analogRead(TEMPRT_PIN) + analogRead(TEMPRT_PIN)) / 2;
    //nTemprt = (t * 5 * 100) / 1024;
    nTemprt = (t * 1.1 * 100) / 1024;
    drawDigit(0, 0x0C);   // Celsuis
    drawDigit(1, 0x0F+9); // Degree sign
    drawDigit(2, (nTemprt/10) % 10);
    drawDigit(3, (nTemprt/1)  % 10);

    if( digitalRead(KEY1)==ON )
    {
        digitalWrite(BEEP_PIN, ON);
        delay(500);
        digitalWrite(BEEP_PIN, OFF);
    }

    if( digitalRead(KEY3)==ON )
    {
      //int pot = analogRead(POT_PIN);
    }

/*
    if( IR.decode(&results) )
    {
        Serial.print("irCode: ");
        Serial.print(results.value, HEX);
        Serial.print(",  bits: ");
        Serial.println(results.bits);
        IR.resume();
    }
*/    
    //-----------------------------------------------------------------//
    if( IR.decode(&results) )
    {
        switch( results.value )
        {
            case BUT_EQ:
                break;
            case BUT_SOUND:
                break;
            case BUT_POWER:
                break;
            case BUT_0://PLAY:
                break;
            case BUT_REWIND:
                break;
            case BUT_PREV:
                break;
            case BUT_NEXT:
                break;
            case BUT_MINUS:
                break;
            case BUT_PLUS:
                break;
        }
        IR.resume();
    }
}


//////////////////////////////////////////////////////////////////////////////////////
void drawDigit(byte column, byte number)
{
    if( number >= sizeof(SEGMENT_MAP) )
    {
        number = sizeof(SEGMENT_MAP) - 1;
    }
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, ~SEGMENT_MAP[number] );
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, SEGMENT_SELECT[column]);
    digitalWrite(LATCH_PIN, HIGH);
}
///////////////////////////////////////////////////////////////////////////////////////
