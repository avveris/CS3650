        .data
intro:   .asciz "collatz("
result:  .asciz "): "
newline: .asciz "\n"

        .text
main:   # the prolog for main
        addi sp, sp, -8
        sw s0, 0(sp)

        # copy argument to temporary rgister
        mv t0, a0

        li s0, 1
loop:   # printing string "collatz(i): "
        li a7, 4
        la a0, intro
        ecall

         # syscall for print integer
        li a7, 1
        mv a0, s0
        ecall

        li a7, 4
        la a0, result
        ecall

        # calling collatz(i)
        mv a0, s0             # arg n
        li a1, 1              # arg x
        jal ra, f

        # printing result
        mv t0, a0
        li a7, 1
        mv a0, t0
        ecall

        li a7, 4
        la a0, newline
        ecall

        # loop counting bounds
        addi s0, s0, 1
        li t1, 100
        blt s0, t1, loop

        # epilog for main
        lw s0, 0(sp)
        addi sp, sp, 8
        li a7, 10
        ecall

f:
        # prolog
        addi sp, sp, -16
        sw ra, 8(sp)
        sw s1, 4(sp)
        sw s2, 0(sp)

        # copy args temp registers
        mv t0, a0
        mv t1, a1

        # save arguments in saved registers
        mv s1, t0
        mv s2, t1

        # base case: if n == 1
        li t2, 1
        beq s1, t2, base_case

        #if even/odd
        andi t2, s1, 1
        beq t2, zero, even_case

odd_case:
        # 3n + 1
        li t2, 3
        mul a0, s1, t2
        addi a0, a0, 1
        addi a1, s2, 1
        jal ra, f
        j end

even_case:
        #  n/2
        srli a0, s1, 1
        addi a1, s2, 1
        jal ra, f
        j end

base_case:
        mv a0, s2

end:    # epilog
        lw s2, 0(sp)
        lw s1, 4(sp)
        lw ra, 8(sp)
        addi sp, sp, 16
        jr ra
        
