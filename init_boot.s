; ------------------------------------------------------------------------------
;          Definitions
; ------------------------------------------------------------------------------

; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

ARM_MODE_USR        EQU     0x10
ARM_MODE_FIQ        EQU     0x11
ARM_MODE_IRQ        EQU     0x12
ARM_MODE_SVC        EQU     0x13
ARM_MODE_ABT        EQU     0x17
ARM_MODE_UND        EQU     0x1B
ARM_MODE_SYS        EQU     0x1F

I_BIT               EQU     0x80            ; when I bit is set, IRQ is disabled
F_BIT               EQU     0x40            ; when F bit is set, FIQ is disabled

AT91C_BASE_AIC      EQU     0xFFFFF000
AIC_IVR             EQU     0x100
AIC_EOICR           EQU     0x130

UND_Stack_Size      EQU     0x00000000
SVC_Stack_Size      EQU     0x00000100
ABT_Stack_Size      EQU     0x00000000
FIQ_Stack_Size      EQU     0x00000000
IRQ_Stack_Size      EQU     0x00000080
USR_Stack_Size      EQU     0x00000400

        PRESERVE8

; ------------------------------------------------------------------------------
;    Area Definition and Entry Point
;    Startup Code must be linked first at Address at which it expects to run.
; ------------------------------------------------------------------------------

        AREA	VECTOR, CODE
        ARM
	
Vectors			; Exception Vectors
		b		HandlerReset	; Handler for Startup
		b		HandlerUndef	; Handler for Undefined mode
		b		HandlerSWI		; Handler for SWI interrupt
		b		HandlerPabort	; Handler for Prefetch Abort
		b		HandlerDabort	; Handler for Data Abort
	;	b		.				; Handler Reserved
		DCD		0x7FFF			; Set for SAM9 bootstrap
		b		HandlerIRQ		; Handler for IRQ interrupt
		b		HandlerFIQ		; Handler for FIQ interrupt

;------------------------------------------------------------------------------
;
;------------------------------------------------------------------------------
HandlerUndef
		b		HandlerUndef


;------------------------------------------------------------------------------
;
;------------------------------------------------------------------------------
HandlerSWI
		b		HandlerSWI

;------------------------------------------------------------------------------
;
;------------------------------------------------------------------------------
HandlerPabort
		b		HandlerPabort

;------------------------------------------------------------------------------
;
;------------------------------------------------------------------------------
HandlerDabort
		b		HandlerDabort

;------------------------------------------------------------------------------
; Handles incoming interrupt requests by branching to the corresponding
; handler, as defined in the AIC. Supports interrupt nesting.
;------------------------------------------------------------------------------
HandlerIRQ
        ;  Save interrupt context on the stack to allow nesting */
        SUB     lr, lr, #4
        STMFD   sp!, {lr}
        MRS     lr, SPSR
        STMFD   sp!, {r0,r1,lr}

        ; Write in the IVR to support Protect Mode */
        LDR     lr, =AT91C_BASE_AIC
        LDR     r0, [r14, #AIC_IVR]
        STR     lr, [r14, #AIC_IVR]

        ; Branch to interrupt handler in Supervisor mode */
        MSR     CPSR_c, #ARM_MODE_SVC
        STMFD   sp!, {r1-r4, r12, lr}
        MOV     lr, pc
        BX      r0
        LDMIA   sp!, {r1-r4, r12, lr}
        MSR     CPSR_c, #ARM_MODE_IRQ :OR: I_BIT

        ; Acknowledge interrupt */
        LDR     lr, =AT91C_BASE_AIC
        STR     lr, [r14, #AIC_EOICR]

        ; Restore interrupt context and branch back to calling code
        LDMIA   sp!, {r0,r1,lr}
        MSR     SPSR_cxsf, lr
        LDMIA   sp!, {pc}^

;------------------------------------------------------------------------------
;
;------------------------------------------------------------------------------
HandlerFIQ
		b		HandlerFIQ

;------------------------------------------------------------------------------
; After a reset, execution starts here, the mode is ARM, supervisor
; with interrupts disabled.
; Initializes the chip and branches to the main() function.
;------------------------------------------------------------------------------

   		AREA	STARTUP, CODE
   		ENTRY        ; Entry point for the application

        EXPORT  HandlerReset
        IMPORT	|Image$$Fixed_region$$Limit|
        IMPORT  |Image$$Relocate_region$$Base|
        IMPORT  |Image$$Relocate_region$$ZI$$Base|
        IMPORT  |Image$$Relocate_region$$ZI$$Limit|
        IMPORT  |Image$$ARM_LIB_STACK$$Base|
        IMPORT  |Image$$ARM_LIB_STACK$$ZI$$Limit|
        
		; Perform low-level initialization of the chip using InitHW()
		IMPORT  InitHW
		
HandlerReset   
        
        ; Set pc to actual code location (i.e. not in remap zone)
	    LDR     pc, =JumpStart
		
JumpStart	    
		; Set up temporary stack (Top of the SRAM)
		LDR     r0, = |Image$$ARM_LIB_STACK$$ZI$$Limit|
        MOV     sp, r0
		; Call Low level init
	    LDR     r0, =InitHW
        MOV     lr, pc
        BX      r0

;Initialize the Relocate_region segment 
		LDR 	r0, = |Image$$Fixed_region$$Limit|
		LDR 	r1, = |Image$$Relocate_region$$Base|
		LDR 	r3, = |Image$$Relocate_region$$ZI$$Base|
	    
	    CMP     r0, r1                 
     	BEQ     %1

; Copy init data
0       CMP     r1, r3         
        LDRCC   r2, [r0], #4   
        STRCC   r2, [r1], #4
        BCC     %0

1       LDR     r1, =|Image$$Relocate_region$$ZI$$Limit|
        MOV     r2, #0
2       CMP     r3, r1                  
        STRCC   r2, [r3], #4
        BCC     %2
     
; Setup Stack for each mode

        LDR     R0, = |Image$$ARM_LIB_STACK$$ZI$$Limit|

;  Enter IRQ Mode and set its Stack Pointer
        MSR     CPSR_c, #ARM_MODE_IRQ:OR:I_BIT:OR:F_BIT
        MOV     SP, R0
        SUB     R4, SP, #IRQ_Stack_Size

; Supervisor mode (interrupts enabled) 
        MSR     CPSR_c, #ARM_MODE_SVC:OR:F_BIT
        MOV     SP, R4         

; Enter the C code

        IMPORT  __main
        LDR     R0, =__main
        BX      R0

JumpLoop
        B       JumpLoop

        AREA  bootm_init, CODE
		
		EXPORT BootmSet_ParamAddr
		EXPORT BootmSet_MachineID
		
BootmSet_ParamAddr
		;r0= paddr
		mov		r2, r0		
        bx      lr
		
BootmSet_MachineID
		;r0= mid
		mov		r1, r0
		
		mov		r0, #0
		mov		ip, #0
		mcr		p15, 0, ip, c13, c0, 0
		mcr		p15, 0, ip, c7, c7, 0
		mcr		p15, 0, ip, c7, c10, 4
		mcr		p15, 0, ip, c8, c7, 0
		mrc		p15, 0, ip, c1, c0, 0
		bic		ip, ip, #0x0001
		mcr		p15, 0, ip, c1, c0, 0
		bx      lr

        END
