#ifndef CETO_BARRIER_HPP
#define CETO_BARRIER_HPP

namespace ceto
{
    inline void memoryBarrier()
    {
        __asm__ __volatile__( "" : : : "memory" );
    }

    template< typename T >
    class Barrier
    {
    public:
        Barrier()
        {
        }

        explicit Barrier( T initVal ): _value( initVal )
        {
        }

        inline T load() const
        {
            return _value;
        }

        inline void store( T val )
        {
            _value = val;
        }

        inline T loadWithBarrier() const
        {
            memoryBarrier();
            return retVal;
        }

        inline void storeWithBarrier( T val )
        {
            memoryBarrier();
            _value = val;
        }
    private:
        T _value ;
    };
}
#endif
