/*
 * mtch6102.h
 *
 * Created: 2021-01-12 오전 9:06:47
 *  Author: KKS
 */ 


#ifndef MTCH6102_H_
#define MTCH6102_H_


#define TOUCHPAD_OK           0x00
#define TOUCHPAD_INIT_ERROR   0xFF

#define TOUCHPAD_DEVICE_SLAVE_ADDR   0x25 

#define TOUCHPAD_REG_FW_MAJOR                     0x00
#define TOUCHPAD_REG_FW_MINOR                     0x01
#define TOUCHPAD_REG_APP_ID_LSB                   0x02
#define TOUCHPAD_REG_APP_ID_MSB                   0x03
#define TOUCHPAD_REG_CMD                          0x04
#define TOUCHPAD_REG_MODE                         0x05
#define TOUCHPAD_REG_MODE_CON                     0x06

#define TOUCHPAD_REG_TOUCH_STATE                  0x10 // Touch state
#define TOUCHPAD_REG_TOUCH_X                      0x11 // Touch X
#define TOUCHPAD_REG_TOUCH_Y                      0x12 // Touch Y
#define TOUCHPAD_REG_TOUCH_LSB                    0x13 // Touch XY
#define TOUCHPAD_REG_GESTURE_STATE                0x14 // Gestrure state
#define TOUCHPAD_REG_GESTURE_DIAG                 0x15 // Gestrure diagnostic

#define TOUCHPAD_REG_NUM_OF_X_CHANNELS            0x20 // Number of x channels
#define TOUCHPAD_REG_NUM_OF_Y_CHANNELS            0x21 // Number of y channels
#define TOUCHPAD_REG_SCAN_COUNT                   0x22
#define TOUCHPAD_REG_TOUCH_THR_X                  0x23
#define TOUCHPAD_REG_TOUCH_THR_Y                  0x24

#define TOUCHPAD_REG_ACTIVE_PERIOD_LSB            0x25
#define TOUCHPAD_REG_ACTIVE_PERIOD_MSB            0x26
#define TOUCHPAD_REG_IDLE_PERIOD_LSB              0x27
#define TOUCHPAD_REG_IDLE_PERIOD_MSB              0x28
#define TOUCHPAD_REG_IDLE_TIMEOUT                 0x29
#define TOUCHPAD_REG_HYSTERESIS                   0x2A

#define TOUCHPAD_REG_DEBOUNCE_UP                  0x2B
#define TOUCHPAD_REG_DEBOUNCE_DOWN                0x2C
#define TOUCHPAD_REG_FILTER_TYPE                  0x31
#define TOUCHPAD_REG_FILTER_THR                   0x32
#define TOUCHPAD_REG_LARGE_ACTIVATION_THR_LSB     0x35
#define TOUCHPAD_REG_LARGE_ACTIVATION_THR_MSB     0x36

#define TOUCHPAD_REG_HORIZONTAL_SWIPE_DISTANCE    0x37 // Horisontal swipe distance
#define TOUCHPAD_REG_VERTICAL_SWIPE_DISTANCE      0x38 // Vertical swipe distance
#define TOUCHPAD_REG_SWIPE_HOLD_BOUNDARY          0x39 // Swipe hold boundary
#define TOUCHPAD_REG_TAP_DISTANCE                 0x3A // Tap distance
#define TOUCHPAD_REG_DISTANCE_BETWEEN_TAPS        0x3B // Distance between taps
#define TOUCHPAD_REG_TAP_HOLD_TIME_LSB            0x3C // Tap hold time (LSB)
#define TOUCHPAD_REG_TAP_HOLD_TIME_MSB            0x3D // Tap hold time (MSB)
#define TOUCHPAD_REG_GESTURE_CLICK_TIME           0x3E // Gesture click time
#define TOUCHPAD_REG_SWIPE_HOLD_THRESHOLD         0x3F // Swipe hold treshold
#define TOUCHPAD_REG_MIN_SWIPE_VELOCITY           0x40 // Min swipe velecity
#define TOUCHPAD_REG_HORIZONTAL_GESTURE_ANGLE     0x41 // Horisontal gesture angle
#define TOUCHPAD_REG_VERTICAL_GESTURE_ANGLE       0x42 // Vertical gesture angle

#define TOUCHPAD_MODE_STANDBY    0x00
#define TOUCHPAD_MODE_GESTURE    0x01
#define TOUCHPAD_MODE_TOUCH_ONLY 0x02
#define TOUCHPAD_MODE_FULL       0x03
#define TOUCHPAD_MODE_RAW_ADC    0x04

#define TOUCHPAD_RAWADC_TYPE_RES_1_2 0x00
#define TOUCHPAD_RAWADC_TYPE_RES_1   0x01
#define TOUCHPAD_RAWADC_TYPE_RES_2   0x02

#define TOUCHPAD_CMD_NV_STORAGE_WRITE   0x80
#define TOUCHPAD_CMD_RESTORE_DEF_CONFIG 0x40
#define TOUCHPAD_CMD_CONFIG_CTRL        0x20
#define TOUCHPAD_CMD_EXECUTE_MANU_TEST  0x08
#define TOUCHPAD_CMD_FORCE_BASELINE     0x01

#define TOUCHPAD_PERIOD_10ms   0x0142
#define TOUCHPAD_PERIOD_20ms   0x0284
#define TOUCHPAD_PERIOD_50ms   0x064C
#define TOUCHPAD_PERIOD_1000ms 0x0C99

#define TOUCHPAD_TOUCH_IS_PRESENT      0x01
#define TOUCHPAD_GESTURE_IS_PRESENT    0x02
#define TOUCHPAD_LARGE_ACT_IS_PRESENT  0x04

#define TOUCHPAD_GS_NO_GESTURE_PRESENT    0x00 // No Gesture Present
#define TOUCHPAD_GS_SINGLE_CLICK          0x10 // Single Click
#define TOUCHPAD_GS_CLICK_AND_HOLD        0x11 // Click and Hold
#define TOUCHPAD_GS_DOUBLE_CLICK          0x20 // Double Click
#define TOUCHPAD_GS_DOWN_SWIPE            0x31 // Down Swipe
#define TOUCHPAD_GS_DOWN_SWIPE_AND_HOLD   0x32 // Down Swipe and Hold
#define TOUCHPAD_GS_RIGHT_SWIPE           0x41 // Right Swipe
#define TOUCHPAD_GS_RIGHT_SWIPE_AND_HOLD  0x42 // Right Swipe and Hold
#define TOUCHPAD_GS_UP_SWIPE              0x51 // Up Swipe
#define TOUCHPAD_GS_UP_SWIPE_AND_HOLD     0x52 // Up Swipe and Hold
#define TOUCHPAD_GS_LEFT_SWIPE            0x61 // Left Swipe
#define TOUCHPAD_GS_LEFT_SWIPE_AND_HOLD   0x62 // Left Swipe and Hold

#define TOUCHPAD_EVENT_TOUCH 1
#define TOUCHPAD_EVENT_GESTURE 2
#define TOUCHPAD_NO_EVENT 0

#define TOUCHPAD_GD_CLICK_TIMEOUT           0x01 // Click Timeout
#define TOUCHPAD_GD_SWIPE_TIMEOUT           0x02 // Swipe Timeout
#define TOUCHPAD_GD_GENERAL_TIMEOUT         0x03 // General Timeout
#define TOUCHPAD_GD_CLICK_THR_EXCEEDED      0x04 // Click Threshold Exceeded
#define TOUCHPAD_GD_SWIPE_THR_EXCEEDED      0x05 // Swipe Threshold Exceeded
#define TOUCHPAD_GD_SWIPE_HOLD_THR          0x06 // Swipe and Hold Threshold Exceeded
#define TOUCHPAD_GD_SWIPE_OPPOSITE_DIR_THR  0x07 // Swipe Opposite Direction Threshold Exceeded
#define TOUCHPAD_GD_SWIPE_HOLD_VALUE        0x09 // Swipe and Hold Value Exceeded
#define TOUCHPAD_GD_OUTSIDE_SWIPE           0x0A // Outside Swipe Angle

#define I2C_WRITE   0
#define I2C_READ   1

uint8_t mtch6102_read_8bit(uint8_t reg_address);
void mtch6102_write_8bit(uint8_t reg_address ,uint8_t* i2c_data_buffer);
void mtch6102_read_xy_pos(void);
void mtch6102_read_touch_status(void);
void mtch6102_dump_reigster(void);

extern volatile uint8_t phase;

typedef struct 
{
	uint16_t xpos;
	uint16_t ypos;
	uint8_t lsb;
	uint16_t x_11_4;
	uint16_t y_11_4;
}mtch6102_pos;

enum touch_status
{
	touch_is_present = 1,
	gesture_is_present,
	touch_gesture_present,
	large_act_is_present,
	touch_large_present,
	gesture_large_present,
	touch_gesture_large_present
};

#endif /* MTCH6102_H_ */