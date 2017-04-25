#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "ballMovement.h"
#include "paddle.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

//int x=10,y=15,direction=2;
int minx=0,maxx=19,miny=0,maxy=39;


void ball(int *x,int *y,int *direction,int f1,int f2,int f3,int f4,int balln){
	switch(*direction){
		case 1:	//printf("case 1\n");
				if(*x==minx){
					if(arr[*x][*y]=='_' || recent[balln-1]=='_'){
						int diff = *y-f1;
						if(diff==0 || diff==1){
							*direction = 6;
							arr[*x+1][*y-1]='O';
							arr[*x][*y]='_';
							*x=*x+1;
							*y=*y-1;
						}
						else if(diff==2){
							*direction = 5;
							arr[*x+1][*y]='O';
							arr[*x][*y]='_';
							*x=*x+1;
						}
						else if(diff==3 || diff==4){
							*direction = 4;
							arr[*x+1][*y+1]='O';
							arr[*x][*y]='_';
							*x=*x+1;
							*y=*y+1;
						}
					}
					else{
						//////////////////update score   wall 1
						/***/

						scp1--;       //To update score of player 1
						arr[20][0]=scp1+'0';
							int kk;
							for(kk=0;kk<2000;kk++){}
							*direction = 6-balln;
							

							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*x=*x+1;
							arr[*x-1][*y]='.';
					}
				}
				else{
					recent[balln-1]=arr[*x-1][*y];
					arr[*x-1][*y]='O';
					arr[*x][*y]='.';
					*x=*x-1;
				}
				break;

		case 2: //printf("case 2\n");
				if(*x==minx && *y==maxy){
					*direction = 6;
					arr[*x+1][*y-2]='O';
					arr[*x][*y]='.';
					*x=*x+1;
					*y=*y-2;
				}
				else if(*x==minx){
					if(arr[*x][*y]=='_' || recent[balln-1]=='_'){
						int diff = *y-f1;
						if(diff==0 || diff==1){
							*direction = 5;
							arr[*x+1][*y]='O';
							arr[*x][*y]='_';
							*x=*x+1;
						}
						else if(diff==2){
							*direction = 4;
							arr[*x+1][*y+1]='O';
							arr[*x][*y]='_';
							*x=*x+1;
							*y=*y+1;
						}
						else if(diff==3 || diff==4){
							*direction = 4;
							arr[*x+1][*y+1]='O';
							arr[*x][*y]='_';
							*x=*x+1;
							*y=*y+1;
						}
					}
					else{
						//////////////////////update score wall 1
						/**direction = 4;
							arr[*x+1][*y+1]='O';
							arr[*x][*y]='.';
							*x=*x+1;
							*y=*y+1;*/
						scp1--;       //To update score of player 1
						arr[20][0]=scp1+'0';
						int kk;
							for(kk=0;kk<2000;kk++){}
							*direction = 4-balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*y=*y+1;
							arr[*x][*y-1]='.';
					}
				}
				else if(*y==maxy){
					if(arr[*x][*y]=='|' || recent[balln-1]=='|'){
						int diff = *x-f2;
						if(diff==0){
							*direction = 8;
							arr[*x-1][*y-1]='O';
							arr[*x][*y]='|';
							*x=*x-1;
							*y=*y-1;
						}
						else if(diff==1){
							*direction = 8;
							arr[*x-1][*y-1]='O';
							arr[*x][*y]='|';
							*x=*x-1;
							*y=*y-1;
						}
						else{
							*direction = 7;
							arr[*x][*y-1]='O';
							arr[*x][*y]='|';
							*y=*y-1;
						}
					}
					else{
						///////////////////////update score wall 2
						/**direction = 8;
							arr[*x-1][*y-1]='O';
							arr[*x][*y]='.';
							*x=*x-1;
							*y=*y-1;*/

						scp2--;       //To update score of player 2
						arr[20][1]=scp2+'0';
						int kk;
							for(kk=0;kk<2000;kk++){}
							*direction = 8-balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*y=*y-1;
							arr[*x][*y+1]='.';
					}
				}
				else{
					recent[balln-1]=arr[*x-1][*y+1];
					arr[*x-1][*y+1]='O';
					arr[*x][*y]='.';
					*x=*x-1;
					*y=*y+1;
				}
				break;

		case 3: //printf("case 3\n");
				if(*y==maxy){
					if(arr[*x][*y]=='|' || recent[balln-1]=='|'){
						int diff = *x-f2;
						if(diff==0){
							*direction = 8;
							arr[*x-1][*y-1]='O';
							arr[*x][*y]='|';
							*x=*x-1;
							*y=*y-1;
						}
						else if(diff==1){
							*direction = 7;
							arr[*x][*y-1]='O';
							arr[*x][*y]='|';
							*y=*y-1;
						}
						else{
							*direction = 6;
							arr[*x+1][*y-2]='O';
							arr[*x][*y]='|';
							*x=*x+1;
							*y=*y-2;	
						}
					}
					else{
						/////////////////////update score wall 2
						/**direction = 7;
							arr[*x][*y-1]='O';
							arr[*x][*y]='.';
							*y=*y-1;*/

						scp2--;       //To update score of player 2
						arr[20][1]=scp2+'0';

						int kk;
							for(kk=0;kk<2000;kk++){}
							*direction = 7-balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*y=*y-1;
							arr[*x][*y+1]='.';
					}
				}
				else{
					
					arr[*x][*y]='.';
					if(*y+1 != maxy){recent[balln-1]=arr[*x][*y+2];arr[*x][*y+2]='O';*y=*y+2;}
					else {recent[balln-1]=arr[*x][*y+1];arr[*x][*y+1]='O';*y=*y+1;}
					
					
				}
				break;

		case 4: //printf("case 4\n");
				if(*x==maxx && *y==maxy){
					*direction = 8;
					arr[*x-1][*y-2]='O';
					arr[*x][*y]='.';
					*x=*x-1;
					*y=*y-2;
				}
				else if(*x==maxx){
					if(arr[*x][*y]=='_' || recent[balln-1]=='_'){
						int diff=*y-f3;
						if(diff==0 || diff==1){
							*direction = 1;
							arr[*x-1][*y]='O';
							arr[*x][*y]='_';
							*x=*x-1;
						}
						else if(diff==2){
							*direction = 2;
							arr[*x-1][*y+1]='O';
							arr[*x][*y]='_';
							*x=*x-1;
							*y=*y+1;
						}
						else{
							*direction = 2;
							arr[*x-1][*y+1]='O';
							arr[*x][*y]='_';
							*x=*x-1;
							*y=*y+1;
						}
					}
					else{
						/////////////////////update score wall 3
						

						scp3--;       //To update score of player 3
						arr[20][2]=scp3+'0';

						*direction = 3-balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*x=*x-1;
							*y=*y+1;
							arr[*x+1][*y-1]='.';
					}
				}
				else if(*y==maxy){
					if(arr[*x][*y]=='|' || recent[balln-1]=='|'){
						int diff=*x-f2;
						if(diff==0){
							*direction = 7;
							arr[*x][*y-1]='O';
							arr[*x][*y]='|';
							*y=*y-1;
						}
						else if(diff==1){
							*direction = 6;
							arr[*x+1][*y-2]='O';
							arr[*x][*y]='|';
							*x=*x+1;
							*y=*y-2;
						}
						else{
							*direction = 6;
							arr[*x+1][*y-2]='O';
							arr[*x][*y]='|';
							*x=*x+1;
							*y=*y-2;
						}
					}
					else{
						////////////////////////update score wall 2
						/**direction = 6;
							arr[*x+1][*y-2]='O';
							arr[*x][*y]='.';
							*x=*x+1;
							*y=*y-2;*/

						scp2--;       //To update score of player 2
						arr[20][1]=scp2+'0';

						int kk;
							for(kk=0;kk<2000;kk++){}
							*direction = 6-balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*x=*x+1;
							*y = *y-2;
							arr[*x-1][*y+2]='.';
					}
				}
				else{
					recent[balln-1]=arr[*x+1][*y+1];
					arr[*x+1][*y+1]='O';
					arr[*x][*y]='.';
					*x=*x+1;
					*y=*y+1;
				}
				break;

		case 5: //printf("case 5\n");
				if(*x==maxx){
					if(arr[*x][*y]=='_' || recent[balln-1]=='_'){
						int diff = *y-f3;
						if(diff==0 || diff==1){
							*direction = 8;
							arr[*x-1][*y-2]='O';
							arr[*x][*y]='_';
							*x=*x-1;
							*y=*y-2;
						}
						else if(diff==2){
							*direction = 1;
							arr[*x-1][*y]='O';
							arr[*x][*y]='_';
							*x=*x-1;
						}
						else{
							*direction = 2;
							arr[*x-1][*y+1]='O';
							arr[*x][*y]='_';
							*x=*x-1;
							*y=*y+1;
						}
					}
					else{
						/////////////////////////////update score wall 3
						

						scp3--;       //To update score of player 3
						arr[20][2]=scp3+'0';

						*direction = 3-balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*x=*x-1;
							arr[*x+1][*y]='.';
					}
				}
				else{
					recent[balln-1]=arr[*x+1][*y];
					arr[*x+1][*y]='O';
					arr[*x][*y]='.';
					*x=*x+1;
				}
				break;

		case 6: //printf("case 6\n");
				if(*y==miny && *x==maxx){
					*direction = 2;
					arr[*x-2][*y+1]='O';
					arr[*x][*y]='.';
					*x=*x-2;
					*y=*y+1;
				}
				else if(*y==miny){
					if(arr[*x][*y]=='|' || recent[balln-1]=='|'){
						int diff = *x-f4;
						if(diff==0){
							*direction = 3;
							arr[*x][*y+1]='O';
							arr[*x][*y]='|';
							*y=*y+1;
						}
						else if(diff==1){
							*direction = 4;
							arr[*x+1][*y+1]='O';
							arr[*x][*y]='|';
							*x=*x+1;
							*y=*y+1;
						}
						else{
							*direction = 4;
							arr[*x+1][*y+1]='O';
							arr[*x][*y]='|';
							*x=*x+1;
							*y=*y+1;
						}
					}
					else{
						///////////////////////////update score wall 4
						


						scp4--;       //To update score of player 4
						arr[20][3]=scp4+'0';

						*direction = 5-balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*x=*x+1;
							*y=*y+1;
							arr[*x-1][*y-1]='.';
					}
				}
				else if(*x==maxx){
					if(arr[*x][*y]=='_' || recent[balln-1]=='_'){
						int diff = *y-f3;
						if(diff==0 || diff==1){
							*direction = 8;
							arr[*x-1][*y-1]='O';
							arr[*x][*y]='_';
							*x=*x-1;
							*y=*y-1;
						}
						else if(diff==2){
							*direction = 8;
							arr[*x-1][*y-1]='O';
							arr[*x][*y]='_';
							*x=*x-1;
							*y=*y-1;
						}
						else{
							*direction = 1;
							arr[*x-1][*y]='O';
							arr[*x][*y]='_';
							*x=*x-1;
						}
					}
					else{
						////////////////////////update score wall 3
						

						scp3--;       //To update score of player 3
						arr[20][2]=scp3+'0';

						*direction = 8-balln;
							//arr[*x-1][*y-1]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*x=*x-1;
							*y=*y-1;
							arr[*x+1][*y+1]='.';
					}
				}
				else{
					recent[balln-1]=arr[*x+1][*y-1];
					arr[*x+1][*y-1]='O';
					arr[*x][*y]='.';
					*x=*x+1;
					*y=*y-1;
				}
				break;

		case 7: //printf("case 7\n");
				if(*y==miny){
					if(arr[*x][*y]=='|' || recent[balln-1]=='|'){
						int diff = *x-f4;
						if(diff==0){
							*direction = 2;
							arr[*x-2][*y+1]='O';
							arr[*x][*y]='|';
							*x=*x-2;
							*y=*y+1;
						}
						else if(diff==1){
							*direction = 3;
							arr[*x][*y+1]='O';
							arr[*x][*y]='|';
							*y=*y+1;
						}
						else{
							*direction = 4;
							arr[*x+1][*y+1]='O';
							arr[*x][*y]='|';
							*x=*x+1;
							*y=*y+1;
						}
					}
					else{
						///////////////////////update score wall 4
						

						scp4--;       //To update score of player 4
						arr[20][3]=scp4+'0';

						*direction = 3-balln;
							//arr[*x][*y+1]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*y=*y+1;
							arr[*x][*y-1]='.';
					}
				}
				else{
					
					arr[*x][*y]='.';
					if(*y-1 != miny){recent[balln-1]=arr[*x][*y-2];arr[*x][*y-2]='O';*y=*y-2;}
					else{recent[balln-1]=arr[*x][*y-1];arr[*x][*y-1]='O';*y=*y-1;}		
				}
				break;

		case 8: //printf("case 8\n");
				if(*x==minx && *y==miny){
					*direction = 4;
					arr[*x+1][*y+2]='O';
					arr[*x][*y]='.';
					*x=*x+1;
					*y=*y+2;
				}
				else if(*x==minx){
					if(arr[*x][*y]=='_' || recent[balln-1]=='_'){
						int diff = *y-f1;
						if(diff==0 || diff==1){
							*direction = 6;
							arr[*x+1][*y-1]='O';
							arr[*x][*y]='_';
							*x=*x+1;
							*y=*y-1;
						}
						else if(diff==2){
							*direction = 6;
							arr[*x+1][*y-1]='O';
							arr[*x][*y]='_';
							*x=*x+1;
							*y=*y-1;
						}
						else{
							*direction = 5;
							arr[*x+1][*y]='O';
							arr[*x][*y]='_';
							*x=*x+1;
						}
					}
					else{
						//////////////////////////update score wall 1
						/***/

						scp1--;       //To update score of player 4
						arr[20][0]=scp1+'0';

						*direction = 6-balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*x=*x+1;
							*y=*y-1;

							arr[*x-1][*y+1]='.';
					}
				}
				else if(*y==miny){
					if(arr[*x][*y]=='|' || recent[balln-1]=='|'){
						int diff = *x-f4;
						if(diff==0){
							*direction = 2;
							arr[*x-1][*y+1]='O';
							arr[*x][*y]='|';
							*x=*x-1;
							*y=*y+1;
						}
						else if(diff==1){
							*direction = 2;
							arr[*x-1][*y+1]='O';
							arr[*x][*y]='|';
							*x=*x-1;
							*y=*y+1;
						}
						else{
							*direction = 3;
							arr[*x][*y+1]='O';
							arr[*x][*y]='|';
							*y=*y+1;
						}
					}
					else{
						//////////////////////////update score wall 4
						

						scp4--;       //To update score of player 4
						arr[20][3]=scp4+'0';

						*direction = 2+balln;
							//arr[10][20]='O';
							arr[*x][*y]='.';
							*x =10;
							*y= 20;
							arr[*x][*y]='O';
							*x=*x-1;
							*y=*y+1;

							arr[*x+1][*y-1]='.';
					}
				}
				else{
					recent[balln-1]=arr[*x-1][*y-1];
					arr[*x-1][*y-1]='O';
					arr[*x][*y]='.';
					*x=*x-1;
					*y=*y-1;
				}
				break;
	}
	return;
}

