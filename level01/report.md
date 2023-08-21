# Walkthrough

> **The Goal:**make buffer overflow to launch a shell pogram, The idea is to blow the buffer in the `main` then jump to the `run` function
 
![Alt stack frame](stack_frame.png)

**Run function**
> Address of the `run()` function `0x08048444`
 ![Alt run](run.png)
 
 1. Make a script that will explode the buffer then jump into the `run()` function (the address of `run()` function has been reversed)
![Alt script](script.png)

 2. Give  script to the program as argument in stdin through a pipe 
![Alt exploit](exploit.png)

> Password : `53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77`
