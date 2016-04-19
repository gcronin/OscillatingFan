
// Value	Register name
//              counter	TCNT2
//              TOP	OCR2A
//              MATCH	OCR2B

//  Clock Select Bits:  set with TCCR2B
//     CS22    CS21   CS20
//     0        0        0    //timer/counter stopped
//     0       0         1   // no prescaler
//     1       0         0    // 64
//



#define OSP_SET_WIDTH(cycles) (OCR2B = 0xff-(cycles-1))

// Setup the one-shot pulse generator and initialize with a pulse width that is (cycles) clock counts long

void osp_setup(uint8_t cycles) {


  TCCR2B =  0;      // Halt counter by setting clock select bits to 0 (No clock source).
              // This keeps anyhting from happeneing while we get set up

  TCNT2 = 0x00;     // Start counting at bottom. 
  OCR2A = 0;      // Set TOP to 0. This effectively keeps us from counting becuase the counter just keeps reseting back to 0.
          // We break out of this by manually setting the TCNT higher than 0, in which case it will count all the way up to MAX and then overflow back to 0 and get locked up again.
  OSP_SET_WIDTH(cycles);    // This also makes new OCR values get loaded frm the buffer on every clock cycle. 

  TCCR2A = _BV(COM2B0) | _BV(COM2B1) | _BV(WGM20) | _BV(WGM21); // OC2B=Set on Match, clear on BOTTOM. Mode 7 Fast PWM.
  TCCR2B = _BV(WGM22) | _BV(CS22) | _BV(CS21) | _BV(CS20);         // Start counting now. WGM22=1 to select Fast PWM mode 7  PRESCALER 32 (011)

  DDRD |= _BV(3);     // Set pin to output (Note that OC2B = GPIO port PD3 = Arduino Digital Pin 3)
}

// Fire a one-shot pulse. Use the most recently set width. 

#define OSP_FIRE() (TCNT2 = OCR2B - 1)

// Test there is currently a pulse still in progress

#define OSP_INPROGRESS() (TCNT2>0)

// Fire a one-shot pusle with the specififed width. 
// Order of operations in calculating m must avoid overflow of the unint8_t.
// TCNT2 starts one count lower than the match value becuase the chip will block any compare on the cycle after setting a TCNT. 

/*************/

long timeStamp = 0;  // note millis uses timer0, (8bit), so we're fine using this...doesn't conflict with timer2
boolean goingDown = false;
int width = 20;  
  
  
void setup()
{
osp_setup(20);
timeStamp = millis();
}


void loop()
{
  if(millis() - timeStamp > 1000)
  {
    if(goingDown)  --width;
    else ++width;
    timeStamp = millis();
  }
  if(width < 21)
  {
    goingDown = false;
  }
  if(width > 30)
  {
    goingDown = true;
  }

  OSP_SET_WIDTH(width);
  OSP_FIRE();
  while (OSP_INPROGRESS());
  delay(20);  //wait 20ms




}
/*************/
