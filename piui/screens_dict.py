#
# Note: On the Adafruit SSD1306 1.3" 128x64 OLED screen, with the default font,
# you can fit 20 characters on a single line and 7 lines of text on the screen
#
#
# Next: For telemetry screens , define an MQTT topic ( probably just use a single broker
#                               and a variable with a default. 
# Next Ideas: 
# 1. Have a "User scripts" menu on the Main menu if it fits.
# 2. Move the IP address to data menu and call it "system data"
# 
# Future idea: Scrolling menus with more than 7 lines! This would take a bit of work
# 
#
#
#  Screen Map:
#   1 - Start Splash/Logo screen
#   2 - Main Menu
#   3 - Telemetry Menu
#   4 - cFS Menu
#   5 - System Menu  
#   6 - Halt System/Are you sure screen
#   7 - Restart System/Are you sure screen
#   8 - Shutdown graphic script screen (displays shutting down graphic)
#   9 - Shutdown text script screen (same thing, displays shutting down text screen)
#  10 - Restart text script screen
#  11 - Badge Graphic Screen 
#  12 - IMU Telemetry data screen
#    
screens = { 1 :  {"screen_type"  : "graphics",
                  "imagefile"    : "/home/pi/ProtoSat/piui/images/protosat_logo_64.png",
                  "exit_to"      : 2 },

            2 :  {"screen_type" : "menu", "screen_name" : "main_menu", "first_menu" : 3, 
                 "rows" : { 1 : { "type" : "text", "text" : "---- Proto-Sat ----"  }, 
                            2 : { "type" : "data", "text" : "IP: "              , "topic": "psz/sys/ipaddr"  },
                            3 : { "type" : "menu", "text" : "Data Menu         ", "next" : 4, "action" : "screen", "arg" : 3  },
                            4 : { "type" : "menu", "text" : "cFS Menu"          , "next" : 5, "action" : "screen", "arg" : 4  },
                            5 : { "type" : "menu", "text" : "Script Menu"       , "next" : 6, "action" : "screen", "arg" : 5  },
                            6 : { "type" : "menu", "text" : "System Menu"       , "next" : 7, "action" : "screen", "arg" : 6  },
                            7 : { "type" : "menu", "text" : "Exit"              , "next" : 3, "action" : "screen", "arg" : 1  },
                          },
                  },

            3 : {"screen_type" : "menu", "screen_name" : "data_menu", "first_menu" : 2,
                 "rows" : { 1 : { "type" : "text", "text" : "---- Data Menu -----" }, 
                            2 : { "type" : "menu", "text" : "IMU Data"          , "next" : 3, "action" : "screen", "arg" : 17 },
                            3 : { "type" : "menu", "text" : "Enviro Data"       , "next" : 4, "action" : "screen", "arg" : 18 },
                            4 : { "type" : "menu", "text" : "cFS Tlm Data"      , "next" : 5, "action" : "screen", "arg" : 19 },
                            5 : { "type" : "menu", "text" : "System Data"       , "next" : 6, "action" : "screen", "arg" : 20 },
                            6 : { "type" : "menu", "text" : "<--Back"           , "next" : 2, "action" : "screen", "arg" :  2 },
                            7 : { "type" : "text", "text" : " "   },
                           }, 
                },

            4 : {"screen_type" : "menu", "screen_name" : "cfs_menu", "first_menu" : 4,
                 "rows" : { 1 : { "type" : "text", "text" : "----- cFS Menu -----"    }, 
                            2 : { "type" : "data", "text" : "cFS Status:",        "topic": "psz/cfs/status" },
                            3 : { "type" : "text", "text" : "--------------------"   },
                            4 : { "type" : "menu", "text" : "Start cFS"         , "next" : 5, "action" : "script", "arg" : "/home/pi/ProtoSat/piui/scripts/startcfs.sh" },
                            5 : { "type" : "menu", "text" : "Stop cFS"          , "next" : 6, "action" : "script", "arg" : "/home/pi/ProtoSat/piui/scripts/stopcfs.sh" },
                            6 : { "type" : "menu", "text" : "Update cFS"        , "next" : 7, "action" : "script", "arg" : "/home/pi/ProtoSat/piui/scripts/updatecfs.sh" },
                            7 : { "type" : "menu", "text" : "<--Back"           , "next" : 4, "action" : "screen", "arg" : 2 },
                           }, 
                },

            5 : {"screen_type" : "menu", "screen_name" : "script_menu", "first_menu" : 2,
                 "rows" : { 1 : { "type" : "text", "text" : "--- Script Menu ----" }, 
                            2 : { "type" : "menu", "text" : "User Script 1"     , "next" : 3, "action" : "script", "arg" : "/home/pi/ProtoSat/piui/scripts/user1.sh" },
                            3 : { "type" : "menu", "text" : "User Script 2"     , "next" : 4, "action" : "script", "arg" : "/home/pi/ProtoSat/piui/scripts/user2.sh" },
                            4 : { "type" : "menu", "text" : "User Script 3"     , "next" : 5, "action" : "script", "arg" : "/home/pi/ProtoSat/piui/scripts/user3.sh" },
                            5 : { "type" : "menu", "text" : "User Script 4"     , "next" : 6, "action" : "script", "arg" : "/home/pi/ProtoSat/piui/scripts/user4.sh" },
                            6 : { "type" : "menu", "text" : "User Script 5"     , "next" : 7, "action" : "script", "arg" : "/home/pi/ProtoSat/piui/scripts/user5.sh" },
                            7 : { "type" : "menu", "text" : "<--Back"           , "next" : 2, "action" : "screen", "arg" : 2  },
                           }, 
                },

            6 : {"screen_type" : "menu", "screen_name" : "system_menu", "first_menu" : 2,
                 "rows" : { 1 : { "type" : "text", "text" : "--- System Menu ---" }, 
                            2 : { "type" : "menu", "text" : "Picture Menu"      , "next" : 3, "action" : "screen", "arg" : 11 },
                            3 : { "type" : "menu", "text" : "Halt System"       , "next" : 4, "action" : "screen", "arg" : 7  },
                            4 : { "type" : "menu", "text" : "Restart System"    , "next" : 5, "action" : "screen", "arg" : 8  },
                            5 : { "type" : "menu", "text" : "<--Back"           , "next" : 2, "action" : "screen", "arg" : 2  },
                            6 : { "type" : "text", "text" : " "   },
                            7 : { "type" : "text", "text" : " "   },
                           }, 
                },


            7 : {"screen_type" : "menu", "screen_name" : "halt_query", "first_menu" : 4,
                 "rows" : { 1 : { "type" : "text", "text" : "+--- Halt System --+" }, 
                            2 : { "type" : "text", "text" : "| Are you Sure?    |" },
                            3 : { "type" : "text", "text" : "+------------------+" },
                            4 : { "type" : "menu", "text" : "No, Return"        ,  "next" : 5, "action" : "screen", "arg" : 6 },
                            5 : { "type" : "menu", "text" : "Yes, Halt!"        ,  "next" : 4, "action" : "screen", "arg" : 9 },
                            6 : { "type" : "text", "text" : "--------------------"  },
                            7 : { "type" : "text", "text" : "               "       },
                           }, 
                },

            8 : {"screen_type" : "menu", "screen_name" : "reboot_query", "first_menu" : 4,
                 "rows" : { 1 : { "type" : "text", "text" : "+- Restart System -+" }, 
                            2 : { "type" : "text", "text" : "| Are you Sure?    |" },
                            3 : { "type" : "text", "text" : "+------------------+" },
                            4 : { "type" : "menu", "text" : "No, Return"        , "next" : 5, "action" : "screen", "arg" : 6},
                            5 : { "type" : "menu", "text" : "Yes, Reboot!"      , "next" : 4, "action" : "screen", "arg" : 10},
                            6 : { "type" : "text", "text" : "--------------------" },
                            7 : { "type" : "text", "text" : "               "      },
                           }, 
                },

            9 : {"screen_type" : "txscript", 
                 "rows" : { 1 : { "text" : "+------------------+" }, 
                            2 : { "text" : "|   Shutting Down! |" },
                            3 : { "text" : "|     Wait For     |" },
                            4 : { "text" : "|    30 Seconds    |" },
                            5 : { "text" : "|   and turn off   |" },
                            6 : { "text" : "|    Proto-Sat!    |" },
                            7 : { "text" : "+------------------+" },
                           }, 
                  "script"      : "/home/pi/ProtoSat/piui/scripts/shutdown.sh",
                  "exit_to"     : 6 },

           10 : {"screen_type" : "txscript", 
                 "rows" : { 1 : { "text" : "+------------------+" }, 
                            2 : { "text" : "|   Restarting!    |" },
                            3 : { "text" : "|     System       |" },
                            4 : { "text" : "|   will restart   |" },
                            5 : { "text" : "|     shortly      |" },
                            6 : { "text" : "|                  |" },
                            7 : { "text" : "+------------------+" },
                           }, 
                  "script"      : "/home/pi/ProtoSat/piui/scripts/restart.sh",
                  "exit_to"     : 6 },

           11 : {"screen_type" : "menu", "screen_name" : "picture_menu", "first_menu" : 2,
                 "rows" : { 1 : { "type" : "text", "text" : "--- Picture Menu ---" }, 
                            2 : { "type" : "menu", "text" : "Show Badge Pic" , "next" : 3, "action" : "screen", "arg" : 12 },
                            3 : { "type" : "menu", "text" : "Show Start Pic" , "next" : 4, "action" : "screen", "arg" : 13 },
                            4 : { "type" : "menu", "text" : "Show Chloe Pic",  "next" : 5, "action" : "screen", "arg" : 15  },
                            5 : { "type" : "menu", "text" : "Show Rusty Pic",  "next" : 6, "action" : "screen", "arg" : 16  },
                            6 : { "type" : "menu", "text" : "Show AdaCat Pic", "next" : 7, "action" : "screen", "arg" : 14  },
                            7 : { "type" : "menu", "text" : "<--Back"        , "next" : 2, "action" : "screen", "arg" : 6  },
                           }, 
                },

           12 :  {"screen_type"  : "graphics",
                   "imagefile"    : "/home/pi/ProtoSat/piui/images/badge_64.png",
                   "exit_to"      : 11 },

           13 :  {"screen_type"  : "graphics",
                   "imagefile"    : "/home/pi/ProtoSat/piui/images/protosat_logo_64.png",
                   "exit_to"      : 11 },

           14 :  {"screen_type"  : "graphics",
                   "imagefile"    : "/home/pi/ProtoSat/piui/images/happycat_oled_64.ppm",
                   "exit_to"      : 11 },
           
           15 :  {"screen_type"  : "graphics",
                   "imagefile"    : "/home/pi/ProtoSat/piui/images/chloe.png",
                   "exit_to"      : 11 },

           16 :  {"screen_type"  : "graphics",
                   "imagefile"    : "/home/pi/ProtoSat/piui/images/rusty.png",
                   "exit_to"      : 11 },

           17 : {"screen_type" : "telemetry", "screen_name" : "imu_data", 
                 "rows" : { 1 : { "type" : "text", "text" : "----- IMU Data -----"}, 
                            2 : { "type" : "data", "text" : "mem: "    ,"topic": "psz/sys/memfree"},
                            3 : { "type" : "data", "text" : "cpuutil: ","topic": "psz/sys/cpuutil"},
                            4 : { "type" : "data", "text" : "hname: "  ,"topic": "psz/sys/hostname"},
                            5 : { "type" : "text", "text" : ""                    },
                            6 : { "type" : "text", "text" : "--------------------"},
                            7 : { "type" : "text", "text" : "Hit key to exit"     },
                          },
                 "exit_to"     : 3 },

           18 : {"screen_type" : "telemetry", "screen_name" : "enviro_data", 
                 "rows" : { 1 : { "type" : "text", "text" : "--- Enviro Data ----"}, 
                            2 : { "type" : "data", "text" : "mem: ","topic":     "psz/sys/memfree"},
                            3 : { "type" : "data", "text" : "cpuutil: ","topic": "psz/sys/cpuutil"},
                            4 : { "type" : "data", "text" : "hname: ","topic":   "psz/sys/hostname"},
                            5 : { "type" : "text", "text" : "               "     },
                            6 : { "type" : "text", "text" : "--------------------"},
                            7 : { "type" : "text", "text" : "Hit key to exit"     },
                          },
                 "exit_to"     : 3 },

           19 : {"screen_type" : "telemetry", "screen_name" : "cfs_data", 
                 "rows" : { 1 : { "type" : "text", "text" : "--- cFS Data -------"}, 
                            2 : { "type" : "data", "text" : "cFS Status:" ,"topic": "psz/cfs/status" },
                            3 : { "type" : "data", "text" : "cpuutil:"    ,"topic": "psz/sys/cpuutil"},
                            4 : { "type" : "data", "text" : "hname:"      ,"topic": "psz/sys/hostname"},
                            5 : { "type" : "text", "text" : " "                   },
                            6 : { "type" : "text", "text" : "--------------------"},
                            7 : { "type" : "text", "text" : "Hit key to exit"     },
                          },
                 "exit_to"     : 3 },
           20 : {"screen_type" : "telemetry", "screen_name" : "sys_data", 
                 "rows" : { 1 : { "type" : "text", "text" : "--- System Data ----"}, 
                            2 : { "type" : "data", "text" : "Mem  :","topic":    "psz/sys/memfree"},
                            3 : { "type" : "data", "text" : "CPU %:","topic":    "psz/sys/cpuutil"},
                            4 : { "type" : "data", "text" : "Host:" ,"topic":    "psz/sys/hostname"},
                            5 : { "type" : "data", "text" : "IP:"   ,"topic":    "psz/sys/ipaddr"},
                            6 : { "type" : "text", "text" : "--------------------"},
                            7 : { "type" : "text", "text" : "Hit key to exit"     },
                          },
                 "exit_to"     : 3 },
          }
