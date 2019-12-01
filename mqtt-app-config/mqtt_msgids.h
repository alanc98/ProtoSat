/*=======================================================================================
** File Name:  mqtt_msgids.h
**
** Title:  Message ID Header File for MQTT Application
**
** $Author:    Alan Cudmore
** $Revision: 1.1 $
** $Date:      2018-07-21
**
** Purpose:  This header file contains declartions and definitions of all MQTT's 
**           Message IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2018-07-21 | Alan Cudmore | Build #: Code Started
**
**=====================================================================================*/
#ifndef _MQTT_MSGIDS_H_
#define _MQTT_MSGIDS_H_

#define MQTT_CMD_MID            	0x18F0
#define MQTT_SEND_HK_MID        	0x18F1

#define MQTT_HK_TLM_MID		        0x08F0


/* Until I have a better idea, need to define the message IDs of packets that will be sent out */

#define MQTT_CMD_1_MID                0x1900

/*
** Linux System messages
*/
#define MQTT_SYS_IPADDR_TLM_MID       0x0900
#define MQTT_SYS_HOSTNAME_TLM_MID     0x0901
#define MQTT_SYS_CPUUTIL_TLM_MID      0x0902
#define MQTT_SYS_MEMFREE_TLM_MID      0x0903
#define MQTT_SYS_DISKFREE_TLM_MID     0x0904

/*
** cFS System messages
*/
#define MQTT_CFS_STATUS_TLM_MID       0x0905
#define MQTT_CFS_2_TLM_MID            0x0906
#define MQTT_CFS_3_TLM_MID            0x0907

/*
** BMP280 messages
*/
#define MQTT_BMP280_TEMP_TLM_MID      0x090A
#define MQTT_BMP280_PRESSURE_TLM_MID  0x090B
#define MQTT_BMP280_ALTITUDE_TLM_MID  0x090C

/*
** LSM9DS1 messages
*/
#define MQTT_LSM9DS1_GYRO_X_TLM_MID    0x0910
#define MQTT_LSM9DS1_GYRO_Y_TLM_MID    0x0911
#define MQTT_LSM9DS1_GYRO_Z_TLM_MID    0x0912
#define MQTT_LSM9DS1_MAG_X_TLM_MID     0x0913
#define MQTT_LSM9DS1_MAG_Y_TLM_MID     0x0914
#define MQTT_LSM9DS1_MAG_Z_TLM_MID     0x0915
#define MQTT_LSM9DS1_ACCEL_X_TLM_MID   0x0916
#define MQTT_LSM9DS1_ACCEL_Y_TLM_MID   0x0917
#define MQTT_LSM9DS1_ACCEL_Z_TLM_MID   0x0918
#define MQTT_LSM9DS1_TEMP_TLM_MID      0x0919

/*
** APDS9960 Messages
*/
#define MQTT_APDS9960_RED_TLM_MID       0x0950
#define MQTT_APDS9960_BLUE_TLM_MID      0x0951
#define MQTT_APDS9960_GREEN_TLM_MID     0x0952
#define MQTT_APDS9960_CLEAR_TLM_MID     0x0953
#define MQTT_APDS9960_COLOR_TMP_TLM_MID 0x0954
#define MQTT_APDS9960_LUX_TLM_MID       0x0955
#define MQTT_APDS9960_PROX_TLM_MID      0x0956
#define MQTT_APDS9960_GESTURE_TLM_MID   0x0957

#endif /* _MQTT_MSGIDS_H_ */

/*=======================================================================================
** End of file mqtt_msgids.h
**=====================================================================================*/
    
