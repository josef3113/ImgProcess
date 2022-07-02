#include <gtest/gtest.h>
#include "time_measure.h"



TEST(TimeMeasurTest, basic_test)
{
	utilities::TimeMeasur measur;

	EXPECT_NO_THROW( measur.Start());
	EXPECT_NO_THROW(measur.Stop());
	EXPECT_NO_THROW(measur.GetTime());
}