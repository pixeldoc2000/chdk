    .section .entry

// Firmware Entry Point

// ordinary startup...

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart

// NEXT: loader/ixus300_sd4000/main.c
