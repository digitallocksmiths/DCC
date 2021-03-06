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
;:                   a                                      ; int
                     .word     291                          ;         0x0123 -> a
;:                   a1                                     ; int
                     .word     2                            ;         0x0002 -> a1
;:                   a2                                     ; int
                     .word     3                            ;         0x0003 -> a2
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to

                     .global   a
a:                   .space       2                         ; int

                     .global   a1
a1:                  .space       2                         ; int

                     .global   a2
a2:                  .space       2                         ; int
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data

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
                     ; ==== If Statement ================== ; L_Statement_If_000002
                                                            ;    : Logical AND start. L_LAndRef_000006
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     tst       r20                          ;   1: Cast Byte to Flag
                     breq      L_LAndFalse_000007           ; 1/2: branch if FALSE
                                                            ;    : fall through on TRUE
                     ldi       r30, lo8(y)                  ;   1: Z = &y
                     ldi       r31, hi8(y)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @y
                     tst       r20                          ;   1: Cast Byte to Flag
                     brne      L_IfElse_000004              ; 1/2: branch if TRUE
                                                            ;    : fall through on FALSE
L_LAndFalse_000007:                                         ;    : Logical AND end (fall through to FALSE) L_LAndRef_000006
L_IfThen_000003:     ;      If Then ------------            ; L_Statement_If_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r20, 0x34                    ;   1: Immediate byte 52
                     ldi       r30, lo8(z)                  ;   1: Z = &z
                     ldi       r31, hi8(z)                  ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @z
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     rjmp      L_IfDone_000005              ; 1/2:
L_IfElse_000004:     ;      If Else ------------            ; L_Statement_If_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldi       r20, 0x45                    ;   1: Immediate byte 69
                     ldi       r30, lo8(z)                  ;   1: Z = &z
                     ldi       r31, hi8(z)                  ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @z
                     ;      Expr end ------------           ; L_Statement_Expression_000009
L_IfDone_000005:     ;      If End --------------           ; L_Statement_If_000002
                     ; ==== If Statement ================== ; L_Statement_If_000010
                                                            ;    : Logical OR start. L_LOrRef_000014
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     tst       r20                          ;   1: Cast Byte to Flag
                     breq      L_LOrTrue_000015             ; 1/2: branch if FALSE
                                                            ;    : fall through on TRUE
                     ldi       r30, lo8(y)                  ;   1: Z = &y
                     ldi       r31, hi8(y)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @y
                     tst       r20                          ;   1: Cast Byte to Flag
                     brne      L_IfElse_000012              ; 1/2: branch if TRUE
                                                            ;    : fall through on FALSE
L_LOrTrue_000015:                                           ;    : Logical OR end (fall through to TRUE) L_LOrRef_000014
L_IfThen_000011:     ;      If Then ------------            ; L_Statement_If_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000016
                     ldi       r20, 0x45                    ;   1: Immediate byte 69
                     ldi       r30, lo8(z)                  ;   1: Z = &z
                     ldi       r31, hi8(z)                  ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @z
                     ;      Expr end ------------           ; L_Statement_Expression_000016
                     rjmp      L_IfDone_000013              ; 1/2:
L_IfElse_000012:     ;      If Else ------------            ; L_Statement_If_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000017
                     ldi       r20, 0x45                    ;   1: Immediate byte 69
                     ldi       r30, lo8(z)                  ;   1: Z = &z
                     ldi       r31, hi8(z)                  ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @z
                     ;      Expr end ------------           ; L_Statement_Expression_000017
L_IfDone_000013:     ;      If End --------------           ; L_Statement_If_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000018
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @x
                     ldi       r30, lo8(y)                  ;   1: Z = &y
                     ldi       r31, hi8(y)                  ;   1:
                     ld        r24, Z                       ;   1: byte <==  RAM @y
                     sub       r20, r24                     ;   1: Compare LT 8
                     brlt      L_LtTrue_000019              ; 1/2:  signed
                     clr       r20                          ;   1:
                     rjmp      L_LtOut_000020               ;   1:
L_LtTrue_000019:     clr       r20                          ;   1:
                     inc       r20                          ;   1:
L_LtOut_000020:                                             ;    :
                     mov       r21, r20                     ;   1: Signed extend 8 to 16 bits
                     lsl       r21                          ;   1:
                     clr       r21                          ;   1: 
                     sbc       r21, r21                     ;   1:
                     ldi       r30, lo8(a)                  ;   1: Z = &a
                     ldi       r31, hi8(a)                  ;   1:
                     st        Z, r20                       ;   1: short ==> RAM @a
                     std       Z+1, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000018
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
