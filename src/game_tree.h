#include <vector>
#include <map>
#include <PGNPly.h>
#include <PGNMove.h>
#include <PGNGameCollection.h>
#include <PGNGameResult.h>
#include <PGNGame.h>

namespace chess {
  class GameTree {
    private:
      struct TreeNode {
        /* The ply that this TreeNode represents */
        pgn::Ply ply_;
        unsigned white_wins_;
        unsigned black_wins_;
        unsigned draws_;
        /* All continuations that we have seen before, mapped from their algebraic notation to the next TreeNode */
        std::map<std::string, TreeNode*>* next_moves_;

        TreeNode();
        TreeNode(pgn::Ply ply);

        //Rule of 5
        TreeNode(const TreeNode& other);
        TreeNode(TreeNode&& other);
        ~TreeNode();
        TreeNode& operator=(const TreeNode& other);
        TreeNode& operator=(TreeNode&& other);

        /* Find the child of this node given a ply. Adds to next_moves_ if necessary */
        TreeNode* NextPosition(const pgn::Ply& ply);

        void UpdateWins(pgn::GameResult result);

        void clear();

      };
      TreeNode* root_;
      unsigned games_;

      /* Initialize the tree with a PNGGameCollection */
      GameTree(pgn::GameCollection& games);

      /* Initialize the tree with an input stream to a pgn file */
      GameTree(std::ifstream pgn_file);

      /* Add a single game to this Tree, updating all fields. */
      void AddGame(const pgn::Game& game);


  };
}
