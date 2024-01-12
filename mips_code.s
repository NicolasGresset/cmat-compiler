.text
# declare a
# copy to a
  li $t0, 1
  sw $t0, a
# declare b
# plus
  lw $t0, a
  li $t1, 2
  add $t0, $t0, $t1
  sw $t0, .tmp0
# copy to b
  lw $t0, .tmp0
  sw $t0, b
.data
  a: .word 0
  b: .word 0
