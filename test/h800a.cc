#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
  int h = socket(PF_INET, SOCK_STREAM, 0);
  if (h < 0) {
    perror("creating socket");
  }
  const int PORT = 5678;
  struct sockaddr_in local;
  // inet_aton(
  local.sin_family = PF_INET;
  local.sin_port = htons(PORT);
  if (bind(h, (sockaddr *)&local, sizeof local) < 0) {
    perror("bind");
	close(h);
	return 1;
  }
  if (listen(h, 10) < 0) {
    perror("listen"); close(h); return 2;
  }
  for (;;) {
    int connect_socket;
	struct sockaddr_in remote;
	unsigned remoteLen = sizeof remote;
	connect_socket = accept(h, (sockaddr *)&remote, &remoteLen);
	printf("Accepted!\n");
	char buf[512];
	int rd = read(connect_socket, buf, sizeof buf);
	printf("read %d bytes '%s'\n", rd, buf);
	close(connect_socket);
	if (buf[0] == 'B') {
	  printf("Bye!\n");
	  break;
	}
  }
  close(h);
}
  
