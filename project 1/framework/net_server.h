#include "net_common.h"

namespace Network
{
    namespace net
    {
        class Server
        {
        private:
            int PORT;
            const char* IP;
            bool server_run;
            // SOOK
            int listening;
            int clientSocket;
            char host[NI_MAXHOST];   
            char service[NI_MAXSERV];
            char buf[4096];
            sockaddr_in hint;
            sockaddr_in client;
            socklen_t clientSize;
        public:
            int Init(int port, const char* ip);
            void Recv();
            void Recv(void(Req_callBack)(std::string msg));
            int Send(std::string msg);
            int ServerIsRunning();
        };
    }
}