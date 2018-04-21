#include <fstream>
#include <iostream>
#include <PGNGameCollection.h>

int main() {
  try {
    std::ifstream caruana("games/Caruana.pgn");
    std::ifstream carlsen("games/Carlsen.pgn");
    pgn::GameCollection games;

    carlsen >> games;
    caruana >> games;

    std::cout << games.size() << std::endl;

    caruana.close();
    carlsen.close();
  }
  catch (std::exception& e) {
    return -1;
  }
  return 0;
}
