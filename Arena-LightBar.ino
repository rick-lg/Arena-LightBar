/// Modified from FastLEDs example ColorPalette.ino

//Move teh 'FastLED' folder to your 'Arduino/libraries' folder
#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    50
//255 max bright
#define BRIGHTNESS  127
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

//#define UPDATES_PER_SECOND 100
#define UPDATES_PER_SECOND 200

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;



#define JUDGE0_BLUE_BUTTON (2)
#define JUDGE0_RED_BUTTON (3)


void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);


    pinMode(JUDGE0_BLUE_BUTTON, INPUT_PULLUP);
    pinMode(JUDGE0_RED_BUTTON, INPUT_PULLUP);


    Serial.println("Here is the start");
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    attachInterrupt(digitalPinToInterrupt(JUDGE0_BLUE_BUTTON), ISR_blue_button_pressed, FALLING);
    attachInterrupt(digitalPinToInterrupt(JUDGE0_RED_BUTTON), ISR_red_button_pressed, FALLING);

}

static uint8_t startIndex = 255/3;

void ISR_blue_button_pressed(void) 
{
    startIndex++;
}

void ISR_red_button_pressed(void) 
{
    startIndex--;
}


bool ping_pong = true;
void loop()
{
  
    
    
    Serial.println("Here is the loop");
   // ChangePalettePeriodically();

    AreanaLEDs(255, 255);
    
    /*if(ping_pong){
      startIndex = startIndex + 1; 
      if(startIndex > 127){
        ping_pong = false;
      }
    }else{
      startIndex--;
      if(startIndex == 30){
        ping_pong = true;
      }
    }*/
    FillLEDsFromPaletteColors( startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}

//When a button is pressed, register it here
/*
#define NUMBER_OF_JUDGES (3)
uint8_t blue[NUMBER_OF_JUDGES];
uint8_t red [NUMBER_OF_JUDGES];
struct JUDGE_BUTTON{
  int pin;
  int mask;
  int state;
  int count;
}

JUDGE_BUTTON judge_blue[NUMBER_OF_JUDGES];
JUDGE_BUTTON judge_red [NUMBER_OF_JUDGES];

void JudgeButton_Init(){
  for(int i = 0; i < NUMBER_OF_JUDGES; i++){
    judge_blue[i];
    judge_red[i];
  }
}*/

void ButtonISR(){

  
}

void AreanaLEDs(int red, int blue){
 #define SPREAD_COUNT (16)
    
    currentBlending = NOBLEND;
    fill_solid( currentPalette, SPREAD_COUNT, CRGB::Blue);
    // and set every fourth one to white.
    for(int i = 0; i < SPREAD_COUNT/2; i++){      
        currentPalette[i] = CRGB::Red;
    }
        currentPalette[SPREAD_COUNT/2] = CRGB::Yellow;
}


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = BRIGHTNESS;
    
    for( int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}
