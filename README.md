# Linux-fake-shell-in-C
A small C project designed to roughly emulate a bash shell. Developed in ubuntu 14.04.

cscd340Lab8.pdf contains a sample run and valgrind run of this program.

Available commands:

Basic commands such as                 "ls -l" and "pwd"
Change directory command               cd
Single pipes such as                   ls -l | wc -w
Aliasing such as                       alias printworkingd="pwd"
Some history functions, such as ! to repeat the most recent command.
A command to print recent commands:   "history"

