#include <cstdio>
#include "gtest/gtest.h"
#include "QosineWaveformLister.h"

namespace {

// The fixture for testing class QosineWaveformLister.
class QosineWaveformListerTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  QosineWaveformListerTest()
  {
     // You can do set-up work for each test here.
  }

  ~QosineWaveformListerTest() override
  {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override
  {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override
  {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case for QosineWaveformLister.
  QosineWaveformLister qwl;
  uint8_t numberOfBitsPerSample;
  uint16_t numberOfSamples;
};

TEST_F( QosineWaveformListerTest, MethodGetNumberOfDifferentWaveformsDoesCheckMinimumNumberOfBitsPerSample )
{
  numberOfBitsPerSample = 1;
  numberOfSamples = 4;
  EXPECT_EQ( qwl.GetNumberOfDifferentWaveforms( numberOfBitsPerSample, numberOfSamples ), 0 );
}

TEST_F( QosineWaveformListerTest, MethodGetNumberOfDifferentWaveformsDoesCheckMaximumNumberOfBitsPerSample )
{
  numberOfBitsPerSample = 25;
  numberOfSamples = 4;
  EXPECT_EQ( qwl.GetNumberOfDifferentWaveforms( numberOfBitsPerSample, numberOfSamples ), 0 );
}

TEST_F( QosineWaveformListerTest, MethodGetNumberOfDifferentWaveformsDoesCheckMinimumNumberOfSamples )
{
  numberOfBitsPerSample = 2;
  numberOfSamples = 3;
  EXPECT_EQ( qwl.GetNumberOfDifferentWaveforms( numberOfBitsPerSample, numberOfSamples ), 0 );
}

TEST_F( QosineWaveformListerTest, MethodGetNumberOfDifferentWaveformsDoesCheckMaximumNumberOfSamples )
{
  numberOfBitsPerSample = 2;
  numberOfSamples = 256;
  EXPECT_EQ( qwl.GetNumberOfDifferentWaveforms( numberOfBitsPerSample, numberOfSamples ), 0 );
}

}  // namespace


GTEST_API_ int main(int argc, char **argv)
{
  printf("Running main() from %s\n", __FILE__);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
