#ifndef MASTERMIND_HPP_INCLUDED
#define MASTERMIND_HPP_INCLUDED

#include <cctype>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>


#include <iostream>


class Mastermind {
  static const unsigned char SLOTS = 4;
  static const unsigned char MAX_NUMBER_OF_GUESSES = 20; // check whether that's true

public:
  Mastermind() : m_solution(generateSolution())
               , m_numberOfGuesses(0)
               , m_pins("RGB")
  {
  }

  void guess(std::string input) {
    std::transform(input.begin(), input.end(), input.begin(), toupper);

    if(!isInputValid(input)) {
      std::cout << "INVALID INPUT!" << std::endl;
      return;
    }

    checkCorrectlyPlacedItems(input); /// should throw

    // matches with wrong place
    checkIncorrectlyPlacedItems(input);

    if(++m_numberOfGuesses == MAX_NUMBER_OF_GUESSES) { /// Move check up or invalidate object
      std::cout << "You lost" << std::endl;
    }
  }

private:
  std::string generateSolution() const {
    /// GENERATE
    return "RGBG"; /// TEMP TO COMPILE
  }

  struct InvalidCharFinder {
    InvalidCharFinder(const std::string& chars) : chars(chars) {}
    bool operator()(char c) const { return chars.find(c) == std::string::npos; }
    std::string chars;
  };

  bool isInputValid(const std::string& input) const {
    return input.size() == SLOTS &&
           std::find_if(input.begin(), input.end(), InvalidCharFinder(m_pins)) == input.end();
  }

  unsigned countCorrectlyPlacedSlots(const std::string& input) const {
    return std::inner_product(input.begin(), input.end(), m_solution.begin(),
                              0, std::plus<int>(), std::equal_to<char>());
  }

  void checkCorrectlyPlacedItems(const std::string& input) const {
    unsigned correct = countCorrectlyPlacedSlots(input);
    if(correct == SLOTS) {
      std::cout << "You won!" << std::endl; /// Throw some gameover exc
      return;
    }
    std::cout << "Correct: " << correct << " - ";
  }

  struct CorrectPinFinder {
    CorrectPinFinder(const std::string& input, const std::string& solution)
        : input(input), solution(solution) {}
    int operator()(char c) const {
      return std::min(std::count(input.begin(), input.end(), c),
                      std::count(solution.begin(), solution.end(), c));
    }
    std::string input;
    std::string solution;
  };

  void checkIncorrectlyPlacedItems(const std::string& input) const {
    unsigned num = 0;
    for(std::string::const_iterator it = m_pins.begin(); it < m_pins.end(); ++it) {
      num += std::min(std::count(input.begin(), input.end(), *it),
                      std::count(m_solution.begin(), m_solution.end(), *it));
    }
    std::cout << "ColorOK: " << num << std::endl;
  }

  const std::string m_solution;
  unsigned          m_numberOfGuesses;
  const std::string m_pins;
};



#endif // MASTERMIND_HPP_INCLUDED
