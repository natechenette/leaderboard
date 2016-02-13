#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <MFRC522.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define sclk 4  // SainSmart: SCL
#define mosi 5  // SainSmart: SDA
#define cs   6  // SainSmart: CS
#define dc   7  // SainSmart: RS/DC
#define rst  8  // SainSmart: RES

Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

float p = 3.1415926;
unsigned long swipedTime;
int tag1 = 0;
int tag2 = 0;
int swipeTimeOut = 10000; //how much time between both cards

void setup(void) {
  Serial.begin(9600);
  SPI.begin();
  Serial.print("Starting cornhole leaderboard...");
  mfrc522.PCD_Init(); // Init MFRC522 card
  Serial.println("Scan PICC to see UID and type...");
  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  // Use this initializer (uncomment) if you're using a 1.44" TFT
  //tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab

  Serial.println("Initialized");

  uint16_t time = millis();
  tft.fillScreen(ST7735_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);

  // large block of text
  tft.fillScreen(ST7735_BLACK);
}

void loop() {

  // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }
    int test = 0; 
    int test2 = 0;  

      if (mfrc522.uid.uidByte[0] == 0xA4 && 
         mfrc522.uid.uidByte[1] == 0xB8 &&
         mfrc522.uid.uidByte[2] == 0xB8 &&
         mfrc522.uid.uidByte[3] == 0x96) {
            int test = 200;
            boolean nate = true;
            Serial.println(test); 
            Serial.println("Nate has checked in to the game.");
            tft.fillScreen(ST7735_BLUE);
            tft.setTextSize(2);
            tft.setCursor(0, 0);
            tft.setTextColor(ST7735_YELLOW);
            tft.print("Nate ");
            tft.setTextColor(ST7735_WHITE);
            tft.println("has checked in ");
            tft.setTextSize(2);
            tft.println("to the game.");
            delay(2000);
            tft.fillScreen(ST7735_BLACK);

             
            if (tag2 == 1 && millis() - swipedTime < swipeTimeOut ){
                   Serial.println("Game started");
            }

            tag1 = 1;
            swipedTime = millis();
      }
  
      if (mfrc522.uid.uidByte[0] == 0x03 && 
         mfrc522.uid.uidByte[1] == 0xFD &&
         mfrc522.uid.uidByte[2] == 0xBC &&
         mfrc522.uid.uidByte[3] == 0x02) {
            int test2 = 300;
            boolean ted = true;
            Serial.println(test2);
            Serial.println("Ted has checked in to the game.");
            tft.fillScreen(ST7735_RED);
            tft.setTextSize(2);
            tft.setCursor(0, 0);
            tft.setTextColor(ST7735_CYAN);
            tft.print("Ted ");
            tft.setTextColor(ST7735_WHITE);
            tft.println("has checked in ");
            tft.setTextSize(2);
            tft.println("to the game.");
            delay(2000);
            tft.fillScreen(ST7735_BLACK);

            if (tag1 == 1 && millis() - swipedTime < swipeTimeOut ){
                   Serial.println("Game started 2");
                   delay(500);
                   
            }
            tag2 = 1;
            swipedTime = millis(); 
  
      }

}






