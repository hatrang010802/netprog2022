#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

struct hostent *host_info;
struct in_addr *address;
int main(int argc, char *argv[]){
    char name[100];
    if (argc > 1){
        strcpy(name, argv[1]);
    }
    else{
        printf("Enter a name: ");
        scanf("%s", name);
    }
    host_info = gethostbyname(name);

    if (host_info == NULL){
        printf("Cannot find address for hostname: %s\n", name);
        return 0;
    }
    printf("Hostname: %s\n", name); 
    int i=0;
    while(1){
        if (host_info->h_addr_list[i]==NULL){
            break;
        }
        else{
            address = (struct in_addr *)(host_info->h_addr_list[i]);
            printf("%s has address %s\n",name, inet_ntoa(*address)); 
        }
        i++;
    }
}