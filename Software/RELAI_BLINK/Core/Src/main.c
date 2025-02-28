/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Steuerung eines Relais und einer LED
  *
  * Dieser Test testet das Relai. Die On-Board LED wird eingschaltet
  * und das Relai an PD2 wird alle 500ms umgeschaltet.
  *
  * Aufbau:
  * Nicht benötigt.
  *
  * Ablauf:
  * - PB1 bleibt aktiv, wodurch die LED immer eingeschaltet bleibt.
  * - PD2 wird periodisch alle 500 ms getoggelt, wodurch das Relais blinkt.
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

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

    while (1) {
        // Wechselt den Zustand des Relais
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);

        // Verzögert die Ausführung für 500 ms (HAL_Delay in Millisekunden)
        HAL_Delay(500);
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
