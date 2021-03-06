; SKC AVR Output

#define		_IO_SPL	0x3D
#define		_IO_SPH	0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################

                     .global   cRom
cRom:                                                       ; char
                     .byte     1                            ;           0x01 -> cRom

                     .global   pcRomtoBss
pcRomtoBss:                                                 ; constant pointer
                     .word     0                            ;         0x0000 -> pcRomtoBss
                     ;.endseg                               ; === End of CONST segment ===


                                                            ; #########################
                                                            ; # Start of INIT segment #
                     .section    INIT,  "a"                 ; #########################
                                                            ; This is the source of the initialization data
;:                   cData                                  ; char
                     .byte     1                            ;           0x01 -> cData
;:                   sData                                  ; short 
                     .word     2                            ;         0x0002 -> sData
;:                   lData                                  ; long
                     .long     3                            ;     0x00000003 -> lData
;:                   pcData                                 ; (generic) pointer
                     .word     336                          ;         0x0150 -> pcData
;:                   psData                                 ; (generic) pointer
                     .word     352                          ;         0x0160 -> psData
;:                   plData                                 ; (generic) pointer
                     .word     lData                        ;                -> plData
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to

                     .global   cData
cData:               .space       1                         ; char

                     .global   sData
sData:               .space       2                         ; short 

                     .global   lData
lData:               .space       4                         ; long

                     .global   pcData
pcData:              .space       2                         ; (generic) pointer

                     .global   psData
psData:              .space       2                         ; (generic) pointer

                     .global   plData
plData:              .space       2                         ; (generic) pointer
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data

                     .global   pcBss
pcBss:               .space       2                         ; (generic) pointer

                     .global   pcBsstoRom
pcBsstoRom:          .space       2                         ; (generic) pointer

                     .global   ppiData
ppiData:             .space       2                         ; (generic) pointer

                     .global   cX
cX:                  .space       1                         ; char

                     .global   pcX
pcX:                 .space       2                         ; (generic) pointer

                     .global   ppcX
ppcX:                .space       2                         ; (generic) pointer

                     .global   sX
sX:                  .space       2                         ; short 

                     .global   psX
psX:                 .space       2                         ; (generic) pointer

                     .global   ppsX
ppsX:                .space       2                         ; (generic) pointer

                     .global   lX
lX:                  .space       4                         ; long

                     .global   plX
plX:                 .space       2                         ; (generic) pointer

                     .global   pplX
pplX:                .space       2                         ; (generic) pointer

                     .global   tA
tA:                  .space       7                         ; Array[7] of char

                     .global   ptA
ptA:                 .space       2                         ; (generic) pointer

                     .global   pptA
pptA:                .space       2                         ; (generic) pointer
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code

                     .global   main
main:                ; ###########################################
                     ; # Function: main                     
                     ; #   Return: unsigned int  (r20,r21)  
                     ; #   Params: lParam           @Y+8   size=4 long , Class[_____]
                     ; #         : iParam           @Y+6   size=2 int , Class[_____]
                     ; #         : cParam           @Y+5   size=1 char , Class[_____]
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
                     ldi       r30, lo8(cData)              ;   1: Z := &cData
                     ldi       r31, hi8(cData)              ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @Z
                     mov       r24, r20                     ;   1: post inc 8
                     inc       r24                          ;   1:
                     st        Z, r24                       ;   1:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000003
                     ldi       r30, lo8(sData)              ;   1: Z := &sData
                     ldi       r31, hi8(sData)              ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     movw      r24, r20                     ;   1: post inc 16
                     adiw      r24, 0x01                    ;   2:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000003
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000004
                     ldi       r30, lo8(lData)              ;   1: Z := &lData
                     ldi       r31, hi8(lData)              ;   1:
                     ld        r20, Z                       ;   1: long <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     movw      r24, r20                     ;   1: post inc 32
                     movw      r26, r22                     ;   1:
                     subi      r24, 0xff                    ;   1:
                     sbci      r25, 0xff                    ;   1:
                     sbci      r26, 0xff                    ;   1:
                     sbci      r27, 0xff                    ;   1:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     std       Z+2, r26                     ;   2:
                     std       Z+3, r27                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000004
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldd       r20, Y+5                     ;   2: reg8 <==cParam
                     mov       r24, r20                     ;   1: post inc 8
                     inc       r24                          ;   1:
                     std       Y+5, r24                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000006
                     ldd       r20, Y+6                     ;   2: reg16 <==iParam
                     ldd       r21, Y+7                     ;   2:
                     movw      r24, r20                     ;   1: post inc 16
                     adiw      r24, 0x01                    ;   2:
                     std       Y+6, r24                     ;   2:
                     std       Y+7, r25                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldd       r20, Y+8                     ;   2: reg32 <==lParam
                     ldd       r21, Y+9                     ;   2:
                     ldd       r22, Y+10                    ;   2:
                     ldd       r23, Y+11                    ;   2:
                     movw      r24, r20                     ;   1: post inc 32
                     movw      r26, r22                     ;   1:
                     subi      r24, 0xff                    ;   1:
                     sbci      r25, 0xff                    ;   1:
                     sbci      r26, 0xff                    ;   1:
                     sbci      r27, 0xff                    ;   1:
                     std       Y+8, r24                     ;   2:
                     std       Y+9, r25                     ;   2:
                     std       Y+10, r26                    ;   2:
                     std       Y+11, r27                    ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000007
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r30, lo8(cData)              ;   1: Z := &cData
                     ldi       r31, hi8(cData)              ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @Z
                     mov       r24, r20                     ;   1: post dec 8
                     dec       r24                          ;   1:
                     st        Z, r24                       ;   1:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldi       r30, lo8(sData)              ;   1: Z := &sData
                     ldi       r31, hi8(sData)              ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     movw      r24, r20                     ;   1: post dec 16
                     sbiw      r24, 0x01                    ;   2:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000009
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldi       r30, lo8(lData)              ;   1: Z := &lData
                     ldi       r31, hi8(lData)              ;   1:
                     ld        r20, Z                       ;   1: long <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     movw      r24, r20                     ;   1: post dec 32
                     movw      r26, r22                     ;   1:
                     subi      r24, 0x01                    ;   1:
                     sbci      r25, 0x00                    ;   1:
                     sbci      r26, 0x00                    ;   1:
                     sbci      r27, 0x00                    ;   1:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     std       Z+2, r26                     ;   2:
                     std       Z+3, r27                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000011
                     ldd       r20, Y+5                     ;   2: reg8 <==cParam
                     mov       r24, r20                     ;   1: post dec 8
                     dec       r24                          ;   1:
                     std       Y+5, r24                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000011
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000012
                     ldd       r20, Y+6                     ;   2: reg16 <==iParam
                     ldd       r21, Y+7                     ;   2:
                     movw      r24, r20                     ;   1: post dec 16
                     sbiw      r24, 0x01                    ;   2:
                     std       Y+6, r24                     ;   2:
                     std       Y+7, r25                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000012
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000013
                     ldd       r20, Y+8                     ;   2: reg32 <==lParam
                     ldd       r21, Y+9                     ;   2:
                     ldd       r22, Y+10                    ;   2:
                     ldd       r23, Y+11                    ;   2:
                     movw      r24, r20                     ;   1: post dec 32
                     movw      r26, r22                     ;   1:
                     subi      r24, 0x01                    ;   1:
                     sbci      r25, 0x00                    ;   1:
                     sbci      r26, 0x00                    ;   1:
                     sbci      r27, 0x00                    ;   1:
                     std       Y+8, r24                     ;   2:
                     std       Y+9, r25                     ;   2:
                     std       Y+10, r26                    ;   2:
                     std       Y+11, r27                    ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000013
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000014
                     ldi       r30, lo8(cData)              ;   1: Z := &cData
                     ldi       r31, hi8(cData)              ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @Z
                     inc       r20                          ;   1:
                     st        Z, r20                       ;   1:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000014
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000015
                     ldi       r30, lo8(sData)              ;   1: Z := &sData
                     ldi       r31, hi8(sData)              ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     adiw      r20, 0x01                    ;   1: pre inc 16
                     st        Z, r20                       ;   1:
                     std       Z+1, r21                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000015
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000016
                     ldi       r30, lo8(lData)              ;   1: Z := &lData
                     ldi       r31, hi8(lData)              ;   1:
                     ld        r20, Z                       ;   1: long <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     subi      r20, 0xff                    ;   1: pre inc 32
                     sbci      r21, 0xff                    ;   1:
                     sbci      r22, 0xff                    ;   1:
                     sbci      r23, 0xff                    ;   1:
                     st        Z, r20                       ;   1:
                     std       Z+1, r21                     ;   2:
                     std       Z+2, r22                     ;   2:
                     std       Z+3, r23                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000016
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000017
                     ldd       r20, Y+5                     ;   2: reg8 <==cParam
                     inc       r20                          ;   1: pre inc 8
                     std       Y+5, r20                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000017
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000018
                     ldd       r20, Y+6                     ;   2: reg16 <==iParam
                     ldd       r21, Y+7                     ;   2:
                     adiw      r20, 0x01                    ;   1: pre inc 16
                     std       Y+6, r20                     ;   2:
                     std       Y+7, r21                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000018
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000019
                     ldd       r20, Y+8                     ;   2: reg32 <==lParam
                     ldd       r21, Y+9                     ;   2:
                     ldd       r22, Y+10                    ;   2:
                     ldd       r23, Y+11                    ;   2:
                     subi      r20, 0xff                    ;   1: pre inc 32
                     sbci      r21, 0xff                    ;   1:
                     sbci      r22, 0xff                    ;   1:
                     sbci      r23, 0xff                    ;   1:
                     std       Y+8, r20                     ;   2:
                     std       Y+9, r21                     ;   2:
                     std       Y+10, r22                    ;   2:
                     std       Y+11, r23                    ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000019
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000020
                     ldi       r30, lo8(cData)              ;   1: Z := &cData
                     ldi       r31, hi8(cData)              ;   1:
                     ld        r20, Z                       ;   1: byte <==  RAM @Z
                     dec       r20                          ;   1: pre dec 8
                     st        Z, r20                       ;   1:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000020
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000021
                     ldi       r30, lo8(sData)              ;   1: Z := &sData
                     ldi       r31, hi8(sData)              ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     sbiw      r20, 0x01                    ;   1: pre dec 16
                     st        Z, r20                       ;   1:
                     std       Z+1, r21                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000021
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000022
                     ldi       r30, lo8(lData)              ;   1: Z := &lData
                     ldi       r31, hi8(lData)              ;   1:
                     ld        r20, Z                       ;   1: long <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     sbci      r20, 0x01                    ;   1: pre dec 32
                     sbci      r21, 0x00                    ;   1:
                     sbci      r22, 0x00                    ;   1:
                     sbci      r23, 0x00                    ;   1:
                     st        Z, r20                       ;   1:
                     std       Z+1, r21                     ;   2:
                     std       Z+2, r22                     ;   2:
                     std       Z+3, r23                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000022
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000023
                     ldd       r20, Y+5                     ;   2: reg8 <==cParam
                     dec       r20                          ;   1: pre dec 8
                     std       Y+5, r20                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000023
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000024
                     ldd       r20, Y+6                     ;   2: reg16 <==iParam
                     ldd       r21, Y+7                     ;   2:
                     sbiw      r20, 0x01                    ;   1: pre dec 16
                     std       Y+6, r20                     ;   2:
                     std       Y+7, r21                     ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000024
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000025
                     ldd       r20, Y+8                     ;   2: reg32 <==lParam
                     ldd       r21, Y+9                     ;   2:
                     ldd       r22, Y+10                    ;   2:
                     ldd       r23, Y+11                    ;   2:
                     subi      r20, 0x01                    ;   1: pre dec 32
                     sbci      r21, 0x00                    ;   1:
                     sbci      r22, 0x00                    ;   1:
                     sbci      r23, 0x00                    ;   1:
                     std       Y+8, r20                     ;   2:
                     std       Y+9, r21                     ;   2:
                     std       Y+10, r22                    ;   2:
                     std       Y+11, r23                    ;   2:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000025
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000026
                     ldi       r30, lo8(pcData)             ;   1: Z := &pcData
                     ldi       r31, hi8(pcData)             ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     movw      r24, r20                     ;   1: post inc 16
                     adiw      r24, 0x01                    ;   2:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000026
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000027
                     ldi       r30, lo8(psData)             ;   1: Z := &psData
                     ldi       r31, hi8(psData)             ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     movw      r24, r20                     ;   1: post inc 16
                     adiw      r24, 0x02                    ;   2:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ldi       r30, lo8(sData)              ;   1: Z = &sData
                     ldi       r31, hi8(sData)              ;   1:
                     st        Z, r20                       ;   1: short ==> RAM @sData
                     std       Z+1, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000027
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000028
                     ldi       r30, lo8(plData)             ;   1: Z = &plData
                     ldi       r31, hi8(plData)             ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @plData
                     ldd       r21, Z+1                     ;   2:
                     movw      r30, r20                     ;   1: Z := (addr)expr
                     ld        r20, Z                       ;   1: long <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     movw      r24, r20                     ;   1: post inc 32
                     movw      r26, r22                     ;   1:
                     subi      r24, 0xff                    ;   1:
                     sbci      r25, 0xff                    ;   1:
                     sbci      r26, 0xff                    ;   1:
                     sbci      r27, 0xff                    ;   1:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     std       Z+2, r26                     ;   2:
                     std       Z+3, r27                     ;   2:
                     ldi       r30, lo8(lData)              ;   1: Z = &lData
                     ldi       r31, hi8(lData)              ;   1:
                     st        Z, r20                       ;   1: long ==> RAM @lData
                     std       Z+1, r21                     ;   2:
                     std       Z+2, r22                     ;   2:
                     std       Z+3, r23                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000028
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000029
                     ldi       r30, lo8(plData)             ;   1: Z = &plData
                     ldi       r31, hi8(plData)             ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @plData
                     ldd       r21, Z+1                     ;   2:
                     movw      r30, r20                     ;   1: Z := (addr)expr
                     ld        r20, Z                       ;   1: long <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     subi      r20, 0xff                    ;   1: pre inc 32
                     sbci      r21, 0xff                    ;   1:
                     sbci      r22, 0xff                    ;   1:
                     sbci      r23, 0xff                    ;   1:
                     st        Z, r20                       ;   1:
                     std       Z+1, r21                     ;   2:
                     std       Z+2, r22                     ;   2:
                     std       Z+3, r23                     ;   2:
                     ldi       r30, lo8(lData)              ;   1: Z = &lData
                     ldi       r31, hi8(lData)              ;   1:
                     st        Z, r20                       ;   1: long ==> RAM @lData
                     std       Z+1, r21                     ;   2:
                     std       Z+2, r22                     ;   2:
                     std       Z+3, r23                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000029
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000030
                     ldi       r30, lo8(plData)             ;   1: Z = &plData
                     ldi       r31, hi8(plData)             ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @plData
                     ldd       r21, Z+1                     ;   2:
                     movw      r30, r20                     ;   1: Z := (addr)expr
                     ld        r20, Z                       ;   1: long <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     movw      r24, r20                     ;   1: post dec 32
                     movw      r26, r22                     ;   1:
                     subi      r24, 0x01                    ;   1:
                     sbci      r25, 0x00                    ;   1:
                     sbci      r26, 0x00                    ;   1:
                     sbci      r27, 0x00                    ;   1:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     std       Z+2, r26                     ;   2:
                     std       Z+3, r27                     ;   2:
                     ldi       r30, lo8(lData)              ;   1: Z = &lData
                     ldi       r31, hi8(lData)              ;   1:
                     st        Z, r20                       ;   1: long ==> RAM @lData
                     std       Z+1, r21                     ;   2:
                     std       Z+2, r22                     ;   2:
                     std       Z+3, r23                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000030
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000031
                     ldi       r30, lo8(plData)             ;   1: Z = &plData
                     ldi       r31, hi8(plData)             ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @plData
                     ldd       r21, Z+1                     ;   2:
                     movw      r30, r20                     ;   1: Z := (addr)expr
                     ld        r20, Z                       ;   1: long <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     sbci      r20, 0x01                    ;   1: pre dec 32
                     sbci      r21, 0x00                    ;   1:
                     sbci      r22, 0x00                    ;   1:
                     sbci      r23, 0x00                    ;   1:
                     st        Z, r20                       ;   1:
                     std       Z+1, r21                     ;   2:
                     std       Z+2, r22                     ;   2:
                     std       Z+3, r23                     ;   2:
                     ldi       r30, lo8(lData)              ;   1: Z = &lData
                     ldi       r31, hi8(lData)              ;   1:
                     st        Z, r20                       ;   1: long ==> RAM @lData
                     std       Z+1, r21                     ;   2:
                     std       Z+2, r22                     ;   2:
                     std       Z+3, r23                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000031
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000032
                     ldi       r30, lo8(psData)             ;   1: Z := &psData
                     ldi       r31, hi8(psData)             ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     movw      r24, r20                     ;   1: post inc 16
                     adiw      r24, 0x02                    ;   2:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     push      r20                          ;   2:
                     ldi       r30, lo8(pcData)             ;   1: Z := &pcData
                     ldi       r31, hi8(pcData)             ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     movw      r24, r20                     ;   1: post inc 16
                     adiw      r24, 0x01                    ;   2:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     movw      r30, r20                     ;   1: pointer to the storage
                     pop       r20                          ;   2:
                     st        Z, r20                       ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000032
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000033
                     ldi       r20, 0x2a                    ;   1: Immediate byte 42
                     push      r20                          ;   2:
                     ldi       r20, 0x64                    ;   1: Immediate short 100
                     ldi       r21, 0x00                    ;   1:
                     movw      r30, r20                     ;   1: pointer to the storage
                     pop       r20                          ;   2:
                     st        Z, r20                       ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000033
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000034
                     ldi       r20, 0x64                    ;   1: Immediate short 100
                     ldi       r21, 0x00                    ;   1:
                     movw      r30, r20                     ;   1: Z := (addr)expr
                     ld        r20, Z                       ;   1: byte <==  RAM @Z
                     mov       r24, r20                     ;   1: post inc 8
                     inc       r24                          ;   1:
                     st        Z, r24                       ;   1:
                     ldi       r30, lo8(cData)              ;   1: Z = &cData
                     ldi       r31, hi8(cData)              ;   1:
                     st        Z, r20                       ;   1: byte ==> RAM @cData
                     ;      Expr end ------------           ; L_Statement_Expression_000034
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 0                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   foo
foo:                 ; ###########################################
                     ; # Function: foo                      
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+3   size=2
                     ; #         : <saved fptr>     @Y+1   size=2
                     ; #   Locals: <none>                   
                     ; #         : sizeof(locals) = 0       
                     ; ###########################################
                     ; #### no frame needed #####           ; no parameters or locals
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000036
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000037
                     ldi       r30, lo8(ptA)                ;   1: Z := &ptA
                     ldi       r31, hi8(ptA)                ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     movw      r24, r20                     ;   1: post inc 16
                     adiw      r24, 0x07                    ;   2:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000037
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000038
                     ldi       r30, lo8(pptA)               ;   1: Z = &pptA
                     ldi       r31, hi8(pptA)               ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @pptA
                     ldd       r21, Z+1                     ;   2:
                     movw      r30, r20                     ;   1: Z := (addr)expr
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     movw      r24, r20                     ;   1: post inc 16
                     adiw      r24, 0x07                    ;   2:
                     st        Z, r24                       ;   1:
                     std       Z+1, r25                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000038
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000039
                     ldi       r30, lo8(ptA)                ;   1: Z := &ptA
                     ldi       r31, hi8(ptA)                ;   1:
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     adiw      r20, 0x07                    ;   1: pre inc 16
                     st        Z, r20                       ;   1:
                     std       Z+1, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000039
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000040
                     ldi       r30, lo8(pptA)               ;   1: Z = &pptA
                     ldi       r31, hi8(pptA)               ;   1:
                     ld        r20, Z                       ;   1: short <==  RAM @pptA
                     ldd       r21, Z+1                     ;   2:
                     movw      r30, r20                     ;   1: Z := (addr)expr
                     ld        r20, Z                       ;   1:, short <==  RAM @Z
                     ldd       r21, Z+1                     ;   2:
                     adiw      r20, 0x07                    ;   1: pre inc 16
                     st        Z, r20                       ;   1:
                     std       Z+1, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000040
                     ;      Compound End --------           ; L_Statement_compound_000036
                     ; #### exit ################           ; 
L_Exit_000035:       ret                                    ;  4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
