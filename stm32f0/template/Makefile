#-------------------------------------------------------------------------
#Set Path
#-------------------------------------------------------------------------

VPATH = scr

#-------------------------------------------------------------------------
#Configurables
#-------------------------------------------------------------------------

NAME         = firmware
CXX          = ~/Documents/ARM/resources/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-g++
OBJCOPY      = ~/Documents/ARM/resources/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-objcopy
CFLAGS       = -Iinc -O0 -Wall -Werror -pedantic -c
M0           = -mthumb -mcpu=cortex-m0
OBJECTS      = main.o system_stm32f0xx.o stm32f0xx_it.o startup_stm32f072.s
LFLAGS       = -TSTM32F072VB_FLASH.ld -Wl,-Map=$(NAME).map 
USE_NONHOST  = --specs=nosys.specs
USE_SEMIHOST = --specs=rdimon.specs 

#-------------------------------------------------------------------------
#PHONY Targets
#-------------------------------------------------------------------------

.PHONY: all
all: $(NAME).hex

.PHONY: debug
debug:	
	~/Documents/ARM/resources/gcc-arm-none-eabi-9-2019-q4-major/bin/arm-none-eabi-gdb $(NAME).elf

.PHONY: clean
clean:
	@rm *.o *.map *.elf  *.hex

#-------------------------------------------------------------------------
#Target Rules
#-------------------------------------------------------------------------

%.o : %.c
	@$(CXX) $(M0) $(CFLAGS) -o $@ $<

$(NAME).elf : $(OBJECTS)
	@$(CXX) $(M0) $(USE_NONHOST) $(LFLAGS) -o $@ $^


$(NAME).hex : $(NAME).elf 
	@$(OBJCOPY) -O ihex $< $@
