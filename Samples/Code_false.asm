; SKC AVR Output

#define		_IO_SPL	0x3D
#define		_IO_SPH	0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################
                     .global   lGlbConst
lGlbConst:                                                  ; long
                     .long     0                            ;     0x00000000 -> lGlbConst
                     .global   baGlbRomArray
baGlbRomArray:                                              ; Array[10] of unsigned char
                     .byte     0                            ;           0x00 -> baGlbRomArray[0]
                     .byte     0                            ;           0x00 -> -------------[1]
                     .byte     0                            ;           0x00 -> -------------[2]
                     .byte     0                            ;           0x00 -> -------------[3]
                     .byte     0                            ;           0x00 -> -------------[4]
                     .byte     0                            ;           0x00 -> -------------[5]
                     .byte     0                            ;           0x00 -> -------------[6]
                     .byte     0                            ;           0x00 -> -------------[7]
                     .byte     0                            ;           0x00 -> -------------[8]
                     .byte     0                            ;           0x00 -> -------------[9]
                     .global   pGlbConst2
pGlbConst2:                                                 ; constant pointer
                     .word     0                            ;         0x0000 -> pGlbConst2
                     .global   pGlbConst3
pGlbConst3:                                                 ; constant pointer
                     .word     0                            ;         0x0000 -> pGlbConst3
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
                     .global   aInvokeCounts
aInvokeCounts:       .space      32                         ; Array[16] of unsigned short 
                     .global   pA
pA:                  .space       2                         ; (generic) pointer
                     .global   lGlbVar
lGlbVar:             .space       4                         ; long
                     .global   baGlbRamArray
baGlbRamArray:       .space      10                         ; Array[10] of unsigned char
                     .global   pGlbVar
pGlbVar:             .space       2                         ; (generic) pointer
                     .global   pGlbConst1
pGlbConst1:          .space       2                         ; (generic) pointer
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code


                     ; ###########################################
                     ; # Function: fooReadTests             
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+25  size=2
                     ; #         : <saved fptr>     @Y+23  size=2
                     ; #   Locals: lLocalVar        @Y+19  size=4 long , Class[_____]
                     ; #         : baLocalArray     @Y+9   size=10 Array[10] of unsigned char , Class[_____]
                     ; #         : pLocalVar        @Y+7   size=2 Pointer to unsigned char , Class[_____]
                     ; #         : pLocalConst1     @Y+5   size=2 Pointer to const unsigned short , Class[_____]
                     ; #         : pLocalConst2     @Y+3   size=2 const Pointer to unsigned short , Class[_____]
                     ; #         : pLocalConst3     @Y+1   size=2 const Pointer to const unsigned short , Class[_____]
                     ; #         : sizeof(locals) = 22      
                     ; ###########################################
                     .global   fooReadTests
fooReadTests:        ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     sbiw      r28, 22                      ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 22                      ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ; ###########################################
                     ; # Function: fooWriteTests            
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+25  size=2
                     ; #         : <saved fptr>     @Y+23  size=2
                     ; #   Locals: lLocalVar        @Y+19  size=4 long , Class[_____]
                     ; #         : baLocalArray     @Y+9   size=10 Array[10] of unsigned char , Class[_____]
                     ; #         : pLocalVar        @Y+7   size=2 Pointer to unsigned char , Class[_____]
                     ; #         : pLocalConst1     @Y+5   size=2 Pointer to const unsigned short , Class[_____]
                     ; #         : pLocalConst2     @Y+3   size=2 const Pointer to unsigned short , Class[_____]
                     ; #         : pLocalConst3     @Y+1   size=2 const Pointer to const unsigned short , Class[_____]
                     ; #         : sizeof(locals) = 22      
                     ; ###########################################
                     .global   fooWriteTests
fooWriteTests:       ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     sbiw      r28, 22                      ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000003
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000004
                     ldi       r20, 0x01                    ;   1: reg32 <== immediate #1
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     sts       lGlbVar, r20                 ;   1: lGlbVar <== reg 
                     sts       lGlbVar+1, r21               ;   1:
                     sts       lGlbVar+2, r22               ;   1:
                     sts       lGlbVar+3, r23               ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000004
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldi       r20, 0xff                    ;   1: reg8 <== immediate #255
                     ;      Expr end ------------           ; L_Statement_Expression_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000006
                     ldi       r20, 0x02                    ;   1: reg8 <== immediate #2
                     ;      Expr end ------------           ; L_Statement_Expression_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldi       r20, 0x03                    ;   1: reg8 <== immediate #3
                     sts       baGlbRamArray, r20           ;   1: baGlbRamArray <== reg 
                     ;      Expr end ------------           ; L_Statement_Expression_000007
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r20, 0x04                    ;   1: reg8 <== immediate #4
                     sts       baGlbRamArray, r20           ;   1: baGlbRamArray <== reg 
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldi       r20, 0x05                    ;   1: reg8 <== immediate #5
                     sts       baGlbRamArray+3, r20         ;   1: baGlbRamArray <== reg 
                     ;      Expr end ------------           ; L_Statement_Expression_000009
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldi       r20, 0x02                    ;   1: reg8 <== immediate #2
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000011
                     ldi       r20, 0x02                    ;   1: reg8 <== immediate #2
                     ;      Expr end ------------           ; L_Statement_Expression_000011
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000012
                     ldi       r20, 0x02                    ;   1: reg8 <== immediate #2
                     ;      Expr end ------------           ; L_Statement_Expression_000012
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000013
                     ldi       r20, 0x01                    ;   1: reg16 <== immediate #1
                     ldi       r21, 0x00                    ;   1:
                     sts       pGlbVar, r20                 ;   1: pGlbVar <== reg 
                     sts       pGlbVar+1, r21               ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000013
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000014
                     ldi       r20, 0x02                    ;   1: reg8 <== immediate #2
                     lds       r30, pGlbVar                 ;   1: reg16 <== Global pGlbVar[0]
                     lds       r31, pGlbVar+1               ;   1:
                     st        Z, r20                       ;   1: @Z <== reg
                     ;      Expr end ------------           ; L_Statement_Expression_000014
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000015
                     ldi       r20, 0x03                    ;   1: reg8 <== immediate #3
                     lds       r30, pGlbVar                 ;   1: reg16 <== Global pGlbVar[0]
                     lds       r31, pGlbVar+1               ;   1:
                     std       Z+2, r20                     ;   2: @Z <== reg
                     ;      Expr end ------------           ; L_Statement_Expression_000015
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000016
                     ldi       r20, 0x01                    ;   1: reg16 <== immediate #1
                     ldi       r21, 0x00                    ;   1:
                     sts       pGlbConst1, r20              ;   1: pGlbConst1 <== reg 
                     sts       pGlbConst1+1, r21            ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000016
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000017
                     ldi       r20, 0x02                    ;   1: reg8 <== immediate #2
                     ;      Expr end ------------           ; L_Statement_Expression_000017
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000018
                     ldi       r20, 0x03                    ;   1: reg8 <== immediate #3
                     ;      Expr end ------------           ; L_Statement_Expression_000018
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000019
                     ldi       r20, 0x04                    ;   1: reg8 <== immediate #4
                     ;      Expr end ------------           ; L_Statement_Expression_000019
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000020
                     ldi       r20, 0x05                    ;   1: reg16 <== immediate #5
                     ldi       r21, 0x00                    ;   1:
                     ldi       r30, lo8(pGlbConst2)         ;   1: reg16 <== ROM Global pGlbConst2[0]
                     ldi       r31, hi8(pGlbConst2)         ;   1:
                     lpm       r24, Z+                      ;   3:
                     lpm       r25, Z+                      ;   3:
                     movw      r30, r24                     ;   1: de-ref pointer
                     st        Z, r20                       ;   1: @Z <== reg
                     std       Z+1, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000020
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000021
                     ldi       r20, 0x06                    ;   1: reg16 <== immediate #6
                     ldi       r21, 0x00                    ;   1:
                     ldi       r30, lo8(pGlbConst2)         ;   1: reg16 <== ROM Global pGlbConst2[0]
                     ldi       r31, hi8(pGlbConst2)         ;   1:
                     lpm       r24, Z+                      ;   3:
                     lpm       r25, Z+                      ;   3:
                     movw      r30, r20                     ;   1: pointer base
                     std       Z+4, r20                     ;   2: @Z <== reg
                     std       Z+5, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000021
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000022
                     ldi       r20, 0x07                    ;   1: reg8 <== immediate #7
                     ;      Expr end ------------           ; L_Statement_Expression_000022
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000023
                     ldi       r20, 0x08                    ;   1: reg8 <== immediate #8
                     ;      Expr end ------------           ; L_Statement_Expression_000023
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000024
                     ldi       r20, 0x09                    ;   1: reg8 <== immediate #9
                     ;      Expr end ------------           ; L_Statement_Expression_000024
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000025
                     ldi       r20, 0x01                    ;   1: reg32 <== immediate #1
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     std       Y+19, r20                    ;   2:  local <== reg lLocalVar
                     std       Y+20, r21                    ;   2:
                     std       Y+21, r22                    ;   2:
                     std       Y+22, r23                    ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000025
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000026
                     ldi       r20, 0x02                    ;   1: reg8 <== immediate #2
                     ;      Expr end ------------           ; L_Statement_Expression_000026
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000027
                     ldi       r20, 0x03                    ;   1: reg8 <== immediate #3
                     std       Y+9, r20                     ;   2:  local <== reg baLocalArray
                     ;      Expr end ------------           ; L_Statement_Expression_000027
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000028
                     ldi       r20, 0x04                    ;   1: reg8 <== immediate #4
                     std       Y+14, r20                    ;   2:  local <== reg baLocalArray
                     ;      Expr end ------------           ; L_Statement_Expression_000028
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000029
                     ldi       r20, 0x05                    ;   1: reg16 <== immediate #5
                     ldi       r21, 0x00                    ;   1:
                     std       Y+7, r20                     ;   2:  local <== reg pLocalVar
                     std       Y+8, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000029
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000030
                     ldi       r20, 0x06                    ;   1: reg16 <== immediate #6
                     ldi       r21, 0x00                    ;   1:
                     std       Y+5, r20                     ;   2:  local <== reg pLocalConst1
                     std       Y+6, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000030
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000031
                     ldi       r20, 0x07                    ;   1: reg8 <== immediate #7
                     ;      Expr end ------------           ; L_Statement_Expression_000031
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000032
                     ldi       r20, 0x08                    ;   1: reg8 <== immediate #8
                     ;      Expr end ------------           ; L_Statement_Expression_000032
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000033
                     ldi       r20, 0x09                    ;   1: reg8 <== immediate #9
                     ldd       r30, Y+7                     ;   1: reg16 <== Local pLocalVar @Frame:7
                     ldd       r31, Y+8                     ;   2:
                     st        Z, r20                       ;   1: @Z <== reg
                     ;      Expr end ------------           ; L_Statement_Expression_000033
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000034
                     ldi       r20, 0x0a                    ;   1: reg8 <== immediate #10
                     ;      Expr end ------------           ; L_Statement_Expression_000034
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000035
                     ldi       r20, 0x0b                    ;   1: reg16 <== immediate #11
                     ldi       r21, 0x00                    ;   1:
                     ldd       r30, Y+3                     ;   1: reg16 <== Local pLocalConst2 @Frame:3
                     ldd       r31, Y+4                     ;   2:
                     st        Z, r20                       ;   1: @Z <== reg
                     std       Z+1, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000035
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000036
                     ldi       r20, 0x0c                    ;   1: reg8 <== immediate #12
                     ;      Expr end ------------           ; L_Statement_Expression_000036
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000037
                     ldi       r20, 0x0d                    ;   1: reg8 <== immediate #13
                     ldd       r30, Y+7                     ;   1: reg16 <== Local pLocalVar @Frame:7
                     ldd       r31, Y+8                     ;   2:
                     std       Z+2, r20                     ;   2: @Z <== reg
                     ;      Expr end ------------           ; L_Statement_Expression_000037
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000038
                     ldi       r20, 0x0e                    ;   1: reg8 <== immediate #14
                     ;      Expr end ------------           ; L_Statement_Expression_000038
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000039
                     ldi       r20, 0x0f                    ;   1: reg16 <== immediate #15
                     ldi       r21, 0x00                    ;   1:
                     ldd       r30, Y+3                     ;   1: reg16 <== Local pLocalConst2 @Frame:3
                     ldd       r31, Y+4                     ;   2:
                     std       Z+8, r20                     ;   2: @Z <== reg
                     std       Z+9, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000039
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000040
                     ldi       r20, 0x10                    ;   1: reg8 <== immediate #16
                     ;      Expr end ------------           ; L_Statement_Expression_000040
                     ;      Compound End --------           ; L_Statement_compound_000003
                     ; #### exit ################           ; 
L_Exit_000002:       adiw      r28, 22                      ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
