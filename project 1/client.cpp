#include "framework/net.h"

int main()
{
    Network::net::Client client;
    client.Init(8080, "127.0.0.1");
    client.Send();
    return 0;
}