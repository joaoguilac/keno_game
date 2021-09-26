/*!
 * @brief This program implements the Keno game.
 *
 * @author João Pedro Fonseca Dantas
 * @author João Guilherme Alves Lopes da Costa
 * @file main.cpp
 */

#include <cstdlib> // EXIT_SUCCESS

#include "keno_common.h"
#include "game_manager.h"
#include "keno_bet.h"

int main(int argc, char *argv[]) {
  keno::GameManager game;

  game.Initialize(argc, argv);

  // Keep running until the game ends or an error occurs.
  while (not game.GameOver()) {
    game.ProcessEvents();
    game.Update();
    game.Render();
  }

  return EXIT_SUCCESS;
}
