#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>

using namespace std;

int main (int argc, int argv[]){

    cout << "Server is running....\n";

    try{
        int port = 3777;
        if(argc > 1)
            port = argv[0];
        ServerSocket server (port);

        while(1){

            ServerSocket new_sock;
            server.accept (new_sock);

            try{
                while (1){
                    string request;
                    string response;
                    new_sock >> request;
                    response = server.process_command(request);
                    new_sock << response;
                }
            }catch (SocketException&) {}
        }
    }catch ( SocketException& e ){
        cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

  return 0;
}
