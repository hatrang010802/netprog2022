#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>
#include <unistd.h>

int main(){
    /* vars */
    int sockfd, clientfd;
    socklen_t clen;
    struct sockaddr_in saddr, caddr;//server addr, client addr 
    unsigned short port = 8784;

    /* create socket */
    //AF_INET -> ipv4
    //SOCK_STREAM -> TCP
    if ((sockfd =  socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error creating socket\n");
        return 1;
    }

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
        if ((clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
            printf("Error accepting connection\n"); 
            return 1;
        }
        printf("Client is connected.\n");

        char message[1000];
        char response[1000];
        char str[1000];

        while(1){

            recv(clientfd, message , sizeof(message),0); //from client
            int i=0;
            do {
                str[i]= message[i]; 
            } while(str[i++] != '\0');

            printf("%s\n", str); //to STDOUT 

            printf("Enter a message:");
            fgets(response, sizeof(response),stdin);  //from STDIN
            if (strncmp("/dc\n", response , 4) == 0) {
                printf("Client is disconnected.\n");
                return 0;
            }
            send(clientfd, response , strlen(response) + 1, 0); //to client
        }
        close(clientfd);
    }
    close(sockfd);
    return 0;
}