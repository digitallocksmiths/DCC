; SKC AVR Output

#define		_IO_SPL	0x3D
#define		_IO_SPH	0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################

                     .global   LStr000006
LStr000006:                                                 ; Array[6] of char
                     .byte     104                          ;       'h' 0x68 -> [0]
                     .byte     101                          ;       'e' 0x65 -> [1]
                     .byte     108                          ;       'l' 0x6c -> [2]
                     .byte     108                          ;       'l' 0x6c -> [3]
                     .byte     111                          ;       'o' 0x6f -> [4]
                     .byte     0                            ;           0x00 -> [5]

                     .global   LStr000008
LStr000008:                                                 ; Array[6] of char
                     .byte     104                          ;       'h' 0x68 -> [0]
                     .byte     101                          ;       'e' 0x65 -> [1]
                     .byte     108                          ;       'l' 0x6c -> [2]
                     .byte     108                          ;       'l' 0x6c -> [3]
                     .byte     111                          ;       'o' 0x6f -> [4]
                     .byte     0                            ;           0x00 -> [5]

                     .global   LStr000010
LStr000010:                                                 ; Array[6] of char
                     .byte     104                          ;       'h' 0x68 -> [0]
                     .byte     101                          ;       'e' 0x65 -> [1]
                     .byte     108                          ;       'l' 0x6c -> [2]
                     .byte     108                          ;       'l' 0x6c -> [3]
                     .byte     111                          ;       'o' 0x6f -> [4]
                     .byte     0                            ;           0x00 -> [5]

                     .global   LStr000017
LStr000017:                                                 ; Array[4] of char
                     .byte     116                          ;       't' 0x74 -> [0]
                     .byte     101                          ;       'e' 0x65 -> [1]
                     .byte     110                          ;       'n' 0x6e -> [2]
                     .byte     0                            ;           0x00 -> [3]

                     .global   LStr000018
LStr000018:                                                 ; Array[7] of char
                     .byte     116                          ;       't' 0x74 -> [0]
                     .byte     119                          ;       'w' 0x77 -> [1]
                     .byte     101                          ;       'e' 0x65 -> [2]
                     .byte     110                          ;       'n' 0x6e -> [3]
                     .byte     116                          ;       't' 0x74 -> [4]
                     .byte     121                          ;       'y' 0x79 -> [5]
                     .byte     0                            ;           0x00 -> [6]

                     .global   LStr000019
LStr000019:                                                 ; Array[7] of char
                     .byte     84                           ;       'T' 0x54 -> [0]
                     .byte     104                          ;       'h' 0x68 -> [1]
                     .byte     105                          ;       'i' 0x69 -> [2]
                     .byte     114                          ;       'r' 0x72 -> [3]
                     .byte     116                          ;       't' 0x74 -> [4]
                     .byte     121                          ;       'y' 0x79 -> [5]
                     .byte     0                            ;           0x00 -> [6]
                     ;.endseg                               ; === End of CONST segment ===


                                                            ; #########################
                                                            ; # Start of INIT segment #
                     .section    INIT,  "a"                 ; #########################
                                                            ; This is the source of the initialization data
;:                   A1                                     ; Array[8] of unsigned short 
                     .word     10                           ;         0x000a -> A1[0]
                     .word     11                           ;         0x000b -> --[1]
                     .word     12                           ;         0x000c -> --[2]
                     .word     13                           ;         0x000d -> --[3]
                     .word     14                           ;         0x000e -> --[4]
                     .word     15                           ;         0x000f -> --[5]
                     .word     16                           ;         0x0010 -> --[6]
                     .word     0                            ;         0x0000 -> --[7]
;:                   A2                                     ; Array[8] of unsigned short 
                     .word     20                           ;         0x0014 -> A2[0]
                     .word     21                           ;         0x0015 -> --[1]
                     .word     22                           ;         0x0016 -> --[2]
                     .word     23                           ;         0x0017 -> --[3]
                     .word     24                           ;         0x0018 -> --[4]
                     .word     25                           ;         0x0019 -> --[5]
                     .word     26                           ;         0x001a -> --[6]
                     .word     27                           ;         0x001b -> --[7]
;:                   A3                                     ; Array[8] of unsigned short 
                     .word     30                           ;         0x001e -> A3[0]
                     .word     31                           ;         0x001f -> --[1]
                     .word     32                           ;         0x0020 -> --[2]
                     .word     33                           ;         0x0021 -> --[3]
                     .word     34                           ;         0x0022 -> --[4]
                     .word     35                           ;         0x0023 -> --[5]
                     .word     36                           ;         0x0024 -> --[6]
                     .word     37                           ;         0x0025 -> --[7]
;:                   A4                                     ; Array[9] of unsigned short 
                     .word     30                           ;         0x001e -> A4[0]
                     .word     31                           ;         0x001f -> --[1]
                     .word     32                           ;         0x0020 -> --[2]
                     .word     33                           ;         0x0021 -> --[3]
                     .word     34                           ;         0x0022 -> --[4]
                     .word     35                           ;         0x0023 -> --[5]
                     .word     36                           ;         0x0024 -> --[6]
                     .word     37                           ;         0x0025 -> --[7]
                     .word     38                           ;         0x0026 -> --[8]
;:                   B1                                     ; Array[3] of Array[2] of unsigned char
                     .byte     11                           ;           0x0b -> B1[0][0]
                     .byte     12                           ;           0x0c -> -----[1]
                     .byte     21                           ;           0x15 -> --[1][0]
                     .byte     22                           ;           0x16 -> -----[1]
                     .byte     0                            ;           0x00 -> --[2][0]
                     .byte     0                            ;           0x00 -> -----[1]
;:                   B2                                     ; Array[3] of Array[2] of unsigned char
                     .byte     11                           ;           0x0b -> B2[0][0]
                     .byte     12                           ;           0x0c -> -----[1]
                     .byte     21                           ;           0x15 -> --[1][0]
                     .byte     22                           ;           0x16 -> -----[1]
                     .byte     31                           ;           0x1f -> --[2][0]
                     .byte     32                           ;       ' ' 0x20 -> -----[1]
;:                   B3                                     ; Array[3] of Array[2] of unsigned char
                     .byte     11                           ;           0x0b -> B3[0][0]
                     .byte     12                           ;           0x0c -> -----[1]
                     .byte     21                           ;           0x15 -> --[1][0]
                     .byte     22                           ;           0x16 -> -----[1]
                     .byte     31                           ;           0x1f -> --[2][0]
                     .byte     32                           ;       ' ' 0x20 -> -----[1]
;:                   B4                                     ; Array[4] of Array[2] of unsigned char
                     .byte     11                           ;           0x0b -> B4[0][0]
                     .byte     12                           ;           0x0c -> -----[1]
                     .byte     21                           ;           0x15 -> --[1][0]
                     .byte     22                           ;           0x16 -> -----[1]
                     .byte     31                           ;           0x1f -> --[2][0]
                     .byte     32                           ;       ' ' 0x20 -> -----[1]
                     .byte     41                           ;       ')' 0x29 -> --[3][0]
                     .byte     42                           ;       '*' 0x2a -> -----[1]
;:                   B5                                     ; Array[4] of Array[2] of unsigned char
                     .byte     11                           ;           0x0b -> B5[0][0]
                     .byte     12                           ;           0x0c -> -----[1]
                     .byte     21                           ;           0x15 -> --[1][0]
                     .byte     22                           ;           0x16 -> -----[1]
                     .byte     31                           ;           0x1f -> --[2][0]
                     .byte     32                           ;       ' ' 0x20 -> -----[1]
                     .byte     41                           ;       ')' 0x29 -> --[3][0]
                     .byte     42                           ;       '*' 0x2a -> -----[1]
;:                   B6                                     ; Array[2] of Array[3] of unsigned char
                     .byte     11                           ;           0x0b -> B6[0][0]
                     .byte     12                           ;           0x0c -> -----[1]
                     .byte     21                           ;           0x15 -> -----[2]
                     .byte     12                           ;           0x0c -> --[1][0]
                     .byte     21                           ;           0x15 -> -----[1]
                     .byte     22                           ;           0x16 -> -----[2]
;:                   C1                                     ; Array[3] of structure ''
                     .byte     11                           ;           0x0b -> C1[0].s1
                     .word     12                           ;         0x000c -> C1[0].s2
                     .word     0                            ;         0x0000 -> C1[0].pszA
                     .byte     0                            ;           0x00 -> C1[0].baA[0]
                     .byte     0                            ;           0x00 -> ---------[1]
                     .byte     0                            ;           0x00 -> ---------[2]
                     .byte     0                            ;           0x00 -> ---------[3]
                     .byte     0                            ;           0x00 -> ---------[4]
                     .byte     0                            ;           0x00 -> ---------[5]
                     .byte     0                            ;           0x00 -> ---------[6]
                     .byte     0                            ;           0x00 -> ---------[7]
                     .byte     0                            ;           0x00 -> ---------[8]
                     .byte     0                            ;           0x00 -> ---------[9]
                     .word     0                            ;         0x0000 -> C1[0].i
                     .byte     21                           ;           0x15 -> --[1].s1
                     .word     22                           ;         0x0016 -> --[1].s2
                     .word     0                            ;         0x0000 -> --[1].pszA
                     .byte     0                            ;           0x00 -> --[1].baA[0]
                     .byte     0                            ;           0x00 -> ---------[1]
                     .byte     0                            ;           0x00 -> ---------[2]
                     .byte     0                            ;           0x00 -> ---------[3]
                     .byte     0                            ;           0x00 -> ---------[4]
                     .byte     0                            ;           0x00 -> ---------[5]
                     .byte     0                            ;           0x00 -> ---------[6]
                     .byte     0                            ;           0x00 -> ---------[7]
                     .byte     0                            ;           0x00 -> ---------[8]
                     .byte     0                            ;           0x00 -> ---------[9]
                     .word     0                            ;         0x0000 -> --[1].i
                     .byte     31                           ;           0x1f -> --[2].s1
                     .word     32                           ;         0x0020 -> --[2].s2
                     .word     0                            ;         0x0000 -> --[2].pszA
                     .byte     0                            ;           0x00 -> --[2].baA[0]
                     .byte     0                            ;           0x00 -> ---------[1]
                     .byte     0                            ;           0x00 -> ---------[2]
                     .byte     0                            ;           0x00 -> ---------[3]
                     .byte     0                            ;           0x00 -> ---------[4]
                     .byte     0                            ;           0x00 -> ---------[5]
                     .byte     0                            ;           0x00 -> ---------[6]
                     .byte     0                            ;           0x00 -> ---------[7]
                     .byte     0                            ;           0x00 -> ---------[8]
                     .byte     0                            ;           0x00 -> ---------[9]
                     .word     0                            ;         0x0000 -> --[2].i
;:                   D0                                     ; Array[2] of unsigned char
                     .byte     1                            ;           0x01 -> D0[0]
                     .byte     0                            ;           0x00 -> --[1]
;:                   D1a                                    ; Array[5] of short 
                     .word     72                           ;         0x0048 -> D1a[0]
                     .word     101                          ;         0x0065 -> ---[1]
                     .word     108                          ;         0x006c -> ---[2]
                     .word     108                          ;         0x006c -> ---[3]
                     .word     111                          ;         0x006f -> ---[4]
;:                   D1b                                    ; Array[6] of short 
                     .word     72                           ;         0x0048 -> D1b[0]
                     .word     101                          ;         0x0065 -> ---[1]
                     .word     108                          ;         0x006c -> ---[2]
                     .word     108                          ;         0x006c -> ---[3]
                     .word     111                          ;         0x006f -> ---[4]
                     .word     0                            ;         0x0000 -> ---[5]
;:                   D1c                                    ; Array[7] of short 
                     .word     72                           ;         0x0048 -> D1c[0]
                     .word     101                          ;         0x0065 -> ---[1]
                     .word     108                          ;         0x006c -> ---[2]
                     .word     108                          ;         0x006c -> ---[3]
                     .word     111                          ;         0x006f -> ---[4]
                     .word     0                            ;         0x0000 -> ---[5]
                     .word     0                            ;         0x0000 ->    [6]
;:                   D1d                                    ; Array[8] of short 
                     .word     72                           ;         0x0048 -> D1d[0]
                     .word     101                          ;         0x0065 -> ---[1]
                     .word     108                          ;         0x006c -> ---[2]
                     .word     108                          ;         0x006c -> ---[3]
                     .word     111                          ;         0x006f -> ---[4]
                     .word     0                            ;         0x0000 -> ---[5]
                     .word     0                            ;         0x0000 ->    [6]
                     .word     0                            ;         0x0000 ->    [7]
;:                   D1e                                    ; Array[16] of short 
                     .word     72                           ;         0x0048 -> D1e[0]
                     .word     101                          ;         0x0065 -> ---[1]
                     .word     108                          ;         0x006c -> ---[2]
                     .word     108                          ;         0x006c -> ---[3]
                     .word     111                          ;         0x006f -> ---[4]
                     .word     0                            ;         0x0000 -> ---[5]
                     .word     0                            ;         0x0000 ->    [6]
                     .word     0                            ;         0x0000 ->    [7]
                     .word     0                            ;         0x0000 ->    [8]
                     .word     0                            ;         0x0000 ->    [9]
                     .word     0                            ;         0x0000 ->    [10]
                     .word     0                            ;         0x0000 ->    [11]
                     .word     0                            ;         0x0000 ->    [12]
                     .word     0                            ;         0x0000 ->    [13]
                     .word     0                            ;         0x0000 ->    [14]
                     .word     0                            ;         0x0000 ->    [15]
;:                   D1f                                    ; Array[6] of short 
                     .word     72                           ;         0x0048 -> D1f[0]
                     .word     101                          ;         0x0065 -> ---[1]
                     .word     108                          ;         0x006c -> ---[2]
                     .word     108                          ;         0x006c -> ---[3]
                     .word     111                          ;         0x006f -> ---[4]
                     .word     0                            ;         0x0000 -> ---[5]
;:                   T1                                     ; structure ''
                     .byte     1                            ;           0x01 -> T1.s1
                     .word     2                            ;         0x0002 -> T1.s2
                     .word     LStr000006                   ;                -> T1.pszA
                     .byte     119                          ;       'w' 0x77 -> T1.baA[0]
                     .byte     111                          ;       'o' 0x6f -> ------[1]
                     .byte     114                          ;       'r' 0x72 -> ------[2]
                     .byte     108                          ;       'l' 0x6c -> ------[3]
                     .byte     100                          ;       'd' 0x64 -> ------[4]
                     .byte     0                            ;           0x00 -> ------[5]
                     .byte     0                            ;           0x00 ->       [6]
                     .byte     0                            ;           0x00 ->       [7]
                     .byte     0                            ;           0x00 ->       [8]
                     .byte     0                            ;           0x00 ->       [9]
                     .word     0                            ;         0x0000 -> T1.i
;:                   aT1                                    ; Array[2] of structure ''
                     .byte     1                            ;           0x01 -> aT1[0].s1
                     .word     2                            ;         0x0002 -> aT1[0].s2
                     .word     LStr000008                   ;                -> aT1[0].pszA
                     .byte     119                          ;       'w' 0x77 -> aT1[0].baA[0]
                     .byte     111                          ;       'o' 0x6f -> ----------[1]
                     .byte     114                          ;       'r' 0x72 -> ----------[2]
                     .byte     108                          ;       'l' 0x6c -> ----------[3]
                     .byte     100                          ;       'd' 0x64 -> ----------[4]
                     .byte     0                            ;           0x00 -> ----------[5]
                     .byte     0                            ;           0x00 ->           [6]
                     .byte     0                            ;           0x00 ->           [7]
                     .byte     0                            ;           0x00 ->           [8]
                     .byte     0                            ;           0x00 ->           [9]
                     .word     0                            ;         0x0000 -> aT1[0].i
                     .byte     1                            ;           0x01 -> ---[1].s1
                     .word     2                            ;         0x0002 -> ---[1].s2
                     .word     LStr000010                   ;                -> ---[1].pszA
                     .byte     0                            ;           0x00 -> ---[1].baA[0]
                     .byte     0                            ;           0x00 -> ----------[1]
                     .byte     0                            ;           0x00 -> ----------[2]
                     .byte     0                            ;           0x00 -> ----------[3]
                     .byte     0                            ;           0x00 -> ----------[4]
                     .byte     0                            ;           0x00 -> ----------[5]
                     .byte     0                            ;           0x00 -> ----------[6]
                     .byte     0                            ;           0x00 -> ----------[7]
                     .byte     0                            ;           0x00 -> ----------[8]
                     .byte     0                            ;           0x00 -> ----------[9]
                     .word     0                            ;         0x0000 -> ---[1].i
;:                   D2                                     ; Array[3] of Array[1] of unsigned char
                     .byte     1                            ;           0x01 -> D2[0][0]
                     .byte     2                            ;           0x02 -> --[1][0]
                     .byte     3                            ;           0x03 -> --[2][0]
;:                   D3                                     ; Array[3] of Array[5] of unsigned char
                     .byte     111                          ;       'o' 0x6f -> D3[0][0]
                     .byte     110                          ;       'n' 0x6e -> -----[1]
                     .byte     99                           ;       'c' 0x63 -> -----[2]
                     .byte     101                          ;       'e' 0x65 -> -----[3]
                     .byte     0                            ;           0x00 -> -----[4]
                     .byte     116                          ;       't' 0x74 -> --[1][0]
                     .byte     119                          ;       'w' 0x77 -> -----[1]
                     .byte     111                          ;       'o' 0x6f -> -----[2]
                     .byte     0                            ;           0x00 -> -----[3]
                     .byte     0                            ;           0x00 ->      [4]
                     .byte     84                           ;       'T' 0x54 -> --[2][0]
                     .byte     104                          ;       'h' 0x68 -> -----[1]
                     .byte     114                          ;       'r' 0x72 -> -----[2]
                     .byte     101                          ;       'e' 0x65 -> -----[3]
                     .byte     101                          ;       'e' 0x65 -> -----[4]
;:                   D4                                     ; Array[4] of Array[5] of unsigned char
                     .byte     111                          ;       'o' 0x6f -> D4[0][0]
                     .byte     110                          ;       'n' 0x6e -> -----[1]
                     .byte     99                           ;       'c' 0x63 -> -----[2]
                     .byte     101                          ;       'e' 0x65 -> -----[3]
                     .byte     0                            ;           0x00 -> -----[4]
                     .byte     116                          ;       't' 0x74 -> --[1][0]
                     .byte     119                          ;       'w' 0x77 -> -----[1]
                     .byte     111                          ;       'o' 0x6f -> -----[2]
                     .byte     0                            ;           0x00 -> -----[3]
                     .byte     0                            ;           0x00 ->      [4]
                     .byte     84                           ;       'T' 0x54 -> --[2][0]
                     .byte     104                          ;       'h' 0x68 -> -----[1]
                     .byte     114                          ;       'r' 0x72 -> -----[2]
                     .byte     101                          ;       'e' 0x65 -> -----[3]
                     .byte     101                          ;       'e' 0x65 -> -----[4]
                     .byte     0                            ;           0x00 -> --[3][0]
                     .byte     0                            ;           0x00 -> -----[1]
                     .byte     0                            ;           0x00 -> -----[2]
                     .byte     0                            ;           0x00 -> -----[3]
                     .byte     0                            ;           0x00 -> -----[4]
;:                   D5                                     ; Array[3] of (generic) pointer
                     .word     LStr000017                   ;                -> D5[0]
                     .word     LStr000018                   ;                -> --[1]
                     .word     LStr000019                   ;                -> --[2]
                                                            ; #########################
                     .section    .data                      ; # Start of DATA segment #
                                                            ; #########################
                                                            ; This is where the initialization data will be copied to

                     .global   A1
A1:                  .space      16                         ; Array[8] of unsigned short 

                     .global   A2
A2:                  .space      16                         ; Array[8] of unsigned short 

                     .global   A3
A3:                  .space      16                         ; Array[8] of unsigned short 

                     .global   A4
A4:                  .space      18                         ; Array[9] of unsigned short 

                     .global   B1
B1:                  .space       6                         ; Array[3] of Array[2] of unsigned char

                     .global   B2
B2:                  .space       6                         ; Array[3] of Array[2] of unsigned char

                     .global   B3
B3:                  .space       6                         ; Array[3] of Array[2] of unsigned char

                     .global   B4
B4:                  .space       8                         ; Array[4] of Array[2] of unsigned char

                     .global   B5
B5:                  .space       8                         ; Array[4] of Array[2] of unsigned char

                     .global   B6
B6:                  .space       6                         ; Array[2] of Array[3] of unsigned char

                     .global   C1
C1:                  .space      51                         ; Array[3] of structure ''

                     .global   D0
D0:                  .space       2                         ; Array[2] of unsigned char

                     .global   D1a
D1a:                 .space      10                         ; Array[5] of short 

                     .global   D1b
D1b:                 .space      12                         ; Array[6] of short 

                     .global   D1c
D1c:                 .space      14                         ; Array[7] of short 

                     .global   D1d
D1d:                 .space      16                         ; Array[8] of short 

                     .global   D1e
D1e:                 .space      32                         ; Array[16] of short 

                     .global   D1f
D1f:                 .space      12                         ; Array[6] of short 

                     .global   T1
T1:                  .space      17                         ; structure ''

                     .global   aT1
aT1:                 .space      34                         ; Array[2] of structure ''

                     .global   D2
D2:                  .space       3                         ; Array[3] of Array[1] of unsigned char

                     .global   D3
D3:                  .space      15                         ; Array[3] of Array[5] of unsigned char

                     .global   D4
D4:                  .space      20                         ; Array[4] of Array[5] of unsigned char

                     .global   D5
D5:                  .space       6                         ; Array[3] of (generic) pointer
                     ;.endseg                               ; === End of DATA segment ===


                                                            ; ########################
                     .section    .bss                       ; # Start of BSS segment #
                                                            ; ########################
                                                            ; Here starts the uninitialized data

                     .global   A0
A0:                  .space      16                         ; Array[8] of unsigned short 

                     .global   B0
B0:                  .space       6                         ; Array[3] of Array[2] of unsigned char

                     .global   C0
C0:                  .space      51                         ; Array[3] of structure ''

                     .global   T0
T0:                  .space      17                         ; structure ''

                     .global   aT0
aT0:                 .space      68                         ; Array[4] of structure ''
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
