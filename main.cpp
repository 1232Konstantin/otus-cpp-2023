
#include <cstdlib>

#include "App.h"

int main(int argc, char *argv[])
{
    size_t BulkSize = 1;

    if (2 == argc)
    {
        BulkSize = atoi(argv[1]);
    }

    Bulk::FBulkApp App(BulkSize);
    App.Begin();

    return 0;
}
