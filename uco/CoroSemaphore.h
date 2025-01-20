#pragma once

/*
    this is user-mode semaphore use in corotine communciate(sync).


    Semaphore sem.
    A coro :    cowait sem object -> co_await sem.accquire() -> {count++}
                cowait sem objcet -> co_await sem.release() -> {count-- }
 */


#include <cassert>
#include <coroutine>
#include<atomic>
#include<list>
#include <mutex>
#include "Scheduler.h"
class CoroSemaphore {

public:
    explicit CoroSemaphore(int init_count = 1):m_count(init_count),m_scheduler(g_scheduler){
    }
    explicit CoroSemaphore(Scheduler& scheduler,int init_count = 1):m_count(init_count),m_scheduler(scheduler){
    }
    ~CoroSemaphore(){}


        
private:
    friend class AccquireOperation;
    friend class ReleaseOperation;
    
    std::atomic<int> m_count;
    std::list<std::coroutine_handle<>> m_wait_list;
    std::mutex m_internal;
    Scheduler& m_scheduler;

private:
    bool TryAccquire(){
        auto count =  m_count.fetch_sub(1,std::memory_order::acq_rel);
        if(count <= 0 ){
            m_count.fetch_add(1,std::memory_order::release);
            return false;
        }
        return true;
    }
    bool Release(){
        std::unique_lock<std::mutex> lock(m_internal);
        if(m_wait_list.size() > 0){
            auto next_handle = m_wait_list.front();
            m_scheduler.add_task(std::move(next_handle));
            m_wait_list.pop_front();
            return true;
        }
        auto count = m_count.fetch_add(1,std::memory_order::relaxed);
        return true;
        
    }
    struct AccquireOperation{
        CoroSemaphore& coro;
    public:

        bool await_ready() noexcept {
            // return true ->resume coro;
            return coro.TryAccquire();
        }
        bool await_suspend(std::coroutine_handle<> handle){
            // Tryaccquire return false;
            {
                std::unique_lock<std::mutex> lock(coro.m_internal);
                if(coro.TryAccquire()){
                    return false;
                }
                coro.m_wait_list.push_back(handle);
                return true;
            }
        }
        void await_resume(){
            //do nothing .   
        }
    };

    struct ReleaseOperation{
        CoroSemaphore& coro;
    public:
        bool await_ready() noexcept{
            coro.Release();
            return true;
        }
        void await_suspend(std::coroutine_handle<> handle){
            
        }
        void await_resume(){
            //do nothing .   
        }
    };

public:
    AccquireOperation accquire(){
        return AccquireOperation{*this};
    }
    ReleaseOperation release(){
        return ReleaseOperation{*this};
    }
};

