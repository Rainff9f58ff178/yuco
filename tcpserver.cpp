
#include "AsyncScheduler.h"
#include "Scheduler.h"
#include <cstdint>
#include <sys/socket.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <system_error>
#include <unistd.h>
#include<cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<vector>
class EchoServer{
    uint32_t m_port;
    uint32_t m_socket;
    AsyncScheduler& async_scheduler;
    std::vector<uint32_t> m_client_fds;
public:
    EchoServer(AsyncScheduler& scheduler,uint32_t port):async_scheduler(scheduler),m_port(port){

    }
    ~EchoServer(){}

    Task<void> Start(){
        m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        struct sockaddr_in addr;
        memset(&addr, 0 , sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(m_port);
        addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(m_socket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)))
        {
            perror("bind");
            exit(1);
        }
        
        if (listen(m_socket, 5))
        {
            perror("listen");
            exit(1);
        }

        g_scheduler.schedule(Accept());

        
        co_return;
    }

    Task<void> ReadAndWrite(int client_fd){
        char buf[1024];
        while(true){
            auto read_bytes = co_await async_scheduler.async_read(client_fd, buf, 1024);
            if(read_bytes > 1){
                auto write_bytes = co_await async_scheduler.async_write(client_fd,buf,read_bytes);
            }else if (read_bytes == 0){
                //close connection;
                close(client_fd);
                break;
            }else {
                // < 0
            }
        }
        co_return;
    }
    Task<void> Accept(){
        struct sockaddr_in peer_addr;
        memset(&peer_addr,0, sizeof(peer_addr));
        socklen_t addrlen = 0;
        while(true){
            int client_fd = co_await async_scheduler.async_accept(m_socket, reinterpret_cast<struct sockaddr*>(&peer_addr), &addrlen,SOCK_NONBLOCK);
            if(client_fd< 0 ){
                //error .
                close(client_fd);
            }else {
                m_client_fds.push_back(client_fd);
                g_scheduler.schedule(ReadAndWrite(client_fd));
            }
        }
        co_return;
    }   
private:

};
int main(){
    AsyncScheduler async_scheduler(g_scheduler);

    EchoServer server(async_scheduler,8080);
    auto service  = server.Start();

    g_scheduler.schedule(std::move(service));
    g_scheduler.execute();
    return 0;
}