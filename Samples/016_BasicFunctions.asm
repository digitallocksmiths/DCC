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
                     ; ==== Compound Statement ============ ; L_Statement_compound_000001
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       ret                                    ;  4: 
                     
         
                            

                     .global   foo_p
foo_p:               ; ###########################################
                     ; # Function: foo_p                    
                     ; #   Return: void                     
                     ; #   Params: i                @Y+5   size=2 int , Class[_____]
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
                     ; ==== Compound Statement ============ ; L_Statement_compound_000003
                     ;      Compound End --------           ; L_Statement_compound_000003
                     ; #### exit ################           ; 
L_Exit_000002:       adiw      r28, 0                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   foo_l
foo_l:               ; ###########################################
                     ; # Function: foo_l                    
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+5   size=2
                     ; #         : <saved fptr>     @Y+3   size=2
                     ; #   Locals: i                @Y+1   size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 2       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     push      r0                           ;   2: One bytes. Local storage
                     push      r0                           ;   2:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000005
                     ;      Compound End --------           ; L_Statement_compound_000005
                     ; #### exit ################           ; 
L_Exit_000004:       adiw      r28, 2                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   foo_p_l
foo_p_l:             ; ###########################################
                     ; # Function: foo_p_l                  
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : <return addr>    @Y+5   size=2
                     ; #         : <saved fptr>     @Y+3   size=2
                     ; #   Locals: i                @Y+1   size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 2       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     push      r0                           ;   2: One bytes. Local storage
                     push      r0                           ;   2:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000007
                     ;      Compound End --------           ; L_Statement_compound_000007
                     ; #### exit ################           ; 
L_Exit_000006:       adiw      r28, 2                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   bar
bar:                 ; ###########################################
                     ; # Function: bar                      
                     ; #   Return: unsigned int  (r20,r21)  
                     ; #   Params: l                @Y+18  size=4 long , Class[_____]
                     ; #         : i                @Y+16  size=2 int , Class[_____]
                     ; #   CPU   : <return addr>    @Y+14  size=2
                     ; #         : <saved fptr>     @Y+12  size=2
                     ; #   Locals: c                @Y+11  size=1 char , Class[_____]
                     ; #         : s1               @Y+9   size=2 short , Class[_____]
                     ; #         : s2               @Y+7   size=2 short , Class[_____]
                     ; #         : s3               @Y+5   size=2 short , Class[_____]
                     ; #   Locals: i2               @Y+3   size=2 int , Class[_____]
                     ; #   Locals: l2               @Y+1   size=4 long , Class[_____]
                     ; #   Locals: c2               @Y+4   size=1 char , Class[_____]
                     ; #         : sizeof(locals) = 11      
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 11                      ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000009
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000010
                     ldi       r20, 0x00                    ;   1: Immediate short 0
                     ldi       r21, 0x00                    ;   1:
                     std       Y+9, r20                     ;   2: reg16 ==> s1
                     std       Y+10, r21                    ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000010
                     ; ==== For Statement ================= ; L_Statement_For_000015
L_ForTest_000011:    ;      For Test ------------           ; L_Statement_For_000015
L_ForBody_000012:    ;      For Body ------------           ; L_Statement_For_000015
                     ; ==== Compound Statement ============ ; L_Statement_compound_000016
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000017
                     ldi       r20, 0x05                    ;   1: Immediate short 5
                     ldi       r21, 0x00                    ;   1:
                     std       Y+3, r20                     ;   2: reg16 ==> i2
                     std       Y+4, r21                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000017
                     ;      Compound End --------           ; L_Statement_compound_000016
L_ForCont_000013:    ;      For Body end --------           ; L_Statement_For_000015
                     rjmp      L_ForTest_000011             ;   2:
L_ForBreak_000014:   ;      For End -------------           ; L_Statement_For_000015
                     ; ==== For Statement ================= ; L_Statement_For_000022
L_ForTest_000018:    ;      For Test ------------           ; L_Statement_For_000022
L_ForBody_000019:    ;      For Body ------------           ; L_Statement_For_000022
                     ; ==== Compound Statement ============ ; L_Statement_compound_000023
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000024
                     ldi       r20, 0x05                    ;   1: Immediate long 5
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     std       Y+1, r20                     ;   2: reg32 ==> l2
                     std       Y+2, r21                     ;   2:
                     std       Y+3, r22                     ;   2:
                     std       Y+4, r23                     ;   2:
                     ;      Expr end ------------           ; L_Statement_Expression_000024
                     ;      Compound End --------           ; L_Statement_compound_000023
L_ForCont_000020:    ;      For Body end --------           ; L_Statement_For_000022
                     rjmp      L_ForTest_000018             ;   2:
L_ForBreak_000021:   ;      For End -------------           ; L_Statement_For_000022
                     ; ==== For Statement ================= ; L_Statement_For_000029
L_ForTest_000025:    ;      For Test ------------           ; L_Statement_For_000029
L_ForBody_000026:    ;      For Body ------------           ; L_Statement_For_000029
                     ; ==== Compound Statement ============ ; L_Statement_compound_000030
                     ; ==== Expr Statement ================ ; L_Statement_Expression_000031
                     ldi       r20, 0x05                    ;   1: Immediate byte 5
                     std       Y+4, r20                     ;   2: reg8 ==> c2
                     ;      Expr end ------------           ; L_Statement_Expression_000031
                     ;      Compound End --------           ; L_Statement_compound_000030
L_ForCont_000027:    ;      For Body end --------           ; L_Statement_For_000029
                     rjmp      L_ForTest_000025             ;   2:
L_ForBreak_000028:   ;      For End -------------           ; L_Statement_For_000029
                     ;      Compound End --------           ; L_Statement_compound_000009
                     ; #### exit ################           ; 
L_Exit_000008:       adiw      r28, 11                      ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
