#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
extern void my_func(int);
#define PAGE_SIZE 4096
#define PAGE_MASK 0xfffff000
#define PAGE_START(addr) ((addr) & PAGE_MASK)
#define PAGE_END(addr)   (PAGE_START(addr) + PAGE_SIZE)

static int si = 10;

void set(){
    si = 20;
}

void my_func_hook(int input){
    printf("my_func_hook: %d\n", input);
}

void hook()
{
    char       line[512];
    FILE      *fp;
    uintptr_t  base_addr = 0;
    uintptr_t  addr;

    //find base address of libtest.so
    if(NULL == (fp = fopen("/proc/self/maps", "r"))) return;
    while(fgets(line, sizeof(line), fp))
    {
        if(NULL != strstr(line, "libmyfunc.so") &&
           sscanf(line, "%"PRIxPTR"-%*lx %*4s 00000000", &base_addr) == 1)
            break;
    }
    fclose(fp);
    if(0 == base_addr) return;

    //the absolute address
    addr = base_addr + 0x201018;
    
    //add write permission
    mprotect((void *)PAGE_START(addr), PAGE_SIZE, PROT_READ | PROT_WRITE);

    //replace the function address
    *(void **)addr = set;

    //clear instruction cache
    __builtin___clear_cache((void *)PAGE_START(addr), (void *)PAGE_END(addr));
}

int main(){
//    hook();
    my_func(1);


    return 0;
}



