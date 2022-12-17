/* Example code with timer intyerrutp that will create an interruption each 
 *  500ms using timer1 and prescalar of 256.
Calculations (for 500ms): 
  System clock 16 Mhz and Prescalar 256;
  Timer 1 speed = 16Mhz/256 = 62.5 Khz    
  Pulse time = 1/62.5 Khz =  16us  
  Count up to = 500ms / 16us = 31250 (so this is the value the OCR register should have)*/  
int currentState  = 0;
int previousState = 0;
int pin           = 0;
int interval      = 1;
int digit[]={2,3,4,5,6,7,8};
void setup(){ 
  for ( int i=0; i<7 ; i++){    //set OUTPUT pin
  pinMode(digit[i],OUTPUT);
  } 
   
  cli();                      //stop interrupts for till we make the settings
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */  
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  /*3. We enable compare match mode on register A*/
  TIMSK1 |= B00000010;        //Set OCIE1A to 1 so we enable compare match A 
  /*4. Set the value of register A to 31250*/
  OCR1A = 62500;             //Finally we set compare register A to this value  
  sei();                     //Enable back the interrupts
}

void loop() {
  if( currentState - previousState >= interval){
    previousState = currentState;
    interval++;
    digitalWrite(digit[pin],LOW);
    pin++;
    if(pin>7){
            interval=1;
            pin=0;
    }
   }else{
    digitalWrite(digit[pin],HIGH);
  }
}


ISR(TIMER1_COMPA_vect){
  
currentState++;

}
