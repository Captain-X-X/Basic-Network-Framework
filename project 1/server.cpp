#include "framework/net.h"
Network::net::Server server;

bool server_output = false;
void request_handle(std::string msg)
{
    if (msg == "ping")
    {                                  
        server.Send("PONG");
    }

    if (server_output)
        std::cout << "[*] SMsg:" << msg << std::endl;
}
int main()
{
    server.Init(8080, "0.0.0.0");
    server.Recv(request_handle);
    return 0;
}