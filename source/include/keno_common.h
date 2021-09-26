#ifndef _KENO_COMMON_H_
#define _KENO_COMMON_H_

/*!
 * @brief This is a set of common definition for classes GameManager and KenoBet.
 * This is to avoid circular referencing.
 *
 * @author Selan R. dos Santos
 * @author João Pedro Fonseca Dantas 
 * @author João Guilherme Alves Lopes da Costa
 * @file keno_common.h
 */

#include <fstream> ///< To handling files.
#include <sstream> ///< To handling the stringstream.
#include <iostream> ///< To use cout and cerr.
#include <vector> ///< To use vector and its methods.
#include <string> ///< To use string ans its methods.
#include <random> ///< To shuffle and random.
#include <algorithm> ///< To sort and get uniques.

namespace keno {
  using number_type = unsigned short int; ///< Data type for a keno hit.
  using cash_type = float; ///< Defines the wage type in this application.
  using set_of_numbers_type = std::vector<number_type>; ///< List of numbers for a keno bet.

  const float PAYOUT_TABLE[15][16] = {
    {0,   3,  -1,  -1,  -1, -1, -1,  -1,  -1,   -1,   -1,   -1,   -1,   -1,   -1,    -1},
    {0,   1,   9,  -1,  -1, -1, -1,  -1,  -1,   -1,   -1,   -1,   -1,   -1,   -1,    -1},
    {0,   1,   2,  16,  -1, -1, -1,  -1,  -1,   -1,   -1,   -1,   -1,   -1,   -1,    -1},
    {0, 0.5,   2,   6,  12, -1, -1,  -1,  -1,   -1,   -1,   -1,   -1,   -1,   -1,    -1},
    {0, 0.5,   1,   3,  15, 50, -1,  -1,  -1,   -1,   -1,   -1,   -1,   -1,   -1,    -1},
    {0, 0.5,   1,   2,   3, 30, 75,  -1,  -1,   -1,   -1,   -1,   -1,   -1,   -1,    -1},
    {0, 0.5, 0.5,   1,   6, 12, 36, 100,  -1,   -1,   -1,   -1,   -1,   -1,   -1,    -1},
    {0, 0.5, 0.5,   1,   3,  6, 19,  90, 720,   -1,   -1,   -1,   -1,   -1,   -1,    -1},
    {0, 0.5, 0.5,   1,   2,  4,  8,  20,  80, 1200,   -1,   -1,   -1,   -1,   -1,    -1},
    {0,   0, 0.5,   1,   2,  3,  5,  10,  30,  600, 1800,   -1,   -1,   -1,   -1,    -1},
    {0,   0, 0.5,   1,   1,  2,  6,  15,  25,  180, 1000, 3000,   -1,   -1,   -1,    -1},
    {0,   0,   0, 0.5,   1,  2,  4,  24,  72,  250,  500, 2000, 4000,   -1,   -1,    -1},
    {0,   0,   0, 0.5, 0.5,  3,  4,   5,  20,   80,  240,  500, 3000, 6000,   -1,    -1},
    {0,   0,   0, 0.5, 0.5,  2,  3,   5,  12,   50,  150,  500, 1000, 2000, 7500,    -1},
    {0,   0,   0, 0.5, 0.5,  1,  2,   5,  15,   50,  150,  300,  600, 1200, 2500, 10000}
  }; ///< Table of payout factors values.
  const cash_type MAX_WAGE{100000}; ///< Maximum number of a wage.

  /**
   * @brief Enumeration to determine the states of the program.
   */
  enum State {
    START = 0, //!< The initial state.
    END, //!< Finishing the program.
    WELCOME, //!< Welcome message.
    READING, //!< Reading the input file.
    PLAYING, //!< Animating the bar charts.
  };

  /**
   * @brief Enumeration to identify a error or warning.
   */
  enum Error {
    kInputManyArguments = 0, //!< The input has too many argumens.
    kMaxSpotsExceeded, //!< Player entered with too many spots.
    kInputFewArguments, //!< The input has too few arguments.
    kBetFileNotFound, //!< Could not find the bet file.
    kInvalidBet, //!< Player entered a invalid bet.
    kInvalidRounds, //!< Player entered a invalid number of rounds.
    kSpotsNotInformed, //!< Player did not inform its spots.
  };
};

#endif
