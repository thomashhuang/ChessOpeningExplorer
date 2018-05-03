#include <map>
#include <iostream>
#include <fstream>

#include <PGNPosition.h>
#include <PGNGameCollection.h>
#include <PGNGame.h>
#include <PGNPly.h>

#include "game_tree.h"
#include "game_traversal.h"
#include "ofApp.h"
#include "ofxGui.h"
#include "gui_themes.h"

#define BOARD_TOP_LEFT_X 50
#define BOARD_TOP_LEFT_Y 50
#define SQUARE_SIZE 60
#define PANEL_TOP_LEFT_X 600
#define PANEL_TOP_LEFT_Y 50
#define NOTES_TOP_LEFT_X 50
#define NOTES_TOP_LEFT_Y 600

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

void ofApp::DrawMovePanel() {
  if (move_panel_ != nullptr) {
    move_panel_->setVisible(false);
  }
  
  move_panel_ = new ofxDatGui(PANEL_TOP_LEFT_X, PANEL_TOP_LEFT_Y);
  
  move_panel_->setTheme(new MovePanelTheme());
  
  // Back button and continuation parsing.
  move_panel_->addButton("back");
  
  move_panel_->addButton(("reset"));
  
  move_panel_->addBreak()->setHeight(15.0f);
    
  std::vector<std::string> continuations = trav_->GetContinuations();
  
  std::vector<std::string> button_labels;
  
  for (std::string move : continuations) {
    GameTraversal::Results r = trav_->GetResults(move);
    std::ostringstream label_stream;
    label_stream << move << " | " << r.games << " | " << r.white_pct << "% | " << r.draw_pct << "% | " << r.black_pct << "%";
    button_labels.push_back(label_stream.str());
  }
  
  // Dropdown panel for continuations.
  ofxDatGuiDropdown* moves = move_panel_->addDropdown("Moves | Games | White Wins | Draws | Black Wins", button_labels);
  moves->expand();
  
  move_panel_->onDropdownEvent(this, &ofApp::MoveClick);
  move_panel_->onButtonEvent(this, &ofApp::BackClick);
  
  GameTraversal::Results current_position_results = trav_->GetResults("");
  
  move_panel_->addBreak()->setHeight(15.0f);
  
  // Add labels for current positions results:
  std::stringstream games_message;
  games_message << "Games: " << current_position_results.games;
  move_panel_->addLabel(games_message.str());
  
  std::stringstream white_wins_message;
  white_wins_message << "White Wins: " << current_position_results.white_pct << "%";
  move_panel_->addLabel(white_wins_message.str());
  
  std::stringstream draws_message;
  draws_message << "Draws: " << current_position_results.draw_pct << "%";
  move_panel_->addLabel(draws_message.str());
  
  std::stringstream black_wins_message;
  black_wins_message << "Black Wins: " << current_position_results.black_pct << "%";
  move_panel_->addLabel(black_wins_message.str());

}

void ofApp::CreateNotesPanel() {
  notes_ = new ofxDatGui(NOTES_TOP_LEFT_X, NOTES_TOP_LEFT_Y);
  notes_->setTheme(new NotesTheme());
  
  notes_->addButton("Save Note");
  notes_->addTextInput("Note Name:");
  
  notes_->addTextInput("Notes:");
  
  notes_->onButtonEvent(this, &ofApp::SaveNote);
}

void ofApp::CreateUploadGamesPanel() {
  upload_panel_ = new ofxDatGui(PANEL_TOP_LEFT_X, NOTES_TOP_LEFT_Y);
  upload_panel_->setTheme(new UploadPanelTheme());
  
  upload_panel_->addButton("Upload");
  upload_panel_->addTextInput("data/games/");
  
  upload_status_ = upload_panel_->addLabel("No Games Uploaded");
  
  upload_panel_->onButtonEvent(this, &ofApp::UploadPGNFile);
}

/* EVENT METHODS */

void ofApp::MoveClick(ofxDatGuiDropdownEvent e) {
  std::string label = e.target->getLabel();
  trav_->push_back(label.substr(0, label.find('|') - 1));
  
  // Sounds when a move is clicked
  if (label.find('+') != label.npos || label.find('#') != label.npos) { // check or checkmate
    check.play();
    
  } else if (label.find('x') != label.npos) { // capture
    capture.play();
    
  } else { // regular move
    move.play();
  }
  
  DrawMovePanel();
}

void ofApp::BackClick(ofxDatGuiButtonEvent e) {
  if (e.target->getLabel() == "back") {
    trav_->pop_back();

  } else if (e.target->getLabel() == "reset") {
    delete trav_;
    trav_ = new GameTraversal(*tree_ );
  }
  DrawMovePanel();
}

void ofApp::SaveNote(ofxDatGuiButtonEvent e) {
  if (e.target->getLabel() == "Save Note") {
    std::string note_name = notes_->getTextInput("Note Name:")->getText();
    std::string note = notes_->getTextInput("Notes:")->getText();
  
    if (note_name != "" && note != "") {
      std::string path_to_file = "../../../data/notes/" + note_name;
      std::ofstream f(path_to_file);
      //Write movelist?...
      f << note << std::endl;
    
      // clear the text inputs
      notes_->getTextInput("Note Name:")->setText("");
      notes_->getTextInput("Notes:")->setText("");
      f.close();
    }
  }
}

void ofApp::UploadPGNFile(ofxDatGuiButtonEvent e) {

  std::string file_name = upload_panel_->getTextInput("data/games/")->getText();

  std::string path_to_file = "../../../data/games/" + file_name;
  std::ifstream pgn(path_to_file);
  
  GameCollection games;
  
  try {
    pgn >> games;

  } catch (exception& e) {
    upload_status_->setLabel("Invalid file.");
    return;
  }
  for (GameCollection::iterator it = games.begin(); it != games.end(); it++) {
    tree_->AddGame(*it);
  }
  std::stringstream message;
  message << "Added " << games.size() << " games.";
  upload_status_->setLabel(message.str());
  
  upload_panel_->getTextInput("data/games/")->setText("");
  
  DrawMovePanel();
  
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
  
  tree_ = new GameTree();
  trav_ = new GameTraversal(*tree_);
  
  
  CreateUploadGamesPanel();
  
  CreateNotesPanel();
  
  DrawMovePanel();
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
