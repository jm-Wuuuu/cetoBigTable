#ifndef CETO_RANDOM_GENERATOR_HPP
#define CETO_RANDOM_GENERATOR_HPP
#include <random>
namespace ceto
{
    class RandomGenerator
    {
    public:
        INT32 operator()();
    private:
        std::random_device _rd;
    };
}
#endif
