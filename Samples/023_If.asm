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

                     .global   w
w:                   .space       1                         ; char

                     .global   x
x:                   .space       1                         ; char

                     .global   y
y:                   .space       1                         ; char

                     .global   z
z:                   .space       1                         ; char
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code

                     .global   main
main:                ; ###########################################
                     ; # Function: main                     
                     ; #   Return: unsigned int  (r20,r21)  
                     ; #   Params: lY               @Y+8   size=4 long , Class[_____]
                     ; #         : sY               @Y+6   size=2 short , Class[_____]
                     ; #         : bY               @Y+5   size=1 char , Class[_____]
                     ; #   CPU   : <return addr>    @Y+3   size=2
                     ; #         : <saved fptr>     @Y+1   size=2
                     ; #   Locals: <none>                   
                     ; #         : sizeof(locals) = 0       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== For Statement ================= ; L_Statement_For_000006
L_ForTest_000002:    ;      For Test ------------           ; L_Statement_For_000006
L_ForBody_000003:    ;      For Body ------------           ; L_Statement_For_000006
L_ForCont_000004:    ;      For Body end --------           ; L_Statement_For_000006
                     rjmp      L_ForTest_000002             ;   2:
L_ForBreak_000005:   ;      For End -------------           ; L_Statement_For_000006
                     ; ==== For Statement ================= ; L_Statement_For_000011
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
L_ForTest_000007:    ;      For Test ------------           ; L_Statement_For_000011
L_ForBody_000008:    ;      For Body ------------           ; L_Statement_For_000011
L_ForCont_000009:    ;      For Body end --------           ; L_Statement_For_000011
                     rjmp      L_ForTest_000007             ;   2:
L_ForBreak_000010:   ;      For End -------------           ; L_Statement_For_000011
                     ; ==== For Statement ================= ; L_Statement_For_000016
L_ForTest_000012:    ;      For Test ------------           ; L_Statement_For_000016
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     tst       r20                          ;   1: Cast Byte to Flag
                     breq      L_ForBreak_000015            ; 1/2: branch if FALSE
                                                            ;    : fall through on TRUE
L_ForBody_000013:    ;      For Body ------------           ; L_Statement_For_000016
L_ForCont_000014:    ;      For Body end --------           ; L_Statement_For_000016
                     rjmp      L_ForTest_000012             ;   2:
L_ForBreak_000015:   ;      For End -------------           ; L_Statement_For_000016
                     ; ==== For Statement ================= ; L_Statement_For_000021
L_ForTest_000017:    ;      For Test ------------           ; L_Statement_For_000021
L_ForBody_000018:    ;      For Body ------------           ; L_Statement_For_000021
L_ForCont_000019:    ;      For Body end --------           ; L_Statement_For_000021
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     rjmp      L_ForTest_000017             ;   2:
L_ForBreak_000020:   ;      For End -------------           ; L_Statement_For_000021
                     ; ==== For Statement ================= ; L_Statement_For_000026
L_ForTest_000022:    ;      For Test ------------           ; L_Statement_For_000026
L_ForBody_000023:    ;      For Body ------------           ; L_Statement_For_000026
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000027
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     ;      Expr end ------------           ; L_Statement_Expression_000027
L_ForCont_000024:    ;      For Body end --------           ; L_Statement_For_000026
                     rjmp      L_ForTest_000022             ;   2:
L_ForBreak_000025:   ;      For End -------------           ; L_Statement_For_000026
                     ; ==== For Statement ================= ; L_Statement_For_000032
                     ldi       r30, lo8(w)                  ;   1: Z = &w
                     ldi       r31, hi8(w)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @w
L_ForTest_000028:    ;      For Test ------------           ; L_Statement_For_000032
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     tst       r20                          ;   1: Cast Byte to Flag
                     breq      L_ForBreak_000031            ; 1/2: branch if FALSE
                                                            ;    : fall through on TRUE
L_ForBody_000029:    ;      For Body ------------           ; L_Statement_For_000032
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000033
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     ;      Expr end ------------           ; L_Statement_Expression_000033
L_ForCont_000030:    ;      For Body end --------           ; L_Statement_For_000032
                     ldi       r30, lo8(y)                  ;   1: Z = &y
                     ldi       r31, hi8(y)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @y
                     rjmp      L_ForTest_000028             ;   2:
L_ForBreak_000031:   ;      For End -------------           ; L_Statement_For_000032
                     ; ==== For Statement ================= ; L_Statement_For_000038
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     ldi       r30, lo8(y)                  ;   1: Z = &y
                     ldi       r31, hi8(y)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @y
                     ldi       r30, lo8(z)                  ;   1: Z = &z
                     ldi       r31, hi8(z)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @z
L_ForTest_000034:    ;      For Test ------------           ; L_Statement_For_000038
                     ldi       r30, lo8(w)                  ;   1: Z = &w
                     ldi       r31, hi8(w)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @w
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r24, Z                       ;   1: byte <==  RAM @x
                     sub       r20, r24                     ;   1: Compare LT 8
                     brge      L_ForBreak_000037            ; 1/2:  branch if (signed) LT FALSE
                                                            ;    :  fall through on (signed) LT TRUE
L_ForBody_000035:    ;      For Body ------------           ; L_Statement_For_000038
                     ; ==== Compound Statement ============ ; L_Statement_compound_000039
                     ; ==== Break Statement =============== ; 
                     rjmp      L_ForBreak_000037            ;   2: break
                     ; ==== Continue Statement ============ ; 
                     rjmp      L_ForCont_000036             ;   2: continue
                     ;      Compound End --------           ; L_Statement_compound_000039
L_ForCont_000036:    ;      For Body end --------           ; L_Statement_For_000038
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     ldi       r30, lo8(y)                  ;   1: Z = &y
                     ldi       r31, hi8(y)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @y
                     ldi       r30, lo8(z)                  ;   1: Z = &z
                     ldi       r31, hi8(z)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @z
                     rjmp      L_ForTest_000034             ;   2:
L_ForBreak_000037:   ;      For End -------------           ; L_Statement_For_000038
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 0                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
