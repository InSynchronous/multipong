#pragma once

#include "../shared/Packet.h"
#include "../shared/State.h"

class Client {
  private:
    int socket_fd;

  public:
    Client(const char *hostname, int ip);
    ~Client();

    ServerTelemetry sendClientTelemetry(State user, bool w, bool a, bool s,
                                        bool d, bool blk);
};
