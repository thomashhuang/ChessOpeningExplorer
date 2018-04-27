#ifndef GAME_TRAVERSAL_H
#define GAME_TRAVERSAL_H

#include <vector>

#include <PGNPly.h>

#include "game_tree.h"

namespace chess {
  class GameTraversal {
    private:
      GameTree::TreeNode* current_;
      std::vector<GameTree::TreeNode*> previous_nodes_;

    public:

      GameTraversal(GameTree& tree);

      /* Play a move. Returns false if the ply is not in the tree */
      bool push_back(pgn::Ply ply);

      /* Go back a ply in the traversal. */
      void pop_back();

      /* Get the current ply. */
      pgn::Ply operator*();

      unsigned GetWhiteWins();

      unsigned GetBlackWins();

      unsigned GetDraws();
  };
}

#endif
