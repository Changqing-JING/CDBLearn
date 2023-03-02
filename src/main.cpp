#include <cstdio>
#include <thread>
#include <windows.h>

int main(){
    int const pid = GetCurrentProcessId();
    printf("pid is %d %x\n", pid, pid);
    while(true){
        printf("hello\n");
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3000ms);
    }
    
    return 0;
}