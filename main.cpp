#include <Arduino.h>

const int PIN_RS = 7;
const int PIN_E = 8;
const int PIN_D4 = 9;
const int PIN_D5 = 10;
const int PIN_D6 = 11;
const int PIN_D7 = 12;

const int LCD_DELAY_MS = 5;

void lcdSend(bool isCommand, uint8_t data) {
    digitalWrite(PIN_RS, isCommand ? LOW : HIGH);
    delay(LCD_DELAY_MS);

    digitalWrite(PIN_D7, (data >> 7) & 1);
    digitalWrite(PIN_D6, (data >> 6) & 1);
    digitalWrite(PIN_D5, (data >> 5) & 1);
    digitalWrite(PIN_D4, (data >> 4) & 1);

    // Wnen writing to the display, data is transfered only
    // on the high to low transition of the E signal.
    digitalWrite(PIN_E, HIGH);
    delay(LCD_DELAY_MS);
    digitalWrite(PIN_E, LOW);

    digitalWrite(PIN_D7, (data >> 3) & 1);
    digitalWrite(PIN_D6, (data >> 2) & 1);
    digitalWrite(PIN_D5, (data >> 1) & 1);
    digitalWrite(PIN_D4, (data >> 0) & 1);

    digitalWrite(PIN_E, HIGH);
    delay(LCD_DELAY_MS);
    digitalWrite(PIN_E, LOW);
}

void lcdCommand(uint8_t cmd) {
    lcdSend(true, cmd);
}

void lcdChar(const char chr) {
    lcdSend(false, (uint8_t)chr);
}

void lcdString(const char* str) {
    while(*str != '\0') {
        lcdChar(*str);
        str++;
    }
}

void setup()
{
    pinMode(PIN_RS, OUTPUT);
    pinMode(PIN_E, OUTPUT);
    pinMode(PIN_D4, OUTPUT);
    pinMode(PIN_D5, OUTPUT);
    pinMode(PIN_D6, OUTPUT);
    pinMode(PIN_D7, OUTPUT);

    // 4-bit mode, 2 lines, 5x7 format
    lcdCommand(0b00110000); 
    // display & cursor home (keep this!)
    lcdCommand(0b00000010); 
    // display on, right shift, underline off, blink off
    lcdCommand(0b00001100); 
    // clear display (optional here)
    lcdCommand(0b00000001); 

    lcdCommand(0b10000000); // set address to 0x00
    lcdString("Using HD44780");
    lcdCommand(0b11000000); // set address to 0x40
    lcdString("LCD directly! :)");
}

void loop()
{
    /* do nothing */
    delay(100);
}
