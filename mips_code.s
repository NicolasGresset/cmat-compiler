.text
line0:
# declare mat X
line1:
# array affect X[0] = ...
  la $t0, X
  l.s $f0, __float_tmp0
  s.s $f0, 0($t0)
line2:
# array affect X[1] = ...
  la $t0, X
  l.s $f0, __float_tmp1
  s.s $f0, 4($t0)
line3:
# declare mat IA
line4:
# array affect IA[0] = ...
  la $t0, IA
  l.s $f0, __float_tmp2
  s.s $f0, 0($t0)
line5:
# array affect IA[1] = ...
  la $t0, IA
  l.s $f0, __float_tmp3
  s.s $f0, 4($t0)
line6:
# array affect IA[2] = ...
  la $t0, IA
  l.s $f0, __float_tmp4
  s.s $f0, 8($t0)
line7:
# array affect IA[3] = ...
  la $t0, IA
  l.s $f0, __float_tmp5
  s.s $f0, 12($t0)
line8:
# declare mat A
line9:
# array affect A[0] = ...
  la $t0, A
  l.s $f0, __float_tmp6
  s.s $f0, 0($t0)
line10:
# array affect A[1] = ...
  la $t0, A
  l.s $f0, __float_tmp7
  s.s $f0, 4($t0)
line11:
# array affect A[2] = ...
  la $t0, A
  l.s $f0, __float_tmp8
  s.s $f0, 8($t0)
line12:
# array affect A[3] = ...
  la $t0, A
  l.s $f0, __float_tmp9
  s.s $f0, 12($t0)
line13:
# array affect A[4] = ...
  la $t0, A
  l.s $f0, __float_tmp10
  s.s $f0, 16($t0)
line14:
# array affect A[5] = ...
  la $t0, A
  l.s $f0, __float_tmp11
  s.s $f0, 20($t0)
line15:
# declare mat B
line16:
# declare mat .tmp0
line17:
# matop plus .tmp0 = A + scalaire
  la $t0, .tmp0
  la $t1, A
  li $t2, 1
  mtc1 $t2, $f2
  cvt.s.w $f2, $f2
  l.s $f0, 0($t1)
  add.s $f0, $f0, $f2
  s.s $f0, 0($t0)
  l.s $f0, 4($t1)
  add.s $f0, $f0, $f2
  s.s $f0, 4($t0)
  l.s $f0, 8($t1)
  add.s $f0, $f0, $f2
  s.s $f0, 8($t0)
  l.s $f0, 12($t1)
  add.s $f0, $f0, $f2
  s.s $f0, 12($t0)
  l.s $f0, 16($t1)
  add.s $f0, $f0, $f2
  s.s $f0, 16($t0)
  l.s $f0, 20($t1)
  add.s $f0, $f0, $f2
  s.s $f0, 20($t0)
line18:
# copy to B
# copy mat B = .tmp0
  la $t0, B
  la $t1, .tmp0
  l.s $f0, 0($t1)
  s.s $f0, 0($t0)
  l.s $f0, 4($t1)
  s.s $f0, 4($t0)
  l.s $f0, 8($t1)
  s.s $f0, 8($t0)
  l.s $f0, 12($t1)
  s.s $f0, 12($t0)
  l.s $f0, 16($t1)
  s.s $f0, 16($t0)
  l.s $f0, 20($t1)
  s.s $f0, 20($t0)
line19:
# declare a
line20:
# copy to a
  li $t0, 0
  sw $t0, a
line21:
# declare i
line22:
# copy to i
  li $t0, 0
  sw $t0, i
line23:
# if lt
  lw $t0, i
  li $t1, 5
  blt $t0, $t1, line25
line24:
# goto
  j line31
line25:
# declare .tmp1
line26:
  li $t0, 1
  lw $t1, i
  add $t0, $t0, $t1
  sw $t0, .tmp1
line27:
# declare b
line28:
# copy to b
  li $t0, 0
  sw $t0, b
line29:
# copy to i
  lw $t0, .tmp1
  sw $t0, i
line30:
# goto
  j line23
line31:
# return 0
  li $v0, 10
  syscall
.data
  __string_newline: .asciiz "\n"
  __string_tab: .asciiz "\t"
  __float_zero: .float 0.0
  X: .float 0.0, 0.0
  __float_tmp0:  .float 1.000000
  __float_tmp1:  .float 2.000000
  IA: .float 0.0, 0.0, 0.0, 0.0
  __float_tmp2:  .float 1.000000
  __float_tmp3:  .float 2.000000
  __float_tmp4:  .float 3.000000
  __float_tmp5:  .float 4.000000
  A: .float 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
  __float_tmp6:  .float 1.000000
  __float_tmp7:  .float 2.000000
  __float_tmp8:  .float 3.000000
  __float_tmp9:  .float 4.000000
  __float_tmp10:  .float 5.000000
  __float_tmp11:  .float 6.000000
  B: .float 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
  .tmp0: .float 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
  a: .word 0
  i: .word 0
  .tmp1: .word 0
  b: .word 0
