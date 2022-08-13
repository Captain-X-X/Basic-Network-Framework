#include "net_server.h"

namespace Network
{
    namespace net
    {
        int Server::Init(int port, const char* ip)
        {
            // Create a socket
            listening = socket(AF_INET, SOCK_STREAM, 0);
            if (listening == -1)
            {
                std::cerr << "Can't create a socket! Quitting" << std::endl;
                return -1;
            }
            hint;
            hint.sin_family = AF_INET;
            hint.sin_port = htons(port);
            inet_pton(AF_INET, ip, &hint.sin_addr);
            bind(listening, (sockaddr*)&hint, sizeof(hint));
            // Tell Winsock the socket is for listening
            listen(listening, SOMAXCONN);
            // Wait for a connection
            client;
            clientSize = sizeof(client);
            clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
            host[NI_MAXHOST];      // Client's remote name
            service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
            memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
            memset(service, 0, NI_MAXSERV);
            server_run = true;
            return 0;
        }

        void Server::Recv()
        {
            while(server_run)
            {
                memset(buf, 0, 4096);
                int bytesReceived = recv(clientSocket, buf, 4096, 0);
                if (bytesReceived == 0)
                {
                    std::cout << "Client disconnected " << std::endl;
                }
                std::cout << std::string(buf, 0, bytesReceived) << std::endl;
            }
        }

        void Server::Recv(void(Req_callBack)(std::string msg))
        {
            while(server_run)
            {
                memset(buf, 0, 4096);
                int bytesReceived = recv(clientSocket, buf, 4096, 0);
                if (bytesReceived == 0)
                {
                    std::cout << "[*] Client disconnected" << std::endl;
                }
                else{
                    Req_callBack(buf);
                    /*
                    int sendRes = send(clientSocket, buf, sizeof(buf) + 1, 0);
                    if (sendRes == -1)
                    {
                        std::cout << "[*] Could not send to client! Whoops!\r\n";
                    }
                    */
                }
            }
        }

        int Server::Send(std::string msg)
        {
            int sendRes = send(clientSocket, msg.c_str(), msg.size()+1, 0);
            if (sendRes == -1)
            {
                std::cout << "[*] Could not send to client! Whoops!\r\n";
                return 1;
            }
            return 0;
        }
        
        int Server::ServerIsRunning()
        {
            return server_run;
        }
    }
}