include	pmode.lib
.386p
pmode segment use16
	assume	cs:pmode, ds:pmode, es:pmode

	org	100h

main		proc	far
start:

Code_selector	=  8
Stack_selector	= 16
Data_selector	= 24
Screen_selector	= 32
R_Mode_Code		= 40
R_Mode_Data		= 48
	mov	R_Mode_SS,ss
	mov	R_Mode_DS,ds
	mov	R_Mode_ES,es
	mov	R_Mode_FS,fs
	mov	R_Mode_GS,gs

	mov	R_Mode_segment,cs
	lea	ax,R_Mode_entry
	mov	R_Mode_offset,ax

	mov	bx,offset GDT + 8
	xor	eax,eax
	mov	edx,eax

	push	cs
	pop	ax

	shl	eax,4
	mov	dx,1024
	mov	cl,10011000b
	call	set_descriptor

	lea	dx,Stack_seg_start
	add	eax,edx
	mov	dx,1024
	mov	cl,10010110b
	call	set_descriptor

	xor	eax,eax
	mov	ax,ds
	shl	eax,4
	mov	dx,0ffffh
	mov	cl,10010010b
	call	set_descriptor

	mov	eax,0b8000h
	mov	edx,4000
	mov	cl,10010010b
	call	set_descriptor

	xor	eax,eax

	push	cs
	pop	ax

	shl	eax,4
	mov	edx,0ffffh
	mov	cl,10011010b
	call	set_descriptor

	mov	cl,10010010b
	call	set_descriptor

	xor	eax,eax
	mov	edx,eax

	mov	ax,ds
	shl	eax,4
	lea	dx,GDT
	add	eax,edx
	mov	GDT_adr,eax

	mov	dx,55
	mov	GDT_lim,dx

	cli

	lgdt	GDTR

	mov	R_Mode_SP,sp
	mov	eax,cr0
	or	al,1
	mov	cr0,eax

	db	0eah
	dw	P_Mode_entry
	dw	Code_selector

P_Mode_entry:

	mov	ax,Screen_selector
	mov	es,ax

	mov	ax,Data_selector
	mov	ds,ax

	mov	ax,Stack_selector
	mov	ss,ax
	mov	sp,0

	lea	bx,Start_P_Mode_ZS
	mov	di,480
	call	putzs

	lea	bx,P_Mode_ZS
	add	di,160
	call	putzs

	db	0eah
	dw	Pre_R_Mode_entry
	dw	R_Mode_Code


Pre_R_Mode_entry:

	mov	ax,R_Mode_Data
	mov	ss,ax
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax


	mov	eax,cr0
	and	al,0feh
	mov	cr0,eax

		db	0eah
R_Mode_offset	dw	?
R_Mode_segment	dw	?

R_Mode_entry:


	mov	ss,R_Mode_SS
	mov	ds,R_Mode_DS
	mov	es,R_Mode_ES
	mov	fs,R_Mode_FS
	mov	gs,R_Mode_GS

	mov	sp,R_Mode_SP
	sti

	lea	bx,R_Mode_ZS
	mov	ax,0b800h
	mov	es,ax
	mov	di,800
	call putzs

	int	20h

init_set_descriptor
init_putzs
Start_P_Mode_ZS:	db	"Entering to protected mode...",0

P_Mode_ZS:	db	"Working in P-mode...",0

R_Mode_ZS:	db	"Back to real address mode...",0

R_Mode_SP	dw	?
R_Mode_SS	dw	?
R_Mode_DS	dw	?
R_Mode_ES	dw	?
R_Mode_FS	dw	?
R_Mode_GS	dw	?

GDTR	label	fword
GDT_lim		dw	?
GDT_adr		dd	?

GDT:
	dd	?,?
	dd	?,?	
	dd	?,?	
	dd	?,?
	dd	?,?
	dd	?,?
	dd	?,?
	db	1024 dup (?)
Stack_seg_start:
main		endp
	pmode	ends
	end	start