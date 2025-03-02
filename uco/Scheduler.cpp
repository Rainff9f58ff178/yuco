#include "Scheduler.h"
#include<chrono>
#include <list>
#include <vector>

void Scheduler::execute(uint32_t thread_num){
    for(uint32_t i=0;i<thread_num;++i){
        working_thread_.emplace_back(std::thread([&,this](){
            while(true){
                std::unique_lock<std::mutex> l(internal_mtx_);

                cv_.wait(l,[&,this](){
                    return tasks_.size() != 0;
                });

                auto co = tasks_.front();
                tasks_.pop_front();
                l.unlock();
                co.resume();
            }
        }));
    }
    // main thread garbage collect 
    std::condition_variable _cv;
    while(true){
        std::unique_lock<std::mutex> lock(internal_mtx_);
        std::vector<std::list<Task<void>>::iterator> need_deleted;
        for(auto it = _t_s_.begin();it!=_t_s_.end();++it){
            if(it->handle_.done())
                need_deleted.push_back(it);
        }
        for(auto& it:need_deleted){
            _t_s_.erase(it);
        }
        _cv.wait_for(lock,std::chrono::seconds(100));
    }

}

void Scheduler::schedule( Task<void>&& job){
    std::unique_lock<std::mutex> lock(internal_mtx_);
    tasks_.push_back(job.handle_);
    _t_s_.push_back(std::move(job));
    cv_.notify_one();
}

void Scheduler::
add_task(std::list<std::coroutine_handle<>>&& tasks){
    if(tasks.empty())   return;
    std::unique_lock<std::mutex> lock(internal_mtx_);
    tasks_.splice(tasks_.end(),std::move(tasks));
    cv_.notify_all();
}

template<>
void Scheduler::sync_wait<void>(Task<void> &&task){
    task.handle_.resume();
    while(!task.handle_.done()){
        std::unique_lock<std::mutex> lock(internal_mtx_);
        if(!tasks_.empty()){
            auto n_t = tasks_.front();
            tasks_.pop_front();
            lock.unlock();
            n_t.resume();
        }
    }
}



Scheduler g_scheduler;





