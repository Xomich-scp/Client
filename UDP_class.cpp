#include "Client_main.h"


string Client_Udp::rely_send(string data)
{
    sendto(sock,data.c_str(),MSG_SIZE,MSG_CONFIRM,
                            (struct sockaddr *)&dest->addr, sizeof(dest->addr));
    char buf[MSG_SIZE];
    while(1)
    {
        fd_set readset;
        FD_ZERO(&readset);
        FD_SET(sock, &readset);
                // Задаём таймаут
        timeval timeout;
        timeout.tv_sec = 600;
        timeout.tv_usec = 0;
        bzero(buf,MSG_SIZE);
        if(select(sock+1, &readset, NULL, NULL, &timeout) <= 0)
        {
            perror("select");
            exit(3);
        }
        if(FD_ISSET(sock, &readset))
        {
            recvfrom(sock,buf,MSG_SIZE,0,NULL,NULL);
            return string(buf);
        }
        else
        {
            sendto(sock,data.c_str(),MSG_SIZE,MSG_CONFIRM,
                            (struct sockaddr *)&dest->addr, sizeof(dest->addr));
        }
    }
}



void Client_Udp::call_server()
{

    int total_send=0;


    char buf[MSG_SIZE];
    bzero(buf,MSG_SIZE);


    buf[0]=(char)msg_part.size();
    buf[1]=(char)255;

    rely_send(string(buf));



    int i=0;
    for(auto it=msg_part.begin();it!=msg_part.end();it++,i++)
    {
        //cout<<endl<<i<<" >"<<it->second<<"<\n";
        rely_send(it->second);

    }
    bzero(buf,MSG_SIZE);

    msg_part.clear();
    msg_part.resize((int)rely_send(string (buf) ).at(0));
    //cout<<"Reply size "<<msg_part.size()<<endl;
    bzero(buf,MSG_SIZE);
    buf[0]=-1;
    buf[1]=-1;
    rely_send(string(buf));
    i=0;
    while(!this->is_recived())
    {
        bzero(buf,MSG_SIZE);
        buf[0]=i+1;
        put_in_msg(rely_send(string(buf)));
        i++;

    }
    //cout<<"FIN"<<endl;
    print_result();
    buf[0]=-1;
    buf[1]=-1;
    rely_send(string(buf));


}

