#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>  

using std::string;
using std::ifstream;

#define filename "testWord"
const int BufSize = 100;

void error_handling(string message);

int main(int argc, char *argv[])
{
    //服务端、客户端文件描述符
    int serv_sd, clnt_sd;
    //缓冲区
    char buf[BufSize];
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    //若未指定端口，返回
    if(argc != 2){
        std::cout<<"Please use "<< argv[0] <<" <port>"<<std::endl;
        exit(1);
    }
    //读文件
    ifstream ifstrm(filename,ifstream::in | ifstream::app);
    serv_sd = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sd, (struct sockaddr *)&serv_adr, sizeof(serv_adr))== -1)
        error_handling("bind() error");
    if (listen(serv_sd, 15)== -1)
        error_handling("listen() error");

    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sd = accept(serv_sd, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);

    if (!ifstrm.is_open())
    { 
        std::cout << "Error opening file" << std::endl;
        exit (1); 
    }  

    while (!ifstrm.eof())
    {
        ifstrm.getline(buf, BufSize);
        write(clnt_sd, buf, BufSize);
    }
    //优雅关闭
    shutdown(clnt_sd, SHUT_WR);
    
    read(clnt_sd, buf, BufSize);
    std::cout<<"receive: "<< buf <<std::endl;
    ifstrm.close();
    close(clnt_sd);
    close(serv_sd);
    return 0;    
}

void error_handling(string message){
    std::cerr << message << std::endl;
    exit(1);
}

