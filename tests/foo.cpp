#include "gtest/gtest.h"
#include "common/foo.h"

#include "gmock/gmock.h"

    using ::testing::HasSubstr;
using ::testing::AllOf;
using ::testing::ThrowsMessage;

namespace {
TEST(FooTest, Check) { EXPECT_EQ(foo(4), (int)(4 + 5)); }
} // namespace
