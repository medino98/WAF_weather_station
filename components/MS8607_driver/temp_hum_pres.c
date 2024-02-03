#include "temp_hum_pres.h"

static esp_err_t read_temp()
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (TEMP_HUM_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x50, true); 
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

static esp_err_t read_adc_value()
{
    uint8_t data[3];
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (TEMP_HUM_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x00, true); 

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (TEMP_HUM_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, &data[0], I2C_MASTER_ACK);
    i2c_master_read_byte(cmd, &data[1], I2C_MASTER_ACK);
    i2c_master_read_byte(cmd, &data[2], I2C_MASTER_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    uint32_t temp = (data[0]<<16)|(data[1]<<8)|data[2];

    printf("Temp: %li \n", temp);

    return ret;
}

static esp_err_t reset_dev()
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (TEMP_HUM_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x1E, true); 
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
} 

void app_main() {
    i2c_master_init();
    printf("The return value of the reset_dev is: 0x%x\r\n", reset_dev());
    vTaskDelay(pdMS_TO_TICKS(10));

    while (1) {
        printf("The return value of read_temp is: 0x%x\r\n", read_temp());
        vTaskDelay(pdMS_TO_TICKS(10)); // Adjust the delay as needed
        printf("The return value of read_adc_value is: 0x%x\r\n", read_adc_value());
        vTaskDelay(pdMS_TO_TICKS(2000)); // Adjust the delay as needed
    
    }
}
