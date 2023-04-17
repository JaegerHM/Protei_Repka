#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include "Log.h"

using namespace std;

int main (int argc, int argv[]){

    RUN_ALL_TESTS();

    try{
        int port = 3777;
        if(argc > 1)
            port = argv[0];
        ServerSocket server (port);

        LOG(INFO) << "Server is running";

        while(1){

            ServerSocket new_sock;
            server.accept (new_sock);
            LOG(INFO) << "Server received connection";

            try{
                while (1){
                    string request;
                    string response;
                    new_sock >> request;
                    LOG(INFO) << "Server received request";
                    response = server.process_command(request);
                    LOG(INFO) << "Server processed received request";
                    new_sock << response;
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
