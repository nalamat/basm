		org		0
		bun		main

; main program starts from 300
		org		300
main:	lda		arr		i
		isz		arr
		isz		i

loop,	add		arr		i	; loop for computing the sum
		isz		arr
		isz		i
		bun		loop

		sta		sum
		out
		hlt

; data part of the program
i:		dec		-5
arr:	dec		500
sum:	dec		0

		org		500
		dec		1
		dec		2
		dec		3
		dec		4
		dec		5

		end					; and we reach the end
