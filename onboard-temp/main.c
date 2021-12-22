#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main(){
    stdio_init_all();

    adc_init(); // initialize ADC hardware
    adc_set_temp_sensor_enabled(true); // enable onboard temperature sensor
    adc_select_input(4); // select onboard temperature sensor channel

    float temperature, voltage;
    while (1) {
        // 12-bit quantization conversion, max. value ADC_VREF (3.3V)
        // 2 ^ 12 == (1 << 12)
        voltage = adc_read() * (3.3f / (1 << 12));
        // Non-linear relationship between voltage and temperature in Celsius from datasheet
        temperature = 27.0 - (voltage - 0.706) / 0.001721;
        printf("%.02f\n", temperature);
        sleep_ms(500);
    }
}

