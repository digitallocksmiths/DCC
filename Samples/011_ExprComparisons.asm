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

                     .global   Comparison
Comparison:          ; ###########################################
                     ; # Function: Comparison               
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+4   size=2
                     ; #         : <saved fptr>     @Y+2   size=2
                     ; #   Locals: c                @Y+1   size=1 char , Class[_____]
                     ; #         : sizeof(locals) = 1       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     push      r0                           ;   2: One byte. Local storage
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000003
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000003
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000004
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000004
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000006
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000007
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000009
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000011
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000011
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000012
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000012
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000013
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000013
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000014
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000014
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000015
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000015
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000016
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000016
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000017
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000017
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000018
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000018
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000019
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000019
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000020
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000020
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000021
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000021
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000022
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000022
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000023
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000023
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000024
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000024
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000025
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000025
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000026
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000026
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000027
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000027
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000028
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000028
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000029
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000029
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000030
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000030
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000031
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000031
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000032
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000032
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000033
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000033
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000034
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000034
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000035
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000035
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000036
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000036
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000037
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000037
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000038
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000038
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000039
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000039
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000040
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000040
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000041
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000041
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000042
                     ldi       r20, 0x01                    ;   1: Immediate byte 1
                     ;      Expr end ------------           ; L_Statement_Expression_000042
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000043
                     ldi       r20, 0x00                    ;   1: Immediate byte 0
                     ;      Expr end ------------           ; L_Statement_Expression_000043
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000044
                     ldd       r20, Y+1                     ;   2: reg8 <==c
                     ;      Expr end ------------           ; L_Statement_Expression_000044
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 1                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
