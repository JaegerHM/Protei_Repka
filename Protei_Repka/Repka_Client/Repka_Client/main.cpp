#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include "Log.h"


using namespace std;


int main (int argc, int argv[]){

    LOG(INFO) << "Programm started";

    try{

        int port = 3777;
        if(argc > 1)
            port = argv[0];
        ClientSocket client_socket ("localhost", port); //connecting to Server

        LOG(INFO) << "Server connected";
        string reply;
        string request;
        while(1){
            string request;
            getline(cin, request);

            client_socket << request;
            LOG(INFO) << "Request sent";
            client_socket >> reply;
            LOG(INFO) << "Reply received";
            cout << reply;

        }
    }catch ( SocketException& e ){
      cout << "Client: Exception was caught:" << e.description() << "\n";
    }
    LOG(INFO) << "Program finished";
  return 0;
}
