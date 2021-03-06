; SKC AVR Output

#define		_IO_SPL	0x3D
#define		_IO_SPH	0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################

                     .global   LStr000001
LStr000001:                                                 ; Array[5] of char
                     .byte     110                          ;       'n' 0x6e -> [0]
                     .byte     101                          ;       'e' 0x65 -> [1]
                     .byte     120                          ;       'x' 0x78 -> [2]
                     .byte     116                          ;       't' 0x74 -> [3]
                     .byte     0                            ;           0x00 -> [4]

                     .global   LStr000003
LStr000003:                                                 ; Array[3] of char
                     .byte     109                          ;       'm' 0x6d -> [0]
                     .byte     101                          ;       'e' 0x65 -> [1]
                     .byte     0                            ;           0x00 -> [2]

                     .global   R2c
R2c:                                                        ; structure 'TagRecord2'
                     .byte     1                            ;           0x01 -> R2c.iR2A
                     .word     10                           ;         0x000a -> R2c.R2B.iR1A
                     .byte     11                           ;           0x0b -> R2c.R2B.cR1B
                     .byte     0                            ;           0x00 -> R2c.R2B.cR1C
                     .byte     0                            ;           0x00 -> R2c.R2B.baR1D[0]
                     .byte     0                            ;           0x00 -> -------------[1]
                     .byte     0                            ;           0x00 -> -------------[2]
                     .byte     0                            ;           0x00 -> -------------[3]
                     .byte     0                            ;           0x00 -> -------------[4]
                     .word     0                            ;         0x0000 -> R2c.R2B.pcR1E
                     .byte     2                            ;           0x02 -> R2c.cR2C
                     .word     5                            ;         0x0005 -> R2c.R2D.iR1A
                     .byte     6                            ;           0x06 -> R2c.R2D.cR1B
                     .byte     7                            ;           0x07 -> R2c.R2D.cR1C
                     .byte     104                          ;       'h' 0x68 -> R2c.R2D.baR1D[0]
                     .byte     101                          ;       'e' 0x65 -> -------------[1]
                     .byte     108                          ;       'l' 0x6c -> -------------[2]
                     .byte     112                          ;       'p' 0x70 -> -------------[3]
                     .byte     0                            ;           0x00 -> -------------[4]
                     .word     LStr000003                   ;                -> R2c.R2D.pcR1E
                     ;.endseg                               ; === End of CONST segment ===


                                                            ; #########################
                                                            ; # Start of INIT segment #
                     .section    INIT,  "a"                 ; #########################
                                                            ; This is the source of the initialization data
;:                   R1                                     ; structure 'TagRecord1'
                     .word     1                            ;         0x0001 -> R1.iR1A
                     .byte     2                            ;           0x02 -> R1.cR1B
                     .byte     3                            ;           0x03 -> R1.cR1C
                     .byte     119                          ;       'w' 0x77 -> R1.baR1D[0]
                     .byte     104                          ;       'h' 0x68 -> --------[1]
                     .byte     97                           ;       'a' 0x61 -> --------[2]
                     .byte     116                          ;       't' 0x74 -> --------[3]
                     .byte     0                            ;           0x00 -> --------[4]
                     .word     LStr000001                   ;                -> R1.pcR1E
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to

                     .global   R1
R1:                  .space      11                         ; structure 'TagRecord1'
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data

                     .global   _R2c
_R2c:                .space      24                         ; structure 'TagRecord2'
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
