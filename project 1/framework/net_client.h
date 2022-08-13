#include "net_common.h"

namespace Network
{
    namespace net
    {
        class Client
        {
        private:
            // SOOK
            int sock;
            int connectRes;
            sockaddr_in hint;
            char buf[4096];
            std::string userInput;
            void Recv();
        public:
            int Init(int port, const char* ip);
            int Send();
            int Send(const char* msg);
            int Connect(const char* ip, int port);
            void Ping();
            void Exit();
        };
    }
}