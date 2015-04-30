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
  struct sockaddr_in remote;
//remote.sin_addr.s_addr = inet_addr("10.55.190.203");
  remote.sin_addr.s_addr = inet_addr("127.0.0.1");
  remote.sin_family = PF_INET;
  remote.sin_port = htons(PORT);
  if (connect(h, (const sockaddr *)&remote, sizeof remote) < 0) {
    perror("connect"); close(h); return 2;
  }
  int wr = write(h, "Let's begin", 12);
  printf("Sent %d bytes\n", wr);
  close(h);
}
  
