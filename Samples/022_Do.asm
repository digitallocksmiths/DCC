                                                            ; DCC AVR Output
                     .extern   SysTrap                      ; 

                     #define _IO_SPL   0x3D
                     #define _IO_SPH   0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################
                     ;.endseg                               ; === End of CONST segment ===


                                                            ; #########################
                                                            ; # Start of INIT segment #
                     .section    INIT,  "a"                 ; #########################
                                                            ; This is the source of the initialization data
;:                   a                                      ; (int)
                     .word     291                          ;         0x0123 -> a
;:                   a1                                     ; (int)
                     .word     2                            ;         0x0002 -> a1
;:                   a2                                     ; (int)
                     .word     3                            ;         0x0003 -> a2
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to
                     .global   a
a:                   .space       2                         ; (int)
                     .global   a1
a1:                  .space       2                         ; (int)
                     .global   a2
a2:                  .space       2                         ; (int)
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data
                     .global   x
x:                   .space       1                         ; (char)
                     .global   y
y:                   .space       1                         ; (char)
                     .global   z
z:                   .space       1                         ; (char)
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code


                     ; ###############################################################
                     ; # Function: main
                     ; ###############################################################
                     ; #    Param: lY               @Y+8   size=4 long , Class[_____]
                     ; #         : sY               @Y+6   size=2 short , Class[_____]
                     ; #   CPU   : <return address> @Y+3   size=3
                     ; #         : <saved fptr>     @Y+1   size=2
                     ; #    Param: bY               r2     size=1 char , Class[_____]
                     ; #   Locals: <none>
                     ; #   Return: unsigned int     r20,r21
                     ; ###############################################################
                     .global   main
main:                ; #### frame setup ################### ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     mov       r2, r20                      ;   1: First parameter is regified
                     ; #### body text ##################### ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ;      Compound Body -------           ; L_Statement_compound_000001
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldi       r20, 0x0a                    ;   1: reg8 <== immediate #10
                     sts       x, r20                       ;   1: x <== reg 
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ; ==== Do Statement ================== ; L_Statement_Do_000006
L_DoAgain_000003:    ;      Do Body ------------            ; L_Statement_Do_000006
                     ; ==== Compound Statement ============ ; L_Statement_compound_000007
                     ;      Compound Body -------           ; L_Statement_compound_000007
                     ;      Compound End --------           ; L_Statement_compound_000007
L_DoTest_000004:     ;      Do test -------------           ; L_Statement_Do_000006
                     lds       r20, x                       ;   1: reg8 <== Global x[0]
                     mov       r24, r20                     ;   1: post dec 8
                     dec       r24                          ;   1:
                     sts       x, r24                       ;   1: x <== reg 
                     tst       r20                          ;   1: Cast Byte to Flag
                     brne      L_DoAgain_000003             ; 1/2: branch if TRUE
                                                            ;    : fall through on FALSE
L_DoBreak_000005:    ;      Do end --------------           ; L_Statement_Do_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r20, 0x0a                    ;   1: reg8 <== immediate #10
                     sts       x, r20                       ;   1: x <== reg 
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Do Statement ================== ; L_Statement_Do_000012
L_DoAgain_000009:    ;      Do Body ------------            ; L_Statement_Do_000012
                     ; ==== Compound Statement ============ ; L_Statement_compound_000013
                     ;      Compound Body -------           ; L_Statement_compound_000013
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000014
                     lds       r20, y                       ;   1: reg8 <== Global y[0]
                     inc       r20                          ;   1: pre inc 8
                     sts       y, r20                       ;   1: y <== reg 
                     ;      Expr end ------------           ; L_Statement_Expression_000014
                     ; ==== Continue Statement ============ ; 
                     rjmp      L_DoTest_000010              ;   2: continue
                     ; ==== Break Statement =============== ; 
                     rjmp      L_DoBreak_000011             ;   2: break
                     ;      Compound End --------           ; L_Statement_compound_000013
L_DoTest_000010:     ;      Do test -------------           ; L_Statement_Do_000012
                     lds       r20, x                       ;   1: reg8 <== Global x[0]
                     mov       r24, r20                     ;   1: post dec 8
                     dec       r24                          ;   1:
                     sts       x, r24                       ;   1: x <== reg 
                     tst       r20                          ;   1: Cast Byte to Flag
                     brne      L_DoAgain_000009             ; 1/2: branch if TRUE
                                                            ;    : fall through on FALSE
L_DoBreak_000011:    ;      Do end --------------           ; L_Statement_Do_000012
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ########################## ; 
L_Exit_000000:       out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         

                     ;.endseg                               ; === End of TEXT segment ===


                                                            ; 
                     .end                                   ; End of generated code.
                     ; eof                                  ; 
