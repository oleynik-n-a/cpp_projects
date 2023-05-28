#include "catch.hpp"
#include "unixpath.h"

TEST_CASE("NormalizePath") {
    REQUIRE("/" == NormalizePath("/", "."));
    REQUIRE("/home/user2" == NormalizePath("/home/user1", "../user2"));

    REQUIRE("/" == NormalizePath("/", ".."));
    REQUIRE("/tmp" == NormalizePath("/home", "../../tmp"));

    REQUIRE("/a" == NormalizePath("/", "../../a/"));
    REQUIRE("/b" == NormalizePath("/", ".././/././/./../b/././././././"));

    REQUIRE("/a/a" == NormalizePath("/a", ".//././a/"));
    REQUIRE("/a/b/c/f" == NormalizePath("/a/b/c/d", "../c/f"));
    REQUIRE("/path" == NormalizePath("/path", "/"));
    REQUIRE("/abc" == NormalizePath("/abc/cde", ".."));
}
