/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Steuerung eines MCP4922 DAC und eines ADCs zur Erzeugung von PWM-Signalen
  *
  * Dieser Test steuert einen MCP4922 Digital-Analog-Wandler (DAC) über SPI
  * und liest kontinuierlich den Wert eines ADCs aus, welcher mit dem DAC verbunden ist.
  * Der ADC-Wert wird verwendet, um die PWM-Ausgangswerte auf den Pins PWM1 und der On-Board LED zu
  * steuern, basierend auf dem ADC-Eingang. An PWM1 kann ein Oszilloskop angeschlossen werden, um das
  * Signal zu visualisieren. Die ADC-Werte werden kontinuierlich
  * überwacht, um den minimalen und maximalen Wert zu ermitteln und den PWM-Ausgang
  * entsprechend zu skalieren.
  *
  * Aufbau:
  * Der MCP4922 DAC wird über die SPI-Schnittstelle an das ModExpES angeschlossen. Der Ausgang des DAC, welcher
  * die analoge Spannung erzeugt, wird direkt mit dem ADC4 verbunden. So wird die vom DAC erzeugte Spannung vom
  * ADC4 gemessen. Um das Signal visuell zu überprüfen, kann ein Oszilloskop an den PWM1-Ausgang, sowie
  * den ADC4-Eingang angeschlossen werden.
  *
  * Ablauf:
  * - Der DAC wird in einer Schleife mit Werten zwischen 0 und 4095 beschrieben.
  * - Der ADC wird gestartet und die Werte werden gelesen.
  * - Der minimalste und maximalste ADC-Wert werden ermittelt, um die PWM-Ausgangswerte
  *   basierend auf dem aktuellen ADC-Wert zu skalieren.
  * - Die PWM-Werte werden über die On-Board LED und PWM1 ausgegeben.
  *
  * Verwendete Peripherien:
  * - SPI (zur Kommunikation mit dem MCP4922 DAC)
  * - ADC (zum Messen von Eingabewerten)
  * - Timer (TIM3 für PWM-Ausgänge)
  *
  *****************************************************************************/

#include "main.h"

#define MCP4922_CS_LOW()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)
#define MCP4922_CS_HIGH() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)

ADC_HandleTypeDef hadc1;

SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim3;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI3_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);

/**
  * @brief  Schreibt einen Wert an den MCP4922 DAC.
  * @param  channel: Der Kanal des MCP4922 (0 oder 1)
  * @param  value: Der Wert, der an den DAC gesendet werden soll (0 bis 4095)
  *
  * Diese Funktion formatiert die Daten gemäß dem MCP4922-Protokoll und
  * sendet den Wert über SPI an den DAC. Der Chip Select wird vor und nach
  * der Übertragung gesteuert.
  */
void MCP4922_Write(uint8_t channel, uint16_t value) {
    uint16_t data = 0;

    // Der Wert wird auf die unteren 12 Bits maskiert (0 bis 4095)
    value &= 0x0FFF;

    // Die Daten werden mit Kanal und Steuerbits formatiert
    data = (channel << 15) | (0x3 << 12) | value;

    // Chip Select wird auf LOW gesetzt, um die Kommunikation zu starten
    MCP4922_CS_LOW();

    // Übertragung der Daten an den MCP4922 via SPI
    HAL_SPI_Transmit(&hspi3, (uint8_t*)&data, 1, HAL_MAX_DELAY);

    // Chip Select wird auf HIGH gesetzt, um die Kommunikation zu beenden
    MCP4922_CS_HIGH();
}


int main(void) {
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_SPI3_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();

  // Variablen zur Speicherung der ADC-Werte und zur Berechnung von Min/Max
  uint16_t adc_value = 0;
  uint16_t adc_min_value = 4095;  // Maximale mögliche ADC-Wert
  uint16_t adc_max_value = 0;     // Minimale mögliche ADC-Wert

  // Starten der PWM-Ausgänge (TIM3 Channel 1 und Channel 4)
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

  while (1) {
      // Schleife zum Schreiben von Werten an den MCP4922 DAC von 0 bis 4095
      for (uint16_t value = 0; value <= 4095; value++) {
          // DAC wird mit dem aktuellen Wert beschickt
          MCP4922_Write(1, value);

          // Starten der ADC-Konvertierung
          HAL_ADC_Start(&hadc1);

          // Warten auf den Abschluss der Konvertierung und Auslesen des ADC-Werts
          if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
              adc_value = HAL_ADC_GetValue(&hadc1);
              float scaled_value = adc_value * (2.7f / 3.3f); // Skaliert den Wert auf 0-2.7V
              adc_value = scaled_value;
          }

          // Beenden der ADC-Konvertierung
          HAL_ADC_Stop(&hadc1);

          // Aktualisieren des minimalen und maximalen ADC-Werts
          if (adc_min_value > adc_value) {
              adc_min_value = adc_value;
          }
          if (adc_max_value < adc_value) {
              adc_max_value = adc_value;
          }

          // Berechnung des skalieren PWM-Werts basierend auf den ADC-Werten
          if (adc_max_value > adc_min_value) {
              // Skaliere den ADC-Wert auf den Bereich 0-4095 für die PWM
              uint16_t pwm_value = (adc_value - adc_min_value) * 4095 / (adc_max_value - adc_min_value);

              // Setze die PWM-Werte für die beiden Kanäle
              TIM3->CCR4 = pwm_value;
              TIM3->CCR1 = pwm_value;
          } else {
              // Wenn min und max gleich sind, setze PWM auf 0
              TIM3->CCR4 = 0;
              TIM3->CCR1 = 0;
          }

          // Kurze Verzögerung von 1 ms
          HAL_Delay(1);
      }
  }
}

/**
  * AUTO GENERATED CODE
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_ADC1_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_SPI3_Init(void)
{
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_TIM3_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 4095;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim3);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
