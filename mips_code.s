.text
  li $t0, 1
  sw $t0, a
  lw $t0, a
  li $t1, 2
  add $t0, $t0, $t1
  sw $t0, .tmp0
  lw $t0, .tmp0
  sw $t0, b
.data
  a: .word 0
  b: .word 0
