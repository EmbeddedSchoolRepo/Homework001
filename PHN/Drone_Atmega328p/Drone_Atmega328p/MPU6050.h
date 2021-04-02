/*
 * MPU6050.h
 *
 * Created: 2021-01-09 오전 8:13:59
 *  Author: phn15
 */ 



#ifndef MPU6050_H_
#define MPU6050_H_

#define I2C_WRITE   0
#define I2C_READ   1


#define MPU6050_ADDR0 0x68
#define MPU6050_ADDR1 0x69

#define XG_OFFS_TC 0x00
#define YG_OFFS_TC 0x01
#define ZG_OFFS_TC 0x02
#define X_FINE_GAIN 0x03
#define Y_FINE_GAIN 0x04
#define Z_FINE_GAIN 0x05
#define XA_OFFS_H 0x06
#define XA_OFFS_L_TC 0x07
#define YA_OFFS_H 0x08
#define YA_OFFS_L_TC 0x09
#define ZA_OFFS_H 0x0A
#define ZA_OFFS_L_TC 0x0B
#define XG_OFFS_USRH 0x13
#define XG_OFFS_USRL 0x14
#define YG_OFFS_USRH 0x15
#define YG_OFFS_USRL 0x16
#define ZG_OFFS_USRH 0x17
#define ZG_OFFS_USRL 0x18
#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define FF_THR 0x1D
#define FF_DUR 0x1E
#define MOT_THR 0x1F
#define MOT_DUR 0x20
#define ZRMOT_THR 0x21
#define ZRMOT_DUR 0x22
#define FIFO_EN 0x23
#define I2C_MST_CTRL 0x24
#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_REG 0x26
#define I2C_SLV0_CTRL 0x27
#define I2C_SLV1_ADDR 0x28
#define I2C_SLV1_REG 0x29
#define I2C_SLV1_CTRL 0x2A
#define I2C_SLV2_ADDR 0x2B
#define I2C_SLV2_REG 0x2C
#define I2C_SLV2_CTRL 0x2D
#define I2C_SLV3_ADDR 0x2E
#define I2C_SLV3_REG 0x2F
#define I2C_SLV3_CTRL 0x30
#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG 0x32
#define I2C_SLV4_DO 0x33
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DI 0x35
#define I2C_MST_STATUS 0x36
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define DMP_INT_STATUS 0x39

//Configuration Register & Setting Value
#define CONFIG 0x1A
#define DLPF_CFG_BIT 2
#define DLPF_CFG_LENGTH 3
#define DLPF_CFG0 0 //Accel Delay : 0, Gyro Delay : 0.98
#define DLPF_CFG1 1 //Accel Delay : 2.0, Gyro Delay : 1.9
#define DLPF_CFG2 2 //Accel Delay : 3.0, Gyro Delay : 2.8
#define DLPF_CFG3 3 //Accel Delay : 4.9, Gyro Delay : 4.8
#define DLPF_CFG4 4 //Accel Delay : 8.5, Gyro Delay : 8.3
#define DLPF_CFG5 5 //Accel Delay : 13.8, Gyro Delay : 13.4
#define DLPF_CFG6 6 //Accel Delay : 19.0, Gyro Delay : 18.6
#define DLPF_CFG7 7 //Accel Delay : rvd, Gyro Delay : rvd

//GYRO Configuration Register & Setting Value
#define GYRO_CONFIG 0x1B
#define GYRO_FS_SEL_BIT      4
#define GYRO_FS_SEL_LENGTH   2
#define GYRO_FS_SEL250 0 //+-250degree/s
#define GYRO_FS_SEL500 1 //+-500degree/s
#define GYRO_FS_SEL1000 2 //+-1000degree/s
#define GYRO_FS_SEL2000 3 //+-2000degree/s

//ACCEL Configuration Register & Setting Value
#define ACCEL_CONFIG 0x1C
#define ACCEL_AFS_SEL_BIT 4
#define ACCEL_AFS_SEL_LENGTH 2
#define ACCEL_AFS_SEL2G 0 //+-2G
#define ACCEL_AFS_SEL4G 1 //+-4G
#define ACCEL_AFS_SEL8G 2 //+-8G
#define ACCEL_AFS_SEL16G 3 //+-16G

/*Interrupt Register*/
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A

/*Accelerometer Data Out Register*/
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C

#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E

#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

/*Temperature Data Out Register*/
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42

/*Gyroscope Data Out Register*/
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44

#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46

#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define SMPLRT_DIV 0x19

//PWR_MGMT_1
#define PWR_MGMT_1 0x6B
#define CLKSEL_BIT 2
#define CLKSEL_LENGTH 3
#define CLKSEL0 0	//8MHz
#define CLKSEL1 1	//PLL with X axis gyro
#define CLKSEL2 2	//PLL with Y axis gyro
#define CLKSEL3 3	//PLL with Z axis gyro
#define CLKSEL4 4	//PLL with external 32.768kHz
#define CLKSEL5 5	//PLL with external 32.768kHz
#define CLKSEL6 6	//Rvd
#define CLKSEL7 7	//Stops the clock and keeps the timing generator in reset
#define SLEEP 6
/*User Define*/


void mpu6050_init(void);
uint8_t mpu6050_readBytes(uint8_t regAddr, uint8_t length, uint8_t *data);
void mpu6050_writeByte(uint8_t regAddr,uint8_t data);
uint8_t mpu6050_readBit(uint8_t regAddr, uint8_t bitNum, uint8_t *data);
void mpu6050_writeBits(uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
void mpu6050_setSleepDisable(void);
void mpu6050_getRawValue(void);
void mpu6050_viewValue(float ax,float ay,float az, float gx,float gy,float gz);
#endif /* MPU6050_H_ */