#define LED_BUTTON_PIN 19
#define BUTTON_PIN 4

#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_8_BIT 8
#define LEDC_BASE_FREQ 5000
#include <EasyButton.h>
#include "Arduino.h"
#include "../webserver/config.h"
#include "../box/handleBox.h"
#include <LITTLEFS.h>

#define DOUBLE_CLICK_DURATION 300
EasyButton button(BUTTON_PIN);
uint32_t lastClickTime = 0;

int countToFactoryReset = 0;
void resetFactory()
{
    LITTLEFS.format();
    delay(1000);
    ESP.restart();
}
void onClick()
{
    // log_d(" running");
    // if (getValue("on_off_tgl") != "true")
    // {
    //     setValue("on_off_tgl", "true");
    //     onBox();
    // }
    // else
    // {
    randomMode();
    // }
}
void onPressed()
{
    log_d(" running");

    if (box.getReactMusic())
    {
        offReact();
    }
    else
    {
        onReact();
    }
}
void doubleClick()
{
    log_d(" running");
    lastClickTime = 0;
    if (getValue("timer_tgl", "true") == "true")
    {
        offTimer();
    }
    else
    {
        onTimer();
    }
}
void buttonHandle(void *pvParameters)
{
    int brightness = 0;       // how bright the LED is
    int fadeAmount = 10;      // how many points to fade the LED by
    int fadeAmountMusic = 20; // how many points to fade the LED by
    while (1)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
        if (digitalRead(BUTTON_PIN) == 0)
        {
            countToFactoryReset++;
            if (countToFactoryReset >= 200)
            {
                countToFactoryReset = 200;
                brightness = 0;
                for (size_t i = 0; i < 20; i++)
                {
                    ledcWrite(LEDC_CHANNEL_0, 0);
                    vTaskDelay(100 / portTICK_PERIOD_MS);
                    ledcWrite(LEDC_CHANNEL_0, 250);
                    vTaskDelay(100 / portTICK_PERIOD_MS);
                }
                resetFactory();
            }
        }
        button.read();

        if (lastClickTime != 0 && millis() - lastClickTime > DOUBLE_CLICK_DURATION)
        {
            lastClickTime = 0;
            onClick();
        }
        if (getValue("on_off_tgl") != "true")
        {
            ledcWrite(LEDC_CHANNEL_0, 0);
        }
        else
        {
            if (getValue("timer_tgl", "true") == "true")
            {
                ledcWrite(LEDC_CHANNEL_0, brightness);
                if (getValue("react_music", "true") == "true")
                {
                    brightness = brightness + fadeAmountMusic;
                    if (brightness <= 0 || brightness >= 240)
                    {
                        fadeAmountMusic = -fadeAmountMusic;
                    }
                }
                else
                {
                    brightness = brightness + fadeAmount;
                    if (brightness <= 0 || brightness >= 250)
                    {
                        fadeAmount = -fadeAmount;
                    }
                }
            }
            else
            {
                ledcWrite(LEDC_CHANNEL_0, 128);
            }
        }
    }
}
void setupButton()
{
    ledcSetup(LEDC_CHANNEL_0, LEDC_BASE_FREQ, LEDC_TIMER_8_BIT);
    ledcAttachPin(LED_BUTTON_PIN, LEDC_CHANNEL_0);
    button.begin();
    button.onPressed([]()
                     { lastClickTime = millis(); });
    button.onPressedFor(3000, onPressed);
    button.onSequence(2, DOUBLE_CLICK_DURATION, doubleClick);
    xTaskCreatePinnedToCore(
        buttonHandle,         /* Task function. */
        "buttonHandle",       /* name of task. */
        4096,                 /* Stack size of task */
        NULL,                 /* parameter of the task */
        configMAX_PRIORITIES, /* priority of the task */
        NULL,                 /* Task handle to keep track of created task */
        0);                   /* pin task to core 0 */
}