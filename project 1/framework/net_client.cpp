#include "net_client.h"

namespace Network
{
    namespace net
    {
        void Client::Recv()
        {
            memset(buf, 0, 4096);
            int bytesReceived = recv(sock, buf, 4096, 0);
            if (bytesReceived == -1)
            {
                std::cout << "[*] There was an error getting response from server\r\n";
            }
            else
            {
                //		Display response
                std::cout << "[*] Server>>" << std::string(buf, bytesReceived) << "\r\n";
            }
        }

        int Client::Init(int port, const char* ip)
        {
            //	Create a socket
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock == -1)
            {
                return 1;
            }
            std::string ipAddress = ip;
            hint.sin_family = AF_INET;
            hint.sin_port = htons(port);
            inet_pton(AF_INET, ip, &hint.sin_addr);
            int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
            if (connectRes == -1)
            {
                return 1;
            }
            return 0;
        }

        int Client::Send()
        {
            do {
                //		Enter lines of text
                std::cout << "[*] Client>>";
                std::getline(std::cin, userInput);
                //std::cin >> userInput;

                //		Send to server
                int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
                if (sendRes == -1)
                {
                    std::cout << "[*] Could not send to server! Whoops!\r\n";
                }
                Recv();
            } while(true);
            return 0;
        }

        int Client::Send(const char* msg)
        {
            int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
            if (sendRes == -1)
            {
                std::cout << "[*] Could not send to server! Whoops!\r\n";
            }
            Recv();
            return 0;
        }

        int Client::Connect(const char* ip, int port)
        {
            connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
            if (connectRes == -1)
            {
                return 1;
            }
            return 0;
        }

        void Client::Ping()
        {

        }

        void Client::Exit()
        {
            close(sock);
        }
    }
}