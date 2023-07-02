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

#define COL1 GPIO_NUM_4
#define COL2 GPIO_NUM_16
#define COL3 GPIO_NUM_17
#define COL4 GPIO_NUM_18

#define ROW1 GPIO_NUM_19
#define ROW2 GPIO_NUM_21
#define ROW3 GPIO_NUM_22
#define ROW4 GPIO_NUM_23

gpio_num_t cols[] = {COL1, COL2, COL3, COL4};
gpio_num_t rows[] = {ROW1, ROW2, ROW3, ROW4};

void setupPins()
{
    ESP_LOGI(TAG, "[A] Setup Pins");
    esp_err_t ret;

    for (int i = 0; i < 4; ++i)
    {
        ret = gpio_set_direction(rows[i], GPIO_MODE_OUTPUT);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "[A] gpio_set_direction Failed (%s)", esp_err_to_name(ret));
        }

        ret = gpio_set_level(rows[i], 0);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "[A] gpio_set_level Failed (%s)", esp_err_to_name(ret));
        }

        ret = gpio_set_direction(cols[i], GPIO_MODE_INPUT);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "[A] gpio_set_direction Failed (%s)", esp_err_to_name(ret));
        }

        ret = gpio_set_pull_mode(cols[i], GPIO_PULLDOWN_ONLY);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "[C] gpio_set_pull_mode Failed (%s)", esp_err_to_name(ret));
        }
    }
}

int scan(int row, int col)
{
    // set to high
    int ret = gpio_set_level(rows[row], 1);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "[A] gpio_set_level Failed (%s)", esp_err_to_name(ret));
    }

    // read button
    int state = gpio_get_level(cols[col]);

    // set to lov
    ret = gpio_set_level(rows[row], 0);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "[A] gpio_set_level Failed (%s)", esp_err_to_name(ret));
    }

    return state;
}

extern "C" void app_main(void)
{
    printf("Hello world!\n");
    setupPins();

    char keys[] = "123A"
                  "456B"
                  "789C"
                  "*0#D";

    while (1)
    {
        std::string s;
        for (int y = 0; y < 4; ++y)
        {
            for (int x = 0; x < 4; ++x)
            {
                int state = scan(y, x);
                if (state)
                {
                    s += keys[x + y * 4];
                }
                // printf("%.2x ", state);
            }
        }
        printf("keys: %s\n", s.c_str());

        vTaskDelay(150 / portTICK_PERIOD_MS);
    }
}