#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

int main(int argc, char *argv[]){
    setbuf(stdout, NULL);

    struct sockaddr_in saddr;
    struct hostent *h;
    struct in_addr *address;
    int sockfd;
    unsigned short port = 8784;

    struct pollfd pollfd;
    pollfd.fd = fileno(stdin); /* file descriptor */
    pollfd.events = POLLIN;   /* events to look for */

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
        fflush(stdin);
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

    setsockopt(sockfd, SOL_SOCKET,SO_REUSEADDR, &(int){ 1 },sizeof(int));//reuse address

    /* Enable nonblocking */
    int sockfl = fcntl(sockfd, F_GETFL , 0);
    sockfl |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, sockfl);

    char message[1000];
    char response[1000];
    char str[1000];

    printf("C: ");
    fflush(stdout);
    while(1){
        if(recv(sockfd, response, sizeof(response), 0)>0){
            int i=0;
            do {
                str[i]= response[i];
            } while (response[i++] != '\0');
            printf("\rServer: ");
            printf("%s", str); // to STDOUT
            printf("C: "); 
        } 

        if (poll(&pollfd,1,0) > 0){
            if (pollfd.revents &POLLIN){
                fgets(message,sizeof(message),stdin); // from STDIN
                if ((strncmp(message , "/quit\n", 6)) == 0) {
                    printf("Server is disconnected.\n");
                    return 0;
                }
                send(sockfd , message , strlen(message) + 1, 0); //to server  
                printf("C: "); 
            }
        }
    }
    close(sockfd);
    return 0;
}