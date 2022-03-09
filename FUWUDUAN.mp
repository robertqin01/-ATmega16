NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0055 =     85. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       00A9  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   00AA   0A2A =   2602. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0055  __start
       0055  __text_start
       0077  _exit
       0078  _delay_us
       007B  _delay_nus
       008A  _delay_ms
       008D  _delay_nms
       009C  _uart0_init
       00A7  _send_data
       00AB  _LCDPort_Init
       00B6  _Write_Com
       00DA  _Write_Data_Byte
       00FA  _LCD_Init
       0120  _Write_Place_xy
       012F  _Write_Data_String
       0150  _Write_Data_char
       0164  _ScanKey
       0181  _main
       041E  _uart0_rx_isr
       04FC  _strlen
       0508  mod16u
       050A  div16u
       050B  xdiv16u
       0524  mod8u
       0526  div8u
       0527  xdiv8u
       053C  pop_xgset00FC
       0543  push_xgsetF0FC
       0545  push_xgset30FC
       0547  push_xgset00FC
       0549  push_xgset003C
       054E  push_xgsetF00C
       0555  pop_xgsetF00C
       055C  push_xgset303C
       0563  pop_xgset303C
       056A  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0055 =     85. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  _jiaxianshi
       0060  __data_start
       0065  _wupin_ming
       00A6  _wupin
       00B5  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   00B5   0051 =     81. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       00B5  __bss_start
       00B5  _jiner
       00B7  _jiner_jilu
       00BD  _jianshu_jilu
       00CF  _count
       00D0  _com_in_buf
       0102  _num
       0103  _ok
       0104  _mode
       0105  _xuhao
       0106  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0030 =     48. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

C:\iccv7avr\lib\crtatmega.o	[ crtatmega.s ]
delay.o	[ delay.c ]
fuwuqi.o	[ fuwuqi.C ]
<library>	[ strlen.s, div16u.s, div8u.s, gpop3.s, gpush.s, gpushz.s, gpusha.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512

