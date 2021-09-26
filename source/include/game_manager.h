#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

/*!
 * @brief Class that defines the management of the Keno game.
 *
 * @author João Pedro Fonseca Dantas
 * @author João Guilherme Alves Lopes da Costa
 * @file game_manager.cpp
 */

#include "keno_common.h"
#include "keno_bet.h"

namespace keno { 
  /**
   * @class
   */
  class GameManager {
    public:
      
      /**
       * @brief Write to user some error or warning found in program process.
       * @param type Error or warning found.
       */
      void WriteError(keno::Error type);
      
      /**
       * @brief Display a welcome message.
       */
      void DisplayWelcome(void);

      /**
       * @brief Display the information read from the data file and a guide.
       */
      void DisplaySummary(void);
      
      /**
       * @brief Display the result of the game.
       */
      void DisplayEnd(void);

      /**
       * @brief Read bet data of a given bet file. 
       * @param path Given bet file path.
       */
      void ReadBetFile(std::string &path);

      /**
       * @brief Start a new game from a given input.
       * @param argc Number of arguments (inputs) of the program execution.
       * @param argv Pointer to the given arguments (inputs).
       */
      void Initialize(int argc, char *argv[]);

      /**
       * @brief Check if the program is still running.
       * @return true if the program has finished.
       * @return false otherwise.
       */
      bool GameOver(void);

      /**
       * @brief Generate a draw and find hits.
       */
      void ProcessEvents(void);

      /**
       * @brief Update the current state of the program.
       */
      void Update(void);

      /**
       * @brief Display the current state of the program after the processing.
       */
      void Render(void);

    private:
      keno::cash_type cash_per_round; ///< The cash to wage for each round
      keno::cash_type initial_credit; ///< Player credit at the beggining of the game
      keno::KenoBet player_bet; ///< The bet given by the player
      keno::number_type current_round{0}; ///< Number of the current round
      keno::number_type number_of_rounds; ///< Total number of rounds
      keno::set_of_numbers_type draw; ///< List of drawn numbers
      keno::set_of_numbers_type hits; ///< Intersection between drawn numbers and player spots
      keno::set_of_numbers_type spots; ///< Chosen number by the player
      keno::State game_state; ///< Representation of error or warning
      std::string bet_file_path; ///< String of the path to the player bet file 
  };
}

#endif
