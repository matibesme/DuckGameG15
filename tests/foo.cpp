#include "common/foo.h"
#include "gtest/gtest.h"

#include "gmock/gmock.h"

using ::testing::AllOf;
using ::testing::HasSubstr;
using ::testing::ThrowsMessage;

namespace {
TEST(FooTest, Check) { EXPECT_EQ(foo(4), (int)(4 + 5)); }
} // namespace
