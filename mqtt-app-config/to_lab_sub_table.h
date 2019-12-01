/************************************************************************
**
**      GSC-18128-1, "Core Flight Executive Version 6.6"
**
**      Copyright (c) 2006-2019 United States Government as represented by
**      the Administrator of the National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      Licensed under the Apache License, Version 2.0 (the "License");
**      you may not use this file except in compliance with the License.
**      You may obtain a copy of the License at
**
**        http://www.apache.org/licenses/LICENSE-2.0
**
**      Unless required by applicable law or agreed to in writing, software
**      distributed under the License is distributed on an "AS IS" BASIS,
**      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**      See the License for the specific language governing permissions and
**      limitations under the License.
**
** File: to_sub_table.h
**
** Purpose: 
**  Define TO Lab CPU specific subscription table 
**
** Notes:
**
*************************************************************************/

/* 
** Add the proper include file for the message IDs below
*/
#include "cfe_msgids.h"

/*
** Common CFS app includes below are commented out
*/
#include "ci_lab_msgids.h"

#include "sample_app_msgids.h"

#include "mqtt_msgids.h"

#if 0
#include "hs_msgids.h"
#include "fm_msgids.h"
#include "sc_msgids.h"
#include "ds_msgids.h"
#include "lc_msgids.h"
#endif

static TO_subscription_t  TO_SubTable[] =
{
            /* CFS App Subscriptions */
            {TO_LAB_HK_TLM_MID,     {0,0},  4},
            {TO_LAB_DATA_TYPES_MID, {0,0},  4},
            {CI_LAB_HK_TLM_MID,     {0,0},  4},
            {SAMPLE_APP_HK_TLM_MID, {0,0},  4},
            {MQTT_HK_TLM_MID,       {0,0},  4},

#if 0
            /* Add these if needed */
            {HS_HK_TLM_MID,         {0,0},  4},
            {FM_HK_TLM_MID,         {0,0},  4},
            {SC_HK_TLM_MID,         {0,0},  4},
            {DS_HK_TLM_MID,         {0,0},  4},
            {LC_HK_TLM_MID,         {0,0},  4},
#endif

            /* cFE Core subscriptions */
            {CFE_ES_HK_TLM_MID,          {0,0},  4},
            {CFE_EVS_HK_TLM_MID,         {0,0},  4},
            {CFE_SB_HK_TLM_MID,          {0,0},  4},
            {CFE_TBL_HK_TLM_MID,         {0,0},  4},
            {CFE_TIME_HK_TLM_MID,        {0,0},  4},
            {CFE_TIME_DIAG_TLM_MID,      {0,0},  4},
            {CFE_SB_STATS_TLM_MID,       {0,0},  4},
            {CFE_TBL_REG_TLM_MID,        {0,0},  4},
            {CFE_EVS_LONG_EVENT_MSG_MID, {0,0}, 32},
            {CFE_ES_SHELL_TLM_MID,       {0,0}, 32},
            {CFE_ES_APP_TLM_MID,         {0,0},  4},
            {CFE_ES_MEMSTATS_TLM_MID,    {0,0},  4},

            /* MQTT Sensor Packet subsriptions */
            {MQTT_SYS_IPADDR_TLM_MID,    {0,0},  4},
            {MQTT_SYS_HOSTNAME_TLM_MID,  {0,0},  4},
            {MQTT_SYS_CPUUTIL_TLM_MID,   {0,0},  4},
            {MQTT_SYS_MEMFREE_TLM_MID,   {0,0},  4},
            {MQTT_SYS_DISKFREE_TLM_MID,  {0,0},  4},

            {MQTT_CFS_STATUS_TLM_MID,    {0,0},  4},

            {MQTT_BMP280_TEMP_TLM_MID,       {0,0},  4},
            {MQTT_BMP280_PRESSURE_TLM_MID,   {0,0},  4},
            {MQTT_BMP280_ALTITUDE_TLM_MID,   {0,0},  4},

            {MQTT_LSM9DS1_GYRO_X_TLM_MID,    {0,0},  4}, 
            {MQTT_LSM9DS1_GYRO_Y_TLM_MID,    {0,0},  4},
            {MQTT_LSM9DS1_GYRO_Z_TLM_MID,    {0,0},  4}, 
            {MQTT_LSM9DS1_MAG_X_TLM_MID,     {0,0},  4},
            {MQTT_LSM9DS1_MAG_Y_TLM_MID,     {0,0},  4},
            {MQTT_LSM9DS1_MAG_Z_TLM_MID,     {0,0},  4},
            {MQTT_LSM9DS1_ACCEL_X_TLM_MID,   {0,0},  4},
            {MQTT_LSM9DS1_ACCEL_Y_TLM_MID,   {0,0},  4}, 
            {MQTT_LSM9DS1_ACCEL_Z_TLM_MID,   {0,0},  4},
            {MQTT_LSM9DS1_TEMP_TLM_MID,      {0,0},  4},

            /*
            ** APDS9960 Messages
            */
            {MQTT_APDS9960_RED_TLM_MID,      {0,0},  4},
            {MQTT_APDS9960_BLUE_TLM_MID,     {0,0},  4}, 
            {MQTT_APDS9960_GREEN_TLM_MID,    {0,0},  4}, 
            {MQTT_APDS9960_CLEAR_TLM_MID,    {0,0},  4},
            {MQTT_APDS9960_COLOR_TMP_TLM_MID,{0,0},  4}, 
            {MQTT_APDS9960_LUX_TLM_MID,      {0,0},  4},
            {MQTT_APDS9960_PROX_TLM_MID,     {0,0},  4},
            {MQTT_APDS9960_GESTURE_TLM_MID,  {0,0},  4},

            {TO_UNUSED,              {0,0},  0},
            {TO_UNUSED,              {0,0},  0}
};

/************************
** End of File Comment ** 
************************/
