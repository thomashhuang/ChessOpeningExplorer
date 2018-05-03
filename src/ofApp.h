
#pragma once

#include <map>

#include <PGNPosition.h>

#include "game_tree.h"
#include "game_traversal.h"
#include "ofMain.h"
#include "ofImage.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp {
  
  private:

    /**
     * Images of the pieces
     * The names of these variables match FEN notation.
     * Capital letters are white pieces, lower case are black.
     */
    ofImage p;
    ofImage r;
    ofImage n;
    ofImage b;
    ofImage q;
    ofImage k;
    ofImage P;
    ofImage R;
    ofImage N;
    ofImage B;
    ofImage Q;
    ofImage K;
    ofImage light_square;
    ofImage dark_square;

    ofSoundPlayer move;
    ofSoundPlayer capture;
    ofSoundPlayer check;
    
    std::map<char, ofImage> piece_map_;

    chess::GameTree* tree_;
    
    chess::GameTraversal* trav_;
    
    /* Gui containing current position's statistics and continuations. */
    ofxDatGui* move_panel_;
    
    /* Gui containing notes controls */
    ofxDatGui* notes_;
    
    /* Gui for uploading games to the app */
    ofxDatGui* upload_panel_;
    
    ofxDatGuiLabel* upload_status_;

    /* Build the map from character representing the piece to the piece image */
    void BuildImageMap();
    
    /* Load the images of the pieces */
    void LoadPieces();
    
    /* Draw the squares */
    void DrawBoard();
    
    /* Draw the pieces on the board */
    void DrawPosition(pgn::Position position);
    
    /* Get the continuations in the current position and create the GUI */
    void DrawMovePanel();
    
    /* Create the panel for taking notes */
    void CreateNotesPanel();
    
    /* Create the panel for uploading games to the app */
    void CreateUploadGamesPanel();
    
    /* Click on a move */
    void MoveClick(ofxDatGuiDropdownEvent e);
    
    /* Click back or reset */
    void BackClick(ofxDatGuiButtonEvent e);
    
    /* Get the text from the note and note_name text fields and save to bin/data/notes/file */
    void SaveNote(ofxDatGuiButtonEvent e);
    
    /* Uplaod a PGN to the game, adding each game to the tree */
    void UploadPGNFile(ofxDatGuiButtonEvent e);

	public:
		void setup();
		void update();
		void draw();

};

