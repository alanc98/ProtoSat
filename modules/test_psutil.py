import os
import psutil
import time

cpu_clk_info = psutil.cpu_freq()
cpu_freq = cpu_clk_info[0]
cpu_count = psutil.cpu_count()
memory_info = psutil.virtual_memory()
memory_avail = memory_info[1]
mb_avail = (memory_avail / (1024*1024))
load_avg = psutil.getloadavg()
cpu_util = (load_avg[0] * 100)
disk_usage = psutil.disk_usage('/')
mb_free = (disk_usage[2] / (1024*1024))

print('CPU Freq = ', cpu_freq)
print('CPU Count = ', cpu_count)
print('Memory MB avail:', '{0:0.2f}'.format(mb_avail))
print('CPU Util = ', cpu_util)
print('Disk MB avail:', '{0:0.2f}'.format(mb_free))

