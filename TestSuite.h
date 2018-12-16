//
// Created by Biny Brion on 10/20/2018.
//

#ifndef PERFORMANCEMONITOR_TESTSUITE_H
#define PERFORMANCEMONITOR_TESTSUITE_H


#include <QtCore/QObject>

class TestSuite : public QObject
{
public:

    TestSuite();

    static std::vector<QObject*>& suite();
};


#endif //PERFORMANCEMONITOR_TESTSUITE_H
