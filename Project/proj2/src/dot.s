.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int vectors
# Arguments:
#   a0 (int*) is the pointer to the start of v0
#   a1 (int*) is the pointer to the start of v1
#   a2 (int)  is the length of the vectors
#   a3 (int)  is the stride of v0
#   a4 (int)  is the stride of v1
# Returns:
#   a0 (int)  is the dot product of v0 and v1
# Exceptions:
# - If the length of the vector is less than 1,
#   this function terminates the program with error code 75.
# - If the stride of either vector is less than 1,
#   this function terminates the program with error code 76.
# =======================================================
dot:
    # Error
    beq a2, zero, error1_dot
    beq a3, zero, error0_dot
    beq a4, zero, error0_dot
    
    # Prologue
    addi sp, sp, -4
    sw ra, 0(sp)

    # t0: counter for loop
    add t0, x0, x0

    # t5 for result
    li t5, 0
loop_start:
    bge t0, a2, loop_end

    # load v0 element from 4 bytes address to t1
    li t1, 4
    mul t1, t1, a3
    mul t1, t1, t0
    add t1, a0, t1
    lw t1, 0(t1)

    # load v1 element from 4 bytes address to t1
    li t2, 4
    mul t2, t2, a4
    mul t2, t2, t0
    add t2, a1, t2
    lw t2, 0(t2)

    # multiplication and add
    mul t4, t1, t2
    add t5, t4, t5

    addi t0, t0, 1
    jal loop_start
loop_end:


    # Epilogue
    mv a0, t5

    lw ra, 0(sp)
    addi sp, sp, 4

    ret
error0_dot:
    li a1, 76
    jal exit2
error1_dot:
    li a1, 75
    jal exit2
