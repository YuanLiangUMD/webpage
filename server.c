#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;
int 
main()
{
   int	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   struct sockaddr_in servaddr, cliaddr;

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(80);
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

   bind(listenfd, (SA*) &servaddr, sizeof(servaddr));

   listen(listenfd, 0);

   for (;;) {
      socklen_t len = sizeof(cliaddr);
      int connfd = accept(listenfd,(SA *) &cliaddr, &len);

      printf("connection begins \n");

     const char * s = " <html><h1> Hello, welcome to Yuan Liang's webpage</h1>"
                        "<p>My email is yliang12@terpmail.umd.edu and I will use it before graduate </p>"
                        "<p>I have projects with C/C++ and will publish most of source codes</p>"
                        "</html>";

      write(connfd, s, strlen(s));
      close(connfd);
   }
   return 0;
}
