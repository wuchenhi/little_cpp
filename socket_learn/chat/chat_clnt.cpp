#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <iostream>

using std::string;
using std::ofstream;

const int BUF_SIZE=100;
const int NAME_SIZE=30;

void error_handling(string message);
void *send_msg(void *arg);
void *recv_msg(void *arg);
void send_msg(char *msg, int len);

char name[NAME_SIZE] = "nobody:";
char msg[BUF_SIZE];

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    pthread_t snd_thread, rcv_thread;
    void *thread_return;
    if (argc != 4)
    {
        std::cout<<"Please use "<< argv[0] <<" <IP> <port> <name>"<<std::endl;
        exit(1);
    }

    sprintf(name, "%s:", argv[3]);
    //std::cout<< argv[3] << ": ";
    sock = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    pthread_create(&snd_thread, NULL, send_msg, (void *)&sock); //创建发送消息线程
    pthread_create(&rcv_thread, NULL, recv_msg, (void *)&sock); //创建接受消息线程
    pthread_join(snd_thread, &thread_return);
    pthread_join(rcv_thread, &thread_return);
    close(sock);
    return 0;
}

void *send_msg(void *arg) // 发送消息
{
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    while (1)
    {
        std::cin >> msg;
        //TODO
        if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
        {
            close(sock);
            exit(0);
        }
        sprintf(name_msg, "%s %s", name, msg);
        write(sock, name_msg, strlen(name_msg));
    }
    return NULL;
}

void *recv_msg(void *arg) // 读取消息
{
    int sock = *((int *)arg);
    char name_msg[NAME_SIZE + BUF_SIZE];
    int str_len;
    while (1)
    {
        str_len = read(sock, name_msg, NAME_SIZE + BUF_SIZE - 1);
        if (str_len == -1)
            return (void *)-1;
        name_msg[str_len] = 0;
        std::cout << name_msg <<std::endl;
    }
    return NULL;
}

void error_handling(string message){
    std::cerr << message << std::endl;
    exit(1);
}