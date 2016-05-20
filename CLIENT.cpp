//
// Created by Guaberx on 18.05.2016.
//
#include "CLIENT.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

int mainC(){
    //Locals
    long SUCCESFUL;
    WSAData WinSockData;
    WORD  DLLVersion;
    DLLVersion = MAKEWORD(2,1);
    SUCCESFUL = WSAStartup(DLLVersion,&WinSockData);

    string RESPONSE;
    string CONVERTER;
    char MESSAGE[200];

    SOCKADDR_IN ADDRESS;

    SOCKET  sock;
    sock = socket(AF_INET,SOCK_STREAM,0);//NULL or 0

    ADDRESS.sin_addr.s_addr  = inet_addr("127.0.0.1");
    ADDRESS.sin_family = AF_INET;
    ADDRESS.sin_port = htons(444);

    cout << "\n\tClient: Do you want to connect to this SERVER? (Y/N)";
    cin >> RESPONSE;

    RESPONSE[0] = tolower(RESPONSE[0]);

    if(RESPONSE == "n"){
        cout << "\n\tOK. Quitting instead.";
    }else if(RESPONSE == "y"){
        connect(sock,(SOCKADDR*)&ADDRESS, sizeof(ADDRESS));

        SUCCESFUL = recv(sock,MESSAGE, sizeof(MESSAGE),0);//NULL or 0

        CONVERTER = MESSAGE;

        cout << "\n\tMessage from SERVER:\n\n\t" << CONVERTER << endl;

        cout<<"\n\n\t";
        system("PAUSE");
        exit(1);
    }
}
