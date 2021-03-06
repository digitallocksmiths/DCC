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

                     .global   LStr000001
LStr000001:                                                 ; Array[6] of char
                     .byte     119                          ;       'w' 0x77 -> [0]
                     .byte     111                          ;       'o' 0x6f -> [1]
                     .byte     114                          ;       'r' 0x72 -> [2]
                     .byte     108                          ;       'l' 0x6c -> [3]
                     .byte     100                          ;       'd' 0x64 -> [4]
                     .byte     0                            ;           0x00 -> [5]

                     .global   LStr000004
LStr000004:                                                 ; Array[4] of char
                     .byte     111                          ;       'o' 0x6f -> [0]
                     .byte     110                          ;       'n' 0x6e -> [1]
                     .byte     101                          ;       'e' 0x65 -> [2]
                     .byte     0                            ;           0x00 -> [3]

                     .global   LStr000005
LStr000005:                                                 ; Array[4] of char
                     .byte     116                          ;       't' 0x74 -> [0]
                     .byte     119                          ;       'w' 0x77 -> [1]
                     .byte     111                          ;       'o' 0x6f -> [2]
                     .byte     0                            ;           0x00 -> [3]

                     .global   LStr000006
LStr000006:                                                 ; Array[6] of char
                     .byte     116                          ;       't' 0x74 -> [0]
                     .byte     104                          ;       'h' 0x68 -> [1]
                     .byte     114                          ;       'r' 0x72 -> [2]
                     .byte     101                          ;       'e' 0x65 -> [3]
                     .byte     101                          ;       'e' 0x65 -> [4]
                     .byte     0                            ;           0x00 -> [5]

                     .global   _s8
_s8:                                                        ; short 
                     .word     -2                           ;         0xfffe -> _s8

                     .global   _ps
_ps:                                                        ; constant pointer
                     .word     LStr000001                   ;                -> _ps

                     .global   _ba
_ba:                                                        ; Array[5] of char
                     .byte     109                          ;       'm' 0x6d -> _ba[0]
                     .byte     97                           ;       'a' 0x61 -> ---[1]
                     .byte     114                          ;       'r' 0x72 -> ---[2]
                     .byte     115                          ;       's' 0x73 -> ---[3]
                     .byte     0                            ;           0x00 -> ---[4]

                     .global   _baa
_baa:                                                       ; Array[4] of Array[1] of char
                     .byte     6                            ;           0x06 -> _baa[0][0]
                     .byte     0                            ;           0x00 -> ----[1][0]
                     .byte     0                            ;           0x00 -> ----[2][0]
                     .byte     0                            ;           0x00 -> ----[3][0]

                     .global   _e
_e:                                                         ; enum 'anon'
                     .word     -1                           ;         0xffff -> _e

                     .global   _st
_st:                                                        ; structure ''
                     .word     8                            ;         0x0008 -> _st.i
                     ;.endseg                               ; === End of CONST segment ===


                                                            ; #########################
                                                            ; # Start of INIT segment #
                     .section    INIT,  "a"                 ; #########################
                                                            ; This is the source of the initialization data
;:                   s8                                     ; short 
                     .word     -1                           ;         0xffff -> s8
;:                   ps                                     ; (generic) pointer
                     .word     LStr000000                   ;                -> ps
;:                   ba                                     ; Array[5] of char
                     .byte     103                          ;       'g' 0x67 -> ba[0]
                     .byte     111                          ;       'o' 0x6f -> --[1]
                     .byte     111                          ;       'o' 0x6f -> --[2]
                     .byte     100                          ;       'd' 0x64 -> --[3]
                     .byte     98                           ;       'b' 0x62 -> --[4]
;:                   baa                                    ; Array[4] of Array[1] of char
                     .byte     5                            ;           0x05 -> baa[0][0]
                     .byte     0                            ;           0x00 -> ---[1][0]
                     .byte     0                            ;           0x00 -> ---[2][0]
                     .byte     0                            ;           0x00 -> ---[3][0]
;:                   e                                      ; enum 'anon'
                     .word     -2                           ;         0xfffe -> e
;:                   st                                     ; structure ''
                     .word     7                            ;         0x0007 -> st.i
;:                   pbaZ                                   ; Array[3] of (generic) pointer
                     .word     LStr000004                   ;                -> pbaZ[0]
                     .word     LStr000005                   ;                -> ----[1]
                     .word     LStr000006                   ;                -> ----[2]
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to

                     .global   s8
s8:                  .space       2                         ; short 

                     .global   ps
ps:                  .space       2                         ; (generic) pointer

                     .global   ba
ba:                  .space       5                         ; Array[5] of char

                     .global   baa
baa:                 .space       4                         ; Array[4] of Array[1] of char

                     .global   e
e:                   .space       2                         ; enum 'anon'

                     .global   st
st:                  .space       2                         ; structure ''

                     .global   pbaZ
pbaZ:                .space       6                         ; Array[3] of (generic) pointer
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
