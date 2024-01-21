#include "IRremote.h"
#define RED 10                      //PIN + MODE
#define GREEN 9                     //PIN + MODE
#define BLUE 11                     //PIN + MODE
#define full_brightness 255 //0     // because of common anode type LED
#define half_brightness 128         // 0 means LED fully ON and
#define zero_brightness 0 // 255    // 255 means LED is OFF

//IR CODES
#define IR_RED    16195807
#define IR_GREEN  16228447
#define IR_BLUE   16212127
#define IR_ON     16236607
#define IR_OFF    16203967
#define IR_YELL   16197847
#define IR_PINK   16214167
#define IR_ALL    16244767
#define IR_FLASH  16240687 
#define IR_PLUS   16187647 
#define IR_MOINS  16220287

//modes
#define ALL  254
#define YELL 253
#define PINK 252
 
// ***********************************************************************************
// ********  Définitions pour manipuler les données en EEPROM               **********
// ***********************************************************************************
#include <EEPROM.h>
#define          PVR_EEPROM_START             600   // Adresse de base des données PVR
#define          DATAEEPROM_MAGIC     384021670UL   // UID de signature de la configuration
#define          DATAEEPROM_VERSION             1   // Version du type de configuration

struct dataEeprom {                         // Structure des données pour le stockage en EEPROM
  unsigned long         magic;              // Magic Number
  byte                  struct_version;     // Structure version :DATAEEPROM_VERSION
  int                   mode;
  int                   R_I;
  int                   B_I;
  int                   G_I;
  // taille totale :  13 bytes (byte = 1 byte, int = 2 bytes, long = float = 4 bytes) 
};




int IRpin = 3;          // pin for the IR sensor
int intr_pin = 2;
int del = 100;
IRrecv irrecv(IRpin);
decode_results results;
unsigned long int recv_code,prev_code;

unsigned short Mode = RED;
unsigned short R_I  = zero_brightness;
unsigned short B_I  = zero_brightness;
unsigned short G_I  = zero_brightness;
void setup() 
{
 int i;
 Serial.begin(9600);
 Serial.println("IR remote operated RGB LED"); 
  irrecv.enableIRIn();        // Start the receiver 
  attachInterrupt(digitalPinToInterrupt(intr_pin), receive_code, CHANGE);
 if ( eeConfigRead ( ) == false ) eeConfigWrite ( );
 }
void loop() 
{
  
   if(recv_code ==IR_ON)  // replace this code with the code that
        {       // have got from your remote
      Serial.println ("switch ON");
      eeConfigRead();
      led_change();
      recv_code = 0;
        }
   if( recv_code ==IR_OFF)  // replace this code with the code that
        {       // have got from your remote
          // red colour
      Serial.println ("switch OFF");
      R_I=B_I=G_I=0;
      led_change();
      recv_code = 0;
        }
    if(recv_code==IR_RED)  // replace this code with the code that
        {       // have got from your remote
          // red colour
      Serial.println ("switch RED");
      R_I = full_brightness;
      B_I = zero_brightness;
      G_I = zero_brightness;
      led_change();
      Mode = RED;
      eeConfigWrite();
      recv_code = 0;
        }
    if(recv_code == IR_GREEN) 
        {
      //green colour
      Serial.println ("switch GREEN");
      R_I = zero_brightness;
      B_I = zero_brightness;
      G_I = full_brightness;
      led_change();
      Mode = GREEN;
      eeConfigWrite();
      recv_code = 0;
        }  
    if(recv_code == IR_BLUE) 
        {
          //blue colour
      Serial.println ("switch BLUE");    
      R_I = zero_brightness;
      B_I = full_brightness;
      G_I = zero_brightness;
      led_change();
      Mode = BLUE;
      eeConfigWrite();
      recv_code = 0;
        }  
   if(recv_code == IR_YELL) 
        {
          //yellow colour
      Serial.println ("switch Yellow");    
      R_I = full_brightness;
      B_I = zero_brightness;
      G_I = full_brightness;
      led_change();
      Mode = YELL;
      eeConfigWrite();
      recv_code = 0;        
        } 
    if(recv_code == IR_ALL) 
        {
          //lightgreen colour
      Serial.println ("switch All");
      R_I = full_brightness;
      B_I = full_brightness;
      G_I = full_brightness;
      led_change();
      Mode = ALL;
      eeConfigWrite();
      recv_code = 0; 
          }   
    if(recv_code == IR_PINK)
         {
              //pink colour
      Serial.println ("switch Pink");    
      R_I = full_brightness;
      B_I = half_brightness;
      G_I = zero_brightness;
      led_change();
      Mode = PINK;
      eeConfigWrite();
      recv_code = 0;            
         }
     if(recv_code == IR_PLUS)
         {
      Serial.println ("switch PLUS");    
      if ( R_I > 0 && R_I < 235 ) R_I+=20;
      if ( B_I > 0 && B_I < 235 ) B_I+=20;
      if ( G_I > 0 && G_I < 235 ) G_I+=20;
      led_change();
      eeConfigWrite();
      recv_code = 0;             
         }
      if(recv_code == IR_MOINS)
         {
      Serial.println ("switch MOINS");    
      if ( R_I > 20 ) R_I-=20;
      if ( B_I > 20 ) B_I-=20;
      if ( G_I > 20 ) G_I-=20;
      led_change();
      eeConfigWrite();
      recv_code = 0;
         }         
    if(recv_code==6292) 
        {
           //skyblue colour
      analogWrite(RED,zero_brightness);
      analogWrite (GREEN, full_brightness);
      analogWrite(BLUE, full_brightness);
        }
   if(recv_code == IR_FLASH) 
        {
    Serial.println ("switch Pink");
    recv_code = 0;      
    rainbow_effect();
    }
      delay(500);
      irrecv.resume();          
    }      
void receive_code()
  {
       if(irrecv.decode(&results)) 
         {   
           if(recv_code != results.value)
           { 
            Serial.print("received code ");
            Serial.println(results.value); 
            recv_code = results.value; 
           }               
         }        
  }   
void rainbow_effect()
  {
  while(1)
    {
// red colour
  analogWrite(RED,full_brightness);
      analogWrite (GREEN, zero_brightness);
      analogWrite(BLUE, zero_brightness);
      delay(500);
      //green colour
      analogWrite(RED,zero_brightness);
      analogWrite (GREEN, full_brightness);
      analogWrite(BLUE, zero_brightness);
      delay(500);
  //blue colour
  analogWrite(RED,zero_brightness);
  analogWrite (GREEN, zero_brightness);
  analogWrite(BLUE, full_brightness);
  delay(500);
  //yellow colour
  analogWrite(RED,full_brightness);
  analogWrite (GREEN, full_brightness);
  analogWrite(BLUE, zero_brightness);
  delay(500);
  //lightgreen colour
  analogWrite(RED,half_brightness);
  analogWrite (GREEN, full_brightness);
  analogWrite(BLUE, zero_brightness);
  delay(500);
  //pink colour
  analogWrite(RED,full_brightness);
  analogWrite (GREEN, zero_brightness);
  analogWrite(BLUE, half_brightness);
  delay(500);
  //skyblue colour
  analogWrite(RED,zero_brightness);
  analogWrite (GREEN, full_brightness);
  analogWrite(BLUE, full_brightness);
  delay(500);
  //orange colour
  analogWrite(RED,full_brightness);
  analogWrite (GREEN, half_brightness);
  analogWrite(BLUE, zero_brightness);
  delay(500);
  //magenta colour  
  analogWrite(RED,full_brightness);
  analogWrite (GREEN, zero_brightness);
  analogWrite(BLUE, full_brightness);
  delay(500);
}
}

///////////////////////////////////////////////////////////////////////////////////////
// eeConfigRead                                                                      //
// Fonction de lecture de la configuration EEPROM                                    //
///////////////////////////////////////////////////////////////////////////////////////
bool eeConfigRead ( void ) {

  dataEeprom pvrConfig;
  EEPROM.get ( PVR_EEPROM_START, pvrConfig );
  if ( pvrConfig.magic != DATAEEPROM_MAGIC ) return false;
  else {
    noInterrupts ( );
    Mode          = pvrConfig.mode;
    R_I           = pvrConfig.R_I;
    B_I           = pvrConfig.B_I;
    G_I           = pvrConfig.G_I;
    interrupts ( );
    Serial.println("Reading RGB");
    Serial.println(R_I);
    Serial.println(G_I);
    Serial.println(B_I);
    return true;
  }
}

///////////////////////////////////////////////////////////////////////////////////////
// eeConfigWrite                                                                     //
// Fonction d'écriture de la configuration EEPROM                                    //
///////////////////////////////////////////////////////////////////////////////////////
void eeConfigWrite ( void ) {

  dataEeprom pvrConfig;
  pvrConfig.magic           = DATAEEPROM_MAGIC;
  pvrConfig.struct_version  = DATAEEPROM_VERSION;
  pvrConfig.mode            = Mode;
  pvrConfig.R_I             = R_I;
  pvrConfig.B_I             = B_I;  
  pvrConfig.G_I             = G_I; 
  EEPROM.put ( PVR_EEPROM_START, pvrConfig );
}

void led_change ( void ) {
      analogWrite(RED, R_I);
      analogWrite (GREEN, G_I);
      analogWrite(BLUE, B_I);
}
