#include <vector>
#include <map>
#include <PNGPly.h>
#include <PGNGameCollection.h>
#include <PGNGame.h>

namespace chess {
  class GameTree {
    private:
      struct TreeNode {
        pgn::Ply ply_;
        unsigned white_wins_;
        unsigned black_wins_;
        unsigned draws_;
        std::map<std::string, TreeNode>* next_moves_;

        TreeNode();
        TreeNode(pgn::Ply ply);

        //Big 5
        TreeNode(const TreeNode& other);
        TreeNode(TreeNode&& other);
        ~TreeNode();
        TreeNode& operator=(const TreeNode& other);
        TreeNode& operator=(TreeNode&& other);

        void clear();

      };
      TreeNode root_;
      unsigned games_;

      TreeNode();
      /* Initialize the tree with a PNGGameCollection */
      TreeNode(const pgn::PGNGameCollection& games);

      /* Initialize the tree with an input stream to a pgn file */
      TreeNode(std::ifstream pgn_file);

      /* Add a single game to this Tree */
      void AddGame(const pgn::PGNGame& game);

  };
}
