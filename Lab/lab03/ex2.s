.globl main

.data
source:
    .word   3
    .word   1
    .word   4
    .word   1
    .word   5
    .word   9
    .word   0
dest:
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

.text
fun:
    addi t0, a0, 1
    sub t1, x0, a0
    mul a0, t0, t1
    jr ra

main:
    # BEGIN PROLOGUE
    addi sp, sp, -20
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw ra, 16(sp)
    # END PROLOGUE
    addi t0, x0, 0  # k
    addi s0, x0, 0  # sum
    la s1, source   # load source[0] address to s1
    la s2, dest     # load dest[0] address to s2
loop:
    slli s3, t0, 2  # s3 = t0 << 2   k << 2, means k*4, four bytes
    add t1, s1, s3  # t1: address of source[0] + s3
    lw t2, 0(t1)    # load word from memory source[k] to t2
    beq t2, x0, exit # loop source[k] == 0, t2:source[k]
    add a0, x0, t2  # a0: source[k] 
    addi sp, sp, -8
    sw t0, 0(sp)    # store word t0:k to memory sp+0
    sw t2, 4(sp)    # store word t2:source[k] to memory sp+4
    jal fun         # function
    lw t0, 0(sp)
    lw t2, 4(sp)    
    addi sp, sp, 8
    add t2, x0, a0  # assign (result of fun a0) to t2
    add t3, s2, s3  # t3: address of dest[0] + s3
    sw t2, 0(t3)    # store word t2 to memory t3 dest[k]
    add s0, s0, t2  # sum += dest[k];
    addi t0, t0, 1  # k++
    jal x0, loop
exit:
    add a0, x0, s0  
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20
    # END EPILOGUE
    jr ra
