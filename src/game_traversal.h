#ifndef GAME_TRAVERSAL_H
#define GAME_TRAVERSAL_H

#include <vector>
#include <cmath>

#include <PGNPly.h>

#include "game_tree.h"

namespace chess {
  class GameTraversal {
    private:
      GameTree::TreeNode* current_;
      std::vector<GameTree::TreeNode*> previous_nodes_;

    public:

      struct Results {
        unsigned white_wins;
        unsigned black_wins;
        unsigned draws;
        unsigned games;
        double white_pct;
        double black_pct;
        double draw_pct;
        Results(unsigned white, unsigned black, unsigned draws) 
          : white_wins(white), black_wins(black), draws(draws), games(white + black + draws) {
            white_pct = float(white) / games * 100;
            black_pct = float(black) / games * 100;
            draw_pct = float(draws) / games * 100;
          }
      };

      GameTraversal(GameTree& tree);

      /* Play a move. Returns false if the ply is not in the tree */
      bool push_back(pgn::Ply ply);

      /* Play a move with a string representation. Like above */
      bool push_back(std::string ply);

      /* Go back a ply in the traversal. */
      void pop_back();

      /* Get the number of games at this position. */
      size_t size();

      /* Get all known responses to the current move. */
      std::vector<std::string> GetContinuations();

      /* Get the ply object for the current node. */
      pgn::Ply GetPly();

      /* Get the position object for the current node. */
      pgn::Position GetPosition();
      
      std::vector<std::string> GetMoveList();

      /* Get the current ply. */
      pgn::Ply operator*();

      unsigned GetWhiteWins();

      unsigned GetBlackWins();

      unsigned GetDraws();

      /* Get a results object for a continuation from this position */
      Results GetResults(std::string ply);
  };
}

#endif
