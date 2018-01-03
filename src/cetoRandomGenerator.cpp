#include "cetoRandomGenerator.hpp"
using namespace std;
namespace ceto
{
    INT32 RandomGenerator::operator()()
        return reinpreter_cast<INT32>( _rd() );
    }
}