/*

This demo listens for the touch controller.

*/

#include <Arduino.h>
#include <Wire.h>

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

        auto t = touch.config();
        t.x_min = 0; t.x_max = 799;
        t.y_min = 0; t.y_max = 479;
        t.pin_int = -1; t.pin_rst = -1;
        t.bus_shared = false;
        t.i2c_port = 1;
        t.pin_sda = 19; t.pin_scl = 20;
        t.freq = 400000;
        t.i2c_addr = 0x5D;
        touch.config(t);
        panel.setTouch(&touch);
        setPanel(&panel);
    }

    private:
    lgfx::Bus_RGB bus;
    lgfx::Panel_RGB panel;
    lgfx::Touch_GT911 touch;
};

Panel screen;
char line[96];
size_t length = 0;
bool overflow = false;
bool touching = false;

void resetTouchIfPresent() {
    Wire.begin(19, 20);
    Wire.setTimeOut(30);
    Wire.beginTransmission(0x18);
    bool present = Wire.endTransmission() == 0;
    if (present) {
        auto readRegister = [](uint8_t reg) -> int {
            Wire.beginTransmission(0x18);
            Wire.write(reg);
            if (Wire.endTransmission(false) != 0 || Wire.requestFrom(0x18, 1) != 1) return -1;
            return Wire.read();
        };
        auto writeRegister = [](uint8_t reg, uint8_t value) {
            Wire.beginTransmission(0x18);
            Wire.write(reg);
            Wire.write(value);
            Wire.endTransmission();
        };
        int output = readRegister(1);
        int config = readRegister(3);
        if (output >= 0 && config >= 0) {
            writeRegister(1, output & ~3);
            writeRegister(3, config & ~3);
            delay(20);
            writeRegister(1, (output & ~3) | 1);
            delay(100);
            writeRegister(3, (config & ~3) | 2);
        }
    }
    Wire.end();
}

void setup() {
    Serial.begin(115200);
    
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    
    resetTouchIfPresent();
    screen.init();
    
    bool touchReady = screen.getPanel()->initTouch();
    Serial.printf("Touch controller: %s\n", touchReady ? "ready" : "not detected");
    screen.fillScreen(TFT_BLACK);
    screen.setTextColor(TFT_WHITE, TFT_BLACK);
    
    screen.setTextSize(4);
    screen.drawString("Hello!", 30, 30);
    
    screen.setTextSize(2);
    screen.drawString("Waiting for stuff. Touch the screen to send an event.", 30, 110);
    screen.drawString(touchReady ? "Touch controller ready" : "Touch controller not detected", 30, 230);
    
    Serial.println("Waiting");
}

void loop() {
    uint16_t x, y;
    bool pressed = screen.getTouch(&x, &y);
    
    if (pressed && (x >= 800 || y >= 480))
        pressed = false;
    
    if (pressed && !touching) {
        Serial.printf("touch: (%u, %u)\n", x, y);
        
        char message[48];
        snprintf(message, sizeof(message), "touch: %u, %u", x, y);
        
        screen.fillRect(30, 270, 400, 30, TFT_BLACK);
        screen.setTextSize(2);
        screen.drawString(message, 30, 270);
    }
    touching = pressed;

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
