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
w:                   .space       2                         ; int

                     .global   x
x:                   .space       2                         ; int

                     .global   y
y:                   .space       2                         ; int

                     .global   z
z:                   .space       2                         ; int
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
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldi       r30, lo8(w)                  ;   1: Z = &w
                     ldi       r31, hi8(w)                  ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @w
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000002
Label_main_here:     ; ==== Expr Statement ================ ; L_Statement_Expression_000003
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @x
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000003
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000004
                     ldi       r30, lo8(y)                  ;   1: Z = &y
                     ldi       r31, hi8(y)                  ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @y
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000004
                     ; ==== Goto Statement ================ ; 
                     rjmp      Label_main_here              ;   2: goto
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldi       r30, lo8(z)                  ;   1: Z = &z
                     ldi       r31, hi8(z)                  ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @z
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000005
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
