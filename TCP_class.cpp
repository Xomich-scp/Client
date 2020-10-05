#include "Client_main.h"


void Client_Tcp::call_server()
{



    char buf[MSG_SIZE];
    bzero(buf,MSG_SIZE);
    buf[0]=(char)msg_part.size();
    send(sock,buf,1,0);
  //  cout<<"Send size "<<buf[0]<<" "<<(int)buf[0]<<endl;
    if(recv(sock,buf,MSG_SIZE,0)<=0)
    {
        close(sock);
        cout<<"Connection lost"<<endl;
        exit(0);
    }
 //   cout<<"Reply:\t"<<buf<<endl;

    for(auto it=msg_part.begin();it!=msg_part.end();it++)
    {
        send(sock,it->second.c_str(),it->second.size(),0);
        it->first=true;
        //cout<<it->second<<endl;
    }


    msg_part.clear();




  //  cout<<"wait reply\n";
    bzero(buf,MSG_SIZE);
    recv(sock,buf,MSG_SIZE,0);
    int new_size=(int)buf[0];
 //   cout<<"Reply size "<<new_size<<" "<<buf<<endl;
    msg_part.resize(new_size);
    send(sock,buf,MSG_SIZE,0);


    while(!this->is_recived())
    {
        bzero(buf,MSG_SIZE);
        if (recv(sock,buf,MSG_SIZE,0)<=0)
        {
            close(sock);
            cout<<"Connection lost"<<endl;
            exit(0);
        }
        put_in_msg(string(buf));

    }


    print_result();




}

