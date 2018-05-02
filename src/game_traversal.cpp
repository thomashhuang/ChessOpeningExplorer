#include <vector>
#include <PGNPly.h>
#include <PGNPosition.h>

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

bool GameTraversal::push_back(std::string ply) {
  Ply p(ply);
  return push_back(p);
}

void GameTraversal::pop_back() {
  if (previous_nodes_.size() > 0) {
    current_ = previous_nodes_[previous_nodes_.size() - 1];
    previous_nodes_.pop_back();
  }
}

size_t GameTraversal::size() {
  return current_->white_wins_ + current_->black_wins_ + current_->draws_;
}

Ply GameTraversal::operator*() {
  return current_->ply_;
}

std::vector<std::string> GameTraversal::GetContinuations() {
  std::vector<std::string> continuations;
  for (auto it = current_->next_moves_->begin(); it != current_->next_moves_->end(); it++) {
    continuations.push_back(it->first);
  }
  return continuations;
}

Ply GameTraversal::GetPly() {
  return current_->ply_;
}

Position GameTraversal::GetPosition() {
  return current_->position_;
}

std::vector<std::string> GameTraversal::GetMoveList() {
    std::vector<std::string> move_list;
    for (GameTree::TreeNode* node : previous_nodes_) {
        move_list.push_back(node->ply_.str());
    }
    return move_list;
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
