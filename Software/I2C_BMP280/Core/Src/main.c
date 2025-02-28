/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Temperaturmessung mit BMP280 über I2C und Ausgabe via USB
  *
  * Dieser Test liest die Temperaturdaten vom BMP280-Sensor über I2C aus
  * und sendet die Messwerte über die USB-Schnittstelle an den PC.
  *
  * Aufbau:
  * Ein Computer muss per USB-C an das Board angeschlossen werden.
  * Der BMP280 muss richtig per I2C an das Board angeschlossen werden.
  * Der Computer hat eine Ausgabe über den richtigen COM-Port auf.
  *
  * Ablauf:
  * - Initialisiert den BMP280-Sensor.
  * - Liest die Kalibrierungsdaten des Sensors aus.
  * - Holt die Roh-Temperaturwerte und berechnet daraus die Temperatur in °C.
  * - Sendet die Temperaturwerte alle 100 ms über die USB-Schnittstelle.
  *
  * Verwendete Peripherien:
  * - I2C1 (zur Kommunikation mit dem BMP280)
  * - USB (Für die Ausgabe der Temperaturwerte)
  *
  *****************************************************************************/

#include "main.h"
#include "usb_device.h"

I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

#define BMP280_I2C_ADDRESS  0x76

uint16_t size;
uint8_t Data[256];

uint16_t dig_T1;
int16_t dig_T2, dig_T3;

uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

/**
 * @brief Initialisiert den BMP280-Sensor mit Standardkonfiguration.
 */
void BMP280_Init() {
    uint8_t settings[2];
    settings[0] = 0xF4;
    settings[1] = 0x27;
    HAL_I2C_Master_Transmit(&hi2c1, BMP280_I2C_ADDRESS << 1, settings, 2, HAL_MAX_DELAY);
}

/**
 * @brief Liest die Kalibrierungsdaten des BMP280 aus dem Speicher.
 */
void BMP280_ReadCalibration() {
    uint8_t calib[6];
    uint8_t reg = 0x88;
    HAL_I2C_Master_Transmit(&hi2c1, BMP280_I2C_ADDRESS << 1, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, BMP280_I2C_ADDRESS << 1, calib, 6, HAL_MAX_DELAY);
    dig_T1 = (calib[1] << 8) | calib[0];
    dig_T2 = (calib[3] << 8) | calib[2];
    dig_T3 = (calib[5] << 8) | calib[4];
}

/**
 * @brief Liest den Rohwert der Temperatur aus dem BMP280.
 * @return Roh-Temperaturwert aus den Registern 0xFA-0xFC
 */
int32_t BMP280_ReadRawTemp() {
    uint8_t reg = 0xFA;
    uint8_t data[3];
    int32_t temp_raw;
    HAL_I2C_Master_Transmit(&hi2c1, BMP280_I2C_ADDRESS << 1, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(&hi2c1, BMP280_I2C_ADDRESS << 1, data, 3, HAL_MAX_DELAY);
    temp_raw = ((int32_t)data[0] << 12) | ((int32_t)data[1] << 4) | ((data[2] >> 4) & 0x0F);
    return temp_raw;
}

/**
 * @brief Berechnet die Temperatur in °C aus dem Rohwert und Kalibrierungsdaten.
 * @param temp_raw: Rohwert der Temperatur
 * @return Temperatur in °C
 */
float BMP280_CalculateTemp(int32_t temp_raw) {
    int32_t var1, var2;
    float temperature;
    var1 = ((((temp_raw >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((temp_raw >> 4) - ((int32_t)dig_T1)) * ((temp_raw >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
    int32_t t_fine = var1 + var2;
    temperature = (t_fine * 5 + 128) >> 8;
    temperature /= 100;
    return temperature;
}

/**
 * @brief Hauptprogramm: Initialisierung und kontinuierliche Temperaturmessung.
 */
int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USB_DEVICE_Init();

    BMP280_Init();
    BMP280_ReadCalibration();

    while (1) {
        // Rohwert der Temperatur vom BMP280 auslesen
        int32_t temp_raw = BMP280_ReadRawTemp();

        // Temperaturwert mit den Kalibrierungsdaten berechnen
        float temp = BMP280_CalculateTemp(temp_raw);

        // Temperatur in eine Ganzzahl umwandeln (nur den ganzzahligen Anteil verwenden)
        int temp_int = (int)temp;

        // Temperaturwert als Zeichenkette formatieren und in das Datenpuffer-Array speichern
        size = sprintf((char *)Data, "Temperature: %d °C\r\n", temp_int);

        // Den formatierten Temperaturwert über USB CDC an den PC senden
        CDC_Transmit_FS(Data, size);

        // Kurze Pause, um die Abtastrate auf 10 Messungen pro Sekunde zu begrenzen
        HAL_Delay(100);
    }

}

/**
  * AUTO GENERATED CODE
  */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
    Error_Handler();
  }
}

static void MX_I2C1_Init(void) {
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void Error_Handler(void) {
  __disable_irq();
  while (1) {}
}
