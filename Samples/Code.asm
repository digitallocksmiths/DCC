                                                            ; DCC AVR Output
                     .extern   SysTrap                      ; 

                     #define _IO_SPL   0x3D
                     #define _IO_SPH   0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################
                     .extern   baBlob                       ; Array[20] of (constant unsigned char)
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
                     .global   pA
pA:                  .space       2                         ; (generic) pointer
                     .global   xXor
xXor:                .space       2                         ; (generic) pointer
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code


                     ; ###############################################################
                     ; # Function: foo
                     ; ###############################################################
                     ; #    Param: x                r2-r5  size=2 
                     ; #   Return: void            
                     ; ###############################################################
                     .extern   foo


                     ; ###############################################################
                     ; # Function: bar
                     ; ###############################################################
                     ; #    Param: y                @Y+10  size=2 unsigned short , Class[_____]
                     ; #   CPU   : <return address> @Y+7   size=3
                     ; #         : <saved fptr>     @Y+5   size=2
                     ; #    Param: x                r2-r5  size=2 
                     ; #   Locals: i                @Y+3   size=2 int , Class[_____]
                     ; #         : j                @Y+1   size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 4
                     ; #   Return: void            
                     ; ###############################################################
                     .global   bar
bar:                 ; #### frame setup ################### ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     sbiw      r28, 4                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     movw      r2, r20                      ;   1: First parameter is regified
                     ; #### body text ##################### ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000002
                     ldi       r20, 0x0a                    ;   1: reg16 <== immediate #10
                     ldi       r21, 0x00                    ;   1:
                     std       Y+3, r20                     ;   2: local <== reg i
                     std       Y+4, r21                     ;   2:
                     ldi       r20, 0x02                    ;   1: reg16 <== immediate #2
                     ldi       r21, 0x00                    ;   1:
                     std       Y+1, r20                     ;   2: local <== reg j
                     std       Y+2, r21                     ;   2:
                     ;      Compound Body -------           ; L_Statement_compound_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000003
                     ldd       r20, Y+1                     ;   1: reg16 <== Local j @Frame:1
                     ldd       r21, Y+2                     ;   2:
                     ldd       r24, Y+3                     ;   1: reg16 <== Local i @Frame:3
                     ldd       r25, Y+4                     ;   2:
                     sub       r24, r20                     ;   1: Sub 16
                     sbc       r25, r21                     ;   1:
                     movw      r20, r24                     ;   1:
                     std       Y+3, r20                     ;   2: local <== reg i
                     std       Y+4, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000003
                     ;      Compound End --------           ; L_Statement_compound_000002
                     ; #### exit ########################## ; 
L_Exit_000001:       adiw      r28, 4                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         

                     ;.endseg                               ; === End of TEXT segment ===


                                                            ; 
                     .end                                   ; End of generated code.
                     ; eof                                  ; 
