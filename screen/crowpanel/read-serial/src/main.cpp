/*

This demo reads strings sent through serial and prints it to the screen.

stty -F /dev/ttyUSB0 115200 raw -echo
printf 'Hello from Linux!\n' > /dev/ttyUSB0

Above works on both my desktop & the dev board itself.

*/

#include <Arduino.h>

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

class Panel : public lgfx::LGFX_Device {
    public:
    Panel() {
        auto b = bus.config();
        b.panel = &panel;
        b.pin_d0 = 15; b.pin_d1 = 7; b.pin_d2 = 6; b.pin_d3 = 5; b.pin_d4 = 4;
        b.pin_d5 = 9; b.pin_d6 = 46; b.pin_d7 = 3; b.pin_d8 = 8; b.pin_d9 = 16; b.pin_d10 = 1;
        b.pin_d11 = 14; b.pin_d12 = 21; b.pin_d13 = 47; b.pin_d14 = 48; b.pin_d15 = 45;
        b.pin_henable = 41; b.pin_vsync = 40; b.pin_hsync = 39; b.pin_pclk = 0;
        b.freq_write = 15000000;
        b.hsync_polarity = 0; b.hsync_front_porch = 40; b.hsync_pulse_width = 48; b.hsync_back_porch = 40;
        b.vsync_polarity = 0; b.vsync_front_porch = 1; b.vsync_pulse_width = 31; b.vsync_back_porch = 13;
        b.pclk_active_neg = 1; b.de_idle_high = 0; b.pclk_idle_high = 0;
        bus.config(b);
        
        auto p = panel.config();
        p.memory_width = p.panel_width = 800;
        p.memory_height = p.panel_height = 480;
        p.offset_x = p.offset_y = 0;
        panel.config(p);
        panel.setBus(&bus);
        setPanel(&panel);
    }

    private:
    lgfx::Bus_RGB bus;
    lgfx::Panel_RGB panel;
};

Panel screen;
char line[96];
size_t length = 0;
bool overflow = false;

void setup() {
    Serial.begin(115200);
    
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    
    screen.init();
    screen.fillScreen(TFT_BLACK);
    screen.setTextColor(TFT_WHITE, TFT_BLACK);
    
    screen.setTextSize(4);
    screen.drawString("Hello!", 30, 30);
    
    screen.setTextSize(2);
    screen.drawString("Waiting for stuff.", 30, 110);
    
    Serial.println("Waiting");
}

void loop() {
    while (Serial.available()) {
        char c = Serial.read();
        if (c == '\r') continue;
        if (c == '\n') {
            if (overflow) {
                Serial.println("ERR line too long");
            } else {
                line[length] = '\0';
                screen.fillRect(30, 155, 740, 40, TFT_BLACK);
                screen.setTextSize(2);
                screen.drawString(line, 30, 155);
                Serial.print("OK ");
                Serial.println(line);
            }
            length = 0;
            overflow = false;
        } else if (length < sizeof(line) - 1 && !overflow) {
            line[length++] = c;
        } else {
            overflow = true;
        }
    }
}
