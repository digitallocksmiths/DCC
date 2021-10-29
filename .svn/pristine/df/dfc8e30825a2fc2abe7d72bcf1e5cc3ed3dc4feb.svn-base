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

                     .global   Unary
Unary:               ; ###########################################
                     ; # Function: Unary                    
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+12  size=2
                     ; #         : <saved fptr>     @Y+10  size=2
                     ; #   Locals: c                @Y+9   size=1 char , Class[_____]
                     ; #         : l                @Y+5   size=4 long , Class[_____]
                     ; #         : x                @Y+3   size=2  Pointer to char , Class[_____]
                     ; #         : y                @Y+1   size=2  Pointer to  Pointer to char , Class[_____]
                     ; #         : sizeof(locals) = 9       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 9                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000003
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000003
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000004
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000004
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldi       r20, 0xff                    ;   1: Immediate byte 255
                     ;      Expr end ------------           ; L_Statement_Expression_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000006
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldi       r20, 0xff                    ;   1: Immediate byte 255
                     ;      Expr end ------------           ; L_Statement_Expression_000007
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldi       r20, 0xff                    ;   1: Immediate byte 255
                     ;      Expr end ------------           ; L_Statement_Expression_000009
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000011
                     ldi       r20, 0xaa                    ;   1: Immediate byte 170
                     ;      Expr end ------------           ; L_Statement_Expression_000011
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000012
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000012
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000013
                     ldi       r20, 0x55                    ;   1: Immediate byte 85
                     ;      Expr end ------------           ; L_Statement_Expression_000013
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000014
                     ldi       r20, 0x55                    ;   1: Immediate long -171
                     ldi       r21, 0xff                    ;   1:
                     ldi       r22, 0xff                    ;   1:
                     ldi       r23, 0xff                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000014
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000015
                     ldi       r20, 0x01                    ;   1: Immediate long 1
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000015
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000016
                     movw      r24, r28                     ;   1: Z = c
                     adiw      r24, 0x09                    ;   2:
                     movw      r20, r24                     ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000016
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000017
                     movw      r24, r28                     ;   1: Z = l
                     adiw      r24, 0x05                    ;   2:
                     movw      r20, r24                     ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000017
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000018
                     ldd       r20, Y+9                     ;   2: reg8 <==c
                     ;      Expr end ------------           ; L_Statement_Expression_000018
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000019
                     ldd       r20, Y+5                     ;   2: reg32 <== l
                     ldd       r21, Y+6                     ;   2:
                     ldd       r22, Y+7                     ;   2:
                     ldd       r23, Y+8                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000019
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000020
                     ldd       r20, Y+3                     ;   2: reg16 <==x
                     ldd       r21, Y+4                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000020
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000021
                     ldd       r20, Y+1                     ;   2: reg16 <==y
                     ldd       r21, Y+2                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000021
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000022
                     ldd       r20, Y+3                     ;   2: reg16 <==x
                     ldd       r21, Y+4                     ;   2:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ;      Expr end ------------           ; L_Statement_Expression_000022
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000023
                     ldd       r20, Y+1                     ;   2: reg16 <==y
                     ldd       r21, Y+2                     ;   2:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000023
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 9                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
