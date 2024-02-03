#ifndef TEMP_HUM_PRES_H_
#define TEMP_HUM_PRES_H_

#include <stdio.h>
#include <driver/i2c.h>
#include <math.h>

#define I2C_MASTER_SCL_IO 27
#define I2C_MASTER_SDA_IO 26
#define I2C_MASTER_NUM I2C_NUM_1
#define I2C_MASTER_FREQ_HZ 100000

#define TEMP_HUM_ADDR 0x76 // I2C address of the temp and pressure sensor part
#define REL_HUM_ADDR 0x40 // I2C address of relative humidity sensor part




#endif // TEMP_HUM_PRES_H_

