#include <map>
#include <fstream>
#include <PGNPly.h>
#include <PGNMove.h>
#include <PGNMoveList.h>
#include <PGNGame.h>
#include <PGNGameCollection.h>
#include "game_tree.h"

using namespace pgn;
using namespace chess;

GameTree::TreeNode::TreeNode() : ply_(Ply()), white_wins_(0), black_wins_(0), draws_(0) {
  next_moves_ = new std::map<std::string, GameTree::TreeNode*>();
}

GameTree::TreeNode::TreeNode(Ply ply) : ply_(ply), white_wins_(0), black_wins_(0), draws_(0) {
  next_moves_ = new std::map<std::string, GameTree::TreeNode*>();
}

GameTree::TreeNode::TreeNode(const TreeNode& other)
    : ply_(other.ply_), white_wins_(other.white_wins_), black_wins_(other.black_wins_), draws_(other.draws_), next_moves_(other.next_moves_) {}

GameTree::TreeNode::TreeNode(TreeNode&& other) 
    : ply_(other.ply_), white_wins_(other.white_wins_), black_wins_(other.black_wins_), draws_(other.draws_), next_moves_(other.next_moves_) {
  other.white_wins_ = 0;
  other.black_wins_ = 0;
  other.draws_ = 0;
  other.next_moves_ = nullptr;
  }

GameTree::TreeNode::~TreeNode() {
  clear();
}

GameTree::TreeNode& GameTree::TreeNode::operator=(const TreeNode& other) {
  if (this != &other) {
    clear();
    ply_ = other.ply_;
    white_wins_ = other.white_wins_;
    black_wins_ = other.black_wins_;
    draws_ = other.draws_;
    next_moves_ = other.next_moves_;
  }
  return *this;
}

GameTree::TreeNode& GameTree::TreeNode::operator=(TreeNode&& other) {
  if (this != &other) {
    clear();
    ply_ = other.ply_;
    white_wins_ = other.white_wins_;
    black_wins_ = other.black_wins_;
    draws_ = other.draws_;
    next_moves_ = other.next_moves_;
    other.clear();
  }
  return *this;
}

void GameTree::TreeNode::clear() {
  white_wins_ = 0;
  black_wins_ = 0;
  draws_ = 0;
  delete next_moves_;
}

GameTree::TreeNode* GameTree::TreeNode::NextPosition(const Ply& ply) {
  if (next_moves_->find(ply.str()) == next_moves_->end()) { // Haven't seen this move before
    next_moves_->emplace(ply.str(), new GameTree::TreeNode(ply));
  }
  return (*next_moves_)[ply.str()];
}

GameTree::TreeNode* GameTree::TreeNode::PlayMove(const std::string& ply) {
  if (next_moves_->find(ply) != next_moves_->end()) {
    return next_moves_->at(ply);
  }
  return nullptr;
}

void GameTree::TreeNode::UpdateWins(GameResult result) {
  if (result.isWhiteWin()) {
    white_wins_++;
  } else if (result.isBlackWin()) {
    black_wins_++;
  } else {
    draws_++;
  }
}

GameTree::GameTree(GameCollection& games) {
  root_ = new TreeNode();
  for (GameCollection::iterator it = games.begin(); it != games.end(); it++) {
    AddGame(*it);
  }
}

GameTree::GameTree(std::ifstream& pgn_file) {
  root_ = new TreeNode();
  GameCollection collection;
  pgn_file >> collection;

  for (GameCollection::iterator it = collection.begin(); it != collection.end(); it++) {
    AddGame(*it);
  }
}

void GameTree::AddGame(const Game& game) {
  games_++;
  GameResult result = game.result();
  root_->UpdateWins(result);

  GameTree::TreeNode* current = root_;
  MoveList moves = game.moves();

  for (MoveList::iterator it = moves.begin(); it != moves.end(); it++) {
    //Parse white's move.
    Ply white_ply = it->white();
    current = current->NextPosition(white_ply);
    current->UpdateWins(result);

    //Parse black's move.
    Ply black_ply = it->black();
    current = current->NextPosition(black_ply);
    current->UpdateWins(result);
  }
}

size_t GameTree::size() const {
  return games_;
}
