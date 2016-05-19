//
// Created by Guaberx on 18.05.2016.
//

#include <winsock.h>
#include "SERVER.h"
using std::cout;
using  std::endl;

int mainS(){
    //main Locals
    long SUCCESSFUL;
    WSAData WinSockData;
    WORD DLLVERSION;

    //WORDS
    DLLVERSION = MAKEWORD(2,1);

    //Start Winsock DLL
    SUCCESSFUL = WSAStartup(DLLVERSION, &WinSockData);

    //Create Socket Structure
    SOCKADDR_IN ADDRESS;
    int AdressSize = sizeof(ADDRESS);

    //Create Sockets
    SOCKET sock_LISTEN;//Listen forn incoming connection
    SOCKET sock_CONNECTION;//Activate if connection found

    //socket Arguments: AF_INET = internet domain(not unix domain);
    //SOCK_STREAM = connection oriented TCP(not SOCK_DGRAM);
    sock_CONNECTION = socket(AF_INET,SOCK_STREAM,0);//NULL en vez del ultimo 0
    ADDRESS.sin_addr.s_addr = inet_addr("127.0.0.1");//Ser IP
    ADDRESS.sin_family = AF_INET;
    ADDRESS.sin_port = htons(444);//port

    sock_LISTEN = socket(AF_INET,SOCK_STREAM,0);//NULL en vez del ultimo 0
    bind(sock_LISTEN,(SOCKADDR*)&ADDRESS, sizeof(ADDRESS));
    listen(sock_LISTEN,SOMAXCONN);//listen without limits
    //SOMAXCONN handles the maximun of connections

    //If connection found
    for(;;){
        cout<<"\n\tSERVER: Waiting for incoming connection...";

        if(sock_CONNECTION = accept(sock_LISTEN,(SOCKADDR*)&ADDRESS,&AdressSize)){
            cout<< "\n\tA connection was found!" << endl;

            //We send a message to the client :)
            SUCCESSFUL = send(sock_CONNECTION,"Welcome! you have connected to bannana server!",46, 0);//NULL en vez del ultimo 0
        }
    }
}
