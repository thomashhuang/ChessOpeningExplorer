#include <fstream>
#include <iostream>
#include <PGNGameCollection.h>

#include "game_tree.h"
#include "game_traversal.h"

using namespace pgn;
using namespace chess;

int main() {

  GameCollection games;

  try {
    std::ifstream caruana("games/caruana.pgn");

    caruana >> games;

    caruana.close();
  }
  catch (std::exception& e) {
    return -1;
  }

  GameTree* tree = new GameTree(games);

  GameTraversal t(*tree);

  std::cout << "Caruana games: Results white black draw" << std::endl;
  std::cout << t.GetWhiteWins() << " " << t.GetBlackWins() << " " << t.GetDraws() << std::endl;

  t.push_back("e4");
  t.push_back("e5");

  std::cout << "After 1.e4 e5" << std::endl;
  std::cout << t.GetWhiteWins() << " " << t.GetBlackWins() << " " << t.GetDraws() << std::endl;
  
  delete tree;

  return 0;
}
