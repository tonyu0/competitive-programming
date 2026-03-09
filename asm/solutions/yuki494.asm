; https://yukicoder.me/problems/no/494
section .data
yuki db  'yukicoder'
buf db  0

section .text
global _start
_start:
  ; read
  mov rsi, buf
  mov rdx, 20
  syscall
  ; ?
  call  check
  ; write
  mov rax, 1
  mov rdi, rax
  lea rsi, [yuki + r10]
  mov rdx, rax
  syscall
  ; exit
  mov rax, 60
  xor rdi, rdi
  syscall

check:
  mov al, [buf + r10]
  mov dil, al
  cmp dil, 63
  jz  check_ret
  inc r10
  loop  check
check_ret:
  ret