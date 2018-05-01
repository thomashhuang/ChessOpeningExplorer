
#pragma once

#include <map>
#include <PGNPosition.h>
#include "game_tree.h"
#include "ofMain.h"
#include "ofImage.h"

class ofApp : public ofBaseApp{
  
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
    
    std::map<char, ofImage> piece_map;

    chess::GameTree* tree;

    void BuildImageMap();
    
    /* Draw the squares */
    void DrawBoard();
    
    /* Draw the pieces on the board */
  void DrawPosition(pgn::Position position);

	public:
		void setup();
		void update();
		void draw();

  /*
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
   */
};

