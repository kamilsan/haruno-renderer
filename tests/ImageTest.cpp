#include <gtest/gtest.h>

#include "Image.hpp"

TEST(ImageTest, Constructor)
{
  const Image img{20, 30};

  EXPECT_EQ(img.getWidth(), 20);
  EXPECT_EQ(img.getHeight(), 30);

  const int len = 3*img.getWidth()*img.getHeight();
  bool isImageBlack = true;

  for(int i = 0; i < len; ++i)
  {
    if(img[i] != 0.0f)
    {
      isImageBlack = false;
    }
  }

  EXPECT_TRUE(isImageBlack);
}

TEST(ImageTest, CopyConstructor)
{
  Image img{20, 30};
  const int mutatedIndex = 20;
  img[mutatedIndex] = 0.5f;

  Image copy = img;

  EXPECT_EQ(copy.getWidth(), img.getWidth());
  EXPECT_EQ(copy.getHeight(), img.getHeight());
  EXPECT_EQ(copy[mutatedIndex], img[mutatedIndex]);
}

TEST(ImageTest, AssigmentOperator)
{
  Image img{20, 30};
  const int mutatedIndex = 20;
  img[mutatedIndex] = 0.5f;

  Image other{10, 20};
  other = img;

  EXPECT_EQ(other.getWidth(), img.getWidth());
  EXPECT_EQ(other.getHeight(), img.getHeight());
  EXPECT_EQ(other[mutatedIndex], img[mutatedIndex]);
}

TEST(ImageTest, GetPixel)
{
  Image img{2, 3};
  const Color newColor = Color{1.0, 0.5f, 0.25f};

  img[6] = newColor.r;
  img[7] = newColor.g;
  img[8] = newColor.b;

  EXPECT_EQ(img.getPixel(0, 1), newColor);
}

TEST(ImageTest, SetPixel)
{
  Image img{2, 3};
  const Color newColor = Color{1.0, 0.5f, 0.25f};

  img.setPixel(0, 1, newColor);

  EXPECT_EQ(img[6], newColor.r);
  EXPECT_EQ(img[7], newColor.g);
  EXPECT_EQ(img[8], newColor.b);
}

TEST(ImageTest, GetAndSetPixel)
{
  Image img{20, 30};
  const Color newColor = Color{1.0, 0.5f, 0.25f};

  img.setPixel(12, 17, newColor);

  EXPECT_EQ(img.getPixel(12, 17), newColor);
}