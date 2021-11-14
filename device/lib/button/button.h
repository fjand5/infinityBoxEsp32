#define LED_BUTTON_PIN 19
#define BUTTON_PIN 18

#define LEDC_CHANNEL_0 0
#define LEDC_TIMER_8_BIT 8
#define LEDC_BASE_FREQ 5000
#include <EasyButton.h>
#include "Arduino.h"
#include "../webserver/config.h"
#include "../box/handleBox.h"
EasyButton button(BUTTON_PIN);
void buttonPressed()
{
    if (getValue("on_off_tgl") != "true")
    {
        setValue("on_off_tgl", "true");
        onBox();
    }
    else
    {

        nextMode();
        setValue("current_mode", String(box.getMode()));
    }
}
void onPressedForDuration()
{
    setValue("on_off_tgl", "false");
    offBox();
}
void onSequenceMatched()
{
    if (getValue("timer_tgl") == "true")
    {
        setValue("timer_tgl", "false");
        offTimer();
    }
    else
    {
        setValue("timer_tgl", "true");
        onTimer();
    }
}
void buttonHandle(void *pvParameters)
{

    int brightness = 0;  // how bright the LED is
    int fadeAmount = 10; // how many points to fade the LED by
    while (1)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
        button.read();
        if (getValue("on_off_tgl") != "true")
        {
            ledcWrite(LEDC_CHANNEL_0, 0);
        }
        else
        {
            if (getValue("timer_tgl") == "true")
            {
                ledcWrite(LEDC_CHANNEL_0, brightness);
                brightness = brightness + fadeAmount;
                if (brightness <= 0 || brightness >= 250)
                {
                    fadeAmount = -fadeAmount;
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
    button.onPressed(buttonPressed);
    button.onPressedFor(3000, onPressedForDuration);
    button.onSequence(2, 1000, onSequenceMatched);
    xTaskCreatePinnedToCore(
        buttonHandle,         /* Task function. */
        "buttonHandle",       /* name of task. */
        4096,                 /* Stack size of task */
        NULL,                 /* parameter of the task */
        configMAX_PRIORITIES, /* priority of the task */
        NULL,                 /* Task handle to keep track of created task */
        0);                   /* pin task to core 0 */
}