#define private public
#include "Mastermind.hpp"

#include <iostream>

#define ASSERT_EQ(a,b) doAssertion((a),(b),__LINE__)
template<typename T, typename U>
void doAssertion(T a, U b, std::size_t line) {
    if(a != b) {
      std::cerr << "Failed test at line " << line << " expected " << a << " but got " << b << std::endl;
    }
}

int main()
{
  Mastermind m;
  m.guess("rrb1"); //invalid
  m.guess("rrbg"); // 3 - 3
  m.guess("rbrg"); // 2 - 3
  m.guess("gbgr"); // 0 - 4
  m.guess("RGBG"); // 4 - 4 - WON

  ASSERT_EQ(false, m.isInputValid("rgbt"));
  ASSERT_EQ(false, m.isInputValid("RGBT"));
  ASSERT_EQ(false, m.isInputValid("RGB1"));
  ASSERT_EQ(true, m.isInputValid("RGBB"));

  ASSERT_EQ(3, m.countCorrectlyPlacedPins("RRBG")); // 3 - 3
  ASSERT_EQ(3, m.countCorrectColorPins("RRBG")); // 3 - 3

  ASSERT_EQ(2, m.countCorrectlyPlacedPins("RBRG")); // 2 - 3
  ASSERT_EQ(3, m.countCorrectColorPins("RBRG")); // 2 - 3

  ASSERT_EQ(0, m.countCorrectlyPlacedPins("GBGR")); // 0 - 4
  ASSERT_EQ(4, m.countCorrectColorPins("GBGR")); // 0 - 4

  ASSERT_EQ(4, m.countCorrectlyPlacedPins("RGBG")); // 4 - 4 - WON
  ASSERT_EQ(4, m.countCorrectColorPins("RGBG")); // 4 - 4 - WON

  return 0;
}
