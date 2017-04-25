#ifndef paddle
#define paddle
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h> 

char arr[21][40];
int lives;
int scp1,scp2,scp3,scp4;
char recent[2];
extern int paddleMove(char c,int user);

#endif

