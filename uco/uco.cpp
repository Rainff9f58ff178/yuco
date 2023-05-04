




#include"uco.h"


int uco_get_version(){
    return 1;
}



namespace uco {
    void swtch(Context** old_context,Context* new_context){

        //old version has some wrong
//        asm volatile(
//                "pushq %rbx\n\t"
//                "pushq %rsi\n\t"
//                "pushq %rdi\n\t"
//                "movq  %rsp, (%rdi)\n\t"
//                "movq  %rsi, %rsp\n\t"
//                "popq %rdi\n\t"
//                "popq %rsi\n\t"
//                "popq %rbx\n\t"
//                );


//          better version
        __asm__ __volatile__(
                "pushq %%rbx\n\t"
                "pushq %%rsi\n\t"
                "pushq %%rdi\n\t"
                "movq %%rsp, (%0)\n\t"
                "movq %1, %%rsp\n\t"
                "popq %%rdi\n\t"
                "popq %%rsi\n\t"
                "popq %%rbx\n\t"
                :
                : "r" (old_context), "r" (new_context)
                :
                );

    }

        u_coroutine::u_coroutine(){
            // run like this  func(arg...);
            state_=EMBYO;
            stray_ptr = new char[8192];
            context=stray_ptr;
            context+=8192;
        }
        u_coroutine::~u_coroutine(){
            delete[] stray_ptr;
        }


        Scheduler::Scheduler(){


        }
        Scheduler::~Scheduler(){

        }


    }


