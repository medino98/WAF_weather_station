#ifndef AS5600_H_
#define AS5600_H_

#include <driver/gpio.h>
#include <driver/i2c.h>
#include <math.h>

//Some general setup for the I2C lines
#define I2C_MASTER_SCL_IO 27
#define I2C_MASTER_SDA_IO 26
#define I2C_MASTER_NUM I2C_NUM_1
#define I2C_MASTER_FREQ_HZ 100000

//Setting the AS5600 addr, and the raw angle register
#define AS5600_ADDR 0x36
#define AS5600_ANGLE_REG 0x0E

/**
 * @brief Initialize the I2C peripheral to some default value.
 */
void i2c_master_init();

/**
 * @brief Read the raw angle value from the as5600 sensor.
 *
 * @param[out] angle The varible to put the scaled angle value into.
 * 
 * @return Returns the scaled angle value (0-359°) in the passed parameter. 
 * 
 */
esp_err_t as5600_read_angle(uint16_t *angle);

#endif // AS5600_H_

