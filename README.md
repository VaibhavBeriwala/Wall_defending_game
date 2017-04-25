# Wall_defending_game


Compilation and execution:

First you need to run the udp_server.c file.
Compile it in terminal using the following command:
  gcc paddle.c ballMovement.c udp_server.c -o server
After compilaton execute it using the following command:
  ./server
  
After server is up and running you need to run udp_client.c file
Compile it using the following command:
  gcc udp_client.c -o client
After compilation you need to pass the ip address of the server  as an
argument while executing udp_client file. Command for the same will be as follows:
  gcc ./client server_ip_address

About the game:

 Players have to defend their wall from the moving ball. Game consists of 3 different levels. First level consists of a ball moving at a normal pace. Ball moves at a faster pace in the second level. In final level, there are two balls in the game. Players have to defend their ball from both the balls in this level.
At the start of each level, every player is given 5 lives. Whenever ball is able to touch a players wall, his life is reduced by one. A level ends when any player's life reaches to 0. After this a prompt appears for starting the next level and the game continues till the 3rd level ends. After the end of 3rd level, final scores of all the players are displayed and the game ends.
