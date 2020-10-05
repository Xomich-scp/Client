#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <set>
#include <arpa/inet.h>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <string>
#include <iostream>
#include <set>
#include <list>
#include <unordered_map>
#include <sstream>
#include <cstring>
#include <vector>
using namespace std;

#define MSG_SIZE 2

class Server
{
    public:

    struct sockaddr_in addr;
    Server(int port)
    {
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        inet_aton("127.0.0.2", &addr.sin_addr);
    }
    Server(string ip, int port)
    {
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        inet_aton(ip.c_str(), &addr.sin_addr);
    }


};


class Client
{
    public:
    void split_input(string &input);

    Server *dest;
    int sock;
    vector<pair<bool,string>> msg_part;
    char* size_send();
    bool is_recived();

    bool debug;
    void put_in_msg(string part );
    void print_result();
    virtual void call_server() = 0;

};




class Client_Udp: public Client
{
    public:
    struct sockaddr_in addr;
    virtual void call_server();
    string rely_send(string data);
    Client_Udp()
    {
        dest = new Server(4000);
        addr.sin_family=AF_INET;
        addr.sin_port=htons(4000);
        inet_aton("127.0.0.3", &addr.sin_addr);

        init_sock();

    }
    Client_Udp(string server_ip, int server_port, string client_ip, int client_port)
    {
        dest = new Server(server_ip,server_port);
        addr.sin_family=AF_INET;
        addr.sin_port=htons(client_port);
        inet_aton(client_ip.c_str(), &addr.sin_addr);

        init_sock();


    }
    ~Client_Udp()
    {
        char buf[1]={-2};
        rely_send(string(buf));
    }


    private:
    void init_sock()
    {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if(sock < 0)
        {
            perror("socket");
            exit(1);
        }

        if( bind(sock,(struct sockaddr *)&addr,sizeof(addr)) < 0)
        {
            perror("bind");
            exit(2);
        }
        fcntl(sock, F_SETFL, O_NONBLOCK);
        printf("Client info\nIP:%s\nPort:%d\n\n",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
        printf("Server info\nIP:%s\nPort:%d\n\nReady to go. Print q for exit\n",inet_ntoa(dest->addr.sin_addr) ,ntohs(dest->addr.sin_port));
    }

};




class Client_Tcp: public Client
{
public:
    virtual void call_server();
    Client_Tcp()
    {
        dest = new Server(3000);
        init_sock();
    }

    Client_Tcp(string server_ip, int server_port)
    {
        dest = new Server(server_ip,server_port);
        init_sock();
    }
    ~Client_Tcp()
    {
        close(sock);
    }
private:
    void init_sock()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0)
        {
            perror("socket");
            exit(1);
        }
        if(connect(sock, (struct sockaddr *)&dest->addr, sizeof(dest->addr)) < 0)
        {
            perror("connect");
            exit(2);
        }
        printf("Server info\nIP:%s\nPort:%d\n\nReady to go. Print q for exit\n",inet_ntoa(dest->addr.sin_addr) ,ntohs(dest->addr.sin_port));
    }
};
