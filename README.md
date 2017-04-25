# Wall_defending_game

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

