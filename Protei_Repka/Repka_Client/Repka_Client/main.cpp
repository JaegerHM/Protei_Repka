#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

using namespace std;

int main (int argc, int argv[]){

    try{

        int port = 3777;
        if(argc > 1)
            port = argv[0];
        ClientSocket client_socket ("localhost", port);

        string reply;
        string request;
        while(1){
            cout << "Type your command:\n";
            string request;
            getline(cin, request);
            client_socket << request;
            client_socket >> reply;
            cout << "We received this response from the server:\n" << reply;
        }
    }catch ( SocketException& e ){
      cout << "Client: Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
