; SKC AVR Output - V1(Jan  4 2020)

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

                     .global   Adding
Adding:              ; ###########################################
                     ; # Function: Adding                   
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : @Y+9, Return Address     
                     ; #         : @Y+7, Preserved Frame Pointer
                     ; #   Locals: @Y+5  , a  size=2 int , Class[_____]
                     ; #         : @Y+3  , a1  size=2 int , Class[_____]
                     ; #         : @Y+1  , a2  size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 6       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 6                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_compound_Id_000001
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x08                    ;   1: Immediate 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+3                     ;   2: a1
                     ldd       r21, Y+4                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+1                     ;   2: a2
                     ldd       r21, Y+2                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ;      Compound End --------           ; L_compound_Id_000001
                     ; #### exit ################           ; 
L_Exit_000000:       adiw      r28, 6                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   Subtracting
Subtracting:         ; ###########################################
                     ; # Function: Subtracting              
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : @Y+9, Return Address     
                     ; #         : @Y+7, Preserved Frame Pointer
                     ; #   Locals: @Y+5  , a  size=2 int , Class[_____]
                     ; #         : @Y+3  , a1  size=2 int , Class[_____]
                     ; #         : @Y+1  , a2  size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 6       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 6                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_compound_Id_000003
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x0a                    ;   1: Immediate 10
                     push      r20                          ;   2:
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     mov       r24, r20                     ;   1:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 8
                     push      r20                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     mov       r24, r20                     ;   1:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 8
                     push      r20                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     mov       r24, r20                     ;   1:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x09                    ;   1: Immediate 9
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     ldi       r21, 0x00                    ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     ldi       r21, 0x00                    ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     sub       r20, r24                     ;   1: Sub 16
                     sbc       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ;      Compound End --------           ; L_compound_Id_000003
                     ; #### exit ################           ; 
L_Exit_000002:       adiw      r28, 6                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   Multiplying
Multiplying:         ; ###########################################
                     ; # Function: Multiplying              
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : @Y+9, Return Address     
                     ; #         : @Y+7, Preserved Frame Pointer
                     ; #   Locals: @Y+5  , a  size=2 int , Class[_____]
                     ; #         : @Y+3  , a1  size=2 int , Class[_____]
                     ; #         : @Y+1  , a2  size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 6       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 6                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_compound_Id_000005
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x0c                    ;   1: Immediate 12
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+3                     ;   2: a1
                     ldd       r21, Y+4                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+1                     ;   2: a2
                     ldd       r21, Y+2                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     ;      Expr end ------------           
                     ;      Compound End --------           ; L_compound_Id_000005
                     ; #### exit ################           ; 
L_Exit_000004:       adiw      r28, 6                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   Dividing
Dividing:            ; ###########################################
                     ; # Function: Dividing                 
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : @Y+9, Return Address     
                     ; #         : @Y+7, Preserved Frame Pointer
                     ; #   Locals: @Y+5  , a  size=2 int , Class[_____]
                     ; #         : @Y+3  , b  size=2 int , Class[_____]
                     ; #         : @Y+1  , c  size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 6       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 6                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_compound_Id_000035
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x18                    ;   1: Immediate 24
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x18                    ;   1: Immediate 24
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     rcall     SysDiv16                     ;  +3: Div 1
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x18                    ;   1: Immediate 24
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     rcall     SysDiv16                     ;  +3: Div 1
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x1c                    ;   1: Immediate 28
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x07                    ;   1: Immediate 7
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     rcall     SysDiv16                     ;  +3: Div 1
                     ;      Expr end ------------           
                     ;      Compound End --------           ; L_compound_Id_000035
                     ; #### exit ################           ; 
L_Exit_000034:       adiw      r28, 6                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   Moding
Moding:              ; ###########################################
                     ; # Function: Moding                   
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : @Y+9, Return Address     
                     ; #         : @Y+7, Preserved Frame Pointer
                     ; #   Locals: @Y+5  , a  size=2 int , Class[_____]
                     ; #         : @Y+3  , b  size=2 int , Class[_____]
                     ; #         : @Y+1  , c  size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 6       
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 6                       ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_compound_Id_000051
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x18                    ;   1: Immediate 24
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     rcall     SysDiv16                     ;  +3: Mod 16
                     movw      r20, r0                      ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     rcall     SysDiv16                     ;  +3: Mod 16
                     movw      r20, r0                      ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x18                    ;   1: Immediate 24
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x07                    ;   1: Immediate 7
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     rcall     SysDiv16                     ;  +3: Mod 16
                     movw      r20, r0                      ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x07                    ;   1: Immediate 7
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     rcall     SysDiv16                     ;  +3: Mod 16
                     movw      r20, r0                      ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x1d                    ;   1: Immediate 29
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x07                    ;   1: Immediate 7
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     movw      r24, r20                     ;   1:
                     pop       r21                          ;   2:
                     pop       r20                          ;   2:
                     rcall     SysDiv16                     ;  +3: Mod 16
                     movw      r20, r0                      ;   1:
                     ;      Expr end ------------           
                     ;      Compound End --------           ; L_compound_Id_000051
                     ; #### exit ################           ; 
L_Exit_000050:       adiw      r28, 6                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   Anding
Anding:              ; ###########################################
                     ; # Function: Anding                   
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : @Y+16, Return Address    
                     ; #         : @Y+14, Preserved Frame Pointer
                     ; #   Locals: @Y+13 , c  size=1 char , Class[_____]
                     ; #         : @Y+11 , s  size=2 short , Class[_____]
                     ; #         : @Y+7  , l  size=4 long , Class[_____]
                     ; #         : @Y+5  , a  size=2 int , Class[_____]
                     ; #         : @Y+3  , a1  size=2 int , Class[_____]
                     ; #         : @Y+1  , a2  size=2 int , Class[_____]
                     ; #         : sizeof(locals) = 13      
                     ; ###########################################
                     ; #### frame setup #########           ; 
                     push      r29                          ;   2: (YH) preserve Frame
                     push      r28                          ;   2: (YL)
                     in        r29, _IO_SPH                 ;   1: FP <- SP
                     in        r28, _IO_SPL                 ;   1:
                     ; #### alloc locals ########           ; 
                     sbiw      r28, 13                      ;   2: FP -= sizeof(locals))
                     out       _IO_SPH, r29                 ;   1: SP <- FP
                     out       _IO_SPL, r28                 ;   1:
                     ; #### body text ###########           ; 
                     ; ==== Compound Statement ============ ; L_compound_Id_000075
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     ldi       r21, 0x00                    ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+3                     ;   2: a1
                     ldd       r21, Y+4                     ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+1                     ;   2: a2
                     ldd       r21, Y+2                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: a
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+13                    ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+11                    ;   2: s
                     ldd       r21, Y+12                    ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: l
                     ldd       r21, Y+8                     ;   2:
                     ldd       r22, Y+9                     ;   2:
                     ldd       r23, Y+10                    ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 32
                     and       r21, r25                     ;   1:
                     and       r22, r26                     ;   1:
                     and       r23, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+13                    ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+11                    ;   2: s
                     ldd       r21, Y+12                    ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: l
                     ldd       r21, Y+8                     ;   2:
                     ldd       r22, Y+9                     ;   2:
                     ldd       r23, Y+10                    ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 32
                     and       r21, r25                     ;   1:
                     and       r22, r26                     ;   1:
                     and       r23, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+13                    ;   2: c
                     mov       r21, r20                     ;   1: Signed extend 8 to 16 bits
                     lsl       r21                          ;   1:
                     clr       r21                          ;   1: 
                     sbc       r21, r21                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+11                    ;   2: s
                     ldd       r21, Y+12                    ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: l
                     ldd       r21, Y+8                     ;   2:
                     ldd       r22, Y+9                     ;   2:
                     ldd       r23, Y+10                    ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 32
                     and       r21, r25                     ;   1:
                     and       r22, r26                     ;   1:
                     and       r23, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+13                    ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+11                    ;   2: s
                     ldd       r21, Y+12                    ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 16
                     and       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: l
                     ldd       r21, Y+8                     ;   2:
                     ldd       r22, Y+9                     ;   2:
                     ldd       r23, Y+10                    ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate -1
                     ldi       r21, 0xff                    ;   1:
                     ldi       r22, 0xff                    ;   1:
                     ldi       r23, 0xff                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     and       r20, r24                     ;   1: And 32
                     and       r21, r25                     ;   1:
                     and       r22, r26                     ;   1:
                     and       r23, r27                     ;   1:
                     ;      Expr end ------------           
                     ;      Compound End --------           ; L_compound_Id_000075
                     ; #### exit ################           ; 
L_Exit_000074:       adiw      r28, 13                      ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   Oring
Oring:               ; ###########################################
                     ; # Function: Oring                    
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : @Y+10, Return Address    
                     ; #         : @Y+8, Preserved Frame Pointer
                     ; #   Locals: @Y+7  , c  size=1 char , Class[_____]
                     ; #         : @Y+5  , s  size=2 short , Class[_____]
                     ; #         : @Y+1  , l  size=4 long , Class[_____]
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
                     ; ==== Compound Statement ============ ; L_compound_Id_000081
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x07                    ;   1: Immediate 7
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     push      r20                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     push      r20                          ;   2:
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     push      r20                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     push      r20                          ;   2:
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     push      r20                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     push      r20                          ;   2:
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     push      r20                          ;   2:
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x04                    ;   1: Immediate 4
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     pop       r24                          ;   2:
                     pop       r24                          ;   2: Mul 8
                     clr       r0                           ;   1:
L_MulMult_000082:    sbrc      r20, 0x00                    ; 1/3:
                     add       r0, r24                      ;   1:
                     lsl       r24                          ;   1:
                     breq      L_MulDone_000083             ; 1/2:
                     lsr       r20                          ;   1:
                     brne      L_MulMult_000082             ; 1/2:
L_MulDone_000083:    mov       r20, r0                      ;   1:
                     mov       r21, r20                     ;   1: Signed extend 8 to 16 bits
                     lsl       r21                          ;   1:
                     clr       r21                          ;   1: 
                     sbc       r21, r21                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 16
                     or        r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 16
                     or        r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+1                     ;   2: l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 32
                     or        r21, r25                     ;   1:
                     or        r22, r26                     ;   1:
                     or        r23, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 16
                     or        r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+1                     ;   2: l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 32
                     or        r21, r25                     ;   1:
                     or        r22, r26                     ;   1:
                     or        r23, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     mov       r21, r20                     ;   1: Signed extend 8 to 16 bits
                     lsl       r21                          ;   1:
                     clr       r21                          ;   1: 
                     sbc       r21, r21                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 16
                     or        r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 16
                     or        r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+1                     ;   2: l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 32
                     or        r21, r25                     ;   1:
                     or        r22, r26                     ;   1:
                     or        r23, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 16
                     or        r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+1                     ;   2: l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate -1
                     ldi       r21, 0xff                    ;   1:
                     ldi       r22, 0xff                    ;   1:
                     ldi       r23, 0xff                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     or        r20, r24                     ;   1: Or 32
                     or        r21, r25                     ;   1:
                     or        r22, r26                     ;   1:
                     or        r23, r27                     ;   1:
                     ;      Expr end ------------           
                     ;      Compound End --------           ; L_compound_Id_000081
                     ; #### exit ################           ; 
L_Exit_000080:       adiw      r28, 7                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            

                     .global   Xoring
Xoring:              ; ###########################################
                     ; # Function: Xoring                   
                     ; #   Return: void                     
                     ; #   Params: <none>                   
                     ; #   CPU   : @Y+10, Return Address    
                     ; #         : @Y+8, Preserved Frame Pointer
                     ; #   Locals: @Y+7  , c  size=1 char , Class[_____]
                     ; #         : @Y+5  , s  size=2 short , Class[_____]
                     ; #         : @Y+1  , l  size=4 long , Class[_____]
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
                     ; ==== Compound Statement ============ ; L_compound_Id_000087
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x06                    ;   1: Immediate 6
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     push      r20                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     push      r20                          ;   2:
                     ldi       r20, 0x05                    ;   1: Immediate 5
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     push      r20                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     push      r20                          ;   2:
                     ldi       r20, 0x05                    ;   1: Immediate 5
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x02                    ;   1: Immediate 2
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     push      r20                          ;   2:
                     ldi       r20, 0x05                    ;   1: Immediate 5
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldi       r20, 0x01                    ;   1: Immediate 1
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x05                    ;   1: Immediate 5
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     pop       r24                          ;   2:
                     pop       r24                          ;   2: Mul 8
                     clr       r0                           ;   1:
L_MulMult_000088:    sbrc      r20, 0x00                    ; 1/3:
                     add       r0, r24                      ;   1:
                     lsl       r24                          ;   1:
                     breq      L_MulDone_000089             ; 1/2:
                     lsr       r20                          ;   1:
                     brne      L_MulMult_000088             ; 1/2:
L_MulDone_000089:    mov       r20, r0                      ;   1:
                     mov       r21, r20                     ;   1: Signed extend 8 to 16 bits
                     lsl       r21                          ;   1:
                     clr       r21                          ;   1: 
                     sbc       r21, r21                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     rcall     SysMul16                     ;  +3: Mul 16
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x03                    ;   1: Immediate 3
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     add       r20, r24                     ;   1: Add 16
                     adc       r21, r25                     ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 16
                     eor       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x00                    ;   1: Immediate 0
                     pop       r24                          ;   2:
                     pop       r24                          ;   2: Mul 8
                     clr       r0                           ;   1:
L_MulMult_000092:    sbrc      r20, 0x00                    ; 1/3:
                     add       r0, r24                      ;   1:
                     lsl       r24                          ;   1:
                     breq      L_MulDone_000093             ; 1/2:
                     lsr       r20                          ;   1:
                     brne      L_MulMult_000092             ; 1/2:
L_MulDone_000093:    mov       r20, r0                      ;   1:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 16
                     eor       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+1                     ;   2: l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0x7f                    ;   1: Immediate 127
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 32
                     eor       r21, r25                     ;   1:
                     eor       r22, r26                     ;   1:
                     eor       r22, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     ldi       r21, 0x00                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 16
                     eor       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+1                     ;   2: l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     ldi       r21, 0x00                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 32
                     eor       r21, r25                     ;   1:
                     eor       r22, r26                     ;   1:
                     eor       r22, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     mov       r21, r20                     ;   1: Signed extend 8 to 16 bits
                     lsl       r21                          ;   1:
                     clr       r21                          ;   1: 
                     sbc       r21, r21                     ;   1:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 16
                     eor       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 16
                     eor       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+1                     ;   2: l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     ldi       r22, 0x00                    ;   1:
                     ldi       r23, 0x00                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 32
                     eor       r21, r25                     ;   1:
                     eor       r22, r26                     ;   1:
                     eor       r22, r27                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+7                     ;   2: c
                     push      r20                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 255
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 8
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+5                     ;   2: s
                     ldd       r21, Y+6                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate 65535
                     ldi       r21, 0xff                    ;   1:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 16
                     eor       r21, r25                     ;   1:
                     ;      Expr end ------------           
                     ; ==== Expr Statement ================ ; 
                     ldd       r20, Y+1                     ;   2: l
                     ldd       r21, Y+2                     ;   2:
                     ldd       r22, Y+3                     ;   2:
                     ldd       r23, Y+4                     ;   2:
                     push      r20                          ;   2:
                     push      r21                          ;   2:
                     push      r22                          ;   2:
                     push      r23                          ;   2:
                     ldi       r20, 0xff                    ;   1: Immediate -1
                     ldi       r21, 0xff                    ;   1:
                     ldi       r22, 0xff                    ;   1:
                     ldi       r23, 0xff                    ;   1:
                     pop       r27                          ;   2:
                     pop       r26                          ;   2:
                     pop       r25                          ;   2:
                     pop       r24                          ;   2:
                     eor       r20, r24                     ;   1: Xor 32
                     eor       r21, r25                     ;   1:
                     eor       r22, r26                     ;   1:
                     eor       r22, r27                     ;   1:
                     ;      Expr end ------------           
                     ;      Compound End --------           ; L_compound_Id_000087
                     ; #### exit ################           ; 
L_Exit_000086:       adiw      r28, 7                       ;   2: Y += sizeof(locals)
                     out       _IO_SPH, r29                 ;   1: SP <- Y
                     out       _IO_SPL, r28                 ;   1:
                     pop       r28                          ;   2: FP <- preserved Frame
                     pop       r29                          ;   2: 
                     ret                                    ;   4: 
                     
         
                            
                     ;.endseg                               ; === End of TEXT segment ===



                     .end                                   ; End of generated code.

; eof
