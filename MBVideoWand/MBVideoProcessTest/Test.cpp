#include <gtest/gtest.h>

#include "MBCore/MBCore.hpp"
#include "MBVideoProcess/MBVideoProcess.hpp"


#include "MBVPAudioTrackTest.hpp"
#include "MBVPReadImageTest.h"
#include "MBVPAudioResTest.hpp"
#include "MBVPVideoText.h"

int main(int argc,char **argv)
{
    MBLog("This is Test\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
