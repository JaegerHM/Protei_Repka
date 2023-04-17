#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include "Log.h"

using namespace std;

int main (int argc, int argv[]){

    RUN_ALL_TESTS(); //running tests in ServerTester.cpp

    try{
        int port = 3777; //default port for connecting
        if(argc > 1)    //if port is given from console
            port = argv[0];
        ServerSocket server (port);

        LOG(INFO) << "Server is running";

        while(1){

            ServerSocket new_sock;
            server.accept (new_sock);   //accepting a new connection with client
            LOG(INFO) << "Server received connection";

            try{
                while (1){
                    string request;
                    string response;
                    new_sock >> request;    //receiving a request with command and it's arguments
                    LOG(INFO) << "Server received request";
                    response = server.process_command(request);     //processing received command and creating a response
                    LOG(INFO) << "Server processed received request";
                    new_sock << response;       //sending a response to a client
                    LOG(INFO) << "Server sent reply";
                }
            }catch (SocketException&) {}
        }
    }catch ( SocketException& e ){
        cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    LOG(INFO) << "Server closed";
  return 0;
}
