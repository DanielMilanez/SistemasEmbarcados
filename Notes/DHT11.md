```C
    void ReadDHT(void);
    void StartDHT11(void);
    void SetPinMode(GPIO_TypeDef* port, uint16_t pin, uint32_t mode);

    int main(void){
        // Outros parametros de inicialização
        HAL_TIM_Base_Start(&htim6);
        StartDHT11();

        while(1){
            ReadDHT();
        }
    }

    // DHT11
    void StartDHT11(void){
        SetPinMode(DHT11_GPIO_Port, DHT11_Pin, GPIO_MODE_OUTPUT_PP);
        HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_RESET);
        HAL_Delay(20);
        HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET);
        HAL_Delay(1);
        SetPinMode(DHT11_GPIO_Port, DHT11_Pin, GPIO_MODE_INPUT);
    }

    void SetPinMode(GPIO_TypeDef* port, uint16_t pin, uint32_t mode){
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = pin;
        GPIO_InitStruct.Mode = mode;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(port, &GPIO_InitStruct);
    }

    void ReadDHT(void){
        uint16_t read[2], data[42];

        while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin));
        while(!HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin));

        __HAL_TIM_SET_COUNTER(&htim6, 0);

        for (int i = 0; i < 42; ++i) {
            while(!HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin));
            read[0] = __HAL_TIM_GET_COUNTER(&htim6);

            while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin));
            read[1] = __HAL_TIM_GET_COUNTER(&htim6);

            data[i] = read[1] - read[0];
        }

        for (int i = 0; i < 40; ++i){
            if ((data[i + 2] >= 20) && (data[i] <= 32)) bitsDHT[i] = 0;
            else if ((data[i] >= 65) && (data[i] <= 75)) bitsDHT[i] = 1;
        }

        for (int i = 0; i < 8; ++i){
            temp += bitsDHT[i + 16] << (7 - i);
            umid += bitsDHT[i] << (7 - i);
        }
    }
```
