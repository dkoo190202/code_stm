
#include "main.h"
#include <stdio.h>
#include <math.h>

#define OUTPUT_PIN_A8 (*(volatile uint32_t *)0x422101A0)
#define OUTPUT_PIN_A11 (*(volatile uint32_t *)0x422101AC)
#define OUTPUT_PIN_A12 (*(volatile uint32_t *)0x422101B0)
#define OUTPUT_PIN_A15 (*(volatile uint32_t *)0x422101BC)

#define OUTPUT_PIN_B2 (*(volatile uint32_t *)0x42218188)
#define OUTPUT_PIN_B3 (*(volatile uint32_t *)0x4221818C)
#define OUTPUT_PIN_B4 (*(volatile uint32_t *)0x42218190)
#define OUTPUT_PIN_B5 (*(volatile uint32_t *)0x42218194)
#define OUTPUT_PIN_B6 (*(volatile uint32_t *)0x42218198)
#define OUTPUT_PIN_B7 (*(volatile uint32_t *)0x4221819C)
#define OUTPUT_PIN_B8 (*(volatile uint32_t *)0x422181A0)
#define OUTPUT_PIN_B9 (*(volatile uint32_t *)0x422181A4)
#define OUTPUT_PIN_B12 (*(volatile uint32_t *)0x422181B0)
#define OUTPUT_PIN_B14 (*(volatile uint32_t *)0x422181B8)

#define INPUT_PIN_A0 (*(volatile uint32_t *)0x42210100)
#define INPUT_PIN_A1 (*(volatile uint32_t *)0x42210104)
#define INPUT_PIN_A4 (*(volatile uint32_t *)0x42210110)
#define INPUT_PIN_A5 (*(volatile uint32_t *)0x42210114)
#define INPUT_PIN_A6 (*(volatile uint32_t *)0x42210118)
#define INPUT_PIN_A7 (*(volatile uint32_t *)0x4221011C)

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

volatile unsigned char data_node1[20] = {0x32, 0x36, 0x32, 0x31, 0x34, 0x34, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
volatile unsigned char check_state_node1 = 0;
volatile unsigned char num_error1 = 0;
volatile unsigned char state_node1 = 0;

volatile unsigned char data_node2[20] = {0x32, 0x36, 0x32, 0x31, 0x34, 0x34, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
volatile unsigned char check_state_node2 = 0;
volatile unsigned char num_error2 = 0;
volatile unsigned char state_node2 = 0;

volatile unsigned char data_node3[20] = {0x32, 0x36, 0x32, 0x31, 0x34, 0x34, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
volatile unsigned char check_state_node3 = 0;
volatile unsigned char num_error3 = 0;
volatile unsigned char state_node3 = 0;

unsigned char number_of_error = 1;

volatile unsigned char state_led = 0;

volatile unsigned char display_mode = 1;

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

unsigned char temp_level1 = 35, temp_level2 = 45;
unsigned int gas_level1 = 1000, gas_level2 = 5000;
unsigned int smoke_level1 = 1000, smoke_level2 = 5000;

unsigned char warning_level = 0;

volatile _Bool ena_sms = 0;

volatile unsigned char node_update = 0;


volatile _Bool call_state = 0;

volatile _Bool verify_call = 0;

volatile _Bool sim_status = 0;
volatile _Bool ok_chua = 0;
volatile _Bool ena_begin = 0, ena_carrier = 0, ena_pb_done = 0, ena_ok = 0, ena_mti = 0;
volatile unsigned char begin_index = 0, carrier_index = 0, pb_done_index = 0, ok_index = 0, mti_index = 0;
const char begin[6] = "BEGIN";
const char carrier[8] = "CARRIER";
const char pb_done[8] = "PB DONE";
const char ok[3] = "OK";
volatile unsigned char mti[20] = {0x54, 0x49, 0x3a, 0x20, 0x22, 0x53, 0x4d, 0x22, 0x2c}; //MTI: "SM",
volatile _Bool mti_ok = 0;
volatile unsigned char id_mes_ascii[4] = {};
volatile unsigned char id_index = 0;
unsigned char id_mess = 0;

volatile _Bool sim_stable = 0;

volatile unsigned char sim_read = 0; // 0: kiem tra trang thai ban dau, 1: bat dau ">", 2: bat "BEGIN" va "NO CARRIER", 3: bat "OK", 4: bat "CMTI"
volatile _Bool sim_config = 0;

volatile _Bool ena_send_node1 = 0, ena_send_node2 = 0, ena_send_node3 = 0;

volatile _Bool ena_send_state_node1 = 0, ena_send_state_node2 = 0, ena_send_state_node3 = 0;

volatile _Bool bell_level1 = 0;

volatile _Bool auto_warning = 1;

volatile _Bool ena_send_warning = 0;

unsigned int biendem = 0;
unsigned int check = 0;

volatile _Bool mti_true = 0;
volatile _Bool ena_id_mess = 0;
_Bool ena_end_of_warning = 0;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_TIM3_Init(void);

#include "delay_us_lib.c"
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
                node_update = 1;
                for (uint8_t i = 0; i < 14; i++) data_node1[i] = data_rx_uart1[i + 1];
            } else if (data_rx_uart1[0] == 2) {
                check_state_node2 = 1;
                node_update = 2;
                for (uint8_t i = 0; i < 14; i++) data_node2[i] = data_rx_uart1[i + 1];
            } else if (data_rx_uart1[0] == 3) {
                check_state_node3 = 1;
                node_update = 3;
                for (uint8_t i = 0; i < 14; i++) data_node3[i] = data_rx_uart1[i + 1];
            }
            ena_rx1 = 0;
        }
        HAL_UART_Receive_IT(&huart1, byte_rx1, 1);
        ////////////////////////////////////////////////////////////////////////////////////////
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
            else if (data_from_esp[0] == 'W') {
                if (warning == 1) ena_send_warning = 1;
                else BELL = (~data_from_esp[1])& 0x01;
            }
            ena_rx2 = 0;
        }
        HAL_UART_Receive_IT(&huart2, byte_rx2, 1);
        /////////////////////////////////////////////////////////////////////////////////
    } else if (huart->Instance == USART3) {// PB DONE
        if (sim_read == 0) {
            if (byte_rx3[0] == 'P') {
                ena_pb_done = 1;
                pb_done_index = 0;
            }
            if (ena_pb_done == 1) {
                if (pb_done[pb_done_index] != byte_rx3[0]) ena_pb_done = 0;
                pb_done_index++;
                if (pb_done_index > 6) sim_stable = 1;
            }
            HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
        } else if (sim_read == 1) {
            if (byte_rx3[0] == 0x3e) {
                delay_us(10000);
                ena_sms = 1;
            }
            HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
        } else if (sim_read == 2) {
            if (byte_rx3[0] == 'B') {
                ena_begin = 1;
                begin_index = 0;
            }
            if (ena_begin == 1) {
                if (begin[begin_index] != byte_rx3[0]) ena_begin = 0;
                begin_index++;
                if (begin_index > 4) verify_call = 1;
            }

            if (byte_rx3[0] == 'C') {
                ena_carrier = 1;
                carrier_index = 0;
            }
            if (ena_carrier == 1) {
                if (carrier[carrier_index] != byte_rx3[0]) ena_carrier = 0;
                carrier_index++;
                if (carrier_index > 6) {
                    sim_status = 0;
                    delay_us(60000);
                    delay_us(60000);
                    delay_us(60000);
                    delay_us(60000);
                }
            }
            HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
        } else if (sim_read == 3) {
            if (byte_rx3[0] == 'O') {
                ena_ok = 1;
                ok_index = 0;
            }
            if (ena_ok == 1) {
                if (ok[ok_index] != byte_rx3[0]) ena_ok = 0;
                else {
                    ok_index++;
                    if (ok_index > 1) sim_status = 0;
                }
            }
            HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
        } else if (sim_read == 4) {
            if (mti_ok == 0) {
                if (byte_rx3[0] == 'T') {
                    sim_status = 1;
                    ena_mti = 1;
                    mti_index = 0;
                }
                if (ena_mti == 1) {
                    if (mti[mti_index] != byte_rx3[0]) {
                        ena_mti = 0;
                        sim_status = 0;
                    } else {
                        mti_index++;
                        if (mti_index > 8) {
                            mti_ok = 1;
                            id_index = 0;
                        }
                    }
                }
            } else if (mti_ok == 1) {
                if (byte_rx3[0] == 0x0d) {
                    sim_status = 1;
                    mti_ok = 0;
                    ena_id_mess = 1;
                } else {
                    id_mes_ascii[id_index] = byte_rx3[0];
                    id_index++;
                }
            }
        }
        HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
    }

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        if (request_node == 1) {
            bf_tx1[1] = '1';
            HAL_UART_Transmit(&huart1, bf_tx1, 3, HAL_MAX_DELAY);
            check_state_node1 = 0;
            if (check_state_node3 == 0) {
                num_error3++;
                if (num_error3 > number_of_error) {
                    if (state_node3 == 1) ena_send_state_node3 = 1;
                    state_node3 = 0;
                }
            } else {
                if (state_node3 == 0) ena_send_state_node3 = 1;
                state_node3 = 1;
                num_error3 = 0;
            }
        } else if (request_node == 2) {
            bf_tx1[1] = '2';
            HAL_UART_Transmit(&huart1, bf_tx1, 3, HAL_MAX_DELAY);
            check_state_node2 = 0;
            if (check_state_node1 == 0) {
                num_error1++;
                if (num_error1 > number_of_error) {
                    if (state_node1 == 1) ena_send_state_node1 = 1;
                    state_node1 = 0;
                }
            } else {
                if (state_node1 == 0) ena_send_state_node1 = 1;
                state_node1 = 1;
                num_error1 = 0;
            }
        } else if (request_node == 3) {
            bf_tx1[1] = '3';
            HAL_UART_Transmit(&huart1, bf_tx1, 3, HAL_MAX_DELAY);
            check_state_node3 = 0;
            if (check_state_node2 == 0) {
                num_error2++;
                if (num_error2 > number_of_error) {
                    if (state_node2 == 1) ena_send_state_node2 = 1;
                    state_node2 = 0;
                }
            } else {
                if (state_node2 == 0) ena_send_state_node2 = 1;
                state_node2 = 1;
                num_error2 = 0;
            }
        }
        request_node++;
        if (request_node > 3) request_node = 1;
        __HAL_TIM_SET_COUNTER(&htim2, 63035); //250ms
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tinh_id_mess() {
    if (id_index == 1) id_mess = id_mes_ascii[0] - 48;
    else if (id_index == 1) id_mess = (id_mes_ascii[0] - 48)*10 + id_mes_ascii[1] - 48;
    else if (id_index == 1) id_mess = (id_mes_ascii[0] - 48)*100 + (id_mes_ascii[1] - 48)*10 + id_mes_ascii[2] - 48;
}

int main(void) {
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_TIM1_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    MX_SPI2_Init();
    MX_TIM2_Init();
    MX_USART3_UART_Init();
    MX_TIM3_Init();
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
    BELL = 1;
    LCD_I2C_INIT();
    //////////////////////////////////////////////////
    OUTPUT_PIN_A8 = 1;
    printf_mode = printf_uart3;
    HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
    printf_mode = printf_uart3;


    HAL_UART_Receive_IT(&huart1, byte_rx1, 1);
    HAL_UART_Receive_IT(&huart2, byte_rx2, 1);


    __HAL_TIM_SET_COUNTER(&htim2, 65500);
    HAL_TIM_Base_Start_IT(&htim2);


    while (1) {

        /// nho sua bien sim_stable
        if (sim_stable == 1) {
            if (sim_config == 0) {
                printf_mode = printf_uart3;
                printf("AT+CMGF=1%c%c", 0x0d, 0x0a); /////////// nhan tin
                sim_read = 3;
                while (sim_status == 1);
                sim_config = 1;

                HAL_Delay(500);
                sim_status = 1; // sim dang ban ( dang chuan bi gui tin nhan )
                printf_mode = printf_uart3;
                sim_read = 1;
                HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                while (ena_sms == 0);
                printf("System is Active%c", 0x1a);
                ena_sms = 0;
                sim_read = 3;
                while (sim_status == 1);
                printf("AT+CMGD=1,4%c%c", 0x0d, 0x0a);
                sim_read = 3;
            }
        }

        if (state_node1 == 0) {
            temp1_float = 0;
            mq21_ppm = 0;
            mp21_ppm = 0;
        }
        if (state_node2 == 0) {
            temp2_float = 0;
            mq22_ppm = 0;
            mp22_ppm = 0;
        }
        if (state_node3 == 0) {
            temp3_float = 0;
            mq23_ppm = 0;
            mp23_ppm = 0;
        }
        printf_mode = printf_lcd_i2c;
        if (display_mode == 1) {
            if (state_node1 == 1) {
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 1:       ");
                LCD_I2C_GOTO_XY(1, 2);
                printf("GAS:%5uPPM  ", (unsigned int) mq21_ppm);
                LCD_I2C_GOTO_XY(1, 3);
                printf("SMO:%5uPPM  ", (unsigned int) mp21_ppm);
                LCD_I2C_GOTO_XY(1, 4);
                printf("TEMP: %0.1f%cC", temp1_float, 223);
            } else {
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 1:       ");
                LCD_I2C_GOTO_XY(1, 2);
                printf("             ");
                LCD_I2C_GOTO_XY(1, 3);
                printf("  DISCONNECT");
                LCD_I2C_GOTO_XY(1, 4);
                printf("             ");
            }
        } else if (display_mode == 2) {
            if (state_node2 == 1) {
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 2:       ");
                LCD_I2C_GOTO_XY(1, 2);
                printf("GAS:%5uPPM  ", (unsigned int) mq22_ppm);
                LCD_I2C_GOTO_XY(1, 3);
                printf("SMO:%5uPPM  ", (unsigned int) mp22_ppm);
                LCD_I2C_GOTO_XY(1, 4);
                printf("TEMP: %0.1f%cC", temp2_float, 223);
            } else {

                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 2:       ");
                LCD_I2C_GOTO_XY(1, 2);
                printf("             ");
                LCD_I2C_GOTO_XY(1, 3);
                printf("  DISCONNECT");
                LCD_I2C_GOTO_XY(1, 4);
                printf("             ");
            }
        } else if (display_mode == 3) {
            if (state_node3 == 1) {
                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 3:       ");
                LCD_I2C_GOTO_XY(1, 2);
                printf("GAS:%5uPPM  ", (unsigned int) mq23_ppm);
                LCD_I2C_GOTO_XY(1, 3);
                printf("SMO:%5uPPM  ", (unsigned int) mp23_ppm);
                LCD_I2C_GOTO_XY(1, 4);
                printf("TEMP: %0.1f%cC", temp3_float, 223);
            } else {

                LCD_I2C_GOTO_XY(1, 1);
                printf("NODE 3:       ");
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
        if (node_update == 1) {
            temp1 = (data_node1[0] - 48) * 100000 + (data_node1[1] - 48) * 10000 + (data_node1[2] - 48) * 1000 + (data_node1[3] - 48) * 100 + (data_node1[4] - 48) * 10 + (data_node1[5] - 48) * 1;
            temp1_float = ((float) temp1 * 200) / 1048576 - 50;

            mq21_adc = (data_node1[6] - 48) * 1000 + (data_node1[7] - 48) * 100 + (data_node1[8] - 48) * 10 + (data_node1[9] - 48) * 1;
            rs_mq21 = (1023 / (float) mq21_adc - 1) * 10; // kilo ohm
            mq21_ppm = pow(10, (1.25 - log10(rs_mq21 / 3.66)) / 0.45);
            if (mq21_ppm > 10000) mq21_ppm = 10000;

            mp21_ppm = pow(10, (1.55 - log10(rs_mq21 / 3.66)) / 0.44);
            if (mp21_ppm > 10000) mp21_ppm = 10000;
            node_update = 0;
        }
        ////////////////////////////////////////////////////////////////////////////////////
        if (node_update == 2) {
            temp2 = (data_node2[0] - 48) * 100000 + (data_node2[1] - 48) * 10000 + (data_node2[2] - 48) * 1000 + (data_node2[3] - 48) * 100 + (data_node2[4] - 48) * 10 + (data_node2[5] - 48) * 1;
            temp2_float = ((float) temp2 * 200) / 1048576 - 50;

            mq22_adc = (data_node2[6] - 48) * 1000 + (data_node2[7] - 48) * 100 + (data_node2[8] - 48) * 10 + (data_node2[9] - 48) * 1;
            rs_mq22 = (1023 / (float) mq22_adc - 1) * 10; // kilo ohm
            mq22_ppm = pow(10, (1.25 - log10(rs_mq22 / 3.66)) / 0.45);
            if (mq22_ppm > 10000) mq22_ppm = 10000;
            mp22_ppm = pow(10, (1.55 - log10(rs_mq22 / 3.66)) / 0.44);
            if (mp22_ppm > 10000) mp22_ppm = 10000;
            node_update = 0;
        }

        //////////////////////////////////////////////////////////////////////////////////
        if (node_update == 3) {
            temp3 = (data_node3[0] - 48) * 100000 + (data_node3[1] - 48) * 10000 + (data_node3[2] - 48) * 1000 + (data_node3[3] - 48) * 100 + (data_node3[4] - 48) * 10 + (data_node3[5] - 48) * 1;
            temp3_float = ((float) temp3 * 200) / 1048576 - 50;

            mq23_adc = (data_node3[6] - 48) * 1000 + (data_node3[7] - 48) * 100 + (data_node3[8] - 48) * 10 + (data_node3[9] - 48) * 1;
            rs_mq23 = (1023 / (float) mq23_adc - 1) * 10; // kilo ohm
            mq23_ppm = pow(10, (1.25 - log10(rs_mq23 / 3.66)) / 0.45);
            if (mq23_ppm > 10000) mq23_ppm = 10000;

            mp23_ppm = pow(10, (1.55 - log10(rs_mq23 / 3.66)) / 0.44);
            if (mp23_ppm > 10000) mp23_ppm = 10000;
            node_update = 0;
        }

        //////////////////////////////////////////////////////////////////////////////////   
        //        if (auto_warning == 1){
        if (temp1_float > temp_level2 || mq21_ppm > gas_level2 || mp21_ppm > smoke_level2 || temp2_float > temp_level2 || mq22_ppm > gas_level2 || mp22_ppm > smoke_level2 || temp3_float > temp_level2 || mq23_ppm > gas_level2 || mp23_ppm > smoke_level2) {
            if (warning_level != 2) {
                warning_level = 2;
                verify_call = 0;
                warning = 1;
                BELL = 0;
                printf_mode = printf_uart2;
                printf("%cW%c%c", 'S', 1, 'P'); // chuong dang bat
            }
        } else if (temp1_float > temp_level1 || mq21_ppm > gas_level1 || mp21_ppm > smoke_level1 || temp2_float > temp_level1 || mq22_ppm > gas_level1 || mp22_ppm > smoke_level1 || temp3_float > temp_level1 || mq23_ppm > gas_level1 || mp23_ppm > smoke_level1) {

            ///////////////////////////////////////
            if (temp1_float > temp_level1) {
                if (temp1_old == 0) {
                    temp1_old = temp1_float;
                    ena_send_node1 = 1;
                } else {
                    if (temp1_float - temp1_old > 2) {
                        temp1_old = temp1_float;
                        ena_send_node1 = 1;
                    }
                }
            } else temp1_old = 0;
            //////////////////////////////////////////////
            if (temp2_float > temp_level1) {
                if (temp2_old == 0) {
                    temp2_old = temp2_float;
                    ena_send_node2 = 1;
                } else {
                    if (temp2_float - temp2_old > 2) {
                        temp2_old = temp2_float;
                        ena_send_node2 = 1;
                    }
                }
            } else temp2_old = 0;
            //////////////////////////////////////////////
            if (temp3_float > temp_level1) {
                if (temp3_old == 0) {
                    temp3_old = temp3_float;
                    ena_send_node3 = 1;
                } else {
                    if (temp3_float - temp3_old > 2) {
                        temp3_old = temp3_float;
                        ena_send_node3 = 1;
                    }
                }
            } else temp3_old = 0;
            //////////////////////////////////////////////
            if (warning_level == 0) {
                warning_level = 1;
                if (sim_config == 1) {
                    if (sim_status == 0) //  sim dang ranh
                    {
                        sim_status = 1; // sim dang ban ( dang chuan bi gui tin nhan )
                        printf_mode = printf_uart3;
                        sim_read = 1;
                        HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                        printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                        while (ena_sms == 0);
                        sim_read = 3;
                        printf("WARNING LEVEL 1%c", 0x1a);
                        ena_sms = 0;
                    }
                }
            } else if (warning_level == 2) {
                warning_level = 1;
                BELL = 1;
                printf_mode = printf_uart2;
                printf("%cW%c%c", 'S', 0, 'P'); // chuong dang tat
            }

        } else {
            if (warning_level == 1) {
                warning = 0;
                ena_end_of_warning = 1;
            }
            warning_level = 0;
            temp1_old = 0;
            temp2_old = 0;
            temp3_old = 0;
        }


        if (warning_level == 2) {
            warning = 1;
            if (sim_config == 1) {
                if (verify_call == 0) {
                    if (sim_status == 0) //  sim dang ranh
                    {
                        sim_status = 1; // sim dang ban ( dang chuan bi goi )
                        printf_mode = printf_uart3;
                        sim_read = 2;
                        HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                        printf("ATD0868390442;%c%c", 0x0d, 0x0a);
                    }
                }
            }
        } else if (warning_level == 1) {
            warning = 0;
            if (sim_config == 1) {
                if (sim_status == 0) { //  sim dang ranh
                    /////////////////////////////////////////////////
                    if (ena_send_node1 == 1) {
                        ena_send_node1 = 0;
                        printf_mode = printf_uart3;
                        sim_read = 1;
                        HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                        printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                        while (ena_sms == 0);
                        sim_read = 3;
                        printf("WARNING - NODE 1\r\n+ Temperature: %0.2f oC\r\n+ Gas: %05lu PPM\r\n+ Smoke: %05lu PPM%c", temp1_old, mq21_ppm, mp21_ppm, 0x1a);
                        ena_sms = 0;
                    }
                    if (ena_send_node2 == 1) {
                        ena_send_node2 = 0;
                        printf_mode = printf_uart3;
                        sim_read = 1;
                        HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                        printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                        while (ena_sms == 0);
                        sim_read = 3;
                        printf("WARNING - NODE 2\r\n+ Temperature: %0.2f oC\r\n+ Gas: %05lu PPM\r\n+ Smoke: %05lu PPM%c", temp2_old, mq22_ppm, mp22_ppm, 0x1a);
                        ena_sms = 0;
                    }
                    if (ena_send_node3 == 1) {
                        ena_send_node3 = 0;
                        printf_mode = printf_uart3;
                        sim_read = 1;
                        HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                        printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                        while (ena_sms == 0);
                        sim_read = 3;
                        printf("WARNING - NODE 3\r\n+ Temperature: %0.2f oC\r\n+ Gas: %05lu PPM\r\n+ Smoke: %05lu PPM%c", temp3_old, mq23_ppm, mp23_ppm, 0x1a);
                        ena_sms = 0;
                    }
                }
            }
        } else {
            warning = 0;
        }

        if (ena_send_state_node1 == 1) {
            if (sim_config == 1) {
                if (sim_status == 0) { //  sim dang ranh
                    printf_mode = printf_uart3;
                    sim_read = 1;
                    HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                    printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                    while (ena_sms == 0);
                    sim_read = 3;
                    if (state_node1 == 1) printf("NODE 1 ON%c", 0x1a);
                    else printf("NODE 1 OFF%c", 0x1a);
                    ena_sms = 0;
                    HAL_Delay(200);
                }
            }
            ena_send_state_node1 = 0;
        }

        if (ena_send_state_node2 == 1) {
            if (sim_config == 1) {
                if (sim_status == 0) { //  sim dang ranh
                    printf_mode = printf_uart3;
                    sim_read = 1;
                    HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                    printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                    while (ena_sms == 0);
                    sim_read = 3;
                    if (state_node2 == 1) printf("     NODE 2 ON%c", 0x1a);
                    else printf("     NODE 2 OFF%c", 0x1a);
                    ena_sms = 0;
                    HAL_Delay(200);
                }
            }
            ena_send_state_node2 = 0;
        }

        if (ena_send_state_node3 == 1) {
            if (sim_config == 1) {
                if (sim_status == 0) { //  sim dang ranh
                    printf_mode = printf_uart3;
                    sim_read = 1;
                    HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                    printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                    while (ena_sms == 0);
                    sim_read = 3;
                    if (state_node3 == 1) printf("          NODE 3 ON%c", 0x1a);
                    else printf("          NODE 3 OFF%c", 0x1a);
                    ena_sms = 0;
                    HAL_Delay(200);
                }
            }
            ena_send_state_node3 = 0;
        }

        if (ena_end_of_warning == 1) {
            if (sim_config == 1) {
                if (sim_status == 0) //  sim dang ranh
                {
                    sim_status = 1; // sim dang ban ( dang chuan bi gui tin nhan )
                    printf_mode = printf_uart3;
                    sim_read = 1;
                    HAL_UART_Receive_IT(&huart3, byte_rx3, 1);
                    printf("AT+CMGS=%c0868390442%c%c%c", 0x22, 0x22, 0x0d, 0x0a);
                    while (ena_sms == 0);
                    sim_read = 3;
                    printf("END OF WARNING%c", 0x1a);
                    ena_sms = 0;
                }
            }
            ena_end_of_warning = 0;
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
            if (warning == 0) {
                HAL_Delay(10);
                if (WR_BT == 0) {
                    while (WR_BT == 0);
                    BELL = ~BELL;
                    printf("%cW%c%c", 'S', (~BELL)& 0x01, 'P');
                }
            }
        }

        if (ena_send_warning == 1) printf("%cW%c%c", 'S', 1, 'P');

        if ((control_devices & 0x01) == 0) RELAY1 = 1;
        else RELAY1 = 0;

        if ((control_devices & 0x02) == 0) RELAY2 = 1;
        else RELAY2 = 0;

        if ((control_devices & 0x04) == 0) RELAY3 = 1;
        else RELAY3 = 0;

        if ((control_devices & 0x08) == 0) RELAY4 = 1;
        else RELAY4 = 0;

        dem++;
        if (dem % 35 == 0) {
            check++;
            printf_mode = printf_uart2;
            printf("%c%05.2f%05lu%05lu%05.2f%05lu%05lu%05.2f%05lu%05lu%05u%c", 'S', temp1_float, (unsigned long) mq21_ppm, (unsigned long) mp21_ppm, temp2_float, (unsigned long) mq22_ppm, (unsigned long) mp22_ppm, temp3_float, (unsigned long) mq23_ppm, (unsigned long) mp23_ppm, check, 'P');
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

    }
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV2;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_SPI2_Init(void) {
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
    if (HAL_SPI_Init(&hspi2) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_TIM1_Init(void) {

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    htim1.Instance = TIM1;
    htim1.Init.Prescaler = 72;
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 65535;
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_TIM2_Init(void) {

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 7200;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 65535;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_TIM3_Init(void) {

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 36000;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 65535;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 512000;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_USART3_UART_Init(void) {
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart3) != HAL_OK) {
        Error_Handler();
    }
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2 | MD0_Pin | MD1_Pin | RELAY4_Pin
            | RELAY3_Pin | RELAY2_Pin | GPIO_PIN_6 | GPIO_PIN_7
            | RELAY1_Pin | GPIO_PIN_9, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, PA8_Pin | LED3_Pin | LED2_Pin | LED1_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5
            | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_2 | MD0_Pin | MD1_Pin | RELAY4_Pin
            | RELAY3_Pin | RELAY2_Pin | GPIO_PIN_6 | GPIO_PIN_7
            | RELAY1_Pin | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = PA8_Pin | LED3_Pin | LED2_Pin | LED1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

struct __FILE {
    int handle;
};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
    (void) (f);
    if      (printf_mode == printf_uart1)   HAL_UART_Transmit(&huart1, (uint8_t *) & ch, 1, HAL_MAX_DELAY);
    else if (printf_mode == printf_uart2)   HAL_UART_Transmit(&huart2, (uint8_t *) & ch, 1, HAL_MAX_DELAY);
    else if (printf_mode == printf_uart3)   HAL_UART_Transmit(&huart3, (uint8_t *) & ch, 1, HAL_MAX_DELAY);
    else if (printf_mode == printf_lcd_i2c) LCD_I2C_CHAR(ch);
    return ch;
}

void Error_Handler(void) {
    __disable_irq();
    while (1) {
    }
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
         ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
