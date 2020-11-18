target extended-remote | openocd -c "gdb_port pipe; log_output openocd.log" -f interface/stlink-v2-1.cfg -f board/st_nucleo_f0.cfg
monitor reset halt
load
