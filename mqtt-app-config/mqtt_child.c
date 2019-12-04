/*************************************************************************
** File:
**   mqtt_child.c
**
*************************************************************************/

/*************************************************************************
** Includes
*************************************************************************/
#include "mqtt_app.h"

/* 
** mqtt_lib
**  Current version uses the Paho Embedded C MQTT Client
*/ 
#include "mqtt_lib.h"

#undef MQTT_DEBUG

/*
** Next to do with this integration. 
** In order to integrate the JSON parsing code, I need to be able
** to build up a packet from a buffer.
** If I can do this correctly, I can get rid of the packets below and
** just have a generic packet to build up. 
** What is the maximum size? 
**
** Start with a packet header and a generic buffer type. 
** Have functions to add these packet data primitives. Either a single
** item for the MQTT_PRIMIITVE data type or mltiples for the JSON_PACKET
** or JSON_PAYLOAD tables type.   
**
** Need to keep track of packet size while building it up
**  Then I can call CFE_SB_InitPacket to init the correct size. 
*/ 

/*
** MQTT data packets to publish
*/
MQTT_INT32_TLM_PKT_t    MQTT_Int32TlmPkt;
MQTT_FLOAT_TLM_PKT_t    MQTT_FloatTlmPkt;
MQTT_DOUBLE_TLM_PKT_t   MQTT_DoubleTlmPkt;
MQTT_STRING32_TLM_PKT_t MQTT_String32TlmPkt;
MQTT_STRING64_TLM_PKT_t MQTT_String64TlmPkt;

/*
** New way
*/
MQTT_GENERIC_TLM_PKT_t  MQTT_GenericTlmPkt;
MQTT_GENERIC_CMD_PKT_t  MQTT_GenericCmdPkt;


/*
** packet construction functions
*/
int32 MQTT_AddInt8ToPacket(uint8 *packet_data_ptr, uint32 DataOffset, int8 data) {
    packet_data_ptr[DataOffset] = (uint8)data;
    return(1);
}

int32 MQTT_AddUint8ToPacket(uint8 *packet_data_ptr, uint32 DataOffset, uint8 data) {
    packet_data_ptr[DataOffset] = data;
    return(1);
}

int32 MQTT_AddInt16ToPacket(uint8 *packet_data_ptr, uint32 DataOffset, int16 data) {
    memcpy(&(packet_data_ptr[DataOffset]),(void *)&data, 2);
    return(2);
}

int32 MQTT_AddUint16ToPacket(uint8 *packet_data_ptr, uint32 DataOffset, uint16 data) {
    memcpy(&(packet_data_ptr[DataOffset]),(void *)&data, 2);
    return(2);
}

int32 MQTT_AddInt32ToPacket(uint8 *packet_data_ptr, uint32 DataOffset, int32 data) {
    memcpy(&(packet_data_ptr[DataOffset]),(void *)&data, 4);
    return(4);
}

int32 MQTT_AddUint32ToPacket(uint8 *packet_data_ptr, uint32 DataOffset, uint32 data) {
    memcpy(&(packet_data_ptr[DataOffset]),(void *)&data, 4);
    return(4);
}

int32 MQTT_AddFloatToPacket(uint8 *packet_data_ptr, uint32 DataOffset, float data) {
    memcpy(&(packet_data_ptr[DataOffset]),(void *)&data, sizeof(float));
    return(sizeof(float));
}

int32 MQTT_AddDoubleToPacket(uint8 *packet_data_ptr, uint32 DataOffset, double data) {
    memcpy(&(packet_data_ptr[DataOffset]),(void *)&data, sizeof(double));
    return(sizeof(double));
}

int32 MQTT_AddStringToPacket(uint8 *packet_data_ptr, uint32 DataOffset, uint32 StringLength, char *data) {



    return(StringLength);
} 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */ 
/* MQTT Format/convert the data and send it on the Software Bus    */
/*                                                                 */ 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MQTT_ConvertAndSendToSB(uint32 MsgType,  CFE_SB_MsgId_t Stream, 
                              uint32 PktType,  uint32         DataType, 
                              uint32 DataSize, char          *payload)
{
   int    status;
   int32  int32_value;
   float  float_value;
   double double_value;

   #ifdef MQTT_DEBUG
      OS_printf("Convert and send %s on SB stream 0x%04X\n", payload, Stream); 
   #endif

   /*
   ** First, switch on the MsgType
   */
   switch (MsgType)
   {
      case MQTT_PRIMITIVE:
         /* Process the MQTT_PRIMITIVE MsgType */
         switch (DataType)
         {
            case MQTT_INT32:
               #ifdef MQTT_DEBUG
                  OS_printf("MQTT --> INT32 Type\n");
               #endif
               status = sscanf(payload, "%d", (int *) &int32_value); 
               if (status == 1)
               {
                  #ifdef MQTT_DEBUG
                     OS_printf("Converted value: %d\n",(int)int32_value);
                  #endif
                  /*
                  ** Initialize TLM packet
                  */
                  CFE_SB_InitMsg(&MQTT_Int32TlmPkt, Stream,
                                  MQTT_INT32_TLM_LNGTH, TRUE);
                  MQTT_Int32TlmPkt.int32_value = int32_value;
                  CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &MQTT_Int32TlmPkt);
                  CFE_SB_SendMsg((CFE_SB_Msg_t *)&MQTT_Int32TlmPkt);
               }
               break;

            case MQTT_FLOAT:
               #ifdef MQTT_DEBUG
                  OS_printf("MQTT --> FLOAT Type\n");
               #endif
               status = sscanf(payload, "%f", &float_value); 
               if (status == 1)
               {
                  #ifdef MQTT_DEBUG
                     OS_printf("Converted value: %f\n",float_value);
                  #endif
                  /*
                  ** Initialize TLM packet
                  */
                  CFE_SB_InitMsg(&MQTT_FloatTlmPkt, Stream,
                                 MQTT_FLOAT_TLM_LNGTH, TRUE);
                  MQTT_FloatTlmPkt.float_value = float_value;
                  CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &MQTT_FloatTlmPkt);
                  CFE_SB_SendMsg((CFE_SB_Msg_t *)&MQTT_FloatTlmPkt);
               }
               break;

            case MQTT_DOUBLE:
               #ifdef MQTT_DEBUG
                  OS_printf("MQTT --> DOUBLE Type\n");
               #endif
               status = sscanf(payload, "%lf", &double_value); 
               if (status == 1)
               {
                  #ifdef MQTT_DEBUG
                     OS_printf("Converted value: %lf\n",double_value);
                  #endif
                  /*
                  ** Initialize TLM packet
                  */
                  CFE_SB_InitMsg(&MQTT_DoubleTlmPkt, Stream,
                                  MQTT_DOUBLE_TLM_LNGTH, TRUE);
                  MQTT_DoubleTlmPkt.double_value = double_value;
                  CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &MQTT_DoubleTlmPkt);
                  CFE_SB_SendMsg((CFE_SB_Msg_t *)&MQTT_DoubleTlmPkt);
               }
               break;

            case MQTT_STRING32:
               #ifdef MQTT_DEBUG
                  OS_printf("MQTT --> STRING32 Type\n");
               #endif
               /*
               ** Initialize TLM packet
               */
               CFE_SB_InitMsg(&MQTT_String32TlmPkt, Stream,
                              MQTT_STRING32_TLM_LNGTH, TRUE);
               strncpy(MQTT_String32TlmPkt.string32,payload, 32); 
               #ifdef MQTT_DEBUG 
                  OS_printf("MQTT --> String32 value = %s\n",MQTT_String32TlmPkt.string32);
               #endif
               CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &MQTT_String32TlmPkt);
               CFE_SB_SendMsg((CFE_SB_Msg_t *)&MQTT_String32TlmPkt);
               break;

            case MQTT_STRING64:
               #ifdef MQTT_DEBUG
                  OS_printf("MQTT --> STRING64 Type\n");
               #endif
               /*
               ** Initialize TLM packet
               */
               CFE_SB_InitMsg(&MQTT_String64TlmPkt, Stream,
                              MQTT_STRING64_TLM_LNGTH, TRUE);
               strncpy(MQTT_String64TlmPkt.string64,payload, 32); 
               #ifdef MQTT_DEBUG
                  OS_printf("MQTT --> String64 value = %s\n",MQTT_String64TlmPkt.string64);
               #endif
               CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &MQTT_String64TlmPkt);
               CFE_SB_SendMsg((CFE_SB_Msg_t *)&MQTT_String64TlmPkt);
               break;

            default:
               OS_printf("MQTT --> ERROR: Unknown type!\n");
         }
         break;
      case MQTT_JSON_PACKET:
         OS_printf("MQTT JSON Packet Message\n");
         break;

      case MQTT_JSON_PAYLOAD:
         OS_printf("MQTT JSON Payload Message\n");
         break;

      default:
         OS_printf("Unknown Message Type\n");

   }
   return (CFE_SUCCESS);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */ 
/* MQTT Client MessageCallback                                     */
/*                                                                 */ 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MQTT_ClientMessageCallback(MessageData* md)
{
    int          index = 0;
    int          end_of_table = 0;
    int          message_found = 0;
    MQTTMessage* message = md->message;
    char         payload_string[80];

    #ifdef MQTT_DEBUG
        OS_printf("In MQTT Message received callback\n");
        OS_printf("   Topic length: %d\n",md->topicName->lenstring.len);
        OS_printf("   Payload length: %d\n",message->payloadlen);
        OS_printf("%.*s\t", md->topicName->lenstring.len, md->topicName->lenstring.data);
        OS_printf("%.*s\n", (int)message->payloadlen, (char*)message->payload);
    #endif

    if(message->payloadlen)
    {
        #ifdef MQTT_DEBUG
            printf("MQTT--> Topic: %s, Value: %s\n", md->topicName->lenstring.data, (char *)message->payload);
        #endif
        /*
        ** Have to search the table to get what we need to send the message
        */ 
        while ( end_of_table == 0  && message_found == 0 )
        {
            if (MQTT_Mqtt2SbTablePtr[index].MsgType == MQTT_UNUSED)
            {
                #ifdef MQTT_DEBUG
                    OS_printf("MQTT --> End of Mqtt2SbTable reached\n");
                #endif
                end_of_table = 1;
            }
            else
            {
                #ifdef MQTT_DEBUG
                    OS_printf("MQTT --> Comparing MQTT Topic:  %s\n",md->topicName->lenstring.data);
                    OS_printf("MQTT -->           Table Engry: %s\n",MQTT_Mqtt2SbTablePtr[index].MqttTopic);
                #endif

                if (strncmp(MQTT_Mqtt2SbTablePtr[index].MqttTopic, md->topicName->lenstring.data, 
                            md->topicName->lenstring.len) == 0)
                {
                    message_found = 1;
                } 
                else
                {
                   index++;
                }
            }
        }

        if (message_found == 1)
        {
            strncpy(payload_string, message->payload, message->payloadlen); 
            payload_string[message->payloadlen] = 0;
            MQTT_ConvertAndSendToSB(MQTT_Mqtt2SbTablePtr[index].MsgType,
                                 MQTT_Mqtt2SbTablePtr[index].MsgId, 
                                 MQTT_Mqtt2SbTablePtr[index].PktType, 
                                 MQTT_Mqtt2SbTablePtr[index].DataType, 
                                 MQTT_Mqtt2SbTablePtr[index].DataLength, 
                                 payload_string);
        }
        else if (end_of_table == 1)
        {
            printf("MQTT --> Message not found before end of table!\n");
        }
    }
    else
    {
        printf("%s (null)\n", md->topicName->lenstring.data);
    }
    fflush(stdout);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MQTT Child Task MQTT Loop                                       */
/* Subscribe to MQTT topics and enter main loop                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MQTT_ChildMqttLoop(void)
{
    int32  result;
    int    index;

    /*
    ** Initialize the MQTT client. 
    ** These parameters are in the platform config file for the app
    */
    result = MQTT_ClientInitialize(MQTT_DEFAULT_SERVER_ADDRESS,
                                   MQTT_DEFAULT_SERVER_PORT,
                                   MQTT_DEFAULT_CLIENT_NAME,
                                   MQTT_DEFAULT_SERVER_USERNAME,
                                   MQTT_DEFAULT_SERVER_PASSWORD);
    if (result != CFE_SUCCESS) 
    {
       OS_printf("MQTT_ClientInitialize Failed - Entering Child Idle Loop!\n");
       MQTT_ChildIdleLoop();
    }
    else
    {
        /*
        ** Go through the MQTT2SB table and subscribe to the MQTT topics
        */  
        for (index = 0; index < MQTT_MQTT2SB_MAX_TBL_ENTRIES; index++)
        { 
            if (MQTT_Mqtt2SbTablePtr[index].MsgType == MQTT_PRIMITIVE) 
              /* May need to include other message types here? */
            {
                #ifdef MQTT_DEBUG
                    OS_printf("MQTT --> Subscribe to Topic: %s\n",
                               MQTT_Mqtt2SbTablePtr[index].MqttTopic);
                #endif

                result = MQTT_ClientSubscribe(MQTT_Mqtt2SbTablePtr[index].MqttTopic, MQTT_QOS2);

                if (result != CFE_SUCCESS)
                {
                    OS_printf("MQTT --> Subscribe to Topic: %s Failed\n",
                               MQTT_Mqtt2SbTablePtr[index].MqttTopic);
                }
            }
            else 
            {
                /* 
                ** Assume the first unused entry is the end of the table 
                */
                break;
            }
        }
    }

    /*
    ** Child Task Main Loop 
    **   Primarily used for getting MQTT subscribed messages 
    */
    while (MQTT_ChildTaskRunStatus == CFE_SUCCESS)
    {
        /* Entry and Exit markers are for easy time marking only; not performance */
        CFE_ES_PerfLogEntry(MQTT_CHILD_TASK_PERF_ID);

        /* Increment the child task Execution Counter */
        CFE_ES_IncrementTaskCounter();

        /* Increment the counter in telemetry */
        MQTT_HkTelemetryPkt.mqtt_child_task_counter++;

        /*
        ** Receive any MQTT messages through the Yield mechanism
        */
        #ifdef MQTT_DEBUG  
            OS_printf("----------MQTT_CHILD -- Before Yield\n");
        #endif

        MQTT_ClientYeild(1000);

        #ifdef MQTT_DEBUG  
            OS_printf("----------MQTT_CHILD -- After Yield\n");
        #endif

        CFE_ES_PerfLogExit(MQTT_CHILD_TASK_PERF_ID);
    }

    MQTT_ClientDisconnect();
 
} /* End of MQTT_ChildMqttLoop() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* MQTT Child Task Idle Loop                                       */
/* Fallback in case the MQTT table is not valid                    */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MQTT_ChildIdleLoop(void)
{
    /*
    ** Main Loop 
    */
    while (MQTT_ChildTaskRunStatus == CFE_SUCCESS)
    {
        /* Entry and Exit markers are for easy time marking only; not performance */
        CFE_ES_PerfLogEntry(MQTT_CHILD_TASK_PERF_ID);

        /* Increment the child task Execution Counter */
        CFE_ES_IncrementTaskCounter();

        /* Increment the counter in telemetry */
        MQTT_HkTelemetryPkt.mqtt_child_task_counter++;

        /*
        ** Receive any MQTT messages through the Yield mechanism
        */  
        OS_TaskDelay(1000);

        CFE_ES_PerfLogExit(MQTT_CHILD_TASK_PERF_ID);
    }
 
} /* End of MQTT_ChildIdleLoop() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* MQTT Child Task                                                 */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MQTT_ChildTask(void)
{
    MQTT_ChildTaskRunStatus = CFE_ES_RegisterChildTask();

    /* 
    ** Cannot subscribe to MQTT Topics unless the Table has been
    ** loaded and is valid. 
    ** If the MQTT table is not valid, just enter an idle loop
    */ 
    if (MQTT_Mqtt2SbTableIsValid == TRUE)
    {
       MQTT_ChildMqttLoop();
    }
    else
    {
       MQTT_ChildIdleLoop();
    }

    /*
    ** If the run status is externally set to something else
    */
    return;

} /* End of MQTT_ChildTask() */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Create MQTT Child task                                          */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 MQTT_CreateChildTask(void)
{
    int32 Status = CFE_SUCCESS;

    /*
    ** Spawn the Idle Task
    */
    Status = CFE_ES_CreateChildTask(&(MQTT_ChildTaskId),      
                                     MQTT_CHILD_TASK_NAME,       
                                     MQTT_ChildTask,         
                                     0,  
                                     MQTT_CHILD_TASK_STACK_SIZE, 
                                     MQTT_CHILD_TASK_PRIORITY,   
                                     MQTT_CHILD_TASK_FLAGS);     
     
    if(Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(MQTT_CR_CHILD_TASK_ERR_EID, CFE_EVS_ERROR,
                          "Error Creating MQTT Child Task,RC=0x%08X",
                          (unsigned int)Status);
        return (Status);
    }

    return(Status);

} /* end MQTT_CustomInit */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void MQTT_CleanupChildTask(void)
{
    /*
    ** Force the Child Task to stop running
    */
    MQTT_ChildTaskRunStatus = !CFE_SUCCESS;

    /*
    ** Delay to let the task stop
    */
    OS_TaskDelay(2000);

    /*
    ** Delete the Idle Task
    */
    CFE_ES_DeleteChildTask(MQTT_ChildTaskId);

} /* end MQTT_CleanupChildTask */

/************************/
/*  End of File Comment */
/************************/
