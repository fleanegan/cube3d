#include <cstdio>
#include "test_utils.h"
#include "test_parsing.h"
#include "test_distance.h"
#include "test_init.h"
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from %s\n", __FILE__);
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}