#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <filesystem>

#include <QCoreApplication>
#include <QtTest>

int main( int argc, char* argv[] )
{
    std::filesystem::current_path(std::filesystem::path("../Scripts/ScriptTest"));
    QCoreApplication a(argc, argv);

    QTEST_SET_MAIN_SOURCE_PATH
        int result = Catch::Session().run( argc, argv );

    return ( result < 0xff ? result : 0xff );
}
