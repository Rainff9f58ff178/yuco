## yuco 
c++ 20 corotinue example 

## example 

```c++
Task<uint64_t> async_read(runtime_state* state,const std::string& file_name,char* buf,uint32_t bytes){
    auto f_fd = open(file_name.c_str(), O_RDONLY);
    if(f_fd == -1) {throw std::runtime_error("no such file");};
    std::cout<<"ready to async_read..."<<std::this_thread::get_id()<<std::endl;
    auto b = co_await state->async_scheduler_->async_read(f_fd, buf, bytes);
    std::cout<<"async_read"<<b<<" size over..."<<std::this_thread::get_id()<<std::endl;
    co_return b;
}

void test_async_read(){
    Scheduler scheduler;
    AsyncScheduler async_scheduler(scheduler);
    char buf[256];
    runtime_state state{&scheduler,&async_scheduler};
    auto task1 = [](runtime_state* state,char* buf)->Task<void>{
        std::cout<<"ready to async_read..."<<std::this_thread::get_id()<<std::endl;
        auto b =co_await async_read(state,"test.log", buf, 256);
        std::cout<<"readed content is :"<<std::string(buf,b)<<std::endl;
        co_return;
    }(&state,buf);

    scheduler.schedule(std::move(task1));
    scheduler.execute();
}
```
Э�̶���Scheduler���ȣ�AsyncSchedulerʹ��iouring�첽readϵͳ���ã���readϵͳ������ɽ���Э�̼���runable���С�

```c++
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
```
����:Echo server


## Note
1.Lambda���ʽ��ΪЭ�̵�ʱ���ܽ��в���Э�̵�һ���˳�������

2.await_suspend����corotinue_handle���resume��Э��
