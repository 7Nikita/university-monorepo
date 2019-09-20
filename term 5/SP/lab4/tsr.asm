page    255
.MODEL  TINY
.CODE
bs=8
tab=9
cr=0Dh
lf=0ah
spc=20h
        ORG 80h
cmd_len db ?
cmd_line db ?
        ORG     100h
;---------------------------
vOldInt LABEL   WORD
Begin   PROC    NEAR
        jmp     Init
Begin   ENDP
        ORG     104h
;---------------------------
IntRout PROC    FAR
        cmp 	ah, 09h
        je  	@0
        jmp 	dword ptr cs:[vOldInt]
@0:
        push    es
        push    di
        push    bx
        push    cx
        push    si
        push    dx
        xor     ax, ax
        mov     si, dx
        mov		dl, [si]
        cmp     dl, '$'
        je		exit

cycle:
        cmp     dl, 65
        jnc     label1
        jmp     label3
label1:
        cmp     dl, 91
        jc      label2
        jmp     label3
label2:
        add     dl, 32
        jmp     label6
label3:
        cmp     dl, 97
        jnc     label4
        jmp     label6
label4:
        cmp     dl, 123
        jc      label5
        jmp     label6
label5:
        sub     dl, 32  
label6:      
        mov     ah, 02h
        int     21h 
        inc		si
        mov		dl, [si]
        cmp     dl, '$'
        je		exit
        jmp     cycle

exit:
        pop 	dx
        pop 	si
    	pop 	cx
    	pop 	bx
    	pop 	di
    	pop 	es
        iret
IntRout ENDP
;---------------------------
flag dw 15687
;---------------------------
Init    PROC    NEAR
        mov     ax, 3521h
        int     21h

        cmp     byte ptr cmd_line[1], 'i'
        je      install
        cmp     byte ptr cmd_line[1], 'd'
        je      uninstall
        jmp     error

install:

        cmp     es:flag, 19864
        je      installed

        mov     flag, 19864

        mov     [vOldInt], bx
        mov     [vOldInt+2], es
 
        mov     dx, offset IntRout
        mov     ax, 2521h
        int     21h
 
        mov     dx, offset Init
        int     27h

uninstall:
        cmp     es:flag, 19864
        jne     uninstall_error

        mov     dx, es:vOldInt
        mov     ds, es:vOldInt+2
        mov     ax, 2521h
        int     21h

        mov     ax, 4ch
        int     21h

installed:
        mov     dx, offset installed_str
        mov     ah, 09h
        int     21h

        mov     ah, 4ch
        int     21h

error:
        mov     dx, offset error_str
        mov     ah, 09h
        int     21h

        mov     ah, 4ch
        int     21h
uninstall_error:
        mov     dx, offset uninstall_error_str
        mov     ah, 09h
        int     21h

        mov     ah, 4ch
        int     21h        
Init    ENDP
installed_str db "Already installed!$"
error_str db "Error! Use 'i' to install, 'd' to delete!$"
uninstall_error_str db "Error! Nothing to delete!$"
;---------------------------
        END     Begin