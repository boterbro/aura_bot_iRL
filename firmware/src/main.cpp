#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ESP32Servo.h>

#define SERVO_YAW_PIN   10  // Ось X
#define SERVO_PITCH_PIN 11  // Ось Y

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

Servo servoYaw;
Servo servoPitch;

const int EYE_W = 50;
const int EYE_H = 70;
const int EYE_R = 15;
const int BASE_LEFT_X = 50;
const int BASE_RIGHT_X = 140;
const int BASE_Y = 85;

void renderFrame(int offsetX, int offsetY) {
    spr.fillSprite(TFT_BLACK);

    int leftX = BASE_LEFT_X + offsetX;
    int rightX = BASE_RIGHT_X + offsetX;
    int eyeY = BASE_Y + offsetY;

    spr.fillRoundRect(leftX, eyeY, EYE_W, EYE_H, EYE_R, TFT_CYAN);
    spr.fillRoundRect(rightX, eyeY, EYE_W, EYE_H, EYE_R, TFT_CYAN);

    spr.pushSprite(0, 0);
}

void setup() {
    Serial.begin(115200);

    tft.init();
    tft.setRotation(0);
    spr.createSprite(240, 240);

    renderFrame(0, 0);

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    
    servoYaw.setPeriodHertz(50);
    servoPitch.setPeriodHertz(50);
    
    // Стандартные тайминги без захода за физический упор
    servoYaw.attach(SERVO_YAW_PIN, 500, 2500);
    servoPitch.attach(SERVO_PITCH_PIN, 500, 2500);

    servoYaw.write(90);
    servoPitch.write(90);
    delay(300);
}

void loop() {
    // Движение вперед (быстро и плавно, шаг 3 градуса)
    for (int posX = 20; posX <= 160; posX += 3) {
        int posY = map(posX, 20, 160, 30, 150);

        servoYaw.write(posX);
        servoPitch.write(posY);

        int eyeOffsetX = map(posX, 20, 160, -22, 22);
        int eyeOffsetY = map(posY, 30, 150, -18, 18);

        renderFrame(eyeOffsetX, eyeOffsetY);
        delay(8); // Оптимальная задержка для плавной динамики
    }

    // Движение назад
    for (int posX = 160; posX >= 20; posX -= 3) {
        int posY = map(posX, 20, 160, 30, 150);

        servoYaw.write(posX);
        servoPitch.write(posY);

        int eyeOffsetX = map(posX, 20, 160, -22, 22);
        int eyeOffsetY = map(posY, 30, 150, -18, 18);

        renderFrame(eyeOffsetX, eyeOffsetY);
        delay(8);
    }
}