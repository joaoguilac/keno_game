/*!
 * @brief Class that defines the management of the Keno game.
 *
 * @author João Pedro Fonseca Dantas
 * @author João Guilherme Alves Lopes da Costa
 * @file game_manager.cpp
 */

#include "game_manager.h"
#include "keno_common.h"

/*!
 * @namespace Keno
 */
namespace keno {
  //============[ GameManager METHODS ]===============//

  void GameManager::WriteError(keno::Error type) {
    switch (type) {
      case kInputManyArguments:
        std::cout
          << "\n>>> WARNING! Many arguments to run the game.\n"
          << "    You only need to specify the executable file and one data input file.\n"
          << "    The arguments after the first input file will be ignored.\n"
          << "    Correct example: ./bin/keno ./data/bet_01.dat\n";
          break;
      case kMaxSpotsExceeded:
        std::cerr
          << "\n>>> WARNING! You can only enter a maximum of 15 numbers for spots.\n"
          << "    We are considering only the first 15 unique valid numbers.\n\n";
          break;
      case kInputFewArguments:
        std::cerr
          << "\n>>> ERROR! You did not specify the data input file to bet.\n"
          << "    You need to run the game and enter the bet data via a file.\n"
          << "    Example: ./bin/keno ./data/bet_01.dat\n\n";
        break;
      case kBetFileNotFound:
        std::cerr
          << "\n>>> ERROR! We didn't can read the file [" << GameManager::bet_file_path << "]\n"
          << "    Probably [" << GameManager::bet_file_path << "] is not a data file or don't exist.\n\n";
          break;
      case kInvalidBet:
        std::cerr
          << "\n>>> ERROR! You have not entered the amount you want to bet or your amount is not allowed.\n"
          << "    Next time enter a value greater than 1 and less than 100000 for your bet.\n\n";
          break;
      case kInvalidRounds:
        std::cerr
          << "\n>>> ERROR! You did not enter the number of rounds or entered a non-positive value.\n"
          << "    Next time enter a value greater than 0 for the number of rounds.\n\n";
          break;
      case kSpotsNotInformed:
        std::cerr
          << "\n>>> ERROR! You did not enter the spots you would like to bet.\n"
          << "    Next time enter at least one spot to play the game.\n\n";
          break;
      default:
        std::cerr << "\n>>> UNKNOWN ERROR!\n";
    }
    if (type > 1) exit(1);
  }

  void GameManager::DisplayWelcome(void) {
    std::cout << "===================================================\n";
    std::cout << "          Welcome to the Keno Game, v2.1\n";
    std::cout << "   Copyright © 2021, João Guilherme & João Pedro\n";
    std::cout << "===================================================\n";
  }

  void GameManager::DisplaySummary(void) {
    keno::set_of_numbers_type numbers = player_bet.get_spots();
    std::cout
      << "    You are going to wage a total of $" << GameManager::initial_credit << " dollars.\n"
      << "    Going for a total of " << GameManager::number_of_rounds << " rounds, waging $" << cash_per_round << " per round.\n\n"
      << "    Your bet has " << player_bet.Size() << " numbers. They are: [ ";
    for (number_type i{0}; i < player_bet.Size(); i++) {
      std::cout << numbers[i] << " ";
    }

    std::cout
      << "]\n"
      << "         -------+---------\n"
      << "         Hits   | Payout\n"
      << "         -------+---------\n";
    for (number_type i{0}; i <= player_bet.Size(); i++) {
      std::cout << "         " << i;
      if (i < 10) {
        std::cout << "      | ";
      }
      else {
        std::cout << "     | ";
      }
      std::cout << keno::PAYOUT_TABLE[player_bet.Size() - 1][i];
      if (i != player_bet.Size()) {
        std::cout << "\n";
      }
    }
  }

  void GameManager::DisplayEnd(void) {
    std::cout
      << "\n>>> End of rounds!\n"
      << "--------------------------------------------------\n\n"
      << "===== SUMMARY =====\n"
      << ">>> You spent in this game a total of $" << initial_credit << " dollars.\n";
    
    keno::cash_type amount{player_bet.get_wage() - initial_credit};
    if (amount > 0) {
      std::cout << ">>> Hooray, you won $" << std::abs(amount) << " dollars. See you next time! ;-)\n";
    }
    else if (amount < 0) {
      std::cout << ">>> Oh no, you lost $" << std::abs(amount) << " dollars. More luck next time! :-(\n";
    }
    else {
      std::cout << ">>> Oops, you kept your initial bet money, you didn't win or lose. More luck next time! :-/\n";
    }
    std::cout << ">>> You are leaving the Keno table with $" << player_bet.get_wage() << " dollars.\n";
  }

  void GameManager::ReadBetFile(std::string &path) {
    std::string line;
    std::stringstream ss;
    keno::number_type number;
    std::ifstream bet_file;
    GameManager::spots.resize(0);

    bet_file.open(path);
    std::cout
      << "\n>>> Preparing to read bet file [" << bet_file_path << "], please wait...\n"
      << "--------------------------------------------------\n";
    if (not bet_file.is_open())
      GameManager::WriteError(kBetFileNotFound);
    std::getline(bet_file, line);
    if (bet_file.fail()) {
      GameManager::WriteError(kBetFileNotFound);
    }
    bet_file.seekg(0); // Put pointer at the beginning of the file
    
    bool get_input{false};
    keno::cash_type player_credit{0};
    while (not bet_file.eof() && not get_input) {
      std::getline(bet_file, line);
      ss.clear();
      ss << line;
      if (ss >> player_credit) {
        if (line[0] == '-' || player_credit > MAX_WAGE) {
          GameManager::WriteError(kInvalidBet);
        }
        get_input = true;
      }
    }
    GameManager::initial_credit = player_credit;

    get_input = false;
    keno::number_type nr{0};
    while (not bet_file.eof() && not get_input) {
      std::getline(bet_file, line);
      ss.clear();
      ss << line;
      if (ss >> nr) {
        if (line[0] == '-' || nr == 0) {
          GameManager::WriteError(kInvalidRounds);
        }
        get_input = true;
      }
    }
    GameManager::number_of_rounds = nr;
    GameManager::cash_per_round = initial_credit / number_of_rounds;

    get_input = false;
    keno::set_of_numbers_type player_numbers;
    while (not bet_file.eof() && not get_input) {
      std::getline(bet_file, line);
      ss.clear();
      ss << line;
      while (ss >> number) {
        if (player_numbers.size() == 15) {
          GameManager::WriteError(kMaxSpotsExceeded);
          break;
        }
        else
          player_numbers.push_back(number);
      }
      GameManager::spots = player_numbers;
    }
    // std::cout << "bet: " << player_credit << " nr: " << nr << " spots: " << spots.size() << std::endl;
    if (player_credit == 0) {
      GameManager::WriteError(kInvalidBet);
    }
    else if (nr == 0) {
      GameManager::WriteError(kInvalidRounds);
    }
    else if (spots.size() == 0) {
      GameManager::WriteError(kSpotsNotInformed);
    }
    std::sort(spots.begin(), spots.end());

    bet_file.close();
    std::cout << ">>> Bet successfully read!\n";
  }
  
  void GameManager::Initialize(int argc, char *argv[]) {
    if (argc > 2)
      GameManager::WriteError(kInputManyArguments);
    else if (argc < 2)
      GameManager::WriteError(kInputFewArguments);
    
    GameManager::bet_file_path = argv[1];
    game_state = keno::State::START;
  }

  bool GameManager::GameOver(void) {
    if (game_state == keno::State::END) {
      player_bet.reset();
      return true;
    }
    else {
      return false;
    }
  }

  void GameManager::ProcessEvents(void) {
    if (game_state == keno::State::WELCOME) {
      // Calls the function that reads the input file.
      GameManager::ReadBetFile(bet_file_path);
      for (keno::number_type i{0}; i < spots.size(); i++) {
          player_bet.AddSpot(spots[i]);
      }
      player_bet.set_wage(initial_credit);
    }
    else if(game_state == keno::State::READING) {
      // Waits for the user to press enter to start the game.
      while (getchar() != '\n') {}
    }
    else if (game_state == keno::State::PLAYING) {
      // Waits for the user to press enter to start the round.
      while (getchar() != '\n') {}
      // Sortear Números;
      keno::set_of_numbers_type range;
      keno::number_type value{1};
      for (number_type i{0}; i < 80; i++) {
        range.push_back(value);
        value++;
      }
      std::random_device rd;  // Will be used to obtain a seed for the random number engine
      std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
      std::shuffle(range.begin(), range.end(), gen);
      draw.assign(range.begin(), range.begin()+20);
      // Ordenar números;
      std::sort(draw.begin(), draw.end());
      // Ver interseção (FindHits)
      hits = player_bet.FindHits(draw);
    }
  }

  void GameManager::Update(void) {
    if (game_state == keno::State::START) {
      game_state = keno::State::WELCOME;
    }
    else if (game_state == keno::State::WELCOME) {
      game_state = keno::State::READING;
    }
    else if (game_state == keno::State::READING) {
      game_state = keno::State::PLAYING;
    }
    else if (game_state == keno::State::PLAYING) {
      if (current_round != number_of_rounds) {
        keno::cash_type total_payout = PAYOUT_TABLE[player_bet.Size() - 1][hits.size()] * cash_per_round;
        keno::cash_type cash_round = total_payout - cash_per_round;
        keno::cash_type player_wage = player_bet.get_wage();
        player_bet.set_wage(player_wage + cash_round);
        current_round++;
      }
      else {
        game_state = keno::State::END;
      }
    }
  }

  void GameManager::Render(void) {
    if (game_state == keno::State::WELCOME) {
      // Display a welcoming message.
      DisplayWelcome();
    }
    else if (game_state == keno::State::READING) {
      // Display a summary of information captured from the bet file.
      DisplaySummary();
    }
    else if (game_state == keno::State::PLAYING) {
      std::cout 
        << "\n" << "         --------------------------------------------------\n"
        << "         This is round #" << current_round << " of " << number_of_rounds << " and your wage is $" << cash_per_round << ". Good luck!\n"
        << "         The draw numbers are: [ ";
      for (keno::number_type i{0}; i < draw.size(); i++) {
        std::cout << draw[i] << " ";
      }
      std::cout 
        << "]\n\n"
        << "         You hit the following number(s) [ ";
      for (keno::number_type i{0}; i < hits.size(); i++) {
        std::cout << hits[i] << " ";
      }
      std::cout
        << "], a total of " << hits.size() << " hits out of " << player_bet.Size() << ".\n"
        << "         Payout rate is " << PAYOUT_TABLE[player_bet.Size() - 1][hits.size()] << ", thus you came out with: $" 
        << PAYOUT_TABLE[player_bet.Size() - 1][hits.size()] * cash_per_round << "\n"
        << "         Your net balance so far is: $" << player_bet.get_wage() << " dollars.";
    }
    else if (game_state == keno::State::END) {
      DisplayEnd();
    }
  }
  
  //============[ End GameManager class ]===============//

} // namespace Keno


