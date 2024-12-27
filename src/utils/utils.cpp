#include "utils.h"

int util::bit_width(int m)
    {
    if (m == 0) return 0;
    else {
        int w = 0;
        while(m >>=1)
        {
            ++w;
        }

        return w;
    }
}