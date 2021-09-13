#include <gtest/gtest.h>

extern "C" {
#include "../src/scale.h"
}

#include "script/tests.txt"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}