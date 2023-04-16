#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

using namespace std;

int main ( int argc, int argv[] )
{
  try
    {

      ClientSocket client_socket ("localhost", 3777);

      std::string reply;
      std::string request;
      while(1)
      {
        std::cout << "Type your command:\n";
        string request;

        getline(cin, request);

        std::cout << request << endl;

        client_socket << request;

        client_socket >> reply;

        std::cout << "We received this response from the server:\n" << reply;
      }
    }
  catch ( SocketException& e ){
      std::cout << "Client: Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
