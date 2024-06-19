

void i2c_start(void)
{
    OUTPUT_PIN_B7 = 1;
    delay_us(1);
    OUTPUT_PIN_B6 = 1;
    delay_us(1);
    OUTPUT_PIN_B7 = 0;
    delay_us(1);
    OUTPUT_PIN_B6 = 0;
}

void i2c_stop(void)
{
    OUTPUT_PIN_B7 = 0;
    delay_us(1);
    OUTPUT_PIN_B6 = 0;
    delay_us(1);
    OUTPUT_PIN_B6 = 1;
    delay_us(1);
    OUTPUT_PIN_B7 = 1;
}

void i2c_write(unsigned char DATA)
{
    unsigned char i,j;
    for(i=0;i<=8;i++)
    {
        if((DATA<<i) & 0x80) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,1);    // MSB fist   
        else            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,0); 
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,1);
        delay_us(1);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,0);
        delay_us(1);
    }
}



//unsigned char i2c_read(unsigned char ACK)
//{
//    unsigned char DATA;
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,0);
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);      
//    for (unsigned char i=0;i<8;i++)
//    {
//        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,1);
//        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7); == 1) DATA = (unsigned char)(DATA << 1) | 1;
//        else            DATA = (unsigned char)(DATA << 1);
//        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,0);
//        __delay_us(10);
//    }
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);    
//    if (ACK == 1) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,0);
//    else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,1);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,1);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,0);
//    return DATA;
//}


//void i2c_start(void)
//{
//    PIN_B7 = 1;
//    for (unsigned char a=0; a<200; a++);// delay
//    PIN_B6 = 1;
//    for (unsigned char a=0; a<200; a++);// delay
//    PIN_B7 = 0;
//    for (unsigned char a=0; a<200; a++);// delay
//    PIN_B6 = 0;
//}

//void i2c_stop(void)
//{
//    PIN_B7 = 0;
//    for (unsigned char a=0; a<200; a++);// delay
//    PIN_B6 = 0;
//    for (unsigned char a=0; a<200; a++);// delay
//    PIN_B6 = 1;
//    for (unsigned char a=0; a<200; a++);// delay
//    PIN_B7 = 1;
//}

//void i2c_write(unsigned char DATA)
//{
//    unsigned char i,j;
//    for(i=0;i<=8;i++)
//    {
//        if((DATA<<i) & 0x80) PIN_B7 = 1;   // MSB fist   
//        else            PIN_B7 = 0;
//        PIN_B6 = 1;
//        for (unsigned char a=0; a<200; a++)j++;// delay
////        delay_us(1);
//        PIN_B6 = 0;
//    }
//}
