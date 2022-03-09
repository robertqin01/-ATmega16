NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0073 =    115. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       00C7  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00C8   0B62 =   2914. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0064  __start
       0064  __text_start
       0086  _exit
       0087  _delay_us
       008A  _delay_nus
       0099  _delay_ms
       009C  _delay_nms
       00AB  _uart0_init
       00B6  _send_data
       00BA  _LCDPort_Init
       00C5  _Write_Com
       00E9  _Write_Data_Byte
       0109  _ScanKey
       0126  _LCD_Init
       014C  _Write_Place_xy
       015B  _Write_Data_String
       017C  _main
       03CE  _uart0_rx_isr
       05A9  _strlen
       05B5  mod16u
       05B7  div16u
       05B8  xdiv16u
       05D1  mod8u
       05D3  div8u
       05D4  xdiv8u
       05E9  empy16s
       05F9  push_xgsetF00C
       0600  pop_xgsetF00C
       0607  push_xgset303C
       060E  pop_xgset303C
       0615  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0073 =    115. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _wupin
       0066  _jiaxianshi
       006B  _wupin_ming
       00D3  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   00D3   0050 =     80. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       00D3  __bss_start
       00D3  _num
       00D4  _jianshu
       00D5  _mode
       00D6  _count
       00D7  _com_in_buf
       0109  _ok
       010A  _xuhao
       010B  _jiner_jilu
       0111  _jianshu_jilu
       0123  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0030 =     48. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
delay.o	[ delay.c ]
zhongduan.o	[ zhongduan.C ]
<library>	[ strlen.s, div16u.s, div8u.s, emul16s.s, gpushz.s, gpusha.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512

