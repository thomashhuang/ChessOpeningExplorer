#include <vector>
#include <PGNPly.h>

#include "game_traversal.h"
#include "game_tree.h"

using namespace chess;
using namespace pgn;

GameTraversal::GameTraversal(GameTree& tree) {
  current_ = tree.root_;
}

bool GameTraversal::push_back(Ply ply) {
  if (current_->next_moves_->find(ply.str()) != current_->next_moves_->end()) {
    previous_nodes_.push_back(current_);
    current_ = current_->next_moves_->at(ply.str()); // move down the tree
    return true;
  }
  return false;
}

void GameTraversal::pop_back() {
  if (previous_nodes_.size() > 0) {
    current_ = previous_nodes_[previous_nodes_.size() - 1];
    previous_nodes_.pop_back();
  }
}

Ply GameTraversal::operator*() {
  return current_->ply_;
}

unsigned GameTraversal::GetWhiteWins() {
  return current_->white_wins_;
}

unsigned GameTraversal::GetBlackWins() {
  return current_->black_wins_;
}

unsigned GameTraversal::GetDraws() {
  return current_->draws_;
}
