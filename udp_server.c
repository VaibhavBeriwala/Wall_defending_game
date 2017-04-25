#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h> 
#include "paddle.h"
#include "ballMovement.h"
 
#define BUFLEN 512 
#define PORT 8888   //The port on which to listen for incoming data

struct sockaddr_in si_me, si_other;
int s, i, slen = sizeof(si_other) , recv_len;
char buf[BUFLEN];

int finalScp1=0,finalScp2=0,finalScp3=0,finalScp4=0;  //final scores of players

int peers;
int changes = 0;
int ball_ctr = 0;
int prev_ball;
struct sockaddr_in peer_list[4];
int qwerty=0;
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int checkRecv(struct sockaddr_in recv){
    for(int i=0;i<4;i++){
        if(peer_list[i].sin_addr.s_addr==recv.sin_addr.s_addr && peer_list[i].sin_port==recv.sin_port) return i+1;
    }
    return 0;
}

void waitForPlayers(){
    int playersReady=0;
    int player1Ready=0,player2Ready=0,player3Ready=0,player4Ready=0;
    printf("starting the game\nwaiting for all players to be ready\n");

    while(playersReady<4){
            memset(buf,'\0',BUFLEN);
            if ((recv_len = recvfrom(s, buf, BUFLEN, MSG_DONTWAIT, (struct sockaddr *) &si_other, &slen)) != -1){
                if(buf[0]=='y'){
                    int temp=checkRecv(si_other);
                    if(temp==1){
                        if(player1Ready !=1){
                            player1Ready=1;
                            playersReady++;
                            printf("player 1 ready\n");
                        }
                    }
                    else if(temp==2){
                        if(player2Ready !=1){
                            player2Ready=1;
                            playersReady++;
                             printf("player 2 ready\n");
                        }
                    }
                    else if(temp==3){
                        if(player3Ready !=1){
                            player3Ready=1;
                            playersReady++;
                            printf("player 3 ready\n");
                        }
                    }
                    else if(temp==4){
                        if(player4Ready !=1){
                            player4Ready=1;
                            playersReady++;
                            printf("player 4 ready\n");
                        }
                    }
                } 
            }
            
    }
}

void sendLevelOverSignal(){
    char temp[1][5];
    memset(temp,'\0',sizeof(temp));
    temp[0][0]='x';temp[0][1]=finalScp1+'0';temp[0][2]=finalScp2+'0';temp[0][3]=finalScp3+'0';temp[0][4]=finalScp4+'0';
    for(peers=0;peers<4;peers++){
        if (sendto(s, temp, sizeof(temp), 0, (struct sockaddr*)&(peer_list[peers]), sizeof(struct sockaddr_in) ) == -1)
            {
                die("sendto()");
            }
    }
}

void changeState(int user,int first){
    int q;
    if(user==4){
        for(q=0;q<20;q++){
            if(arr[q][0] != 'O') arr[q][0]='.';
        }
        arr[first][0]='|';arr[first+1][0]='|';arr[first+2][0]='|';
    }
    

    else if(user==1){
        for(q=0;q<40;q++){
            if(arr[0][q] != 'O')arr[0][q]='.';
        }
        arr[0][first]='_';arr[0][first+1]='_';arr[0][first+2]='_';arr[0][first+3]='_';arr[0][first+4]='_';
    }
    
    else if(user==2){
        for(q=0;q<20;q++){
            if(arr[q][39] != 'O')arr[q][39]='.';
        }
        arr[first][39]='|';arr[first+1][39]='|';arr[first+2][39]='|';
    }
    

    else if(user==3){
        for(q=0;q<40;q++){
            if(arr[19][q] != 'O')arr[19][q]='.';
        }
        arr[19][first]='_';arr[19][first+1]='_';arr[19][first+2]='_';arr[19][first+3]='_';arr[19][first+4]='_';
    }
    
}

void level1(){
    printf("starting level 1 of the game\n");
    int e,d;
    for(e=0;e<20;e++){
        for(d=0;d<40;d++){
            arr[e][d]='.';
        }
    }

    //scores
    scp1=scp2=scp3=scp4 =5;

    //paddle
    arr[0][3]='_';arr[0][4]='_';arr[0][5]='_';arr[0][6]='_';arr[0][7]='_';
    arr[19][3]='_';arr[19][4]='_';arr[19][5]='_';arr[19][6]='_';arr[19][7]='_';
    arr[3][39]='|';arr[4][39]='|';arr[5][39]='|';
    arr[3][0]='|';arr[4][0]='|';arr[5][0]='|';
    arr[20][0]=scp1+'0';arr[20][1]=scp2+'0';arr[20][2]=scp3+'0';arr[20][3]=scp4+'0';
    int f1=3,f2=3,f3=3,f4=3;

    //ball
    int x1=15,y1=2,direction1=2;
    arr[x1][y1]='O';

    ball_ctr=0;

    while(1)
    {   
        if(scp1==0 || scp2==0 || scp3==0 || scp4==0) break;
        ball_ctr++;
        //send the message to all clients
        if(changes || (ball_ctr==prev_ball+1000000)){
            for(peers=0;peers<4;peers++){
                buf[0]=peers;
                //usleep(120000);
                if(ball_ctr==prev_ball+1000000){
                    prev_ball = ball_ctr;
                    ball(&x1,&y1,&direction1,f1,f2,f3,f4,1);
                    //ball(&x2,&y2,&direction2,f1,f2,f3,f4);
                }
                if (sendto(s, arr, sizeof(arr), 0, (struct sockaddr*)&(peer_list[peers]), sizeof(struct sockaddr_in) ) == -1)
                    {
                        die("sendto()");
                    }
            }
            changes = 0;
        }
         
        //try to receive some data, this is a blocking call
        memset(buf,'\0',BUFLEN);
        if ((recv_len = recvfrom(s, buf, BUFLEN, MSG_DONTWAIT, (struct sockaddr *) &si_other, &slen)) != -1)
        {
            printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
            //change arr based on input received from clients
            int user=buf[0]-'0';
            char action=buf[1];
            printf("Data:user: %d and action:%c\n" ,user,action);
            int firstPos=paddleMove(action,user);
            //printf("first......%d\n",firstPos);
            if(user==1)f1=firstPos;
            else if(user==2) f2=firstPos;
            else if(user==3) f3=firstPos;
            else if(user==4) f4=firstPos;
            changeState(user,firstPos);
            changes = 1;
        }    
    }
    finalScp1+=scp1;finalScp2+=scp2;finalScp3+=scp3;finalScp4+=scp4;
}

void level2(){

    printf("starting level 2 of the game\n");
    int e,d;
    for(e=0;e<20;e++){
        for(d=0;d<40;d++){
            arr[e][d]='.';
        }
    }

    //scores
    scp1=scp2=scp3=scp4 =5;

    //paddle
    arr[0][3]='_';arr[0][4]='_';arr[0][5]='_';arr[0][6]='_';arr[0][7]='_';
    arr[19][3]='_';arr[19][4]='_';arr[19][5]='_';arr[19][6]='_';arr[19][7]='_';
    arr[3][39]='|';arr[4][39]='|';arr[5][39]='|';
    arr[3][0]='|';arr[4][0]='|';arr[5][0]='|';
    arr[20][0]=scp1+'0';arr[20][1]=scp2+'0';arr[20][2]=scp3+'0';arr[20][3]=scp4+'0';
    int f1=3,f2=3,f3=3,f4=3;

    //ball
    int x1=15,y1=2,direction1=2;
    arr[x1][y1]='O';

    ball_ctr=prev_ball=0;

    while(1)
    {   
        if(scp1==0 || scp2==0 || scp3==0 || scp4==0) break;
        ball_ctr++;
        //send the message to all clients
        if(changes || (ball_ctr==prev_ball+650000)){
            for(peers=0;peers<4;peers++){
                buf[0]=peers;
                //usleep(120000);
                if(ball_ctr==prev_ball+650000){
                    prev_ball = ball_ctr;
                    ball(&x1,&y1,&direction1,f1,f2,f3,f4,1);
                    //ball(&x2,&y2,&direction2,f1,f2,f3,f4);
                }
                if (sendto(s, arr, sizeof(arr), 0, (struct sockaddr*)&(peer_list[peers]), sizeof(struct sockaddr_in) ) == -1)
                    {
                        die("sendto()");
                    }
            }
            changes = 0;
        }
         
        //try to receive some data, this is a blocking call
        memset(buf,'\0',BUFLEN);
        if ((recv_len = recvfrom(s, buf, BUFLEN, MSG_DONTWAIT, (struct sockaddr *) &si_other, &slen)) != -1)
        {
            printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
            //change arr based on input received from clients
            int user=buf[0]-'0';
            char action=buf[1];
            printf("Data:user: %d and action:%c\n" ,user,action);
            int firstPos=paddleMove(action,user);
            //printf("first......%d\n",firstPos);
            if(user==1)f1=firstPos;
            else if(user==2) f2=firstPos;
            else if(user==3) f3=firstPos;
            else if(user==4) f4=firstPos;
            changeState(user,firstPos);
            changes = 1;
        }    
    }
    finalScp1+=scp1;finalScp2+=scp2;finalScp3+=scp3;finalScp4+=scp4;
}

void level3(){

    printf("starting level 3 of the game\n");
    int e,d;
    for(e=0;e<20;e++){
        for(d=0;d<40;d++){
            arr[e][d]='.';
        }
    }

    //scores
    scp1=scp2=scp3=scp4 =5;

    //paddle
    arr[0][3]='_';arr[0][4]='_';arr[0][5]='_';arr[0][6]='_';arr[0][7]='_';
    arr[19][3]='_';arr[19][4]='_';arr[19][5]='_';arr[19][6]='_';arr[19][7]='_';
    arr[3][39]='|';arr[4][39]='|';arr[5][39]='|';
    arr[3][0]='|';arr[4][0]='|';arr[5][0]='|';
    arr[20][0]=scp1+'0';arr[20][1]=scp2+'0';arr[20][2]=scp3+'0';arr[20][3]=scp4+'0';
    int f1=3,f2=3,f3=3,f4=3;

    //ball1
    int x1=15,y1=2,direction1=2;
    arr[x1][y1]='O';

    //ball2
    int x2=10,y2=20,direction2=4;//ball 2
    arr[x2][y2]='O';

    ball_ctr=prev_ball=0;

    while(1)
    {   
        if(scp1==0 || scp2==0 || scp3==0 || scp4==0) break;
        ball_ctr++;
        //send the message to all clients
        if(changes || (ball_ctr==prev_ball+1000000)){
            for(peers=0;peers<4;peers++){
                buf[0]=peers;
                //usleep(120000);
                if(ball_ctr==prev_ball+1000000){
                    prev_ball = ball_ctr;
                    ball(&x1,&y1,&direction1,f1,f2,f3,f4,1);
                    ball(&x2,&y2,&direction2,f1,f2,f3,f4,2);
                }
                if (sendto(s, arr, sizeof(arr), 0, (struct sockaddr*)&(peer_list[peers]), sizeof(struct sockaddr_in) ) == -1)
                    {
                        die("sendto()");
                    }
            }
            changes = 0;
        }
         
        //try to receive some data, this is a blocking call
        memset(buf,'\0',BUFLEN);
        if ((recv_len = recvfrom(s, buf, BUFLEN, MSG_DONTWAIT, (struct sockaddr *) &si_other, &slen)) != -1)
        {
            printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
            //change arr based on input received from clients
            int user=buf[0]-'0';
            char action=buf[1];
            printf("Data:user: %d and action:%c\n" ,user,action);
            int firstPos=paddleMove(action,user);
            //printf("first......%d\n",firstPos);
            if(user==1)f1=firstPos;
            else if(user==2) f2=firstPos;
            else if(user==3) f3=firstPos;
            else if(user==4) f4=firstPos;
            changeState(user,firstPos);
            changes = 1;
        }    
    }
    finalScp1+=scp1;finalScp2+=scp2;finalScp3+=scp3;finalScp4+=scp4;
}




int main(void)
{
     
    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //initial handshaking of all players with the server
    printf("waiting for all the players to connect to the server\n");
    
    for(peers=0;peers<4;peers++){
        memset(buf,'\0',BUFLEN);
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
        if(buf[0]=='0'){
            peer_list[qwerty++]=si_other;
            printf("peer %s :%d connected\n",inet_ntoa(si_other.sin_addr),ntohs(si_other.sin_port));
        }    
    }
    printf("all the four players connected to server\n");
    
    for(peers=0;peers<4;peers++){
        memset(buf,'\0',BUFLEN);
        buf[0]=peers;
        if (sendto(s, buf, sizeof(buf), 0, (struct sockaddr*)&(peer_list[peers]), sizeof(struct sockaddr_in) ) == -1)
            {
                die("sendto()");
            }
    }

    
    //for level 1
    waitForPlayers();
    level1();
    printf("level 1 over\n");
    printf("FINAL SCORES AFTER LEVEL 1\n");
    printf("player1:%d   player2:%d   player2:%d   player4:%d \n", finalScp1,finalScp2,finalScp3,finalScp4);
    sendLevelOverSignal();

    //for level 2
    waitForPlayers();
    level2();
    printf("level 2 over\n");
    printf("FINAL SCORES AFTER LEVEL 2\n");
    printf("player1:%d   player2:%d   player2:%d   player4:%d \n", finalScp1,finalScp2,finalScp3,finalScp4);
    sendLevelOverSignal();

    //for level 3
    waitForPlayers();
    level3();
    printf("level 3 over\n");
    printf("FINAL SCORES AFTER LEVEL 3\n");
    printf("player1:%d   player2:%d   player2:%d   player4:%d \n", finalScp1,finalScp2,finalScp3,finalScp4);
    sendLevelOverSignal();
    
    printf("closing the game\n");
    
 
    close(s);
    return 0;
}
