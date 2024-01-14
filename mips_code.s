.text
line0:
# declare a
line1:
# copy to a
  li $t0, 0
  sw $t0, a
line2:
# declare i
line3:
# copy to i
  li $t0, 0
  sw $t0, i
line4:
# if lt
  lw $t0, i
  li $t1, 5
  blt $t0, $t1, line6
line5:
# goto
  j line12
line6:
# declare .tmp0
line7:
  li $t0, 1
  lw $t1, i
  add $t0, $t0, $t1
  sw $t0, .tmp0
line8:
# declare b
line9:
# copy to b
  li $t0, 0
  sw $t0, b
line10:
# copy to i
  lw $t0, .tmp0
  sw $t0, i
line11:
# goto
  j line4
line12:
# return 0
  li $v0, 10
  syscall
.data
  __string_newline: .asciiz "\n"
  __string_tab: .asciiz "\t"
  __float_zero: .float 0.0
  a: .word 0
  i: .word 0
  .tmp0: .word 0
  b: .word 0
