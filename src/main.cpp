#include <cstdio>
#include <cstdint>
#include <thread>
#include <windows.h>



extern "C"{
    __declspec(dllexport) int y;
    __declspec(dllexport) void *p;
}

int main(){
    int const pid = GetCurrentProcessId();
    printf("pid is %d %x\n", pid, pid);

    y = 1;
    p = nullptr;

    uint32_t counter = 0;

    while(true){
        printf("hello %d\n", counter);
        counter++;
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3000ms);
    }
    
    return 0;
}