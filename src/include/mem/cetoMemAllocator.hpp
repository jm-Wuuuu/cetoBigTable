#ifndef CETO_MEM_MONITOR_HPP
#define CETO_MEM_MONITOR_HPP
#include "ceto.hpp"
namespace ceto
{

    class MemAllocator: public CetoObject
    {
    public:
        explicit MemAllocator(): _allocSize(0){ }
        MemAllocator(const MemAllocator& other) = delete;
        MemAllocator& operator =(const MemAllocator& other) = delete;
        CHAR* alloc(UINT32 byte);
        void release(void* buffer);
    private:
        INT32 _allocSize;
    };

/*    inline MemAllocator& getMemAllocator()
    {
        static MemAllocator memAllocator;
        return memAllocator;
    }*/
}
#endif
