//#include <Adafruit_GFX.h> 
//#include <Adafruit_ST7735.h> 
#include <SPI.h>
#include <MFRC522.h>

/*
// TFT SCREEN
#define TFT_CS 10 //CHANGE
#define TFT_RST 0
#define TFT_DC 8//CHANGE
*/

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

/*
#define TFT_SCLK 6  // set these to be whatever pins you like!
#define TFT_MOSI 7   // set these to be whatever pins you like!
tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
*/

void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    SPI.begin();            // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    Serial.println("Scan PICC to see UID and type...");

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
    
    if (mfrc522.uid.uidByte[0] == 0xA4 && 
       mfrc522.uid.uidByte[1] == 0xB8 &&
       mfrc522.uid.uidByte[2] == 0xB8 &&
       mfrc522.uid.uidByte[3] == 0x96) {
          Serial.println("Hi Nate");

    }
}
