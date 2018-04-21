#include <map>
#include <PGNPly.h>
#include "game_tree.h"

using namespace pgn;

chess::TreeNode::TreeNode() : ply_(Ply()), white_wins_(0), black_wins_(0), draws_(0) {
  next_moves_ = new std::map(std::string, TreeNode);
}

chess::TreeNode::TreeNode(Ply ply) : ply_(ply), white_wins_(0), black_wins_(0), draws_(0) {
  next_moves_ = new std::map(std::string, TreeNode);
}

chess::TreeNode::TreeNode(const TreeNode& other)
    : ply_(other.ply_), white_wins_(other.white_wins_), black_wins_(other.black_wins_), draws_(other.draws), next_moves_(other.next_moves_) {}

chess::TreeNode::TreeNode(TreeNode&& other) 
    : ply_(other.ply_), white_wins_(other.white_wins_), black_wins_(other.black_wins_), draws_(other.draws), next_moves_(other.next_moves_) {
  other.ply_ = NULL;
  other.white_wins_ = 0;
  other.black_wins_ = 0;
  other.draws_ = 0;
  other.next_moves_ = nullptr;
  }

chess::TreeNode::~TreeNode() {
  clear();
}

chess::TreeNode& chess::TreeNode::operator=(const TreeNode& other) {
  if (this != &other) {
    clear();
    ply_ = other.ply_;
    white_wins_ = other.white_wins_;
    black_wins_ = other.black_wins_;
    draws_ = other.draws_;
    next_moves_ = other.next_moves_;
  }
}

chess::TreeNode& chess::TreeNode::operator=(TreeNode&& other) {
  if (this != &other) {
    clear();
    ply_ = other.ply_;
    white_wins_ = other.white_wins_;
    black_wins_ = other.black_wins_;
    draws_ = other.draws_;
    next_moves_ = other.next_moves_;
    other.clear();
  }
}

void chess::TreeNode::clear() {
  ply_ = NULL;
  white_wins_ = 0;
  black_wins_ = 0;
  draws_ = 0;
  delete next_moves_;
}

