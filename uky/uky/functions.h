
extern Adafruit_ILI9341 tft;

void printCenteredString(const String &buf, int x, int y) {
    int16_t x1, y1;
    uint16_t w, h;
    tft.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    tft.setCursor(x - w / 2, y);
    tft.setTextColor(PRIMARY);
    tft.print(buf);
}


void clear() {
    tft.fillScreen(BLACK);
}



