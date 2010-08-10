    .section .entry

// CHDK entry point

MOV     SP, #0x1900
MOV     R11, #0
B       copy_and_restart

// ---> jumps to loader\ixus900_sd900\resetcode\main.c copy_and_restart()
