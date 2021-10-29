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
                     ;.endseg                               ; === End of BSS segment ===


                                                            ; #########################
                     .section    .text                      ; # Start of TEXT segment #
                                                            ; #########################
                                                            ; Here starts the executable code

                     .global   main
main:                ; ###########################################
                     ; # Function: main                     
                     ; #   Return: unsigned int  (r20,r21)  
                     ; #   Params: lY               @Y+15  size=4 long , Class[_____]
                     ; #         : sY               @Y+13  size=2 short , Class[_____]
                     ; #         : bY               @Y+12  size=1 char , Class[_____]
                     ; #   CPU   : <return addr>    @Y+10  size=2
                     ; #         : <saved fptr>     @Y+8   size=2
                     ; #   Locals: c                @Y+7   size=1 char , Class[_____]
                     ; #         : s1               @Y+5   size=2 short , Class[_____]
                     ; #         : s2               @Y+3   size=2 short , Class[_____]
                     ; #         : s3               @Y+1   size=2 short , Class[_____]
                     ; #         : sizeof(locals) = 7       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 7                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ; ==== Switch Statement ============== ; L_Statement_Switch_000005
                     ldd       r20, Y+15                    ;   2: reg32 <== lY
                     ldd       r21, Y+16                    ;   2:
                     ldd       r22, Y+17                    ;   2:
                     ldd       r23, Y+18                    ;   2:
L_Case_000003_2:     cpi       r20, 0x78                    ;   1: -> Case 305419896
                     brne      L_Case_000003_3              ; 1/2:
                     cpi       r21, 0x56                    ;   1:
                     brne      L_Case_000003_3              ; 1/2:
                     cpi       r22, 0x34                    ;   1:
                     brne      L_Case_000003_3              ; 1/2:
                     cpi       r23, 0x12                    ;   1:
                     breq      L_Body_000004_1              ; 1/2:
L_Case_000003_3:     cpi       r20, 0x03                    ;   1: -> Case 3
                     brne      L_Case_000003_4              ; 1/2:
                     cpi       r21, 0x00                    ;   1:
                     brne      L_Case_000003_4              ; 1/2:
                     cpi       r22, 0x00                    ;   1:
                     brne      L_Case_000003_4              ; 1/2:
                     cpi       r23, 0x00                    ;   1:
                     breq      L_Body_000004_2              ; 1/2:
L_Case_000003_4:     cpi       r20, 0xff                    ;   1: -> Case -1
                     brne      L_Case_000003_5              ; 1/2:
                     cpi       r21, 0xff                    ;   1:
                     brne      L_Case_000003_5              ; 1/2:
                     cpi       r22, 0xff                    ;   1:
                     brne      L_Case_000003_5              ; 1/2:
                     cpi       r23, 0xff                    ;   1:
                     breq      L_Body_000004_2              ; 1/2:
L_Case_000003_5:     jrmp      L_Body_000004_3              ;   2: -> Default
L_Body_000004_1:     ;      Case ----------------           ; L_Statement_Switch_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000006
                     ldi       r20, 0x01                    ;   1: Immediate short 1
                     ldi       r21, 0x00                    ;   1:
                     std       Y+5, r20                     ;   2: reg16 ==> s1
                     std       Y+6, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000006
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000007
                     ldi       r20, 0x02                    ;   1: Immediate short 2
                     ldi       r21, 0x00                    ;   1:
                     std       Y+3, r20                     ;   2: reg16 ==> s2
                     std       Y+4, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000007
L_Body_000004_2:     ;      Case ----------------           ; L_Statement_Switch_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000008
                     ldi       r20, 0x01                    ;   1: Immediate short 1
                     ldi       r21, 0x00                    ;   1:
                     std       Y+5, r20                     ;   2: reg16 ==> s1
                     std       Y+6, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000008
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000009
                     ldi       r20, 0x02                    ;   1: Immediate short 2
                     ldi       r21, 0x00                    ;   1:
                     std       Y+3, r20                     ;   2: reg16 ==> s2
                     std       Y+4, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000009
                     ; ==== Break Statement =============== ; 
                     rjmp      L_Break_000002               ;   2: break
L_Body_000004_3:     ;      Default -------------           ; L_Statement_Switch_000005
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldi       r20, 0x01                    ;   1: Immediate short 1
                     ldi       r21, 0x00                    ;   1:
                     std       Y+5, r20                     ;   2: reg16 ==> s1
                     std       Y+6, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000011
                     ldi       r20, 0x02                    ;   1: Immediate short 2
                     ldi       r21, 0x00                    ;   1:
                     std       Y+3, r20                     ;   2: reg16 ==> s2
                     std       Y+4, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000011
                     ; ==== Break Statement =============== ; 
                     rjmp      L_Break_000002               ;   2: break
L_Break_000002:      ;      Switch end ----------           ; L_Statement_Switch_000005
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 7                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
