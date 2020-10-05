#include "Client_main.h"



int main(int argc, char** argv)
{

    Client *myClient;
    switch(argc)
    {
        case 1: myClient=new Client_Tcp();break;
        case 3: myClient=new Client_Tcp(string(argv[1]),stoi(argv[2]));break;
        case 5: myClient=new Client_Udp(string(argv[1]),stoi(argv[2]),string(argv[3]),stoi(argv[4]));break;
        default: cout<<"Incorrect number of params. Input SERVER_IP SERVER_PORT for tcp-client, SERVER_IP SERVER_PORT CLIENT_IP CLIENT_PORT for udp-client or leave it blanc for test mode"<<endl;exit(0);break;
    }




    string input_msg;

    while(1)
    {
        getline(cin,input_msg);


        if(input_msg.compare("q")==0) break;

        myClient->split_input(input_msg);
        if(myClient->msg_part.size()>=254) cout<<"Error. Message too long\n";
        else
        myClient->call_server();

        input_msg.clear();
        cout<<endl;

    }




    return 0;
}
