/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Testprogramm zur Steuerung von GPIO-Pins auf dem ModExpES
  *
  * Dieses Programm testet die Funktionalität der digitalen GPIO-Ausgänge.
  * Die Pins PA8, PA9 und PA10 sowie PC0 bis PC4 werden als digitale Ausgänge konfiguriert.
  * Das Programm setzt alle Pins zunächst auf LOW und schaltet sie anschließend nacheinander auf HIGH.
  *
  * Aufbau:
  * - Schließe GPIO1 bis 8 an einem Ausgabegerät der Wahl an.
  * - Für diesen Test wurde das Modul H-Brücke V1.0 von der Hochschule Bonn-Rhein-Sieg benutzt.
  *
  * Ablauf:
  * - Alle GPIO-Pins werden initial auf LOW gesetzt.
  * - Danach werden die Pins PA8, PA9 und PA10 jeweils nacheinander mit einer kurzen Verzögerung auf HIGH gesetzt.
  * - Anschließend werden die Pins PC0 bis PC4 in gleicher Weise aktiviert.
  * - Der Vorgang wird kontinuierlich in einer Endlosschleife wiederholt.
  *
  * Verwendete Peripherien:
  * - GPIO (PA8, PA9, PA10, PC0, PC1, PC2, PC3, PC4)
  *
  */

#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

const uint16_t gpio_pins[] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10}; // GPIO1-3 (PA)
GPIO_TypeDef* gpio_ports[] = {GPIOA, GPIOA, GPIOA};

const uint16_t gpio_pins_pc[] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4}; // GPIO4-8 (PC)
GPIO_TypeDef* gpio_ports_pc[] = {GPIOC, GPIOC, GPIOC, GPIOC, GPIOC};

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    while (1) {
        // Alle GPIOs auf GND setzen
        for (int i = 0; i < 3; i++) {
            HAL_GPIO_WritePin(gpio_ports[i], gpio_pins[i], GPIO_PIN_RESET);
        }
        for (int i = 0; i < 5; i++) {
            HAL_GPIO_WritePin(gpio_ports_pc[i], gpio_pins_pc[i], GPIO_PIN_RESET);
        }
        HAL_Delay(1000);  // 1 Sekunde warten

        // GPIOs nacheinander einschalten
        for (int i = 0; i < 3; i++) {
            HAL_GPIO_WritePin(gpio_ports[i], gpio_pins[i], GPIO_PIN_SET);  // Einschalten
            HAL_Delay(100);  // Verzögerung
        }
        for (int i = 0; i < 5; i++) {
            HAL_GPIO_WritePin(gpio_ports_pc[i], gpio_pins_pc[i], GPIO_PIN_SET);  // Einschalten
            HAL_Delay(100);  // Verzögerung
        }
    }
}

void SystemClock_Config(void) {
    // Wird von CubeMX generiert
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // GPIO1 - GPIO3 (PA8, PA9, PA10)
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // GPIO4 - GPIO8 (PC0, PC1, PC2, PC3, PC4)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
