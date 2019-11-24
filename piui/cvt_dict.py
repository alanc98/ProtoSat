#
# CVT
# This is the CVT, or Current Value Table for the piui user interface.
# The CVT holds variables, which have: 
#   1. a name similar to an MQTT topic, 
#   2. a current value
#
cvt = {  "psz/sys/ipaddr"          : { "value" : "127.0.0.1" },
         "psz/sys/hostname"        : { "value" : "protosat"  },
         "psz/sys/cpuutil"         : { "value" : "0.0"       },
         "psz/sys/memfree"         : { "value" : "0"         },
         "psz/cfs/status"          : { "value" : "stopped"   },
         "psz/bmp280/temp"         : { "value" : "0.0"       },
         "psz/bmp280/pressure"     : { "value" : "0.0"       },
         "psz/bmp280/altitude"     : { "value" : "0.0"       },
         "psz/lsm9ds1/gyro_x"      : { "value" : "0.0"       },
         "psz/lsm9ds1/gyro_y"      : { "value" : "0.0"       },
         "psz/lsm9ds1/gyro_z"      : { "value" : "0.0"       },
         "psz/lsm9ds1/mag_x"       : { "value" : "0.0"       },
         "psz/lsm9ds1/mag_y"       : { "value" : "0.0"       },
         "psz/lsm9ds1/mag_z"       : { "value" : "0.0"       },
         "psz/lsm9ds1/accel_x"     : { "value" : "0.0"       },
         "psz/lsm9ds1/accel_y"     : { "value" : "0.0"       },
         "psz/lsm9ds1/accel_z"     : { "value" : "0.0"       },
         "psz/lsm9ds1/temp"        : { "value" : "0.0"       },
         "psz/apds9960/red"        : { "value" : "100"       },
         "psz/apds9960/green"      : { "value" : "200"       },
         "psz/apds9960/blue"       : { "value" : "300"       },
         "psz/apds9960/clear"      : { "value" : "50"        },
         "psz/apds9960/color_temp" : { "value" : "123.01"    },
         "psz/apds9960/lux"        : { "value" : "123.34"    },
         "psz/apds9960/prox"       : { "value" : "10.1"      },
         "psz/apds9960/gesture"    : { "value" : "left"      },
      }

