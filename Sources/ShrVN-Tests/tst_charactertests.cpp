#include <catch.hpp>
#include <characters.hpp>
#include <filesystem>

TEST_CASE("My first test with Catch2", "[fancy]")
{
    Characters a("Jean");
    REQUIRE(a.GetName() == "Jean");
    REQUIRE(a.GetBlueValue() == 0);
    REQUIRE(a.GetGreenValue() == 0);
    REQUIRE(a.GetRedValue() == 0);
}
