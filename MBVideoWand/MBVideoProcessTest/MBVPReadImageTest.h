//
// Created by redknot on 2020/1/5.
//

#ifndef EYE_VIDEO_WAND_EYERVPREADIMAGETEST_H
#define EYE_VIDEO_WAND_EYERVPREADIMAGETEST_H

#include <gtest/gtest.h>
#include "MBVideoProcess/MBVideoProcess.hpp"

TEST(MBVideoWand, Read_Image){
    MB::MBVPVideoImage image;
    int ret = image.LoadFromImageFile("/home/redknot/Videos/timg.jpeg");
}

#endif //EYE_VIDEO_WAND_EYERVPREADIMAGETEST_H
