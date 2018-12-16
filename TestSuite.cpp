//
// Created by Biny Brion on 10/20/2018.
//

#include "TestSuite.h"

TestSuite::TestSuite()
{ printf("In here! \n");
    suite().push_back(this);
}

std::vector<QObject *> &TestSuite::suite()
{
    static std::vector<QObject*> testObjects;

    return testObjects;
}
