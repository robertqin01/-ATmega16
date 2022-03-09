CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATMega16  -l -g -MLongJump -MHasMul -MEnhanced 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = delay.o fuwuqi.o 

FUWUDUAN:	$(FILES)
	$(CC) -o FUWUDUAN $(LFLAGS) @FUWUDUAN.lk   -lcatmega
delay.o: C:\iccv7avr\include\iom16v.h .\..\M16_~02V\delay.h
delay.o:	..\M16_~02V\delay.c
	$(CC) -c $(CFLAGS) ..\M16_~02V\delay.c
fuwuqi.o: C:\iccv7avr\include\iom16v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h .\..\M16_~02V\uart.h .\..\M16_~02V\delay.h
fuwuqi.o:	..\M16_~02V\fuwuqi.C
	$(CC) -c $(CFLAGS) ..\M16_~02V\fuwuqi.C
