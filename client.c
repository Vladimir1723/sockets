#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)	{
	int slave_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in sock_addr;
	sock_addr.sin_family = PF_INET;
	sock_addr.sin_port = htons(12345);
	sock_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

   	connect(slave_socket, (struct sockaddr*)(&sock_addr), sizeof(sock_addr));

	char *send_buffer = "PING";
	send(slave_socket, send_buffer, strlen(send_buffer), MSG_NOSIGNAL);

	int recv_buffer[256] = {[0] = 0};
	recv(slave_socket, recv_buffer, 256, MSG_NOSIGNAL);
	
	printf("%s\n", recv_buffer);

	shutdown(slave_socket, SHUT_RDWR);
	close(slave_socket);
		
	return 0;
}
