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
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+3   size=2
                     ; #         : <saved fptr>     @Y+1   size=2
                     ; #   Locals: <none>                   
                     ; #         : sizeof(locals) = 0       
                     ; ###########################################
                     ; #### no frame needed #####           ; no parameters or locals
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldi       r30, lo8(w)                  ;   1: Z = &w
                     ldi       r31, hi8(w)                  ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @w
                     ldd       r21, Z+1                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                                                            ;    : Ternary start
                     ldi       r30, lo8(x)                  ;   1: Z = &x
                     ldi       r31, hi8(x)                  ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @x
                     ldd       r21, Z+1                     ;   2:
                     or        r20, r21                     ;   1: Cast Short to Flag
                     breq      L_TernaryFalse_000003        ; 1/2: branch if FALSE
                                                            ;    : fall through on TRUE
                     ldi       r30, lo8(y)                  ;   1: Z = &y
                     ldi       r31, hi8(y)                  ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @y
                     ldd       r21, Z+1                     ;   2:
                     rjmp      L_TernaryExit_000004         ;   2:
L_TernaryFalse_000003:                                      ;    :
                     ldi       r30, lo8(z)                  ;   1: Z = &z
                     ldi       r31, hi8(z)                  ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @z
                     ldd       r21, Z+1                     ;   2:
L_TernaryExit_000004:                                       ;    : Ternary end
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     ldi       r30, lo8(w)                  ;   1: Z = &w
                     ldi       r31, hi8(w)                  ;   1:
                     st        Z, r20                       ;   1: short ==> RAM @w
                     std       Z+1, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       ret                                    ;  4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
