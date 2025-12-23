.globl factorial

.data
n: .word 8

.text
main:
    la t0, n            # load address of n to t0
    lw a0, 0(t0)        # load word from memory (address of n) to a0
    jal ra, factorial

    addi a1, a0, 0      # a1 = a0
    addi a0, x0, 1      # a0 = 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    addi t2, a0, -1      # t2 = n - 1
loop:
    beq t2, x0, exit    # 0 exit loop
    mul a0, a0, t2      # a0 = a0 * t2
    addi t2, t2, -1       # t2 = t2 - 1
    jal x0, loop        # must not change ra
exit:
    jr ra

# result = n
# for(i = n-1; i >= 1; i--) // i < 1 exit
#    result = result*i

