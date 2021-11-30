#include <stdio.h>
#include <stdlib.h>

#include "gtest/gtest.h"

using ::testing::InitGoogleTest;

#include "color.h"
#include <iostream>
#include <bitset>

namespace
{
    ids::color_mask g_mask{.r=0x00'ff'00'00,
                           .g=0x00'00'ff'00,
                           .b=0x00'00'00'ff,
                           .a=0xff'00'00'00
                           };
                    
    ids::rgb g_color{g_mask};    
    
    TEST(ColorTest, set_mask)
    {
        g_color.set_mask(g_mask);
        EXPECT_TRUE(g_color.get_mask() == g_mask);
    }
                       
    TEST(ColorTest, set_rgb)
    {
        g_color.set_rgb(0xb3,0xc2,0xd5,0xfe);
        
        //this test can fail if mask is not argb order
        EXPECT_EQ(g_color.get_rgb(),0xfe'b3'c2'd5);
    }
    TEST(ColorTest, constructor)
    {
        ids::rgb color{0x22,0x43,0xf3,0x8a,g_mask};
        
       EXPECT_EQ(color.get_red(),   0x22);
       EXPECT_EQ(color.get_green(), 0x43);
       EXPECT_EQ(color.get_blue(),  0xf3);
       EXPECT_EQ(color.get_alpha(), 0x8a);
    }
    
    TEST(ColorTest, set_red)
    {
        g_color.set_red(0x2c);
        EXPECT_EQ(g_color.get_red(), 0x2c);
    }
    TEST(ColorTest, set_green)
    {
        g_color.set_green(0xae);
        EXPECT_EQ(g_color.get_green(), 0xae);
    }
    TEST(ColorTest, set_blue)
    {
        g_color.set_blue(0xe2);
        EXPECT_EQ(g_color.get_blue(), 0xe2);
    }
    TEST(ColorTest, set_alpha)
    {
        g_color.set_alpha(0xfa);
        EXPECT_EQ(g_color.get_alpha(), 0xfa);
    }
}

int main(int argc, char **argv)
{
  InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
