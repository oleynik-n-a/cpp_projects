#include "catch.hpp"
#include "unixpath.h"

TEST_CASE("NormalizePath") {
    REQUIRE("/" == NormalizePath("/", "."));
    REQUIRE("/home/user2" == NormalizePath("/home/user1", "../user2"));

    REQUIRE("/a/b/c/f" == NormalizePath("/a/b/c/d", "../c/f"));
    REQUIRE("/tmp" == NormalizePath("/home", "../../tmp"));

    REQUIRE("/a" == NormalizePath("/", "../../a/"));
    REQUIRE("/b" == NormalizePath("/", ".././/././/./../b/././././././"));
}
