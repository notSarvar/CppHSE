#include <catch.hpp>

#include "unixpath.h"

TEST_CASE("UnixPath") {
    UnixPath path("/home");

    path.ChangeDirectory(".");
    REQUIRE("/home" == path.GetAbsolutePath());

    path.ChangeDirectory("/home/user");
    REQUIRE("/home/user" == path.GetAbsolutePath());
    REQUIRE("./user" == path.GetRelativePath());

    path.ChangeDirectory("..");
    REQUIRE("/home" == path.GetAbsolutePath());
    REQUIRE("." == path.GetRelativePath());

    path.ChangeDirectory("/sarvar/lol");
    REQUIRE("/sarvar/lol" == path.GetAbsolutePath());
    REQUIRE("../sarvar/lol" == path.GetRelativePath());

    path.ChangeDirectory(".././././tmp/dir/..");
    REQUIRE("/sarvar/tmp" == path.GetAbsolutePath());
    REQUIRE("../sarvar/tmp" == path.GetRelativePath());
}
