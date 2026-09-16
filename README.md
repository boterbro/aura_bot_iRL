# 🤖 Aura Bot — Autonomous Modular AI Robot (v1.1.0)

![Platform](https://img.shields.io/badge/Platform-ESP32--S3-blue)
![Framework](https://img.shields.io/badge/Framework-PlatformIO-orange)
![Display](https://img.shields.io/badge/Display-ST7789%20IPS-green)
![Camera](https://img.shields.io/badge/Camera-OV5640-purple)
![Status](https://img.shields.io/badge/Status-v1.1.0%20Stable-brightgreen)

Проект локального автономного AI-робота с выразительной спрайтовой анимацией глаз на IPS-дисплее и кинематической головой (2-DOF Pan/Tilt), оснащенной камерой OV5640 на длинном шлейфе для осмотра пространства.

---

## 📌 Аппаратная Схема (Hardware Setup)

| Компонент | Модель / Детали | Пин ESP32-S3 | Примечания |
| :--- | :--- | :--- | :--- |
| **MCU** | ESP32-S3-N16R8 | Native USB OTG | 16MB Flash, 8MB PSRAM |
| **Display** | GMT130 IPS 240x240 (ST7789) | SCK: 19, SDA: 20, RES: 21, DC: 47, BLK: 38 | Закреплен на сервах (CS=-1) |
| **Camera** | OV5640 (Длинный шлейф FPC) | Параллельная шина DVP | Закреплена соосно экрану |
| **Servo X (Yaw)** | SG90 / MG90S | GPIO 10 (Timer 0) | Питание от 5V шины ESP32 |
| **Servo Y (Pitch)**| SG90 / MG90S | GPIO 11 (Timer 1) | Питание от 5V шины ESP32 |

---

## 🎭 Система Именованных Эмоций (Sprite Emotion Engine)

В автономном режиме без ПК выводятся базовые круглые глаза (`EMOTION_IDLE`). При подключении ИИ-агента эмоции переключаются по именам:
- `EMOTION_IDLE`
- `EMOTION_HAPPY`
- `EMOTION_SAD`
- `EMOTION_SURPRISED`
- `EMOTION_ANGRY`
- `EMOTION_THINKING`

---

## 🛠 Ключевые Настройки и Решения

1. **Двойная буферизация (TFT_eSprite):**  
   Отрисовка кадра происходит в скрытом спрайте `240x240` и выводится за один такт через `spr.pushSprite(0, 0)`, устраняя мерцание.
2. **Стабилизация SPI без пина CS:**  
   Частота SPI ограничена `10 МГц` (`-DSPI_FREQUENCY=10000000`), используется порт `HSPI` (`-DUSE_HSPI_PORT=1`).
3. **Безопасные Углы:**  
   Сервоприводы ограничены диапазоном `20°...160°`, задержка шага `8 мс`.

---

## 🚀 Команды для сборки и загрузки

```bash
# Прошивка через PlatformIO CLI
pio run --target upload