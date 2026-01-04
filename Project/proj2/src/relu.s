.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
# 	a0 (int*) is the pointer to the array
#	a1 (int)  is the # of elements in the array
# Returns:
#	None
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 78.
# ==============================================================================
relu:
    # Error
    beq a1, zero, error
    # Prologue
    addi sp, sp, -4
    sw ra, 0(sp)

    # t0: counter
    add t0, x0, x0
loop_start:
    
    bge t0, a1, loop_end

    # load element from 4 bytes address to t1
    li t1, 4
    mul t1, t0, t1
    add t2, a0, t1
    lw t1, 0(t2)

    # t1 >= 0
    bge t1, x0, loop_continue

    li t1, 0
    sw t1, 0(t2)

loop_continue:

    addi t0, t0, 1
    jal x0, loop_start

loop_end:
    # Epilogue
    lw ra, 0(sp)
    addi sp, sp, 4
	ret
error:
    li a1, 78
    jal exit2
