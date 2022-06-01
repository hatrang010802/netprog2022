#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<netdb.h>

int main(int argc, char *argv[]){
    struct sockaddr_in saddr;
    struct hostent *h;
    struct in_addr *address;
    int sockfd;
    unsigned short port = 8784;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Error creating socket\n");
        return 1;
    }
    char name[255];
    if (argc > 1){
        strcpy(name, argv[1]);
    }
    else{
        printf("Enter a name: ");
        scanf("%s", name);
    }
    h = gethostbyname(name);

    if (h == NULL){
        printf("Unknown host !!!\n");
        return 0;
    }
    printf("Hostname: %s\n", name); 
    int i=0;
    while(1){
        if (h->h_addr_list[i]==NULL){
            break;
        }
        else{
            address = (struct in_addr *)(h->h_addr_list[i]);
            printf("%s has address %s\n",name, inet_ntoa(*address)); 
        }
        i++;
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;//ipv4
    memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    saddr.sin_port = htons(port);
    
    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0){
        printf("Cannot connect\n");
        return 1;
    }
    printf("Successfully connected to Server.\n");

    char message[255];
    char response[255];
    while(1){
        printf("Enter a message: ");
        scanf("%s", message); // from STDIN
        send(sockfd , message , sizeof(message), 0); //to server
        recv(sockfd, response , sizeof(response), 0); //from server
        printf("%s\n", response); // to STDOUT
        if ((strncmp(response , "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
    return 0;
}