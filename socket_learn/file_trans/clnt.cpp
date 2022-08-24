#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>  

using std::string;
using std::ofstream;

#define filename "getWord"
const int BufSize = 100;

void error_handling(string message);

int main(int argc, char *argv[])
{
    //描述符
    int sd;
    //缓冲区
    char buf[BufSize];
    struct sockaddr_in serv_adr;
    //若未指定ip/端口，返回
    if (argc != 3)
    {
        std::cout<<"Please use "<< argv[0] <<" <IP> <port>"<<std::endl;
        exit(1);
    }
    //写文件
    ofstream ofstrm(filename, ofstream::out | ofstream::app);
    sd = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));
    
    if (connect(sd, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error");

    while (read(sd, buf, BufSize)) 
        ofstrm << buf <<std::endl;

    std::cout<< "Received file data" <<std::endl;
    write(sd, "Thank you", 10);
    ofstrm.close();
    close(sd);
    return 0;
}

void error_handling(string message){
    std::cerr << message << std::endl;
    exit(1);
}