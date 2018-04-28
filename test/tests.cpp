#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <iostream>
#include <fstream>

#include <PGNGameCollection.h>

#include "../src/game_tree.h"
#include "../src/game_traversal.h"

using namespace chess;
using namespace pgn;

TEST_CASE("GameTree::single_game_size") {
  std::ifstream s("games/sample.pgn");
  GameTree t(s);
  REQUIRE(t.size() == 1);
  s.close();
}

TEST_CASE("GameTree::single_game_creation") {
  std::ifstream s("games/sample.pgn");
  GameTree t(s);
  GameTraversal trav(t);
  REQUIRE(trav.GetBlackWins() == 1);
  REQUIRE(trav.GetWhiteWins() == 0);
  REQUIRE(trav.GetDraws() == 0);
  s.close();
}

TEST_CASE("GameTree::single_game_content") {
  std::ifstream s("games/sample.pgn");
  GameTree t(s);
  GameTraversal trav(t);
  std::vector<std::string> moves = {"d4", "Nf6", "c4", "e6", "g3", "d5", "Bg2", "Be7", "Nf3", "O-O"};
  for (std::string ply : moves) {
    REQUIRE(trav.push_back(ply));
  }
}

TEST_CASE("GameTree::single_game_incorrect_content") {
  std::ifstream s("games/sample.pgn");
  GameTree t(s);
  GameTraversal trav(t);
  std::string wrong_move = "e4";
  REQUIRE(!trav.push_back(wrong_move));
}

TEST_CASE("GameTree::large_database_size") {
  std::ifstream s("games/Caruana.pgn");
  GameCollection c;
  s >> c;
  GameTree* t = new GameTree(c);
  REQUIRE(t->size() == c.size());
  delete t;
  s.close();
}
