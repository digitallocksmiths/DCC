; SKC AVR Output

#define		_IO_SPL	0x3D
#define		_IO_SPH	0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################

                     .global   nRomVar
nRomVar:                                                    ; short 
                     .word     4660                         ;         0x1234 -> nRomVar
                     ;.endseg                               ; === End of CONST segment ===


                                                            ; #########################
                                                            ; # Start of INIT segment #
                     .section    INIT,  "a"                 ; #########################
                                                            ; This is the source of the initialization data
;:                   nRamVar                                ; short 
                     .word     22136                        ;         0x5678 -> nRamVar
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to

                     .global   nRamVar
nRamVar:             .space       2                         ; short 
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

                     .global   main
main:                ; ###########################################
                     ; # Function: main                     
                     ; #   Return: unsigned int  (r20,r21)  
                     ; #   Params: lParam           @Y+10  size=4 long , Class[_____]
                     ; #         : iParam           @Y+8   size=2 int , Class[_____]
                     ; #   CPU   : <return addr>    @Y+6   size=2
                     ; #         : <saved fptr>     @Y+4   size=2
                     ; #   Locals: cLocal           @Y+3   size=1 char , Class[_____]
                     ; #         : ilocal           @Y+1   size=2 short , Class[_____]
                     ; #         : sizeof(locals) = 3       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 3                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldi       r20, 0xad                    ;   1: Immediate short 57005
                     ldi       r21, 0xde                    ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000003
                     ldi       r30, lo8(nRomVar)            ;   1: Z = &nRomVar
                     ldi       r31, hi8(nRomVar)            ;   1:
                     lpm       r20, Z+                      ;   3: short <== ROM @nRomVar
                     lpm       r21, Z                       ;   3:
                     ;      Expr end ------------           ; L_Statement_Expression_000003
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000004
                     ldi       r30, lo8(nRamVar)            ;   1: Z = &nRamVar
                     ldi       r31, hi8(nRamVar)            ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @nRamVar
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000004
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldd       r20, Y+10                    ;   2: reg32 <== lParam
                     ldd       r21, Y+11                    ;   2:
                     ldd       r22, Y+12                    ;   2:
                     ldd       r23, Y+13                    ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000006
                     ldd       r20, Y+8                     ;   2: reg16 <==iParam
                     ldd       r21, Y+9                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldd       r20, Y+3                     ;   2: reg8 <==cLocal
                     ;      Expr end ------------           ; L_Statement_Expression_000007
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldd       r20, Y+1                     ;   2: reg16 <==ilocal
                     ldd       r21, Y+2                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 3                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
