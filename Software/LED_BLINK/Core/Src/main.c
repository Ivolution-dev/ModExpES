/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Testprogramm zur Steuerung eines Relais und einer LED
  *
  * Dieser Test steuert einen digitalen Ausgang für ein Relais sowie eine LED.
  * Der Pin PD2 wird dauerhaft auf HIGH gesetzt, um das Relais einzuschalten.
  * Der Pin PB1 wird periodisch getoggelt, um die On-Board LED blinken zu lassen.
  *
  * Aufbau:
  * Nicht benötigt.
  *
  * Ablauf:
  * - Das Relais wird dauerhaft aktiviert.
  * - Die LED wird mit einer Frequenz von 1 Hz ein- und ausgeschaltet.
  *
  * Verwendete Peripherien:
  * - GPIO (PB1 für LED, PD2 für Relais)
  *
  *****************************************************************************/

#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    // PD2 (Relais) dauerhaft einschalten
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);

    while (1) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);  // PB1 (LED) toggeln
        HAL_Delay(500);  // 500ms warten
    }
}

/**
  * AUTO GENERATED CODE
  */
void SystemClock_Config(void) {
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
