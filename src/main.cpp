#include <fstream>
#include <iostream>
#include <PGNGameCollection.h>
#include "game_tree.h"

using namespace pgn;
using namespace chess;

int main() {

  GameCollection games;

  try {
    std::ifstream caruana("games/Caruana.pgn");
    std::ifstream carlsen("games/Carlsen.pgn");

    carlsen >> games;
    caruana >> games;

    caruana.close();
    carlsen.close();
  }
  catch (std::exception& e) {
    return -1;
  }
  GameTree* tree = new GameTree(games);

  std::cout << tree->size() << std::endl;


  return 0;
}
