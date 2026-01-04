.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
# - If malloc returns an error,
#   this function terminates the program with error code 88.
# - If you receive an fopen error or eof, 
#   this function terminates the program with error code 90.
# - If you receive an fread error or eof,
#   this function terminates the program with error code 91.
# - If you receive an fclose error or eof,
#   this function terminates the program with error code 92.
# ==============================================================================
# Pseudocode:
# int fopen(char *a1, int a2)    
# Opens file with name a1 with permissions a2.
# args:
#   a1 = filepath
#   a2 = permissions (0, 1, 2, 3, 4, 5 = r, w, a, r+, w+, a+)
# return:
#   a0 = file descriptor
# On failure, a0 is set to -1.

# int fread(int a1, void *a2, size_t a3)
# Reads a3 bytes of the file into the buffer a2.
# args:
#   a1 = file descriptor
#   a2 = pointer to the buffer you want to write the read bytes to.
#   a3 = Number of bytes to be read.
# return:
#   a0 = Number of bytes actually read.
# On failure, a0 is set to -1.

# the first 8 bytes contains the two 4 byte dimensions of the matrix, which will tell you how many bytes to read from the rest of the file

# void* malloc(int a0) 
# Allocates heap memory and return a pointer to it
# args:
#   a0 is the # of bytes to allocate heap memory for
# return:
#   a0 is the pointer to the allocated heap memory
# malloc row*column memory space

# int fclose(int a1)
# Closes the file descriptor a1.
# args:
#   a1 = file descriptor
# return:
#   a0 = 0 on success, and EOF (-1) otherwise.
# ==============================================================================
read_matrix:
    # ==================================
    # Prologue
	addi sp, sp, -24
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)

    mv s0, a0   # the pointer to string representing the filename
    mv s1, a1   # the number of rows
    mv s2, a2   # the number of columns

    # ================================== 
    # Open file
    # Opens file with name a1 with permissions a2.
    addi sp, sp, -12
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)

    mv a1, s0
    li a2, 0
    jal ra, fopen

    mv s3, a0   # file descriptor

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    addi sp, sp, 12
    # ==================================    
    # Reads rows
    # Reads a3 bytes of the file into the buffer a2.
    addi sp, sp, -16
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)

    mv a1, s3
    mv a2, s1
    li a3, 4
    jal ra, fread

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    addi sp, sp, 16
    # ==================================    
    # Reads columns
    # Reads a3 bytes of the file into the buffer a2.
    addi sp, sp, -16
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)

    mv a1, s3
    mv a2, s2
    li a3, 4
    jal ra, fread

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    addi sp, sp, 16
    # ==================================    
    # Reads matrix
    # Reads a3 bytes of the file into the buffer a2.
    addi sp, sp, -16
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)

    mv a1, s3       # file descriptor
    # ==============
    # malloc
    addi sp, sp, -8
    sw a0, 0(sp)
    sw a1, 4(sp)

    lw t0, 0(s1)
    lw t1, 0(s2)
    mul t2, t0, t1
    slli t2, t2, 2

    mv a0, t2
    jal ra, malloc
    mv s4, a0       # a0 is the pointer of allocated memory 

    lw a0, 0(sp)
    lw a1, 4(sp)
    addi sp, sp, 8
    # ==============
    # read data
    lw t0, 0(s1)
    lw t1, 0(s2)
    mul t2, t0, t1
    slli t2, t2, 2

    mv a2, s4   # buffer
    mv a3, t2
    jal ra, fread 

    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    addi sp, sp, 16
    # ==================================

    mv a0, s4

    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    addi sp, sp, 24

    ret
