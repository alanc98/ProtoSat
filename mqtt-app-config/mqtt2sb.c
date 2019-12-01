/*************************************************************************
** File:
**   $Id: mqtt2sb_table.c $
**
** Copyright 2018-2019 - Alan Cudmore
**
** Purpose: 
**   MQTT to Software Bus routing table 
**
** Notes:
** 
** 
*************************************************************************/

/*************************************************************************
** Includes
*************************************************************************/
#include "mqtt_app.h"
#include "cfe_tbl_filedef.h"

/*************************************************************************
** Exported Data
*************************************************************************/
/*
** Table file header
*/
static CFE_TBL_FileDef_t CFE_TBL_FileDef __attribute__((__used__)) =
{
    "MQTT_Mqtt2SbTable", MQTT_APP_NAME "." MQTT_MQTT2SB_TABLENAME,
    "MQTT MQTT to SB table", "mqtt2sb.tbl",
    (sizeof(MQTT_Mqtt2SbTableEntry_t) * MQTT_MQTT2SB_MAX_TBL_ENTRIES)
};

/*
** This is the MQTT to Software Bus table (mqtt2sb) 
** 
** Each table entry has the following:
**  Type: MQTT_UNUSED, MQTT_TLM_PKT, MQTT_CMD_PACKET
**  Message ID:
**  Data Type:
**  Data Length: (may not be needed)
*/
MQTT_Mqtt2SbTableEntry_t MQTT_Mqtt2SbTable[MQTT_MQTT2SB_MAX_TBL_ENTRIES] =
{
    /*
    ** ProtoSat Zero System Information 
    */
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SYS_IPADDR_TLM_MID,
        .MqttTopic         = "psz/sys/ipaddr",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_STRING16,
        .DataLength        = 16
    },
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SYS_HOSTNAME_TLM_MID,
        .MqttTopic          = "psz/sys/hostname",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_STRING32,
        .DataLength        = 32
    },
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SYS_CPUUTIL_TLM_MID,
        .MqttTopic          = "psz/sys/cpuutil",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SYS_MEMFREE_TLM_MID,
        .MqttTopic          = "psz/sys/memfree",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_SYS_DISKFREE_TLM_MID,
        .MqttTopic          = "psz/sys/diskfree",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },

    /*
    ** ProtoSatZero cFS Status 
    */

    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_CFS_STATUS_TLM_MID,
        .MqttTopic          = "psz/cfs/status",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_STRING16,
        .DataLength        = 16
    },

    /*
    ** ProtoSatZero BMP280 
    */

    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_BMP280_TEMP_TLM_MID,
        .MqttTopic          = "psz/bmp280/temp",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_BMP280_PRESSURE_TLM_MID,
        .MqttTopic          = "/psz/bmp280/pressure",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_BMP280_ALTITUDE_TLM_MID,
        .MqttTopic          = "psz/bmp280/altitude",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },

    /*
    ** ProtoSatZero LSM9DS1 
    */

    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_GYRO_X_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/gyro_x",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_GYRO_Y_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/gyro_y",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_GYRO_Z_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/gyro_z",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_MAG_X_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/mag_x",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_MAG_Y_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/mag_y",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_MAG_Z_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/mag_z",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_ACCEL_X_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/accel_x",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_ACCEL_Y_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/accel_y",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_ACCEL_Z_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/accel_z",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_LSM9DS1_TEMP_TLM_MID,
        .MqttTopic         = "psz/lsm9ds1/temp",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },

    /*
    ** ProtoSatZero APDS9960 Color/Gesture/Prox sensor 
    */
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_APDS9960_RED_TLM_MID,
        .MqttTopic         = "psz/apds9960/red",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_APDS9960_GREEN_TLM_MID,
        .MqttTopic         = "psz/apds9960/green",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_APDS9960_BLUE_TLM_MID,
        .MqttTopic         = "psz/apds9960/blue",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_APDS9960_CLEAR_TLM_MID,
        .MqttTopic         = "psz/apds9960/clear",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_APDS9960_COLOR_TMP_TLM_MID,
        .MqttTopic         = "psz/apds9960/color_temp",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_APDS9960_LUX_TLM_MID,
        .MqttTopic         = "psz/apds9960/lux",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_APDS9960_PROX_TLM_MID,
        .MqttTopic         = "psz/apds9960/prox",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_FLOAT,
        .DataLength        = 4
    },
    {   
        .MsgType           = MQTT_PRIMITIVE,
        .MsgId             = MQTT_APDS9960_GESTURE_TLM_MID,
        .MqttTopic         = "psz/apds9960/gesture",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_STRING16,
        .DataLength        = 4 
    },

    /* ------------------ Unused ----------------------- */

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },
    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    /* 30 */

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    /* 40 */

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    },

    {   .MsgType           = MQTT_UNUSED,
        .MsgId             = 0,
        .MqttTopic          = "null",
        .PktType           = MQTT_TLM_PKT,
        .DataType          = MQTT_INT32,
        .DataLength        = 4
    }
}; 

/************************/
/*  End of File Comment */
/************************/
