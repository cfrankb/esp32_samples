/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "sdkconfig.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_freertos_hooks.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include <stdio.h>
#include <string>

static const char *TAG = "main";

#define LEFT GPIO_NUM_4
#define RIGHT GPIO_NUM_5
#define UP GPIO_NUM_18
#define DOWN GPIO_NUM_19

gpio_num_t sanwaPins[] = {LEFT, RIGHT, UP, DOWN};

void setupPins()
{
    ESP_LOGI(TAG, "[A] Setup Pins");
    esp_err_t ret;

    for (int i = 0; i < 4; ++i)
    {
        ret = gpio_set_direction(sanwaPins[i], GPIO_MODE_INPUT);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "[A] gpio_set_direction Failed (%s)", esp_err_to_name(ret));
        }
        ret = gpio_set_pull_mode(sanwaPins[i], GPIO_PULLUP_ONLY);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "[C] gpio_set_pull_mode Failed (%s)", esp_err_to_name(ret));
        }
    }
}

int scan(int dir)
{
    // read button
    int state = gpio_get_level(sanwaPins[dir]);
    return state;
}

extern "C" void app_main(void)
{
    printf("Hello world!\n");
    setupPins();

    const char *aims[] = {"LEFT",
                          "RIGHT",
                          "UP",
                          "DOWN"};

    while (1)
    {
        std::string s;
        for (int x = 0; x < 4; ++x)
        {
            int state = scan(x);
            printf("%.2x ", state);
            if (state == 0)
            {
                s += aims[x] + std::string(" ");
            }
        }
        printf("%s \n", s.c_str());

        vTaskDelay(150 / portTICK_PERIOD_MS);
    }
}