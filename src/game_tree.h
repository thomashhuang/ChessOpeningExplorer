#ifndef GAME_TREE_H
#define GAME_TREE_H

#include <vector>
#include <map>

#include <PGNPly.h>
#include <PGNMove.h>
#include <PGNGameCollection.h>
#include <PGNGameResult.h>
#include <PGNGame.h>
#include <PGNPosition.h>

namespace chess {
  class GameTree {

    friend class GameTraversal;

    private:
      struct TreeNode {
        /* The ply that this TreeNode represents */
        pgn::Ply ply_;
        /* The current position */
        pgn::Position position_;
        unsigned white_wins_;
        unsigned black_wins_;
        unsigned draws_;
        /* All continuations that we have seen before, mapped from their algebraic notation to the next TreeNode */
        std::map<std::string, TreeNode*>* next_moves_;

        TreeNode();
        TreeNode(pgn::Ply ply, pgn::Position position);

        //Rule of 5
        TreeNode(const TreeNode& other);
        TreeNode(TreeNode&& other);
        ~TreeNode();
        TreeNode& operator=(const TreeNode& other);
        TreeNode& operator=(TreeNode&& other);

        /* Update the results of this TreeNode */
        void UpdateWins(pgn::GameResult result);

        /* Find the child of this node given a ply. Adds to next_moves_ if necessary */
        TreeNode* NextPosition(pgn::Ply& ply, pgn::Position& position);

        /* Clear all data in this node and its children */
        void clear();

      };
      TreeNode* root_;
      size_t games_;

    public:
      /* Initialize the tree with a PNGGameCollection */
      GameTree(pgn::GameCollection& games);

      /* Initialize the tree with an input stream to a pgn file */
      GameTree(std::ifstream& pgn_file);

      /* Add a single game to this Tree, updating all fields. */
      void AddGame(const pgn::Game& game);

      /* Get the number of games in this tree. */
      size_t size() const;


  };
}

#endif
