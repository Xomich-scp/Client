#include "Client_main.h"


void Client:: split_input(string &input)
{

    int total_pack=input.length()/(MSG_SIZE-1)+1;

    msg_part.resize(total_pack);

    for(int i=0; i<total_pack; i++)
    {
        msg_part[i]=make_pair(false,input.substr(i*(MSG_SIZE-1),(MSG_SIZE-1)) + char(i+1));
     //   cout<<">"<<msg_part[i].first<<"<\t"<<msg_part[i].second<<endl;
    }

}

void Client::put_in_msg(string part)
{
   // cout<<"Lol >"<<part<<"<"<<endl;
    int index=(int)part.at(part.length()-1)-1;
   // cout<<"Put: "<<part<<" index "<<index<<endl;
    if(index==254) return;
    part.pop_back();

    if(msg_part.size()<=index) msg_part.resize(index+1);
    if(!msg_part[index].first)
    {
        msg_part[index].first=true;
        msg_part[index].second=part;
        debug=true;
    }
}

bool Client:: is_recived()
{
/*
    if(debug)
    {
        for(auto it=msg_part.begin(); it!=msg_part.end(); it++)
        {
            cout<<it->second<<"\t"<<it->first<<endl;
        }
        debug=false;

    }
    */

    for(auto it=msg_part.begin(); it!=msg_part.end(); it++)
    {
        if(!it->first) return false;
    }
    return true;
}
void Client:: print_result()
{
    for(auto it=msg_part.begin();it!=msg_part.end();it++) cout<<it->second;
    //cout<<"\nPrinted"<<endl;
}
