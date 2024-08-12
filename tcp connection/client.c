#include <stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include <string.h>

int main(){
    char *ip="127.0.0.1";
    int port=5567;

    int sock;
    int server;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;
    sock=socket(AF_INET,SOCK_STREAM,0);      //this creates a tcp socket 
    if(sock<0){
        printf("[-]sockerror\n");
        exit(1);
    }
    printf("[+] Client TCP created\n");

    memset(&addr,'\0',sizeof(addr));
    addr.sin_family=AF_INET;  //AF_INET means ipv4 address type
    addr.sin_port=port;
    addr.sin_addr.s_addr=inet_addr(ip); //no need to bind in client


    connect(sock,(struct sockaddr*)&addr,sizeof(addr));
    printf("connected to the server\n");
    while(1){
    bzero(buffer,sizeof buffer);
     printf("SYSTEM :: Type your message now\n");
    if(fgets(buffer,sizeof buffer,stdin)==NULL){
        perror("fgets error\n");}
    buffer[strcspn(buffer,"\n")]='\0';
   
    send(sock,buffer,strlen(buffer),0);
    if(strcmp(buffer,"exit")==0)break;
    bzero(buffer,sizeof buffer);
    recv(sock,buffer,sizeof buffer,0);
    printf("Server: %s\n",buffer);
    }
    close(sock);
    return 0;
}