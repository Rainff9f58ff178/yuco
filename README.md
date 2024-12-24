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
协程对象被Scheduler调度，AsyncScheduler使用iouring异步read系统调用，当read系统调用完成将此协程加入runable队列。



## Note
1.Lambda表达式作为协程的时候不能进行捕获，协程第一次退出后析构

2.await_suspend返回corotinue_handle后会resume此协程
