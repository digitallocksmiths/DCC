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
;:                   A1                                     ; union 'TagUnion1'
                     .byte     5                            ;           0x05 -> A1.bU1
                     .byte     0                            ;                -> A1 packed to size 4
                     .byte     0                            ; 
                     .byte     0                            ; 
;:                   A2                                     ; union 'TagUnion1'
                     .byte     5                            ;           0x05 -> A2.bU1
                     .byte     0                            ;                -> A2 packed to size 4
                     .byte     0                            ; 
                     .byte     0                            ; 
;:                   A3                                     ; union 'TagUnion1'
                     .byte     5                            ;           0x05 -> A3.bU1
                     .byte     0                            ;                -> A3 packed to size 4
                     .byte     0                            ; 
                     .byte     0                            ; 
;:                   B1                                     ; union 'TagUnion2'
                     .long     5                            ;     0x00000005 -> B1.lU2
;:                   B2                                     ; union 'TagUnion2'
                     .long     5                            ;     0x00000005 -> B2.lU2
;:                   B3                                     ; union 'TagUnion2'
                     .long     5                            ;     0x00000005 -> B3.lU2
;:                   C1                                     ; union 'TagUnion3'
                     .byte     11                           ;           0x0b -> C1.R1.bR1
                     .byte     22                           ;           0x16 -> C1.R1.nR1
                     .byte     0                            ;                -> C1 packed to size 3
;:                   C2                                     ; union 'TagUnion3'
                     .byte     11                           ;           0x0b -> C2.R1.bR1
                     .byte     22                           ;           0x16 -> C2.R1.nR1
                     .byte     0                            ;                -> C2 packed to size 3
;:                   C3                                     ; union 'TagUnion3'
                     .byte     11                           ;           0x0b -> C3.R1.bR1
                     .byte     0                            ;           0x00 -> C3.R1.nR1
                     .byte     0                            ;                -> C3 packed to size 3
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to

                     .global   A1
A1:                  .space       4                         ; union 'TagUnion1'

                     .global   A2
A2:                  .space       4                         ; union 'TagUnion1'

                     .global   A3
A3:                  .space       4                         ; union 'TagUnion1'

                     .global   B1
B1:                  .space       4                         ; union 'TagUnion2'

                     .global   B2
B2:                  .space       4                         ; union 'TagUnion2'

                     .global   B3
B3:                  .space       4                         ; union 'TagUnion2'

                     .global   C1
C1:                  .space       3                         ; union 'TagUnion3'

                     .global   C2
C2:                  .space       3                         ; union 'TagUnion3'

                     .global   C3
C3:                  .space       3                         ; union 'TagUnion3'
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data

                     .global   A0
A0:                  .space       4                         ; union 'TagUnion1'

                     .global   B0
B0:                  .space       4                         ; union 'TagUnion2'

                     .global   C0
C0:                  .space       3                         ; union 'TagUnion3'
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
