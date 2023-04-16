#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>

using namespace std;

int main ( int argc, int argv[] )
{
  std::cout << "Server is running....\n";

  try
    {
        ServerSocket server ( 3777 );
        while ( true )
        {
            ServerSocket new_sock;
            server.accept ( new_sock );

            try
            {
                while (1)
                {
                    std::string request;
                    std::string response;
                    new_sock >> request;

                    response = server.process_command(request);

                    new_sock << response;
                }
            }catch ( SocketException& ) {}
        }
    }catch ( SocketException& e ){
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

  return 0;
}
