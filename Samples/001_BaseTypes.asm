; SKC AVR Output

#define		_IO_SPL	0x3D
#define		_IO_SPH	0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################

                     .global   LStr000000
LStr000000:                                                 ; Array[6] of char
                     .byte     104                          ;       'h' 0x68 -> [0]
                     .byte     101                          ;       'e' 0x65 -> [1]
                     .byte     108                          ;       'l' 0x6c -> [2]
                     .byte     108                          ;       'l' 0x6c -> [3]
                     .byte     111                          ;       'o' 0x6f -> [4]
                     .byte     0                            ;           0x00 -> [5]

                     .global   iConst
iConst:                                                     ; int
                     .word     4660                         ;         0x1234 -> iConst

                     .global   lConst
lConst:                                                     ; long
                     .long     305419896                    ;     0x12345678 -> lConst
                     ;.endseg                               ; === End of CONST segment ===


                                                            ; #########################
                                                            ; # Start of INIT segment #
                     .section    INIT,  "a"                 ; #########################
                                                            ; This is the source of the initialization data
;:                   data_s8                                ; char
                     .byte     1                            ;           0x01 -> data_s8
;:                   data_ps8                               ; (generic) pointer
                     .word     2                            ;         0x0002 -> data_ps8
;:                   data_u8                                ; unsigned char
                     .byte     3                            ;           0x03 -> data_u8
;:                   data_pu8                               ; (generic) pointer
                     .word     4                            ;         0x0004 -> data_pu8
;:                   data_s16                               ; short 
                     .word     5                            ;         0x0005 -> data_s16
;:                   data_ps16                              ; (generic) pointer
                     .word     6                            ;         0x0006 -> data_ps16
;:                   data_u16                               ; unsigned short 
                     .word     7                            ;         0x0007 -> data_u16
;:                   data_pu16                              ; (generic) pointer
                     .word     8                            ;         0x0008 -> data_pu16
;:                   data_s32                               ; long
                     .long     9                            ;     0x00000009 -> data_s32
;:                   data_ps32                              ; (generic) pointer
                     .word     10                           ;         0x000a -> data_ps32
;:                   data_u32                               ; unsigned long
                     .long     11                           ;     0x0000000b -> data_u32
;:                   data_pu32                              ; (generic) pointer
                     .word     12                           ;         0x000c -> data_pu32
;:                   pc                                     ; (generic) pointer
                     .word     LStr000000                   ;                -> pc
;:                   p0                                     ; (generic) pointer
                     .word     baArray                      ;                -> p0
;:                   p1                                     ; (generic) pointer
                     .word     baArray                      ;                -> p1
;:                   p2                                     ; (generic) pointer
                     .word     data_u32                     ;                -> p2
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to

                     .global   data_s8
data_s8:             .space       1                         ; char

                     .global   data_ps8
data_ps8:            .space       2                         ; (generic) pointer

                     .global   data_u8
data_u8:             .space       1                         ; unsigned char

                     .global   data_pu8
data_pu8:            .space       2                         ; (generic) pointer

                     .global   data_s16
data_s16:            .space       2                         ; short 

                     .global   data_ps16
data_ps16:           .space       2                         ; (generic) pointer

                     .global   data_u16
data_u16:            .space       2                         ; unsigned short 

                     .global   data_pu16
data_pu16:           .space       2                         ; (generic) pointer

                     .global   data_s32
data_s32:            .space       4                         ; long

                     .global   data_ps32
data_ps32:           .space       2                         ; (generic) pointer

                     .global   data_u32
data_u32:            .space       4                         ; unsigned long

                     .global   data_pu32
data_pu32:           .space       2                         ; (generic) pointer

                     .global   pc
pc:                  .space       2                         ; (generic) pointer

                     .global   p0
p0:                  .space       2                         ; (generic) pointer

                     .global   p1
p1:                  .space       2                         ; (generic) pointer

                     .global   p2
p2:                  .space       2                         ; (generic) pointer
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data

                     .global   bss_s8
bss_s8:              .space       1                         ; char

                     .global   bss_u8
bss_u8:              .space       1                         ; unsigned char

                     .global   bss_s16
bss_s16:             .space       2                         ; short 

                     .global   bss_u16
bss_u16:             .space       2                         ; unsigned short 

                     .global   bss_s32
bss_s32:             .space       4                         ; long

                     .global   bss_u32
bss_u32:             .space       4                         ; unsigned long

                     .global   baArray
baArray:                                                    ; Array[0] of unsigned char

                     .global   baArray2
baArray2:            .space      20                         ; Array[10] of unsigned short 
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
