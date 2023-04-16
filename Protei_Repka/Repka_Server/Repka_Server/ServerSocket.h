#include <string>
#include "Socket.h"
#include <map>

class ServerSocket : private Socket
{
 public:
  std::map<std::string, std::string> vault;

  std::string process_command(std::string request);
  ServerSocket ( int port );
  ServerSocket (){};
  virtual ~ServerSocket();

  const ServerSocket& operator << ( const std::string& ) const;
  const ServerSocket& operator >> ( std::string& ) const;

  void accept ( ServerSocket& );

};
