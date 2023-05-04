
#include<iostream>
#include"uco.h"
using namespace std;

using namespace uco;
Scheduler scheduler;
void A(){
    int i=0;
       while(1){
           if(i==3)
               break;
           i++;
           ::printf("hello Im a\n");
           sleep(1);
           scheduler.yield();
       }

        scheduler.exit();
}
void B(){
    while(1){
        ::printf("hello Im b coroutine\n");
        sleep(1);
        scheduler.yield();
    }
}

int main(){

    using namespace uco;

    scheduler.new_uco(A);
    scheduler.new_uco(B);


    scheduler.sheduler();
    return 0;
}
