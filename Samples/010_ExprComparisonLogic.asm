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

                     .global   ComparisonLogic
ComparisonLogic:     ; ###########################################
                     ; # Function: ComparisonLogic          
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+11  size=2
                     ; #         : <saved fptr>     @Y+9   size=2
                     ; #   Locals: c                @Y+8   size=1 char , Class[_____]
                     ; #         : c2               @Y+7   size=1 char , Class[_____]
                     ; #         : s                @Y+5   size=2 short , Class[_____]
                     ; #         : l                @Y+1   size=4 long , Class[_____]
                     ; #         : sizeof(locals) = 8       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 8                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical And
                     breq      L_LAndOut_000004             ; 1/2:
                     ldd       r20, Y+5                     ;   2: reg16 <==s
                     ldd       r21, Y+6                     ;   2:
                     or        r20, r21                     ;   1: Cast Short to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
L_LAndOut_000004:                                           ;    :
                     tst       r20                          ;   1: Logical And
                     breq      L_LAndOut_000003             ; 1/2:
                     ldd       r20, Y+1                     ;   2: reg32 <== l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     or        r20, r21                     ;   1: Cast Long to Flag
                     or        r20, r22                     ;   1:
                     or        r20, r23                     ;   1:
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
L_LAndOut_000003:                                           ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical And
                     breq      L_LAndOut_000006             ; 1/2:
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
L_LAndOut_000006:                                           ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000007
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000009
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical And
                     breq      L_LAndOut_000011             ; 1/2:
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
L_LAndOut_000011:                                           ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000012
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical And
                     breq      L_LAndOut_000013             ; 1/2:
                     ldd       r20, Y+7                     ;   2: reg8 <==c2
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
L_LAndOut_000013:                                           ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000012
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000014
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical And
                     breq      L_LAndOut_000016             ; 1/2:
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
L_LAndOut_000016:                                           ;    :
                     tst       r20                          ;   1: Logical And
                     breq      L_LAndOut_000015             ; 1/2:
                     ldd       r20, Y+7                     ;   2: reg8 <==c2
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
L_LAndOut_000015:                                           ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000014
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000017
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000017
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000018
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000018
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000019
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000019
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000020
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical And
                     breq      L_LAndOut_000021             ; 1/2:
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
L_LAndOut_000021:                                           ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000020
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000022
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000022
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000023
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical Or
                     brne      L_LOrOut_000024              ; 1/2:
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
L_LOrOut_000024:                                            ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000023
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000025
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000025
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000026
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000026
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000027
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000027
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000028
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical Or
                     brne      L_LOrOut_000029              ; 1/2:
                     ldd       r20, Y+7                     ;   2: reg8 <==c2
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
L_LOrOut_000029:                                            ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000028
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000030
                     ldd       r20, Y+8                     ;   2: reg8 <==c
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
                     tst       r20                          ;   1: Logical Or
                     brne      L_LOrOut_000032              ; 1/2:
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
L_LOrOut_000032:                                            ;    :
                     tst       r20                          ;   1: Logical Or
                     brne      L_LOrOut_000031              ; 1/2:
                     ldd       r20, Y+7                     ;   2: reg8 <==c2
                     or        r20, r20                     ;   1: Cast Byte to Flag
                     subi      r20, 0x01                    ;   1:
                     sbc       r20, r20                     ;   1:
                     andi      r20, 0x01                    ;   1:
L_LOrOut_000031:                                            ;    :
                     ;      Expr end ------------           ; L_Statement_Expression_000030
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000033
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000033
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000034
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000034
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000035
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000035
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000036
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000036
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 8                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
