#include <fstream>
#include <iostream>
#include <PGNGameCollection.h>
#include <PGNPly.h>
#include <PGNSquare.h>
#include <PGNPosition.h>

#include "game_tree.h"
#include "game_traversal.h"
#include "ofApp.h"
#include "ofMain.h"



using namespace pgn;
using namespace chess;

int main() {

  ofSetupOpenGL(1024, 768, OF_WINDOW);
  /*
  GameCollection games;

  try {
    std::ifstream game("games/sample.pgn");

    game >> games;

    game.close();
  }
  catch (std::exception& e) {
    return -1;
  }

  GameTree* tree = new GameTree(games);

  GameTraversal t(*tree);

  t.push_back("d4");

  Position p = t.GetPosition();
  std::cout << p.fen() << std::endl;


  delete tree;
   */
  ofRunApp(new ofApp());

  return 0;
  
}
