all:
	gcc main.c utils.c cd.c clear.c echo.c exit.c history.c ls.c pinfo.c pwd.c repeat.c redir.c jobs.c sig.c fg.c bg.c -o world   
compile: