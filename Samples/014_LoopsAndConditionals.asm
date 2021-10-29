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

                     .global   bar
bar:                 ; ###########################################
                     ; # Function: bar                      
                     ; #   Return: unsigned int  (r20,r21)  
                     ; #   Params: l                @Y+14  size=4 long , Class[_____]
                     ; #         : i                @Y+12  size=2 int , Class[_____]
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
                     ; ==== Goto Statement ================ ; 
                     rjmp      Label_bar_l1                 ;   2: goto
Label_bar_l1:        ; ==== If Statement ================== ; L_Statement_If_000002
                     ldd       r20, Y+5                     ;   2: reg16 <==s1
                     ldd       r21, Y+6                     ;   2:
                     or        r20, r21                     ;   1: Cast Short to Flag
                     breq      L_IfElse_000004              ; 1/2: branch if FALSE
                                                            ;    : fall through on TRUE
L_IfThen_000003:     ;      If Then ------------            ; L_Statement_If_000002
                     ; ==== Break Statement =============== ; 
                     ; ***** Unexpected break statement found here ***
                     rjmp      L_IfDone_000005              ; 1/2:
L_IfElse_000004:     ;      If Else ------------            ; L_Statement_If_000002
                     ; ==== Continue Statement ============ ; 
                     ; ***** Unexpected continue statement found here ***
L_IfDone_000005:     ;      If End --------------           ; L_Statement_If_000002
                     ;      Compound End --------           ; L_Statement_compound_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 7                       ;   2: Y += sizeof(locals)
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
                     ; #   CPU   : <return addr>    @Y+4   size=2
                     ; #         : <saved fptr>     @Y+2   size=2
                     ; #   Locals: c                @Y+1   size=1 char , Class[_____]
                     ; #         : sizeof(locals) = 1       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     push      r0                           ;   2: One byte. Local storage
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_Statement_compound_000007
Label_foo_l2:        ; ==== If Statement ================== ; L_Statement_If_000008
                     ldd       r20, Y+1                     ;   2: reg8 <==c
                     tst       r20                          ;   1: Cast Byte to Flag
                     breq      L_IfElse_000010              ; 1/2: branch if FALSE
                                                            ;    : fall through on TRUE
L_IfThen_000009:     ;      If Then ------------            ; L_Statement_If_000008
                     ; ==== Goto Statement ================ ; 
                     rjmp      Label_foo_l1                 ;   2: goto
                     rjmp      L_IfDone_000011              ; 1/2:
L_IfElse_000010:     ;      If Else ------------            ; L_Statement_If_000008
                     ; ==== Goto Statement ================ ; 
                     rjmp      Label_foo_l2                 ;   2: goto
L_IfDone_000011:     ;      If End --------------           ; L_Statement_If_000008
                     ;      Compound End --------           ; L_Statement_compound_000007
                     ; #### exit ################           ; 
L_Exit_000006:       adiw      r28, 1                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
