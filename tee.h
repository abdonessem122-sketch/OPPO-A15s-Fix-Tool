#include <stdint.h>
typedef uint32_t u32;
typedef uint64_t u64;


static inline uintptr_t HOOK_ADDR(uintptr_t x){ 
    return 0x4000000+x; 
}


typedef struct {
    uint32_t magic;
    uint32_t ver;
    uint32_t flags;
} DownloadArg;

u32 tee_dispatch(u32 cmd,u32 arg1,u32 arg2,u32 arg3);

