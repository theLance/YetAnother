#ifndef MASTERMIND_HPP_INCLUDED
#define MASTERMIND_HPP_INCLUDED

#include <cctype>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>

#include <iostream>

struct GameOver {
  enum Outcome { WON, LOST } outcome;
  GameOver(Outcome outcome) : outcome(outcome) {}
};

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

    unsigned correct = countCorrectlyPlacedPins(input);
    if(correct == SLOTS) {
      throw GameOver(GameOver::WON);
    }
    std::cout << "Correct: " << correct << " ColorOK: " << countCorrectColorPins(input) << std::endl;

    if(++m_numberOfGuesses == MAX_NUMBER_OF_GUESSES) { /// Move check up or invalidate object
      throw GameOver(GameOver::LOST);
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

  unsigned countCorrectlyPlacedPins(const std::string& input) const {
    return std::inner_product(input.begin(), input.end(), m_solution.begin(),
                              0, std::plus<int>(), std::equal_to<char>());
  }

  struct CorrectPinFinder {
    CorrectPinFinder(const std::string& input, const std::string& solution)
        : input(input), solution(solution)
    {}
    int operator()(int i, char c) const {
      return i + std::min(std::count(input.begin(), input.end(), c),
                          std::count(solution.begin(), solution.end(), c));
    }
    std::string input;
    std::string solution;
  };

  unsigned countCorrectColorPins(const std::string& input) const {
    return std::accumulate(m_pins.begin(), m_pins.end(), 0, CorrectPinFinder(input, m_solution));
  }

  const std::string m_solution;
  unsigned          m_numberOfGuesses;
  const std::string m_pins;
};



#endif // MASTERMIND_HPP_INCLUDED
