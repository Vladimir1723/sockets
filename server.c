#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)	{
	int master_socket = socket(PF_INET, 
							   SOCK_STREAM, 
							   IPPROTO_TCP);

	struct sockaddr_in sock_addr;
	sock_addr.sin_family = PF_INET;
	sock_addr.sin_port = htons(12345);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(master_socket, (struct sockaddr*)(&sock_addr),
		 sizeof(sock_addr));

	listen(master_socket, SOMAXCONN);
		
	while(1)	{

		int slave_socket = accept(master_socket, 0, 0);
		
		int recv_buffer[256] = {[0] = 0};
	   	recv(slave_socket, recv_buffer, 256, MSG_NOSIGNAL);
		printf("%s\n", recv_buffer);
	  	
		send(slave_socket, recv_buffer, strlen(recv_buffer),
			 MSG_NOSIGNAL);
		
		shutdown(slave_socket, SHUT_RDWR);
		close(slave_socket);
	}
	
	return 0;
}
