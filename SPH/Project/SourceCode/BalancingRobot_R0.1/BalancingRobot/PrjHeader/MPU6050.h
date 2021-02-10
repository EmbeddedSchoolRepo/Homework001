/*
 * MPU6050.h
 *
 * Created: 2020-12-01 오후 1:42:19
 *  Author: SPH
 */ 
#ifndef MPU6050_H_
#define MPU6050_H_

#include "PrjHeader.h"
#include "uart.h"
#include "twi.h"

/************************************************************************/
/*                  MPU6050 Scale Factor                                */
/************************************************************************/
#define ACCEL_LSB_FS2G 16384
#define ACCEL_LSB_FS4G 8192
#define ACCEL_LSB_FS8G 4096
#define ACCEL_LSB_FS16G 2048

#define GYRO_LSB_FS250 131
#define GYRO_LSB_FS500 65.5
#define GYRO_LSB_FS1000 32.8
#define GYRO_LSB_FS2000 16.4

/************************************************************************/
/*                MPU6050 Register Address Definition                   */
/************************************************************************/
/*SELF Function TEST Register Address*/
#define SELF_TEST_X 0x0D
#define SELF_TEST_Y 0x0E
#define SELF_TEST_Z 0x0F
#define SELF_TEST_A 0x10 //Only Accelerometer

/*Sampling Rate Devision Register*/
#define SMPLRT_DIV 0x19
#define SMPLRT_DIV_LEN 7

/*Configuration Register*/
//Configuration Register & Setting Value
#define CONFIG 0x1A
#define DLPF_CFG_LEN 3
#define DLPF_CFG_BIT 2
#define DLPF_CFG0 0 //Accel Delay : 0, Gyro Delay : 0.98
#define DLPF_CFG1 1 //Accel Delay : 2.0, Gyro Delay : 1.9
#define DLPF_CFG2 2 //Accel Delay : 3.0, Gyro Delay : 2.8
#define DLPF_CFG3 3 //Accel Delay : 4.9, Gyro Delay : 4.8
#define DLPF_CFG4 4 //Accel Delay : 8.5, Gyro Delay : 8.3
#define DLPF_CFG5 5 //Accel Delay : 13.8, Gyro Delay : 13.4
#define DLPF_CFG6 6 //Accel Delay : 19.0, Gyro Delay : 18.6
#define DLPF_CFG7 7 //Accel Delay : rvd, Gyro Delay : rvd

#define EXT_SYNC_LEN 3
#define EXT_SYNC_BIT 5
#define EXT_SYNC_SET0 0 //InputDisable
#define EXT_SYNC_SET1 1 //Temp Sensor Out L
#define EXT_SYNC_SET2 2 //GYRO_X OUT L
#define EXT_SYNC_SET3 3 //GYRO_Y OUT L
#define EXT_SYNC_SET4 4 //GYRO_Z OUT L
#define EXT_SYNC_SET5 5 //ACCEL_X OUT L
#define EXT_SYNC_SET6 6 //ACCEL_Y OUT L
#define EXT_SYNC_SET7 7 //ACCEL_Z OUT L

//GYRO Configuration Register & Setting Value
#define GYRO_CONFIG 0x1B
#define GYRO_FS_SEL_LEN 2
#define GYRO_FS_SEL_BIT 4
#define GYRO_FS_SEL250 0 //+-250degree/s
#define GYRO_FS_SEL500 1 //+-500degree/s
#define GYRO_FS_SEL1000 2 //+-1000degree/s
#define GYRO_FS_SEL2000 3 //+-2000degree/s

#define GYRO_XG_ST_LEN 1
#define GYRO_XG_ST_BIT 7
#define GYRO_XG_ST_SET 1
#define GYRO_XG_ST_RESET 0

#define GYRO_YG_ST_LEN 1
#define GYRO_YG_ST_BIT 6
#define GYRO_YG_ST_SET 1
#define GYRO_YG_ST_RESET 0

#define GYRO_ZG_ST_LEN 1
#define GYRO_ZG_ST_BIT 5
#define GYRO_ZG_ST_SET 1
#define GYRO_ZG_ST_RESET 0

#define ACCEL_CONFIG 0x1C
#define ACCEL_AFS_SEL_LEN 2
#define ACCEL_AFS_SEL_BIT 4
#define ACCEL_AFS_SEL2G 0 //+-2G
#define ACCEL_AFS_SEL4G 1 //+-4G
#define ACCEL_AFS_SEL8G 2 //+-8G
#define ACCEL_AFS_SEL16G 3 //+-16G

#define ACCEL_XA_ST_LEN 1
#define ACCEL_XA_ST_BIT 7
#define ACCEL_XA_ST_SET 1
#define ACCEL_XA_ST_RESET 0

#define ACCEL_YA_ST_LEN 1
#define ACCEL_YA_ST_BIT 6
#define ACCEL_YA_ST_SET 1
#define ACCEL_YA_ST_RESET 0

#define ACCEL_ZA_ST_LEN 1
#define ACCEL_ZA_ST_BIT 5
#define ACCEL_ZA_ST_SET 1
#define ACCEL_ZA_ST_RESET 0

/*FIFO Register*/
#define FIFO_EN 0x23
#define SLV0_FIFO_EN_LEN 1
#define SLV0_FIFO_EN_BIT 0

#define SLV1_FIFO_EN_LEN 1
#define SLV1_FIFO_EN_BIT 1

#define SLV2_FIFO_EN_LEN 1
#define SLV2_FIFO_EN_BIT 2


#define ACCEL_FIFO_EN_LEN 1
#define ACCEL_FIFO_EN_BIT 3

#define ZG_FIFO_EN_LEN 1
#define ZG_FIFO_EN_BIT 4

#define YG_FIFO_EN_LEN 1
#define YG_FIFO_EN_BIT 5

#define XG_FIFO_EN_LEN 1
#define XG_FIFO_EN_BIT 6

#define TEMP_FIFO_EN_LEN 1
#define TEMP_FIFO_EN_BIT 7

#define FIFO_COUNTH 0x72
#define FIFO_COUNTL 0x73
#define FIFO_R_W 0x74

/*I2C Register*/
#define I2C_MST_CTRL 0x24

#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_REG 0x26
#define I2C_SLV0_CTRL 0x27
#define I2C_SLV0_DO 0x63

#define I2C_SLV1_ADDR 0x28
#define I2C_SLV1_REG 0x29
#define I2C_SLV1_CTRL 0x2A
#define I2C_SLV1_DO 0x64

#define I2C_SLV2_ADDR 0x2B
#define I2C_SLV2_REG 0x2C
#define I2C_SLV2_CTRL 0x2D
#define I2C_SLV2_DO 0x65

#define I2C_SLV3_ADDR 0x2E
#define I2C_SLV3_REG 0x2F
#define I2C_SLV3_CTRL 0x30
#define I2C_SLV3_DO 0x66

#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG 0x32
#define I2C_SLV4_DO 0x33
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DI 0x35

#define I2C_MST_STATUS 0x36

#define I2C_MST_DELAY_CTRL 0x67


/*Interrupt Register*/
#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A

#define FIFO_OVF_INT_EN 4
#define FIFO_OVF_INT_EN_LEN 1

#define I2C_MST_INT_EN 3
#define I2C_MST_INT_EN_LEN 1

#define DATA_RDY_INT_EN 0
#define DATA_RDY_INT_EN_LEN 1

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

/*External Sensor Data*/
#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60

/*ETC Register*/
#define SIGNAL_PATH_RESET 0x68
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define CLKSEL_LEN 3
#define CLKSEL_BIT 2
#define CLKSEL0 0
#define CLKSEL1 1
#define CLKSEL2 2
#define CLKSEL3 3
#define CLKSEL4 4
#define CLKSEL5 5
#define CLKSEL6 6
#define CLKSEL7 7

#define CYCLE_LEN 1
#define CYCLE_BIT 5

#define SLEEP_MODE_LEN 1
#define SLEEP_MODE_BIT 6

#define DEVICE_RESET_LEN 1
#define DEVICE_RESET_BIT 7

#define PWR_MGMT_2 0x6C
#define WHO_AM_I 0x75

/************************************************************************/
/*                  MPU6050 Axis Structure Definition                   */
/************************************************************************/
typedef struct  
{
	int16_t Xaxis;
	int16_t Yaxis;
	int16_t Zaxis;
}Axis_Data_Struct;

typedef Axis_Data_Struct* pAxis_Data;

/************************************************************************/
/*                    MPU6050 I2C Address Definition                    */
/************************************************************************/
#define MPU6050_ADD0 0x68
#define MPU6050_ADD1 0x69

/************************************************************************/
/*                  MPU6050.c USR Function Definition                   */
/************************************************************************/
//void Calc_Accel_RollPitch(pAxis_Data AccelData, pAngle_3Dim Accel_Angle);
//void get_MPU6050_RawData(Axis_Data_Struct* Accel_Data, Axis_Data_Struct* Gyro_Data);

uint8_t MPU6050_ReadBytes(uint8_t reg_addr, uint8_t len, uint8_t* pData);
uint8_t MPU6050_ReadByte(uint8_t reg_addr, uint8_t* pData);
void MPU6050_WriteBytes(uint8_t reg_addr, uint8_t len, uint8_t* pData);
void MPU6050_WriteByte(uint8_t reg_addr, uint8_t data);
void MPU6050_WriteBits(uint8_t reg_addr, uint8_t bit, uint8_t len, uint8_t data);

void RunMPU6050(void);
void InitMPU6050(void);

pAngle_3Dim getAcceleroData(void);
pAngle_3Dim getGyroData(void);

#endif /* MPU6050_H_ */