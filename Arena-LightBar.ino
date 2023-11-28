/// Modified from FastLEDs example ColorPalette.ino

//Move the 'FastLED' folder to your 'Arduino/libraries' folder
#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    30
//255 max bright
#define BRIGHTNESS  127
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define YELLOW_LED_WIDTH (3)

#define UPDATES_PER_SECOND 30

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

static uint8_t startIndex = NUM_LEDS/2;

void incrementStartIndex(){
    startIndex++;
    startIndex = (startIndex>NUM_LEDS)?NUM_LEDS-1:startIndex;
  
}
void decrementStartIndex(){  
    startIndex--;
    startIndex = (startIndex<0)?0:startIndex;
}

void ISR_blue_button_pressed(void) 
{
    incrementStartIndex();
    delay(50);
}

void ISR_red_button_pressed(void) 
{
    decrementStartIndex();
    delay(50);
}

void loop()
{
    
  for(int i = 0; i < startIndex; i++) { 
     leds[i] = CRGB::Blue;
  } 
  
  for(int i = 0; i < YELLOW_LED_WIDTH; i++){
    leds[startIndex+i] = CRGB::Yellow;
  }  
  
  for(int i = startIndex+YELLOW_LED_WIDTH; i < NUM_LEDS; i++) { 
    leds[i] = CRGB::Red;
  } 
  FastLED.show(); 
  
  if(digitalRead(JUDGE0_BLUE_BUTTON) == LOW){
    incrementStartIndex();
  }
  if(digitalRead(JUDGE0_RED_BUTTON) == LOW){
    decrementStartIndex();
  }

  FastLED.delay(1000 / UPDATES_PER_SECOND);
    
}
    
