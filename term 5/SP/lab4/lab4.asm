;tasm lab4.asm
;tlink lab4.obj
;tsr i

model small
.386
.stack 256
.data
  line db 100, ?, 100 Dup(?)
  str_input db "Input string: $"
.code

print_string proc
  push ax
  mov ah, 09h
  int 21h
  pop ax
  ret
print_string endp

start:
  MOV AX, @data
  MOV DS, AX
  
  lea dx, str_input
  call print_string
  
  lea dx, line
  mov ah, 0ah
  int 21h

  mov dl,0ah
  mov ah,2
  int 21h 

  xor bx,bx
  mov bl,[line+1]
  mov [line+2+bx],'$'

  lea dx, line + 2
  call print_string

  MOV AH, 4ch
  INT 21h
end start