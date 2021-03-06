; SKC AVR Output

#define		_IO_SPL	0x3D
#define		_IO_SPH	0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################
                     ;.endseg                               ; === End of CONST segment ===


                                                            ; #########################
                                                            ; # Start of INIT segment #
                     .section    INIT,  "a"                 ; #########################
                                                            ; This is the source of the initialization data
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code

                     .global   Shift
Shift:               ; ###########################################
                     ; # Function: Shift                    
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+17  size=2
                     ; #         : <saved fptr>     @Y+15  size=2
                     ; #   Locals: s8               @Y+14  size=1 char , Class[_____]
                     ; #         : s16              @Y+12  size=2 short , Class[_____]
                     ; #         : s32              @Y+8   size=4 long , Class[_____]
                     ; #         : u8               @Y+7   size=1 unsigned char , Class[_____]
                     ; #         : u16              @Y+5   size=2 unsigned short , Class[_____]
                     ; #         : u32              @Y+1   size=4 unsigned long , Class[_____]
                     ; #         : sizeof(locals) = 14      
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 14                      ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldi       r20, 0xff                    ;   1: Immediate byte 255
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000003
                     ldi       r20, 0x3f                    ;   1: Immediate byte 63
                     ;      Expr end ------------           ; L_Statement_Expression_000003
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000004
                     ldi       r20, 0x7f                    ;   1: Immediate byte 127
                     ;      Expr end ------------           ; L_Statement_Expression_000004
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldi       r20, 0x3f                    ;   1: Immediate byte 63
                     ;      Expr end ------------           ; L_Statement_Expression_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000006
                     ldi       r20, 0x80                    ;   1: Immediate short 65408
                     ldi       r21, 0xff                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldi       r20, 0x80                    ;   1: Immediate short 16256
                     ldi       r21, 0x3f                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000007
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r20, 0x80                    ;   1: Immediate short 32640
                     ldi       r21, 0x7f                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldi       r20, 0x80                    ;   1: Immediate short 16256
                     ldi       r21, 0x3f                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000009
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldi       r20, 0x07                    ;   1: Immediate byte 7
                     push      r20                          ;   2:
                     ldd       r20, Y+14                    ;   2: reg8 <==s8
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000011             ; 2/3:
L_RSLagain_000012:   asr       r20                          ;   1: >> 8 (signed)
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000012            ; 2/3:
L_RSLdone_000011:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000013
                     ldi       r20, 0x08                    ;   1: Immediate byte 8
                     push      r20                          ;   2:
                     ldd       r20, Y+14                    ;   2: reg8 <==s8
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000014             ; 2/3:
L_RSLagain_000015:   asr       r20                          ;   1: >> 8 (signed)
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000015            ; 2/3:
L_RSLdone_000014:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000013
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000016
                     ldi       r20, 0x0f                    ;   1: Immediate byte 15
                     push      r20                          ;   2:
                     ldd       r20, Y+12                    ;   2: reg16 <==s16
                     ldd       r21, Y+13                    ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000017             ; 2/3:
L_RSLagain_000018:   asr       r21                          ;   1: >> 16 (signed)
                     ror       r20                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000018            ; 2/3:
L_RSLdone_000017:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000016
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000019
                     ldi       r20, 0x10                    ;   1: Immediate byte 16
                     push      r20                          ;   2:
                     ldd       r20, Y+12                    ;   2: reg16 <==s16
                     ldd       r21, Y+13                    ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000020             ; 2/3:
L_RSLagain_000021:   asr       r21                          ;   1: >> 16 (signed)
                     ror       r20                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000021            ; 2/3:
L_RSLdone_000020:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000019
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000022
                     ldi       r20, 0x1f                    ;   1: Immediate byte 31
                     push      r20                          ;   2:
                     ldd       r20, Y+8                     ;   2: reg32 <== s32
                     ldd       r21, Y+9                     ;   2:
                     ldd       r22, Y+10                    ;   2:
                     ldd       r23, Y+11                    ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000023             ; 2/3:
L_RSLagain_000024:   asr       r23                          ;   1: >> 32 (signed)
                     ror       r22                          ;   1:
                     ror       r21                          ;   1:
                     ror       r20                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000024            ; 2/3:
L_RSLdone_000023:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000022
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000025
                     ldi       r20, 0x20                    ;   1: Immediate byte 32
                     push      r20                          ;   2:
                     ldd       r20, Y+12                    ;   2: reg16 <==s16
                     ldd       r21, Y+13                    ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000026             ; 2/3:
L_RSLagain_000027:   asr       r21                          ;   1: >> 16 (signed)
                     ror       r20                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000027            ; 2/3:
L_RSLdone_000026:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000025
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000028
                     ldi       r20, 0x07                    ;   1: Immediate byte 7
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: reg8 <==u8
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000029             ; 2/3:
L_RSLagain_000030:   lsr       r20                          ;   1: >> 8 (unsigned)
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000030            ; 2/3:
L_RSLdone_000029:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000028
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000031
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000031
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000032
                     ldi       r20, 0x0f                    ;   1: Immediate byte 15
                     push      r20                          ;   2:
                     ldd       r20, Y+5                     ;   2: reg16 <==u16
                     ldd       r21, Y+6                     ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000033             ; 2/3:
L_RSLagain_000034:   lsr       r21                          ;   1: >> 16 (unsigned)
                     ror       r20                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000034            ; 2/3:
L_RSLdone_000033:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000032
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000035
                     ldi       r20, 0x00                    ;   1: Immediate short 0
                     ldi       r21, 0x00                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000035
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000036
                     ldi       r20, 0x1f                    ;   1: Immediate byte 31
                     push      r20                          ;   2:
                     ldd       r20, Y+1                     ;   2: reg32 <== u32
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Right
                     breq      L_RSLdone_000037             ; 2/3:
L_RSLagain_000038:   lsr       r23                          ;   1: >> 32 (unsigned)
                     ror       r22                          ;   1:
                     ror       r21                          ;   1:
                     ror       r20                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_RSLagain_000038            ; 2/3:
L_RSLdone_000037:                                           ; ---: Shift Right done.
                     ;      Expr end ------------           ; L_Statement_Expression_000036
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000039
                     ldi       r20, 0x00                    ;   1: Immediate short 0
                     ldi       r21, 0x00                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000039
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000040
                     ldi       r20, 0xfe                    ;   1: Immediate byte 254
                     ;      Expr end ------------           ; L_Statement_Expression_000040
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000041
                     ldi       r20, 0xfe                    ;   1: Immediate byte 254
                     ;      Expr end ------------           ; L_Statement_Expression_000041
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000042
                     ldi       r20, 0xfe                    ;   1: Immediate byte 254
                     ;      Expr end ------------           ; L_Statement_Expression_000042
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000043
                     ldi       r20, 0xfe                    ;   1: Immediate byte 254
                     ;      Expr end ------------           ; L_Statement_Expression_000043
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000044
                     ldi       r20, 0x00                    ;   1: Immediate short 65024
                     ldi       r21, 0xfe                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000044
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000045
                     ldi       r20, 0x00                    ;   1: Immediate short 65024
                     ldi       r21, 0xfe                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000045
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000046
                     ldi       r20, 0x00                    ;   1: Immediate short 65024
                     ldi       r21, 0xfe                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000046
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000047
                     ldi       r20, 0x00                    ;   1: Immediate short 65024
                     ldi       r21, 0xfe                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000047
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000048
                     ldi       r20, 0x07                    ;   1: Immediate byte 7
                     push      r20                          ;   2:
                     ldd       r20, Y+14                    ;   2: reg8 <==s8
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Left
                     breq      L_LSLdone_000049             ; 2/3:
L_LSLagain_000050:   lsl       r20                          ;   1: << 8
                     dec       r24                          ;   1:
                     brne      L_LSLagain_000050            ; 2/3:
L_LSLdone_000049:                                           ; ---: Shift left done.
                     ;      Expr end ------------           ; L_Statement_Expression_000048
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000051
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000051
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000052
                     ldi       r20, 0x0f                    ;   1: Immediate byte 15
                     push      r20                          ;   2:
                     ldd       r20, Y+12                    ;   2: reg16 <==s16
                     ldd       r21, Y+13                    ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Left
                     breq      L_LSLdone_000053             ; 2/3:
L_LSLagain_000054:   lsl       r20                          ;   1: << 16
                     rol       r21                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_LSLagain_000054            ; 2/3:
L_LSLdone_000053:                                           ; ---: Shift left done.
                     ;      Expr end ------------           ; L_Statement_Expression_000052
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000055
                     ldi       r20, 0x00                    ;   1: Immediate short 0
                     ldi       r21, 0x00                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000055
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000056
                     ldi       r20, 0x1f                    ;   1: Immediate byte 31
                     push      r20                          ;   2:
                     ldd       r20, Y+8                     ;   2: reg32 <== s32
                     ldd       r21, Y+9                     ;   2:
                     ldd       r22, Y+10                    ;   2:
                     ldd       r23, Y+11                    ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Left
                     breq      L_LSLdone_000057             ; 2/3:
L_LSLagain_000058:   lsl       r20                          ;   1: << 32
                     rol       r21                          ;   1:
                     rol       r22                          ;   1:
                     rol       r23                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_LSLagain_000058            ; 2/3:
L_LSLdone_000057:                                           ; ---: Shift left done.
                     ;      Expr end ------------           ; L_Statement_Expression_000056
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000059
                     ldi       r20, 0x00                    ;   1: Immediate short 0
                     ldi       r21, 0x00                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000059
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000060
                     ldi       r20, 0x07                    ;   1: Immediate byte 7
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: reg8 <==u8
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Left
                     breq      L_LSLdone_000061             ; 2/3:
L_LSLagain_000062:   lsl       r20                          ;   1: << 8
                     dec       r24                          ;   1:
                     brne      L_LSLagain_000062            ; 2/3:
L_LSLdone_000061:                                           ; ---: Shift left done.
                     ;      Expr end ------------           ; L_Statement_Expression_000060
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000063
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000063
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000064
                     ldi       r20, 0x0f                    ;   1: Immediate byte 15
                     push      r20                          ;   2:
                     ldd       r20, Y+5                     ;   2: reg16 <==u16
                     ldd       r21, Y+6                     ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Left
                     breq      L_LSLdone_000065             ; 2/3:
L_LSLagain_000066:   lsl       r20                          ;   1: << 16
                     rol       r21                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_LSLagain_000066            ; 2/3:
L_LSLdone_000065:                                           ; ---: Shift left done.
                     ;      Expr end ------------           ; L_Statement_Expression_000064
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000067
                     ldi       r20, 0x00                    ;   1: Immediate short 0
                     ldi       r21, 0x00                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000067
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000068
                     ldi       r20, 0x1f                    ;   1: Immediate byte 31
                     push      r20                          ;   2:
                     ldd       r20, Y+1                     ;   2: reg32 <== u32
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     pop       r24                          ;   2:
                     Tst       r24                          ;   1: Shift Left
                     breq      L_LSLdone_000069             ; 2/3:
L_LSLagain_000070:   lsl       r20                          ;   1: << 32
                     rol       r21                          ;   1:
                     rol       r22                          ;   1:
                     rol       r23                          ;   1:
                     dec       r24                          ;   1:
                     brne      L_LSLagain_000070            ; 2/3:
L_LSLdone_000069:                                           ; ---: Shift left done.
                     ;      Expr end ------------           ; L_Statement_Expression_000068
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000071
                     ldi       r20, 0x00                    ;   1: Immediate short 0
                     ldi       r21, 0x00                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000071
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 14                      ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
