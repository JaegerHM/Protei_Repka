#include <string>
#include "Socket.h"

class ClientSocket : public Socket
{
 public:

  ClientSocket (std::string host, int port);
  virtual ~ClientSocket(){};

  const ClientSocket& operator << (const std::string&) const;
  const ClientSocket& operator >> (std::string&) const;

};
