#include <cstdio>
#include "QosineConfig.h"

using namespace std;

int main( int argc, char *argv[] )
{
    if ( argc == 1 )
    {
        fprintf( stdout, "%s Version %d.%d", argv[0], Qosine_VERSION_MAJOR, Qosine_VERSION_MINOR );
        return 1;
    }
    else
    {
        return 0;
    }
}
