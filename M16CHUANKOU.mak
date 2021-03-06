CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATMega16  -l -g -MLongJump -MHasMul -MEnhanced 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = delay.o mian.o 

M16CHUANKOU:	$(FILES)
	$(CC) -o M16CHUANKOU $(LFLAGS) @M16CHUANKOU.lk   -lcatmega
delay.o:	delay.c
	$(CC) -c $(CFLAGS) delay.c
mian.o:	mian.c
	$(CC) -c $(CFLAGS) mian.c
