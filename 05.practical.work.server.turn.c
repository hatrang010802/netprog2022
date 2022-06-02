#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>

int main(){
    /* vars */
    int sockfd, clen, clientfd;
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
    /*accept*/ 
    clen = sizeof(caddr);
    if ((clientfd = accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error accepting connection\n"); 
        return 1;
    }
    printf("Client is connected.\n");

    char message[1000];
    char response[1000];

    while(1){
        recv(clientfd, message , sizeof(message),0); //from client
        printf("%s", message); //to STDOUT
        printf("Enter a message:");
        fgets(response, sizeof(response),stdin);  //from STDIN
        send(clientfd, response , strlen(response) + 1, 0); //to client
        if (strncmp("exit", response , 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }

    return 0;
}