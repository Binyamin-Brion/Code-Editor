#include <iostream>
#include <QtWidgets/QApplication>
#include <QtTest/qtestcase.h>
#include "MainWindow.h"
#include "TestSuite.h"
#include <QtCharts>

enum class ShaderType
{
    VERTEX_SHADER,
    FRAGMENT_SHADER
};

struct VertexShader
{

};

int main(int argc, char *argv[])
{
    QApplication app{argc, argv};

    MainWindow mainWindow;

    mainWindow.show();

    auto &suite = TestSuite::suite();

    int testStatus = 0;

    for(const auto &i : suite)
    {
      //  testStatus |= QTest::qExec(i, argc, argv);
    }

    return app.exec();
}