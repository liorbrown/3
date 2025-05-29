// liorbrown@outlook.co.il

#include "Merchant.hpp"

void Merchant::arrested()
{
    --*this;

    if (this->coins)
        --*this;
}