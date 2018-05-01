#include <map>
#include <PGNPosition.h>
#include <iostream>
#include "ofApp.h"
#include "ofxGui.h"

#define BOARD_TOP_LEFT_X 50
#define BOARD_TOP_LEFT_Y 50
#define SQUARE_SIZE 60


void ofApp::BuildImageMap() {

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
        ofImage piece = piece_map.at(piece_grid[x_square][y_square]); // image of the piece.
        piece.draw(x, y, SQUARE_SIZE, SQUARE_SIZE);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::setup() {
  p.load("bp.png");
  r.load("br.png");
  n.load("bn.png");
  b.load("bb.png");
  q.load("bq.png");
  k.load("bk.png");
  P.load("wp.png");
  R.load("wr.png");
  N.load("wn.png");
  B.load("wb.png");
  Q.load("wq.png");
  K.load("wk.png");
  light_square.load("l.jpg");
  dark_square.load("d.png");

  move.load("move.wav");
  check.load("check.wav");
  capture.load("capture.mp3");
  
  piece_map.emplace('p', p);
  piece_map.emplace('r', r);
  piece_map.emplace('n', n);
  piece_map.emplace('b', b);
  piece_map.emplace('q', q);
  piece_map.emplace('k', k);
  piece_map.emplace('P', P);
  piece_map.emplace('R', R);
  piece_map.emplace('N', P);
  piece_map.emplace('B', B);
  piece_map.emplace('Q', Q);
  piece_map.emplace('K', K);
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
  DrawBoard();
  pgn::Position p;
  DrawPosition(p);
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
