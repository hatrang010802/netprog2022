#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

int main(){
    setbuf(stdout, NULL);

    /* vars */
    int sockfd, clientfd;
    socklen_t clen;
    struct sockaddr_in saddr, caddr;//server addr, client addr 
    unsigned short port = 8784;

    struct pollfd pollfd;
    pollfd.fd = fileno(stdin); /* file descriptor */
    pollfd.events = POLLIN;   /* events to look for */
    

    /* create socket */
    //AF_INET -> ipv4
    //SOCK_STREAM -> TCP
    if ((sockfd =  socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        return 1;
    }

    setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &(int){ 1 },sizeof(int));//reuse address

    /* Enable nonblocking */
    int sockfl = fcntl(sockfd, F_GETFL , 0);
    sockfl |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, sockfl);

    /* set up address */
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    /* bind */
    if (bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0){
        printf("Error binding\n");  
        return 1;
    }
    /* listen */
    if (listen(sockfd, 5) < 0){
        printf("Error listening\n");  
        return 1;
    }
    while(1){
        /*accept*/ 
        clen = sizeof(caddr);
        clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen);
        if (clientfd > 0) {

            printf("Client is connected.\n");

            /* Nonblocking client */
            int clientfl = fcntl(clientfd, F_GETFL, 0);
            clientfl |= O_NONBLOCK;
            fcntl(clientfd, F_SETFL, clientfl);

            char message[1000];
            char response[1000];
            char str[1000];

            printf("S: ");
            fflush(stdout);

            while(1){
                if(recv(clientfd, message , sizeof(message),0)> 0){ //from client
                    int i=0;
                    do {
                        str[i]= message[i]; 
                    } while(str[i++] != '\0');
                    printf("\rClient: ");
                    printf("%s", str); //to STDOUT 
                    printf("S: "); 
                } 

                if (poll(&pollfd,1,0) > 0){
                    if (pollfd.revents &POLLIN){
                        fgets(response, sizeof(response),stdin);  //from STDIN
                        if (strncmp("/dc\n", response , 4) == 0) {
                            printf("Client is disconnected.\n");
                            return 0;
                        }
                        send(clientfd, response , strlen(response) + 1, 0); //to client
                        printf("S: ");
                    }
                }
            }
            close(clientfd);
        }
    }
    close(sockfd);
    return 0;
}