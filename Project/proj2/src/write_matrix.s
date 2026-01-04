.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
# - If you receive an fopen error or eof,
#   this function terminates the program with error code 93.
# - If you receive an fwrite error or eof,
#   this function terminates the program with error code 94.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 95.
# ==============================================================================
write_matrix:
    # =======================================
    # Prologue
    addi sp, sp, -24
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw ra, 20(sp)

    mv s0, a0   # pointer to string representing the filename
    mv s1, a1   # the pointer to the start of the matrix in memory
    mv s2, a2   # rows
    mv s3, a3   # columns

    # ================================== 
    # Open file
    # Opens file with name a1 with permissions a2.
    addi sp, sp, -12
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)

    mv a1, s0
    li a2, 1
    jal ra, fopen

    mv s4, a0   # file descriptor

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    addi sp, sp, 12

    # ==================================    
    # Write rows
    # Writes a3 * a4 bytes from the buffer in a2 to the file descriptor a1.
    addi sp, sp, -20
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)

    mv a1, s4   # file descriptor

    addi sp, sp, -4
    sw s2, 0(sp)
    mv a2, sp   # buffer, stack pointer
    lw s2, 0(sp)
    addi sp, sp, 4

    li a3, 1
    li a4, 4

    jal ra, fwrite

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    lw a4, 16(sp)
    addi sp, sp, 20

    # ==================================    
    # Write rows
    # Writes a3 * a4 bytes from the buffer in a2 to the file descriptor a1.
    addi sp, sp, -20
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)

    mv a1, s4   # file descriptor

    addi sp, sp, -4
    sw s3, 0(sp)
    mv a2, sp   # buffer, stack pointer
    lw s3, 0(sp)
    addi sp, sp, 4

    li a3, 1
    li a4, 4

    jal ra, fwrite

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    lw a4, 16(sp)
    addi sp, sp, 20

    # ==================================    
    # Write matrix
    # Writes a3 * a4 bytes from the buffer in a2 to the file descriptor a1.
    addi sp, sp, -20
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)

    mv a1, s4   # file descriptor
    mv a2, s1   # buffer
    mul a3, s2, s3 # rows * columns
    li a4, 4

    jal ra, fwrite

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    lw a4, 16(sp)
    addi sp, sp, 20

    # ==================================    
    # Close file
    # Closes the file descriptor a1.
    addi sp, sp, -4
    sw a1, 0(sp)

    mv a1, s4   # file descriptor

    jal ra, fclose

    lw a1, 0(sp)
    addi sp, sp, 4

    # =======================================
    # Epilogue

    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw ra, 20(sp)
    addi sp, sp, 24

    ret
