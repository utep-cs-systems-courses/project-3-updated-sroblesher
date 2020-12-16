	.arch msp43030g2553
	.p2align 1,0		;Align to power of 2.
	.text
	.global centerValid
	.global drawPixelAssembly
	.global redLedOn
	.global state_advance
	.extern drawPixel
	.extern red_on
	.extern led_changed
	.extern new_first_state
	.extern second_state
	.extern new_third_state
	.extern new_fourth_state
	.extern state		;button last pressed
	;; Outgoing return value
	;; Incoming parameters
	;; Stack Pointer use for variables
	;; Unsigend comparison
centerValid:	       ;centerValid(initialCol, initicalRow)
	sub #2, r1		;Space for two variables conatining max col and max row
	mov.b #111, 0(r1)	;Max col
	mov.b #120, 1(r1)	;Max row
	
	cmp.b 0(r1), r12	;notValid if initialCol > 0(r1)
	jc notValid
	cmp.b 1(r1), r13	;not valid if initialRow > 1(r1)
	jc notValid
	
	add #2, r1		;Restore stack pointer
	jmp valid
	
valid:
	mov.b #1, r12		;Returns true
	pop r0

notValid:
	mov.b #0, r12		;Returns false
	pop r0

	;; Helper for drawing triangle
	;; Stack Pointer use for variables
	;; Outcoming Parameters
drawPixelAssembly:
	sub #5, r1		;Space for stack pointer
	mov r15, 0(r1)		;fontFgColor -> u_int
	mov.b r12, 2(r1)	;col -> u_char
	mov.b r13, 3(r1)	;initialCol -> u_char 
	mov.b r14, 4(r1)	;row + initialRow -> u_int
        add.b r13, r12		;initialCol+col
	mov.b 4(r1), r13	;row + initialRow
	mov 0(r1), r14		;fontFgColor
	
	call #drawPixel		;drawPixel(initialCol+col, row+initialRow, fontFgColor)

	mov.b 3(r1), r12	;initialCol
	sub.b 2(r1), r12	;initialCol-col
	mov.b 4(r1), r13	;row + initialRow
	mov 0(r1), r14		;fontFgColor
	
	call #drawPixel		;drawPixel(initialCol-col, row+initialRow, fontFgColor)
	add #5, r1		;Restore stack pointer
	pop r0			;Return

	
	;; Red light on, function
redLedOn:
	mov.b #1, &red_on	;red_on = 1
	mov.b #1, &led_changed	;led_changed = 1
	pop r0 			;return



	;; Jump Table -> switch
	;; Signed comparison
	;; Ingoing return value
jt:
	.word default		;jt[0]
	.word state1		;jt[1]
	.word state2		;jt[2]
	.word state3		;jt[3]
	.word state4		;jt[4]
	
state_advance:
	mov.b #0, r13		;r13 will contain variable "changed" which is a char
	cmp &state, #4		;If state more than 4
	jl default		;N != V, meaning result is negative
	cmp #0, &state		;If state less than 0
	jl default

	mov &state, r14
	add r14, r14		;to go to the correct state
	mov jt(r14), r0		;jmp to jt[state]
	
state1:
	call #new_first_state	;Call function
	mov.b r12, r13		;Assign value returned by function to variable "changed"
	jmp end		;break
	
state2:
	call #second_state
	mov.b r12, r13		;changed = second_state()
	jmp end
	
state3:
	call #new_third_state
	mov.b r12, r13		;changed = new_third_state()
	jmp end
	
state4:
	call #new_fourth_state
	mov.b r12, r13		;changed = new_fourth_state
	jmp end
	
default:			;goto end
end:
	mov.b r13, &led_changed	;led_changed = changed
	call #led_update	;led_update()
	pop r0			;Return
