#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    // PB1 (LED) dauerhaft einschalten
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

    while (1) {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_2);  // PD2 (Relais) toggeln
        HAL_Delay(500);  // 500ms warten
    }
}

void SystemClock_Config(void) {
    // Wird von CubeMX generiert.
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();  // GPIOB aktivieren
    __HAL_RCC_GPIOD_CLK_ENABLE();  // GPIOD aktivieren

    // PB1 als Ausgang für LED konfigurieren
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // PD2 als Ausgang für Relais konfigurieren
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
