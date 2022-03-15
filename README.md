# README OF MY WORLD
Operating Systems and Programming 
Assignment 2
To run the code, you must install readline package 
`sudo apt install libreadline-dev `

To build: `make`

To run: `./world`
## world.h
Contains all the header files and functions are specified.
## utils.c
Contains all the functions to redirect the input to the respective function and break the input in token for extracting flags in it.
## cd.c
Contains the functions for changing directory.
cd <dir>
<br>
cd ..
<br>
cd ~ -> home
<br>
cd -> home
<br>
cd ../..
<br>

## clear.c
Contains the functions for clearing the screen.
clear -> clear the screen
## echo.c
Contains the functions for printing the text.
echo <text>
## exit.c
Contains the functions for exiting the program.
exit
quit
## history.c
Contains the functions for printing history.
Works for the last 20 history over multiple sessions.
## ls.c
Contains the functions for listing the files.
<br>
ls -l -> list the files in long format
<br>
ls -> list the files in short format
<br>
ls -a -> list all the files
<br>
ls -l <file> -> list the file in long format
<br>
ls -l <dir> -> list the files of dir. in long format
<br>
ls -la <dir1> <dir2>
<br>
ls -l <dir1> -a <dir2>
<br>

## main.c
Contains the main function.
Basically for the signal handler and starting the main loop.
## pinfo.c
Contains the functions for printing the information about the process.
pinfo -> pinfo of shell
<br>
pinfo <pid> -> pinfo of process

## pwd.c
Contains the functions for printing the current working directory.
pwd

## repeat.c
Contains the functions for repeating the command n number of times.(n will be given by the user)
repeat <n(number)> <command> -> command will be executed n number of times

## redirection.c
Contains the functions for redirection of the input and output from any file.
">" -> redirect the output to the file
">>" -> append the output to the file
"<" -> redirect the input to the file

## Command Pipelines ("exec_com" function in util.c)
Contains the functions for executing the command pipelines in the shell and using a output of 1st function as a input in the next function.
func1 | func2 | func3 -> output of func1 will be used as input in func2 and output of func2 will be used as input in func3, and finally the func3 will be executed.

## jobs.c
Contains the functions for printing all the jobs in sorting order.
Flags:
-r -> Printing the jobs with the status of running (sorted).
-s -> Printing the jobs with the status of stopped (sorted).

## sig.c
Contains the function to direct the signal for a particular process/job.

## bg.c
Contains the functions to change the process of stopped job to running.

## fg.c
Contains the functions to run a background process in the foreground.

## Signal Handling (Ctrl+C,Ctrl+Z in main.c file and Ctrl+D in util.c file)
Contains the functions for handling the signal.
-> Ctrl+C -> Terminate the process
-> Ctrl+Z -> Shift the process to background and change the status to stopped
-> Ctrl+D -> Logout the shell
