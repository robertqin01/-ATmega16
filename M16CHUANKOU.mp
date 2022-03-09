NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0010 =     16. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0064  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0064   0350 =    848. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0032  __text_start
       0032  __start
       0054  _exit
       0055  _delay_us
       0058  _delay_nus
       0067  _delay_ms
       006A  _delay_nms
       0079  _uart0_init
       0084  _send_data
       0088  _send_dat
       00AB  _Send_595
       00BC  _temptoseg
       00F9  _uart0_rx_isr
       015A  _keyscan
       0186  _main
       01DA  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0010 =     16. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _ledcode
       0070  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0070   0047 =     71. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0070  __bss_start
       0070  _display_data
       0074  _count
       0075  _com_in_buf
       00A7  _shu4
       00A8  _shu3
       00A9  _shu2
       00AA  _shu1
       00AB  _mode
       00AC  _crcdat
       00AE  _geshu
       00AF  _shu
       00B3  _datbuf
       00B7  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0030 =     48. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
delay.o	[ delay.c ]
mian.o	[ mian.c ]
<library>	

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512

