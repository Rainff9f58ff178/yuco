

#include<list>
#include<memory>
#include<cstring>
int get_uco_version();

namespace uco{
struct Context{
    void* edi;
    void* esi;
    void* ebx;
    void* ebp;
    void* eip;
};
enum STATE{RUNABLE,SLEEP,RUNNING,DEADED,EMBYO};
class Scheduler;

class u_coroutine{
private:
    char* context;
    char* stray_ptr;
    STATE state_;
public:

    friend Scheduler;
    u_coroutine();
    ~u_coroutine();
};

void swtch(Context** old_context,Context* new_context);

class Scheduler{

private:
    std::list<std::shared_ptr<u_coroutine>> tasks_;
    char* main_context;
    u_coroutine* current_coroutine;
public:
    Scheduler();

    template<typename Func>
    void new_uco(Func&& func){
        std::shared_ptr<u_coroutine> uco_sptr(new u_coroutine());
        tasks_.push_back(uco_sptr);


        //for exit
        uco_sptr->context-=sizeof(void*);
        char* top_rbp = uco_sptr->context;


        uco_sptr->context-=sizeof(void*);
        *((uint64_t*)uco_sptr->context)=(uint64_t)this;

        uco_sptr->context-=sizeof(void*);
        auto member_addr=&Scheduler::exit;
        void* ptr=(void*&)member_addr;;
        *((uint64_t*)uco_sptr->context)=(uint64_t)ptr;



        //for parameters
//        uco_sptr->context-=sizeof...(args);
//        char* begin =(char*) uco_sptr->context;
//        (copy_to(args,&begin),...);
//        //for first parameter:Scheduer Obecjt;
//        uco_sptr->context-=sizeof(void*);
//        *((uint64_t*)uco_sptr->context)=(uint64_t)this;

        //ready for fake context;
        uco_sptr->context-=sizeof(Context);
        ((Context*)(uco_sptr->context))->eip =(void*)func;
        ((Context*)(uco_sptr->context))->ebp=(void*)top_rbp;
        ((Context*)(uco_sptr->context))->ebx=(void*)0;
        ((Context*)(uco_sptr->context))->esi=(void*)0;
        ((Context*)(uco_sptr->context))->edi=(void*)0;
        uco_sptr->state_=STATE::RUNABLE;
    }
    template<typename E>
    void copy_to(E e,char** dest){
        memcpy(*dest,&e,sizeof(e));
        *dest=(*dest)+sizeof(e);
    }




    void sheduler(){
        for(;;){
            for(auto it =tasks_.begin();it!=tasks_.end();++it){

                if(it->get()->state_==DEADED){
                    tasks_.erase(it);
                    break;
                }
                if(it->get()->state_==STATE::RUNABLE){

                    current_coroutine=it->get();
                    current_coroutine->state_=RUNNING;
                    swtch((Context**)&this->main_context,(Context*)current_coroutine->context);

                }
            }
        }
    }
    void yield(){
        if(current_coroutine->state_!=DEADED){
            current_coroutine->state_=STATE::RUNABLE;
        }
        swtch((Context**)&current_coroutine->context,(Context*)this->main_context);
    }
    void exit(){

        /*
         *
         *
         * */
        this->current_coroutine->state_=DEADED;
        yield();
    }


    ~Scheduler();

};
}

