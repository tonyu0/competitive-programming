; https://yukicoder.me/problems/no/656
section .bss
in_buf  resb  0
in_size resb  10
in_now resb 0
out_buf resb  30
out_size  resb  0

section .text
global _start
_start:
  call  read
  call  calc
  call  putint
  call  write
  call  exit

read:
  mov rax,  0
  mov rdi,  0
  mov rsi,  in_buf
  mov rdx,  in_size
  syscall
  ret

nextchar:
  mov rdi,  in_buf
  add rdi,  [in_now]
  mov al, [rdi]
  add byte [in_now], 1
  ret

calc:
  xor rax,  rax
calc1:
  push  rax
  call  nextchar
  mov dil,  al
  pop rax
  cmp dil,  48
  ; 0 or 1~9 or 終端で別分岐
  jz  calc2
  jb  calc3
  movzx rcx,  dil
  sub rcx,  48
  add rax,  rcx
  jmp calc1
calc2:
  add rax,  10
  jmp calc1
calc3:
  mov rdi, rax
  ret


putchar:
  mov rax,  out_buf
  add rax,  [out_size]
  mov [rax],  dil
  add byte [out_size], 1
  ret
putint:
  mov rcx,  0
  mov rax,  rdi
putint_calc:
  cmp rax,  0
  je  putint_out
  xor rdx,  rdx
  mov rbx,  10
  div rbx
  push  rdx
  add rcx,  1
  jmp putint_calc
putint_out:
  pop rdi
  add rdi,  48
  push  rcx
  call  putchar
  pop rcx
  loop  putint_out
putint_ret:
  ret

write:
  mov rax,  1
  mov rdi,  1
  mov rsi,  out_buf
  mov rdx,  [out_size]
  syscall
  ret

exit:
  mov rax,  60
  xor rdi,  rdi
  syscall