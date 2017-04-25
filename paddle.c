#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h> 
#include "paddle.h"

int paddleMove(char c,int user){
	printf("action received %c\n",c);
	if(user==4){
		int first;
		for(first=0;first<20;first++){
			if(arr[first][0]=='|') break;
		}
		if(c=='w'){
			int last=first+2;
			if(first==0) return 0;
			else{
				//arr[last][0]='.';
				//arr[first-1][0]='|';
				return first-1;
			}
		}
		else if(c=='s'){
			int last=first+2;
			if(last==19) return 17;
			else{
				//arr[last+1][0]='|';
				//arr[first][0]='.';
				return first+1;
			}
		}
		else return first;

	}

	else if(user==2){
		int first;
		for(first=0;first<20;first++){
			if(arr[first][39]=='|') break;
		}
		if(c=='w'){
			int last=first+2;
			if(first==0) return 0;
			else{
				//arr[last][39]='.';
				//arr[first-1][39]='|';
				return first-1;
			}
		}
		else if(c=='s'){
			int last=first+2;
			if(last==19) return 17;
			else{
				//arr[last+1][39]='|';
				//arr[first][39]='.';
				return first+1;
			}
		}
		else return first;

	}

	else if(user==1){
		int first;
		for(first=0;first<40;first++){
			if(arr[0][first]=='_') break;
		}
		if(c=='a'){
			int last=first+4;
			if(first==0) return 0;
			else{
				//arr[0][last]='.';
				//arr[0][first-1]='_';
				if(first-1 !=0 ){/*arr[0][first-2]='_';arr[0][last-1]='.';*/return first-2;}
				return first-1;
			}
		}
		else if(c=='d'){
			int last=first+4;
			if(last==39) return 35;
			else{
				//arr[0][last+1]='_';
				//arr[0][first]='.';
				if(last+1 !=39 ){/*arr[0][last+2]='_';arr[0][first+1]='.';*/return first+2;}
				return first+1;
			}
		}
		else return first;

	}

	else if(user==3){
		int first;
		for(first=0;first<40;first++){
			if(arr[19][first]=='_') break;
		}
		if(c=='a'){
			int last=first+4;
			if(first==0) return 0;
			else{
				//arr[19][last]='.';
				//arr[19][first-1]='_';
				if(first-1 !=0 ){/*arr[19][first-2]='_';arr[19][last-1]='.';*/return first-2;}
				return first-1;
			}
		}
		else if(c=='d'){
			int last=first+4;
			if(last==39) return 35;
			else{
				//arr[19][last+1]='_';
				//arr[19][first]='.';
				if(last+1 !=39 ){/*arr[19][last+2]='_';arr[19][first+1]='.';*/return first+2;}
				return first+1;
			}
		}
		else return first;
	}	
}