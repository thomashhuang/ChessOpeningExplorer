#include <map>
#include <iostream>
#include <fstream>

#include <PGNPosition.h>
#include <PGNPly.h>

#include "game_tree.h"
#include "game_traversal.h"
#include "ofApp.h"
#include "ofxGui.h"

#define BOARD_TOP_LEFT_X 50
#define BOARD_TOP_LEFT_Y 50
#define SQUARE_SIZE 60
#define PANEL_TOP_LEFT_X 600
#define PANEL_TOP_LEFT_Y 100

using namespace chess;
using namespace pgn;

void ofApp::BuildImageMap() {
  piece_map_.emplace('p', p);
  piece_map_.emplace('r', r);
  piece_map_.emplace('n', n);
  piece_map_.emplace('b', b);
  piece_map_.emplace('q', q);
  piece_map_.emplace('k', k);
  piece_map_.emplace('P', P);
  piece_map_.emplace('R', R);
  piece_map_.emplace('N', N);
  piece_map_.emplace('B', B);
  piece_map_.emplace('Q', Q);
  piece_map_.emplace('K', K);
}

void ofApp::LoadPieces() {
  p.load("icons/bp.png");
  r.load("icons/br.png");
  n.load("icons/bn.png");
  b.load("icons/bb.png");
  q.load("icons/bq.png");
  k.load("icons/bk.png");
  P.load("icons/wp.png");
  R.load("icons/wr.png");
  N.load("icons/wn.png");
  B.load("icons/wb.png");
  Q.load("icons/wq.png");
  K.load("icons/wk.png");
}

void ofApp::DrawBoard() {
  for (int x_square = 0; x_square < 8; x_square++) {
    bool is_light_square = x_square % 2 == 0; //even columns start with light square
    int x = BOARD_TOP_LEFT_X + (x_square * SQUARE_SIZE);

    for (int y_square = 0; y_square < 8; y_square++) {
      int y = BOARD_TOP_LEFT_Y + (y_square * SQUARE_SIZE);

      if (is_light_square) {
        light_square.draw(x, y, SQUARE_SIZE, SQUARE_SIZE);
      } else {
        dark_square.draw(x, y, SQUARE_SIZE, SQUARE_SIZE);
      }
      is_light_square = !is_light_square; //flip the square color
    }
  }
}

void ofApp::DrawPosition(pgn::Position position) {
  std::string fen = position.fen();
  std::string pieces = fen.substr(0, fen.find(' '));
  char piece_grid[8][8];
  int x = 0;
  int y = 0;
  for (char c : pieces) {
    if (c == '/') { // end of a rank
      x = 0;
      y++;
    } else if (c >= '0' && c <= '8') {
      int spaces = c - '0'; // convert number char to int;

      for (int i = 0; i < spaces; i++) { // insert empty squares in grid.
        piece_grid[x][y] = ' ';
        x++; // will never reach 8 with valid FEN.
      }
    } else { // a piece
      piece_grid[x][y] = c;
      x++;
    }
  }

  for (int y_square = 0; y_square < 8; y_square++) {
    int y = BOARD_TOP_LEFT_Y + (y_square * SQUARE_SIZE);

    for (int x_square = 0; x_square < 8; x_square++) {
      int x = BOARD_TOP_LEFT_X + (x_square * SQUARE_SIZE);

      if (piece_grid[x_square][y_square] != ' ') { // skip empty squares
        ofImage piece = piece_map_.at(piece_grid[x_square][y_square]); // image of the piece.
        piece.draw(x, y, SQUARE_SIZE, SQUARE_SIZE);
      }
    }
  }
}

void ofApp::SetUpMovePanel() {
  
  move_panel_ = new ofxDatGui(PANEL_TOP_LEFT_X, PANEL_TOP_LEFT_Y);
  
  move_panel_->addButton("back");
    
  std::vector<std::string> continuations = trav_->GetContinuations();
  
  for (std::string move : continuations) {
    GameTraversal::Results r = trav_->GetResults(move);
    std::ostringstream label_stream;
    label_stream << move << " | " << r.games << " | " << r.white_pct << "% | " << r.draw_pct << "% | " << r.black_pct << "%";
    move_panel_->addButton(label_stream.str());
  }

  move_panel_->onButtonEvent(this, &ofApp::MoveClick);
}

void ofApp::MoveClick(ofxDatGuiButtonEvent e) {
  std::string label = e.target->getLabel();
  if (label == "back") {
    trav_->pop_back();
  } else {
    trav_->push_back(label.substr(0, label.find('|') - 1));
  }
  SetUpMovePanel();
}

//--------------------------------------------------------------
void ofApp::setup() {

  light_square.load("icons/l.jpg");
  dark_square.load("icons/d.png");

  move.load("sounds/move.wav");
  check.load("sounds/check.wav");
  capture.load("sounds/capture.mp3");
  
  LoadPieces();
  BuildImageMap();
  
  std::ifstream game_stream("../../../data/games/Carlsen.pgn");
  
  
  tree_ = new GameTree(game_stream);
  trav_ = new GameTraversal(*tree_);
  
  SetUpMovePanel();
}

//--------------------------------------------------------------
void ofApp::update() {
  draw();
}

//--------------------------------------------------------------
void ofApp::draw(){
  DrawBoard();
  DrawPosition(trav_->GetPosition());
}

/*
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
*/
