# Walkthrough

**Main** : 
This program checking if an integer value from the command line is equal to 0x1a7 (423 in decimal).  
If the condition is met, it allocates memory for the string "/bin/sh," sets user and group IDs, and then executes the shell.  
Otherwise, it prints "No !" to the standard error stream

**Process**:  
>   Make reverse engineering with Githdra  retrieved source file in C language to analyse it
>   Run the program with given argument


## How to find the password:  
When give to the program `423` as argument it launch a shell that shell it laucnh with rights to display file 
```

level0@RainFall:~$ ./level0 423
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a

```
