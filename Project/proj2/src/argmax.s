.globl argmax

.text
# =================================================================
# FUNCTION: Given a int vector, return the index of the largest
#	element. If there are multiple, return the one
#	with the smallest index.
# Arguments:
# 	a0 (int*) is the pointer to the start of the vector
#	a1 (int)  is the # of elements in the vector
# Returns:
#	a0 (int)  is the first index of the largest element
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 77.
# =================================================================
argmax:
    # Error
    beq a1, zero, error_argmax
    # Prologue
    addi sp, sp, -4
    sw, ra, 0(sp)

    # t0: counter
    add t0, x0, x0

loop_start:
    bge t0, a1, loop_end

    # load element from 4 bytes address to t1
    li t1, 4
    mul t1, t0, t1
    add t2, a0, t1
    lw t1, 0(t2)

    # compare t1: new value with old max value t3
    beq t0, x0, update
    # t3 < t1
    blt t3, t1, update
loop_continue:
    addi t0, t0, 1
    jal loop_start
update:
    # update max value and index
    mv t3, t1   # max value
    mv t4, t0   # index
    addi t0, t0, 1
    jal loop_start

loop_end:
    
    # Epilogue
    mv a0, t4

    lw, ra, 0(sp)
    addi sp, sp, 4
    ret

error_argmax:
    li a1, 77
    jal exit2
