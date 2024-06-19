

//#include "main.h"

void pulse_ena_pin(void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1); //E PIN
	delay_us(20);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0); //E PIN
	delay_us(20);
}

void lcd_send_nibbles(unsigned char nibbles, unsigned char type) {
	if (type == 1) //command
			{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1); //RS PIN
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0); //RW PIN
	} else if (type == 0) // data
			{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0); //RS PIN
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0); //RW PIN
	} else {
	};
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (nibbles >> 3) & (0x01)); //D7 PIN
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (nibbles >> 2) & (0x01)); //D6 PIN
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (nibbles >> 1) & (0x01)); //D5 PIN
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (nibbles) & (0x01));	  //D4 PIN
	pulse_ena_pin();
}

void lcd_cmd(unsigned char cmd) {
	lcd_send_nibbles(cmd >> 4, 0);
	lcd_send_nibbles(cmd, 0);
}

void lcd_init(void) {
	HAL_Delay(20);
	lcd_send_nibbles(0x03, 0);
	HAL_Delay(5);
	lcd_send_nibbles(0x03, 0);
	HAL_Delay(1);
	lcd_send_nibbles(0x03, 0);
	lcd_send_nibbles(0x02, 0);
	lcd_cmd(0x28);
	lcd_cmd(0x08);
	lcd_cmd(0x01);
	HAL_Delay(2);
	lcd_cmd(0x0C);
	lcd_cmd(0x80);
}

void lcd_char(unsigned char char_data) {
	lcd_send_nibbles(char_data >> 4, 1);
	lcd_send_nibbles(char_data, 1);
}

void lcd_string(uint8_t *str) {
	while ((*str) != 0) {
		lcd_char(*str);
		str++;
	}
}
void lcd_xy(unsigned char x, unsigned char y) {
	if (y <= 4 && y > 0 && x > 0 && x <= 20) {
		if (y == 1)
			lcd_cmd(0x7F + x);
		else if (y == 2)
			lcd_cmd(0xBF + x);
		else if (y == 3)
			lcd_cmd(0x93 + x);
		else if (y == 4)
			lcd_cmd(0xD3 + x);
	}
}