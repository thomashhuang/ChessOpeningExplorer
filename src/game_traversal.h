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
  };
}

#endif
