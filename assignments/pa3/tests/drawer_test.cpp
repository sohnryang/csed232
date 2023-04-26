#include "classic.hpp"
#include "downsample.hpp"
#include "drawer.hpp"
#include "gradient.hpp"
#include "scale.hpp"
#include "upsample.hpp"

#include <vector>

#include <gtest/gtest.h>

TEST(Drawer, Drawer) {
  int width = 3, height = 3;
  std::vector<int> sample_image = {100, 160, 120, 100, 30, 100, 100, 100, 170};
  gradient *g = new gradient(width, height, sample_image);
  drawer d(g);
  EXPECT_EQ(d.draw(), R"(|- 
|+-
 | 
)");
}

TEST(Drawer, Downsample) {
  int width = 4, height = 4;
  std::vector<int> sample_image = {2,  18, 37, 18, 18, 37, 18, 37,
                                   18, 37, 18, 37, 18, 37, 18, 37};
  {
    classic *c = new classic(width, height, sample_image);
    drawer d(c);
    EXPECT_EQ(d.draw(), R"(@&%&
&%&%
&%&%
&%&%
)");
  }
  {
    classic *c = new classic(width, height, sample_image);
    downsample ds(c);
    EXPECT_EQ(ds.draw(), R"(@%
&&
)");
  }
}

TEST(Drawer, Upsample) {
  int width = 2, height = 2;
  std::vector<int> sample_image = {2, 37, 18, 18};
  {
    classic *c = new classic(width, height, sample_image);
    drawer d(c);
    EXPECT_EQ(d.draw(), R"(@%
&&
)");
  }
  {
    classic *c = new classic(width, height, sample_image);
    upsample u(c);
    EXPECT_EQ(u.draw(), R"(@@%%
@@%%
&&&&
&&&&
)");
  }
}

TEST(Drawer, Scale) {
  int width = 2, height = 2;
  std::vector<int> sample_image = {2, 37, 18, 18};
  classic *c = new classic(width, height, sample_image);
  scale s(c, 2, -2);
  EXPECT_EQ(s.draw(), R"(@@%%
)");
}
