/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <math.h>

#define OUTPUT_PIN_A0 (*(volatile uint32_t *)0x42210180)
#define OUTPUT_PIN_A1 (*(volatile uint32_t *)0x42210184)
#define OUTPUT_PIN_A2 (*(volatile uint32_t *)0x42210188)
#define OUTPUT_PIN_A3 (*(volatile uint32_t *)0x4221018C)
#define OUTPUT_PIN_A4 (*(volatile uint32_t *)0x42210190)
#define OUTPUT_PIN_A5 (*(volatile uint32_t *)0x42210194)
#define OUTPUT_PIN_A6 (*(volatile uint32_t *)0x42210198)
#define OUTPUT_PIN_A7 (*(volatile uint32_t *)0x4221019C)
#define OUTPUT_PIN_A8 (*(volatile uint32_t *)0x422101A0)
#define OUTPUT_PIN_A9 (*(volatile uint32_t *)0x422101A4)
#define OUTPUT_PIN_A10 (*(volatile uint32_t *)0x422101A8)
#define OUTPUT_PIN_A11 (*(volatile uint32_t *)0x422101AC)
#define OUTPUT_PIN_A12 (*(volatile uint32_t *)0x422101B0)
#define OUTPUT_PIN_A13 (*(volatile uint32_t *)0x422101B4)
#define OUTPUT_PIN_A14 (*(volatile uint32_t *)0x422101B8)
#define OUTPUT_PIN_A15 (*(volatile uint32_t *)0x422101BC)

#define OUTPUT_PIN_B0 (*(volatile uint32_t *)0x42218180)
#define OUTPUT_PIN_B1 (*(volatile uint32_t *)0x42218184)
#define OUTPUT_PIN_B2 (*(volatile uint32_t *)0x42218188)
#define OUTPUT_PIN_B3 (*(volatile uint32_t *)0x4221818C)
#define OUTPUT_PIN_B4 (*(volatile uint32_t *)0x42218190)
#define OUTPUT_PIN_B5 (*(volatile uint32_t *)0x42218194)
#define OUTPUT_PIN_B6 (*(volatile uint32_t *)0x42218198)
#define OUTPUT_PIN_B7 (*(volatile uint32_t *)0x4221819C)
#define OUTPUT_PIN_B8 (*(volatile uint32_t *)0x422181A0)
#define OUTPUT_PIN_B9 (*(volatile uint32_t *)0x422181A4)
#define OUTPUT_PIN_B10 (*(volatile uint32_t *)0x422181A8)
#define OUTPUT_PIN_B11 (*(volatile uint32_t *)0x422181AC)
#define OUTPUT_PIN_B12 (*(volatile uint32_t *)0x422181B0)
#define OUTPUT_PIN_B13 (*(volatile uint32_t *)0x422181B4)
#define OUTPUT_PIN_B14 (*(volatile uint32_t *)0x422181B8)
#define OUTPUT_PIN_B15 (*(volatile uint32_t *)0x422181BC)

#define OUTPUT_PIN_C0 (*(volatile uint32_t *)0x42220180)
#define OUTPUT_PIN_C1 (*(volatile uint32_t *)0x42220184)
#define OUTPUT_PIN_C2 (*(volatile uint32_t *)0x42220188)
#define OUTPUT_PIN_C3 (*(volatile uint32_t *)0x4222018C)
#define OUTPUT_PIN_C4 (*(volatile uint32_t *)0x42220190)
#define OUTPUT_PIN_C5 (*(volatile uint32_t *)0x42220194)
#define OUTPUT_PIN_C6 (*(volatile uint32_t *)0x42220198)
#define OUTPUT_PIN_C7 (*(volatile uint32_t *)0x4222019C)
#define OUTPUT_PIN_C8 (*(volatile uint32_t *)0x422201A0)
#define OUTPUT_PIN_C9 (*(volatile uint32_t *)0x422201A4)
#define OUTPUT_PIN_C10 (*(volatile uint32_t *)0x422201A8)
#define OUTPUT_PIN_C11 (*(volatile uint32_t *)0x422201AC)
#define OUTPUT_PIN_C12 (*(volatile uint32_t *)0x422201B0)
#define OUTPUT_PIN_C13 (*(volatile uint32_t *)0x422201B4)
#define OUTPUT_PIN_C14 (*(volatile uint32_t *)0x422201B8)
#define OUTPUT_PIN_C15 (*(volatile uint32_t *)0x422201BC)

#define INPUT_PIN_A0 (*(volatile uint32_t *)0x42210100)
#define INPUT_PIN_A1 (*(volatile uint32_t *)0x42210104)
#define INPUT_PIN_A2 (*(volatile uint32_t *)0x42210108)
#define INPUT_PIN_A3 (*(volatile uint32_t *)0x4221010C)
#define INPUT_PIN_A4 (*(volatile uint32_t *)0x42210110)
#define INPUT_PIN_A5 (*(volatile uint32_t *)0x42210114)
#define INPUT_PIN_A6 (*(volatile uint32_t *)0x42210118)
#define INPUT_PIN_A7 (*(volatile uint32_t *)0x4221011C)
#define INPUT_PIN_A8 (*(volatile uint32_t *)0x42210120)
#define INPUT_PIN_A9 (*(volatile uint32_t *)0x42210124)
#define INPUT_PIN_A10 (*(volatile uint32_t *)0x42210128)
#define INPUT_PIN_A11 (*(volatile uint32_t *)0x4221012C)
#define INPUT_PIN_A12 (*(volatile uint32_t *)0x42210130)
#define INPUT_PIN_A13 (*(volatile uint32_t *)0x42210134)
#define INPUT_PIN_A14 (*(volatile uint32_t *)0x42210138)
#define INPUT_PIN_A15 (*(volatile uint32_t *)0x4221013C)



#define RELAY1 OUTPUT_PIN_B8
#define RELAY2 OUTPUT_PIN_B5
#define RELAY3 OUTPUT_PIN_B4
#define RELAY4 OUTPUT_PIN_B3

#define BELL OUTPUT_PIN_B9

#define MD0 OUTPUT_PIN_B12
#define MD1 OUTPUT_PIN_B14

#define LED1 OUTPUT_PIN_A15
#define LED2 OUTPUT_PIN_A12
#define LED3 OUTPUT_PIN_A11

#define SL_BT INPUT_PIN_A0
#define WR_BT INPUT_PIN_A7

#define BT1 INPUT_PIN_A1
#define BT2 INPUT_PIN_A4
#define BT3 INPUT_PIN_A5
#define BT4 INPUT_PIN_A6

#define LATCH OUTPUT_PIN_B2

unsigned char byte_rx1[1] = {0};
unsigned char bf_tx1[3] = {'S', '1', 'P'};
unsigned char rx1_index = 0;
unsigned char ena_rx1 = 0;
unsigned char data_rx_uart1[20] = {};

unsigned char byte_rx2[1] = {0};
unsigned char bf_tx2[20] = {'S', '1', 'P'};
unsigned char rx2_index = 0;
unsigned char ena_rx2 = 0;
unsigned char data_rx_uart2[10] = {};
unsigned char data_from_esp[2] = {0};
unsigned char data_send_esp[60] = {0};
unsigned char control_devices = 0;

unsigned char byte_rx3[1] = {0};
unsigned char bf_tx3[10] = {};
unsigned char rx3_index = 0;
unsigned char ena_rx3 = 0;
unsigned char data_rx_uart3[30] = {};

unsigned char request_node = 1;

unsigned char printf_mode = 0;
#define printf_uart1 0
#define printf_uart2 1
#define printf_uart3 2
#define printf_lcd 3
#define printf_lcd_i2c 4



unsigned char data_node1[20] = {0x32, 0x36, 0x32, 0x31, 0x34, 0x34, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
unsigned char check_state_node1 = 0;
unsigned char num_error1 = 0;
unsigned char state_node1 = 0;

unsigned char data_node2[20] = {0x32, 0x36, 0x32, 0x31, 0x34, 0x34, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
unsigned char check_state_node2 = 0;
unsigned char num_error2 = 0;
unsigned char state_node2 = 0;

unsigned char data_node3[20] = {0x32, 0x36, 0x32, 0x31, 0x34, 0x34, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
unsigned char check_state_node3 = 0;
unsigned char num_error3 = 0;
unsigned char state_node3 = 0;

unsigned char number_of_error = 0;

unsigned char state_led = 0;

unsigned char display_mode = 1;

// unsigned long A6 = 0x42000000 + (unsigned int)(&GPIOB->ODR)  * 32 + 9 * 4;
//unsigned long A0 = 0x42000000 + (unsigned int) (&GPIOA->IDR) * 32 + 0 * 4;

unsigned long dem = 0;

unsigned long temp1 = 0;
float temp1_float;
float temp1_old = 0;
unsigned long mq21_ppm = 0;
unsigned long mq21_old = 0;
unsigned int mq21_adc = 0;
float rs_mq21 = 0;
unsigned int mp21_adc = 0;
unsigned long mp21_ppm = 0;
unsigned long mp21_old = 0;

unsigned long temp2 = 0;
float temp2_float = 0;
float temp2_old = 0;
unsigned int mq22_adc = 0;
float rs_mq22 = 0;
unsigned long mq22_ppm = 0;
unsigned long mq22_old = 0;
unsigned int mp22_adc = 0;
unsigned long mp22_ppm = 0;
unsigned long mp22_old = 0;

unsigned long temp3 = 0;
float temp3_float = 0;
float temp3_old = 0;
unsigned int mq23_adc = 0;
float rs_mq23 = 0;
unsigned long mq23_ppm = 0;
unsigned long mq23_old = 0;
unsigned int mp23_adc = 0;
unsigned long mp23_ppm = 0;
unsigned long mp23_old = 0;

unsigned char wifi_status = 0;
unsigned char warning = 0;

unsigned char temp_level1 = 35, temp_level2 = 40;
unsigned int gas_level1 = 1000, gas_level2 = 5000;
unsigned int smoke_level1 = 1000, smoke_level2 = 5000;

uint8_t check_temp_n1, check_temp_n2, check_temp_n3;
uint8_t check_mp_n1, check_mp_n2, check_mp_n3;
uint8_t check_mq_n1, check_mq_n2, check_mq_n3;

uint8_t node1, node2, node3;

volatile _Bool ena_sms=0;

volatile unsigned char node_update = 0;

volatile _Bool sim_mode=0;

volatile _Bool call_state=0;

volatile _Bool no_carrier = 0;

volatile _Bool begin = 0;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "delay_us_lib.c"
//#include "lcd_lib.c"
#include "i2c_lib.c"
#include "lcd_i2c_lib.c"

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
    
        if (byte_rx1[0] == 'S') {
            ena_rx1 = 1;
            rx1_index = 0;
        } else if (byte_rx1[0] != 'P' && ena_rx1 == 1) {
            data_rx_uart1[rx1_index] = byte_rx1[0];
            rx1_index++;
            if (rx1_index > 15) ena_rx1 = 0;
        } else if (byte_rx1[0] == 'P' && ena_rx1 == 1) {
            if (data_rx_uart1[0] == 1) {
                check_state_node1 = 1;
                node_update =1;
                for (uint8_t i = 0; i < 14; i++) data_node1[i] = data_rx_uart1[i + 1];
            } else if (data_rx_uart1[0] == 2) {
                check_state_node2 = 1;
                node_update =2;
                for (uint8_t i = 0; i < 14; i++) data_node2[i] = data_rx_uart1[i + 1];
            } else if (data_rx_uart1[0] == 3) {
                check_state_node3 = 1;
                node_update =3;
                for (uint8_t i = 0; i < 14; i++) data_node3[i] = data_rx_uart1[i + 1];
            }
            ena_rx1 = 0;
        }
        HAL_UART_Receive_IT(&huart1, byte_rx1, 1);
    } else if (huart->Instance == USART2) {
        if (byte_rx2[0] == 'S') {
            ena_rx2 = 1;
            rx2_index = 0;
        } else if (byte_rx2[0] != 'P' && ena_rx2 == 1) {
            data_rx_uart2[rx2_index] = byte_rx2[0];
            rx2_index++;
            if (rx1_index > 3) ena_rx1 = 0;
        } else if (byte_rx2[0] == 'P' && ena_rx2 == 1) {
            data_from_esp[0] = data_rx_uart2[0];
            data_from_esp[1] = data_rx_uart2[1];
            if (data_from_esp[0] == 'C') control_devices = data_from_esp[1];
            else if (data_from_esp[0] == 'F') wifi_status = data_from_esp[1];
            else if (data_from_esp[0] == 'W') warning = data_from_esp[1];
            ena_rx2 = 0;
        }
        HAL_UART_Receive_IT(&huart2, byte_rx2, 1);
    } else if (huart->Instance == USART3) {
      if (sim_mode == 0)
      {
        if (byte_rx3[0] == 0x3e) ena_sms = 1;
        else HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
      }
      else 
      {
        if (byte_rx3[0] == 'B') begin =1;
        else if (byte_rx3[0] == 'R') no_carrier = 1; 
        else HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
      }
    }
        
}
//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        if (request_node == 1) {
            bf_tx1[1] = '1';
            HAL_UART_Transmit(&huart1, bf_tx1, 3, HAL_MAX_DELAY);
            check_state_node1 = 0;
            if (check_state_node3 == 0) {
                num_error3++;
                if (num_error3 > number_of_error) state_node3 = 0;
            } else {
                state_node3 = 1;
                num_error3 = 0;
            }
        } else if (request_node == 2) {
            bf_tx1[1] = '2';
            HAL_UART_Transmit(&huart1, bf_tx1, 3, HAL_MAX_DELAY);
            check_state_node2 = 0;
            if (check_state_node1 == 0) {
                num_error1++;
                if (num_error1 > number_of_error) state_node1 = 0;
            } else {
                state_node1 = 1;
                num_error1 = 0;
            }
        } else if (request_node == 3) {
            bf_tx1[1] = '3';
            HAL_UART_Transmit(&huart1, bf_tx1, 3, HAL_MAX_DELAY);
            check_state_node3 = 0;
            if (check_state_node2 == 0) {
                num_error2++;
                if (num_error2 > number_of_error) state_node2 = 0;
            } else {
                state_node2 = 1;
                num_error2 = 0;
            }
        }
        request_node++;
        if (request_node > 3) request_node = 1;
        __HAL_TIM_SET_COUNTER(&htim2, 61535); //150ms
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
    //////////////////////////////////////////////
    HAL_TIM_Base_Start(&htim1);
    MD0 = 0;
    MD1 = 0;
    RELAY1 = 1;
    RELAY2 = 1;
    RELAY3 = 1;
    RELAY4 = 1;
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LCD_I2C_INIT();
    //////////////////////////////////////////////////
OUTPUT_PIN_A8 = 1;
//LCD_BACKLIGHT_OFF();
    printf_mode = printf_uart3;
//        printf("AT%c%c", 0x0d, 0x0a);
//        HAL_Delay(3);
//        printf("ATE%c%c", 0x0d, 0x0a);
//        HAL_Delay(3);
            printf("AT+CMGF=1%c%c", 0x0d, 0x0a); /////////// nhan tin
//            HAL_Delay(3);
//        printf("AT&W%c%c", 0x0d, 0x0a);
//        HAL_Delay(20);
    //    printf("AT+CMGD=1,4%c%c", 0x0d, 0x0a);
    //    printf("AT+CUSD=1,%c*101#%c,%u%c%c",0x22, 0x22, 17, 0x0d, 0x0a);
    //    printf("AT+CUSD?%c%c", 0x0d, 0x0a);
    //
    //    printf("AT+CMGS=%c0862335521%c%c%c",0x22, 0x22, 0x0d, 0x0a); //
//              printf("AT+CMGS=%c0868390442%c%c%c",0x22, 0x22, 0x0d, 0x0a); //
//              HAL_Delay(150); //
//              printf("hellooo%c", 0x1a); /////////////////////
//      HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
//      sim_mode =1;
//        printf("ATD0868390442;%c%c", 0x0d, 0x0a); // goi dien
        
    //    printf("AT+CNMI=2,2%c%c", 0x0d, 0x0a);
    //    printf("AT+CMGR=3%c%c", 0x0d, 0x0a);
//HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
    printf_mode = printf_uart3;
    
//     printf("AT+CMGF=1%c%c", 0x0d, 0x0a); /////////// dua ve dang text
//    HAL_Delay(100);


    HAL_UART_Receive_IT(&huart1, byte_rx1, 1);
    HAL_UART_Receive_IT(&huart2, byte_rx2, 1);
    
    
    __HAL_TIM_SET_COUNTER(&htim2, 65500);
    HAL_TIM_Base_Start_IT(&htim2);

    //    __HAL_TIM_SET_COUNTER(&htim3, 65500);
    //    HAL_TIM_Base_Start_IT(&htim3);

    BELL = 1;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1) {
        LATCH  = ~LATCH;
        printf_mode = printf_lcd_i2c;
        LCD_I2C_GOTO_XY(10, 1);
        printf("%u", call_state);
        if (display_mode == 1) {
            if (state_node1 == 1) {
                printf_mode = printf_lcd_i2c;
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 1:");
                LCD_I2C_GOTO_XY(1, 2);
                printf("GAS:%5uPPM", (unsigned int) mq21_ppm);
                LCD_I2C_GOTO_XY(1, 3);
                printf("SMO:%5uPPM", (unsigned int) mp21_ppm);
                LCD_I2C_GOTO_XY(1, 4);
                printf("TEMP: %0.1f%cC", temp1_float, 223);
            } else {
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 1:");
                LCD_I2C_GOTO_XY(1, 2);
                printf("             ");
                LCD_I2C_GOTO_XY(1, 3);
                printf("  DISCONNECT");
                LCD_I2C_GOTO_XY(1, 4);
                printf("             ");
            }
        } else if (display_mode == 2) {
            if (state_node2 == 1) {
                printf_mode = printf_lcd_i2c;
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 2:");
                LCD_I2C_GOTO_XY(1, 2);
                printf("GAS:%5uPPM", (unsigned int) mq22_ppm);
                LCD_I2C_GOTO_XY(1, 3);
                printf("SMO:%5uPPM", (unsigned int) mp22_ppm);
                LCD_I2C_GOTO_XY(1, 4);
                printf("TEMP: %0.1f%cC", temp2_float, 223);
            } else {
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 2:");
                LCD_I2C_GOTO_XY(1, 2);
                printf("             ");
                LCD_I2C_GOTO_XY(1, 3);
                printf("  DISCONNECT");
                LCD_I2C_GOTO_XY(1, 4);
                printf("             ");
            }
        } else if (display_mode == 3) {
            if (state_node3 == 1) {
                printf_mode = printf_lcd_i2c;
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 3:");
                LCD_I2C_GOTO_XY(1, 2);
                printf("GAS:%5uPPM", (unsigned int) mq23_ppm);
                LCD_I2C_GOTO_XY(1, 3);
                printf("SMO:%5uPPM", (unsigned int) mp23_ppm);
                LCD_I2C_GOTO_XY(1, 4);
                printf("TEMP: %0.1f%cC", temp3_float, 223);
            } else {
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 3:");
                LCD_I2C_GOTO_XY(1, 2);
                printf("             ");
                LCD_I2C_GOTO_XY(1, 3);
                printf("  DISCONNECT");
                LCD_I2C_GOTO_XY(1, 4);
                printf("             ");
            }
        }

        LCD_I2C_GOTO_XY(15, 1);
        if (RELAY1 == 0) printf("D1: ON");
        else printf("D1:OFF");

        LCD_I2C_GOTO_XY(15, 2);
        if (RELAY2 == 0) printf("D2: ON");
        else printf("D2:OFF");

        LCD_I2C_GOTO_XY(15, 3);
        if (RELAY3 == 0) printf("D3: ON");
        else printf("D3:OFF");

        LCD_I2C_GOTO_XY(15, 4);
        if (RELAY4 == 0) printf("D4: ON");
        else printf("D4:OFF");
        //////////////////////////////////////////////////////////////////////////////
        if (node_update == 1){
        temp1 = (data_node1[0] - 48) * 100000 + (data_node1[1] - 48) * 10000 + (data_node1[2] - 48) * 1000 + (data_node1[3] - 48) * 100 + (data_node1[4] - 48) * 10 + (data_node1[5] - 48) * 1;
        temp1_float = ((float) temp1 * 200) / 1048576 - 50;

        mq21_adc = (data_node1[6] - 48) * 1000 + (data_node1[7] - 48) * 100 + (data_node1[8] - 48) * 10 + (data_node1[9] - 48) * 1;
        rs_mq21 = (1023 / (float) mq21_adc - 1) * 10; // kilo ohm
        mq21_ppm = pow(10, (1.25 - log10(rs_mq21 / 3.66)) / 0.45);
        if (mq21_ppm > 10000) mq21_ppm = 10000;

        mp21_ppm = pow(10, (1.55 - log10(rs_mq21 / 3.66)) / 0.44);
        if (mp21_ppm > 10000) mp21_ppm = 10000;
        node_update =0;}
        ////////////////////////////////////////////////////////////////////////////////////
         if (node_update ==2){
        temp2 = (data_node2[0] - 48) * 100000 + (data_node2[1] - 48) * 10000 + (data_node2[2] - 48) * 1000 + (data_node2[3] - 48) * 100 + (data_node2[4] - 48) * 10 + (data_node2[5] - 48) * 1;
        temp2_float = ((float) temp2 * 200) / 1048576 - 50;

        mq22_adc = (data_node2[6] - 48) * 1000 + (data_node2[7] - 48) * 100 + (data_node2[8] - 48) * 10 + (data_node2[9] - 48) * 1;
        rs_mq22 = (1023 / (float) mq22_adc - 1) * 10; // kilo ohm
        mq22_ppm = pow(10, (1.25 - log10(rs_mq22 / 3.66)) / 0.45);
        if (mq22_ppm > 10000) mq22_ppm = 10000;
        mp22_ppm = pow(10, (1.55 - log10(rs_mq22 / 3.66)) / 0.44);
        if (mp22_ppm > 10000) mp22_ppm = 10000;
        node_update =0;}
        
        //////////////////////////////////////////////////////////////////////////////////
        if (node_update ==3){
        temp3 = (data_node3[0] - 48) * 100000 + (data_node3[1] - 48) * 10000 + (data_node3[2] - 48) * 1000 + (data_node3[3] - 48) * 100 + (data_node3[4] - 48) * 10 + (data_node3[5] - 48) * 1;
        temp3_float = ((float) temp3 * 200) / 1048576 - 50 ;

        mq23_adc = (data_node3[6] - 48) * 1000 + (data_node3[7] - 48) * 100 + (data_node3[8] - 48) * 10 + (data_node3[9] - 48) * 1;
        rs_mq23 = (1023 / (float) mq23_adc - 1) * 10; // kilo ohm
        mq23_ppm = pow(10, (1.25 - log10(rs_mq23 / 3.66)) / 0.45);
        if (mq23_ppm > 10000) mq23_ppm = 10000;
        
        mp23_ppm = pow(10, (1.55 - log10(rs_mq23 / 3.66)) / 0.44);
        if (mp23_ppm > 10000) mp23_ppm = 10000;
        node_update =0;}

        //////////////////////////////////////////////////////////////////////////////////      
        if(node3 == 1){
          if(check_temp_n3){
            if(temp3_float >= 38){
            if (call_state == 0){
              call_state = 1;
              printf_mode = printf_uart3;
              HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
              sim_mode =1;
              printf("ATD0868390442;%c%c", 0x0d, 0x0a);
            }
            else if (begin == 1) call_state = 1;
            else if (no_carrier == 1) call_state = 0;
					}
					else if(temp3_float - temp3_old >=2.0)
					{
//						temp3_old = temp3_float;
//						printf_mode = printf_uart3;
//						printf("AT+CMGS=%c0868390442%c%c%c",0x22, 0x22, 0x0d, 0x0a);
//            HAL_Delay(20);
//						printf("Warning - NODE3 - Temperature: %0.2f%c", temp3_float, 0x1a);
					}
					else if(temp3_float < 36)
					{
            call_state = 0;
						node3 = 0;
						check_temp_n3 = 0;
            begin=0;
            no_carrier=0;
            HAL_Delay(200);
					}
				}
        }
			if(node3 == 0){
				if((temp3_float >=36)) 
				{
					node3 = 1;
					warning = 1;
//          printf_mode = printf_lcd_i2c;
//					printf_mode = printf_uart2;
//					warning = warning | 0x01;
//					printf("%cW%c%c", 'S', warning, 'P');
					printf_mode = printf_uart3;
          sim_mode =0;
          OUTPUT_PIN_A8 = ~OUTPUT_PIN_A8;
          HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
					printf("AT+CMGS=%c0868390442%c%c%c",0x22, 0x22, 0x0d, 0x0a);
//          HAL_Delay(20);
//          if (data_rx_uart3[18]== 0x3e || data_rx_uart3[19]== 0x3e ) ena_sms = 1;
          while(ena_sms ==0){};
          printf("Warning - NODE3 - Temperature: %0.2f - Gas: %05luppm - Smoke: %05luppm%c", temp3_float, mq23_ppm, mp23_ppm, 0x1a);
           ena_sms = 0;
          if(temp3_float >=36) check_temp_n3 = 1;
//          if(mq23_ppm >= 30) check_mq_n3 = 1;
//          if(mp23_ppm >= 50) check_mp_n3 = 1;
          temp3_old = temp3_float;
//          mq23_old = mq23_ppm;
//          mp23_old = mp23_ppm;
        }
      }
      
      
        
        printf_mode = printf_uart2;
        if (SL_BT == 0) {
            HAL_Delay(10);
            if (SL_BT == 0) {
                while (SL_BT == 0);
                display_mode++;
                if (display_mode > 3) display_mode = 1;
            }
        }

        if (BT1 == 0) {
            HAL_Delay(10);
            if (BT1 == 0) {
                while (BT1 == 0);
                RELAY1 = ~RELAY1;
                if (RELAY1 == 0) control_devices = control_devices | 0x01;
                else control_devices = control_devices & 0xfe;
                printf("%cB%c%c", 'S', control_devices, 'P');
            }
        }

        if (BT2 == 0) {
            HAL_Delay(10);
            if (BT2 == 0) {
                while (BT2 == 0);
                RELAY2 = ~RELAY2;
                if (RELAY2 == 0) control_devices = control_devices | 0x02;
                else control_devices = control_devices & 0xfd;
                printf("%cB%c%c", 'S', control_devices, 'P');
            }
        }

        if (BT3 == 0) {
            HAL_Delay(10);
            if (BT3 == 0) {
                while (BT3 == 0);
                RELAY3 = ~RELAY3;
                if (RELAY3 == 0) control_devices = control_devices | 0x04;
                else control_devices = control_devices & 0xfb;
                printf("%cB%c%c", 'S', control_devices, 'P');
            }
        }

        if (BT4 == 0) {
            HAL_Delay(10);
            if (BT4 == 0) {
                while (BT4 == 0);
                RELAY4 = ~RELAY4;
                if (RELAY4 == 0) control_devices = control_devices | 0x08;
                else control_devices = control_devices & 0xf7;
                printf("%cB%c%c", 'S', control_devices, 'P');
            }
        }

        if (WR_BT == 0) {
            HAL_Delay(10);
            if (WR_BT == 0) {
                while (WR_BT == 0);
                BELL = ~BELL;
                if (BELL == 0) warning = 1;
                else warning =0;
                printf("%cW%c%c", 'S', warning, 'P');

            }
        }

        if ((control_devices & 0x01) == 0) RELAY1 = 1;
        else RELAY1 = 0;

        if ((control_devices & 0x02) == 0) RELAY2 = 1;
        else RELAY2 = 0;

        if ((control_devices & 0x04) == 0) RELAY3 = 1;
        else RELAY3 = 0;

        if ((control_devices & 0x08) == 0) RELAY4 = 1;
        else RELAY4 = 0;
        
        if (warning == 0) BELL =1;
        else BELL =0;
        dem++;
        if (dem % 250 == 0) {
            printf("%c%0.2f%05lu%05lu%0.2f%05lu%05lu%0.2f%05lu%05lu%c", 'S', temp1_float, (unsigned long) mq21_ppm, (unsigned long) mp21_ppm, temp2_float, (unsigned long) mq22_ppm, (unsigned long) mp22_ppm, temp3_float, (unsigned long) mq23_ppm, (unsigned long) mp23_ppm, 'P');
            //S25.55100001000025.55100001000025.551000010000P
        }
        if (dem % 10 == 0) {
            if (state_led == 1) {
                LED1 = 0;
                LED2 = 0;
                LED3 = 0;
                state_led = 0;
            } else if (state_led == 0) {
                if (state_node1 == 0) LED1 = 1;
                if (state_node2 == 0) LED2 = 1;
                if (state_node3 == 0) LED3 = 1;
                state_led = 1;
            }
        }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 72;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 921600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|MD0_Pin|MD1_Pin|RELAY4_Pin
                          |RELAY3_Pin|RELAY2_Pin|GPIO_PIN_6|GPIO_PIN_7
                          |RELAY1_Pin|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, PA8_Pin|LED3_Pin|LED2_Pin|LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA4 PA5
                           PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 MD0_Pin MD1_Pin RELAY4_Pin
                           RELAY3_Pin RELAY2_Pin PB6 PB7
                           RELAY1_Pin PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|MD0_Pin|MD1_Pin|RELAY4_Pin
                          |RELAY3_Pin|RELAY2_Pin|GPIO_PIN_6|GPIO_PIN_7
                          |RELAY1_Pin|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8_Pin LED3_Pin LED2_Pin LED1_Pin */
  GPIO_InitStruct.Pin = PA8_Pin|LED3_Pin|LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
struct __FILE {
    int handle;
};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
    (void) (f);
    if (printf_mode == printf_uart1) HAL_UART_Transmit(&huart1, (uint8_t *) & ch, 1, HAL_MAX_DELAY);
    else if (printf_mode == printf_uart2) HAL_UART_Transmit(&huart2, (uint8_t *) & ch, 1, HAL_MAX_DELAY);
    else if (printf_mode == printf_uart3) HAL_UART_Transmit(&huart3, (uint8_t *) & ch, 1, HAL_MAX_DELAY);
        //    else if (printf_mode == printf_lcd) lcd_char(ch);
    else if (printf_mode == printf_lcd_i2c) LCD_I2C_CHAR(ch);
    return ch;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
         ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
