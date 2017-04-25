#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#include <termios.h> 
#include <unistd.h>
#include <sys/types.h> 
 
#define BUFLEN 512 
#define PORT 8888   //The port on which to send data
int user; int levelNo=0;

struct sockaddr_in si_other;
int s, i, slen=sizeof(si_other);
char buf[BUFLEN];
char recvBuf[21][40];
char message[BUFLEN];

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

void die(char *s)
{
    perror(s);
    exit(1);
}

void sendReadyConfirmaton(){
	char y='\0';
    printf("enter y to start the game\n");
    while(y!= 'y')scanf("%c",&y);
    memset(message,'\0',BUFLEN);
    message[0]=y;
    if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }
    printf("starting the game .....waiting for other players to get ready\n");
    levelNo++;
}


int main(int argc,char*argv[])
{	
	
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
    
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(argv[1] , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    
    memset(message,'\0',BUFLEN);
    message[0]='0';message[1]='\0';
    if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
    {
        die("sendto()");
    }
    printf("waiting for other players to join the game\n");

    if (recvfrom(s, buf, BUFLEN,0, (struct sockaddr *) &si_other, &slen) != -1)
    {
        printf("you are user number : %d\n",(int)buf[0]);
        user=(int)buf[0]+1;
    }
    else{
        die("recvfrom()");
    }

    sendReadyConfirmaton();

    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);     
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    char action;
    while(1)
    {   
        memset(message,'\0',BUFLEN);
        struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
        if( poll(&mypoll, 1, 5) )
        {   
            scanf("%c", &action);

            message[0]= user+'0';
            message[1]=action;
            //send the message
            if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
         

        memset(recvBuf,'\0', BUFLEN);
        if (recvfrom(s, &recvBuf, sizeof(recvBuf), MSG_DONTWAIT, (struct sockaddr *) &si_other, &slen) != -1)
        {	

        	if(recvBuf[0][0]=='x'){
        		printf("\nlevel %d over\n",levelNo);
        		printf("FINAL SCORES AFTER LEVEL %d\n",levelNo);
   				printf("player1:%d   player2:%d   player2:%d  player4:%d \n", recvBuf[0][1]-'0',recvBuf[0][2]-'0',recvBuf[0][3]-'0',recvBuf[0][4]-'0');   
        		if(levelNo<3)sendReadyConfirmaton();
        		else if(levelNo==3) break;
        	}
        	else{
        		 int m,n;
	        	 system("clear");
			     for(m=0;m<20;m++){
			     	for(n=0;n<40;n++){
			     		if(recvBuf[m][n]=='_' || recvBuf[m][n]=='|')printf("%s%c%s",COLOR_GREEN,recvBuf[m][n],COLOR_RESET);
			    		else printf("%s%c%s",COLOR_BLUE,recvBuf[m][n],COLOR_RESET);
			     	}
			     	printf("\n");
			     }
			     printf("----------------LIVE SCORE BOARD----------------\n\n");
			     printf("\n Player1: %c lives remaining.\n", recvBuf[20][0]);
			     printf("\n Player2: %c lives remaining.\n", recvBuf[20][1]);
			     printf("\n Player3: %c lives remaining.\n", recvBuf[20][2]);
			     printf("\n Player4: %c lives remaining.\n", recvBuf[20][3]);
        	}
        	 
        }    
    }
    
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    close(s);
    return 0;
}
