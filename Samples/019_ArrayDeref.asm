; SKC AVR Output

#define		_IO_SPL	0x3D
#define		_IO_SPH	0x3E

                                                            ; ##########################
                                                            ; # Start of CONST segment #
                     .section    CONST, "a"                 ; ##########################

                     .global   baRom
baRom:                                                      ; Array[5] of char
                     .byte     0                            ;           0x00 -> baRom[0]
                     .byte     0                            ;           0x00 -> -----[1]
                     .byte     0                            ;           0x00 -> -----[2]
                     .byte     0                            ;           0x00 -> -----[3]
                     .byte     0                            ;           0x00 -> -----[4]

                     .global   saRom
saRom:                                                      ; Array[5] of short 
                     .word     0                            ;         0x0000 -> saRom[0]
                     .word     0                            ;         0x0000 -> -----[1]
                     .word     0                            ;         0x0000 -> -----[2]
                     .word     0                            ;         0x0000 -> -----[3]
                     .word     0                            ;         0x0000 -> -----[4]

                     .global   laRom
laRom:                                                      ; Array[5] of long
                     .long     0                            ;     0x00000000 -> laRom[0]
                     .long     0                            ;     0x00000000 -> -----[1]
                     .long     0                            ;     0x00000000 -> -----[2]
                     .long     0                            ;     0x00000000 -> -----[3]
                     .long     0                            ;     0x00000000 -> -----[4]
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

                     .global   baRam
baRam:               .space       5                         ; Array[5] of char

                     .global   saRam
saRam:               .space      10                         ; Array[5] of short 

                     .global   laRam
laRam:               .space      20                         ; Array[5] of long
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code

                     .global   main
main:                ; ###########################################
                     ; # Function: main                     
                     ; #   Return: unsigned int  (r20,r21)  
                     ; #   Params: laParam          @Y+41  size=2  Pointer to long , Class[_____]
                     ; #         : saParam          @Y+39  size=2  Pointer to short , Class[_____]
                     ; #         : baParam          @Y+37  size=2  Pointer to char , Class[_____]
                     ; #   CPU   : <return addr>    @Y+35  size=2
                     ; #         : <saved fptr>     @Y+33  size=2
                     ; #   Locals: baLocal          @Y+31  size=2  Pointer to char , Class[_____]
                     ; #         : saLocal          @Y+21  size=10 Array[5] of short , Class[_____]
                     ; #         : laLocal          @Y+1   size=20 Array[5] of long , Class[_____]
                     ; #         : sizeof(locals) = 32      
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 32                      ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000002
                     ldi       r20, lo8(baRom)              ;   1: Z = &baRom
                     ldi       r21, hi8(baRom)              ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000002
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000003
                     ldi       r20, lo8(baRom)              ;   1: Z = baRom
                     ldi       r21, hi8(baRom)              ;   1:
                     ldi       r24, 0x01                    ;   1: Immediate short 1
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     lpm       r20, Z                       ;   3: data is in ROM
                     ;      Expr end ------------           ; L_Statement_Expression_000003
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000004
                     ldi       r20, lo8(saRom)              ;   1: Z = saRom
                     ldi       r21, hi8(saRom)              ;   1:
                     ldi       r24, 0x02                    ;   1: Immediate short 2
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     lpm       r20, Z+                      ;   3: data is in ROM
                     lpm       r21, Z+                      ;   3:
                     ;      Expr end ------------           ; L_Statement_Expression_000004
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000005
                     ldi       r20, lo8(laRom)              ;   1: Z = laRom
                     ldi       r21, hi8(laRom)              ;   1:
                     ldi       r24, 0x04                    ;   1: Immediate short 4
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     lpm       r20, Z+                      ;   3: data is in ROM
                     lpm       r21, Z+                      ;   3:
                     lpm       r22, Z+                      ;   3:
                     lpm       r23, Z+                      ;   3:
                     ;      Expr end ------------           ; L_Statement_Expression_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000006
                     ldi       r20, lo8(laRom)              ;   1: Z = laRom
                     ldi       r21, hi8(laRom)              ;   1:
                     ldi       r24, 0x08                    ;   1: Immediate short 8
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     lpm       r20, Z+                      ;   3: data is in ROM
                     lpm       r21, Z+                      ;   3:
                     lpm       r22, Z+                      ;   3:
                     lpm       r23, Z+                      ;   3:
                     ;      Expr end ------------           ; L_Statement_Expression_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldi       r20, lo8(baRam)              ;   1: Z = &baRam
                     ldi       r21, hi8(baRam)              ;   1:
                     ;      Expr end ------------           ; L_Statement_Expression_000007
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r20, lo8(baRam)              ;   1: Z = baRam
                     ldi       r21, hi8(baRam)              ;   1:
                     ldi       r24, 0x01                    ;   1: Immediate short 1
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldi       r20, lo8(saRam)              ;   1: Z = saRam
                     ldi       r21, hi8(saRam)              ;   1:
                     ldi       r24, 0x02                    ;   1: Immediate short 2
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000009
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldi       r20, lo8(laRam)              ;   1: Z = laRam
                     ldi       r21, hi8(laRam)              ;   1:
                     ldi       r24, 0x04                    ;   1: Immediate short 4
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000011
                     ldi       r20, lo8(laRam)              ;   1: Z = laRam
                     ldi       r21, hi8(laRam)              ;   1:
                     ldi       r24, 0x08                    ;   1: Immediate short 8
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000011
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000012
                     ldd       r20, Y+37                    ;   2: reg16 <==baParam
                     ldd       r21, Y+38                    ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000012
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000013
                     ldd       r20, Y+37                    ;   2: reg16 <==baParam
                     ldd       r21, Y+38                    ;   2:
                     ldi       r24, 0x01                    ;   1: Immediate short 1
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ;      Expr end ------------           ; L_Statement_Expression_000013
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000014
                     ldd       r20, Y+39                    ;   2: reg16 <==saParam
                     ldd       r21, Y+40                    ;   2:
                     ldi       r24, 0x02                    ;   1: Immediate short 2
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000014
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000015
                     ldd       r20, Y+41                    ;   2: reg16 <==laParam
                     ldd       r21, Y+42                    ;   2:
                     ldi       r24, 0x04                    ;   1: Immediate short 4
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000015
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000016
                     ldd       r20, Y+41                    ;   2: reg16 <==laParam
                     ldd       r21, Y+42                    ;   2:
                     ldi       r24, 0x08                    ;   1: Immediate short 8
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000016
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000017
                     ldd       r20, Y+31                    ;   2: reg16 <==baLocal
                     ldd       r21, Y+32                    ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000017
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000018
                     ldd       r20, Y+31                    ;   2: reg16 <==baLocal
                     ldd       r21, Y+32                    ;   2:
                     ldi       r24, 0x01                    ;   1: Immediate short 1
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ;      Expr end ------------           ; L_Statement_Expression_000018
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000019
                     movw      r24, r28                     ;   1: Z = saLocal
                     adiw      r24, 0x15                    ;   2:
                     movw      r20, r24                     ;   1:
                     ldi       r24, 0x02                    ;   1: Immediate short 2
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000019
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000020
                     movw      r24, r28                     ;   1: Z = laLocal
                     adiw      r24, 0x01                    ;   2:
                     movw      r20, r24                     ;   1:
                     ldi       r24, 0x04                    ;   1: Immediate short 4
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000020
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000021
                     movw      r24, r28                     ;   1: Z = laLocal
                     adiw      r24, 0x01                    ;   2:
                     movw      r20, r24                     ;   1:
                     ldi       r24, 0x08                    ;   1: Immediate short 8
                     ldi       r25, 0x00                    ;   1:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r30, r20                     ;   1: de-ref pointer
                     ld        r20, Z                       ;   1: data is in RAM
                     ldd       r21, Z+1                     ;   2:
                     ldd       r22, Z+2                     ;   2:
                     ldd       r23, Z+3                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000021
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 32                      ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
