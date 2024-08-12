#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
    char *ip="127.0.0.1";
    int port =5567;
    int server_sock,client_sock;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t addr_size;
    char buffer[1024];
    int n;
    server_sock=socket(AF_INET,SOCK_STREAM,0);
    if(server_sock<0){
        perror("[-]Socket error\n");
        exit(1);
    }
    printf("[+] TCP server socket created\n");

    memset(&serveraddr,'\0',sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=port;
    serveraddr.sin_addr.s_addr=inet_addr(ip);
    n=bind(server_sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(n<0){
        perror("[-]Bind error\n");
        exit(1);
    }
    printf("[+] TCP SOCKET BOUND to port %d\n",port);
    n=listen(server_sock,1);
    if(n<0){
        perror("listen error\n");exit(1);
    }
    printf("server listening\n");
    addr_size=sizeof(clientaddr);
    client_sock=accept(server_sock,(struct sockaddr*) &clientaddr,&addr_size);
    printf("Client connection ready\n");
    while(1){
    
        bzero(buffer,sizeof(buffer));
        recv(client_sock,buffer,sizeof(buffer),0);
        printf("Client: %s\n",buffer);
        printf("SYSTEM :: Type your message now\n");
        if(fgets(buffer,sizeof buffer,stdin)==NULL){
            perror("fgets\n");
        }
        buffer[strcspn(buffer,"\n")]='\0';
         
        send(client_sock,buffer,strlen(buffer),0);
        if(strcmp(buffer,"exit")==0){break;}

        
        }
    close(server_sock);
    return 0;

}