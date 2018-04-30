
#pragma once

#include "ofMain.h"
#include "ofImage.h"

class ofApp : public ofBaseApp{
  
  private:
    /** 
     * Black pieces are capital letters, white pieces are lower case.
     * Note that the dimensions are flipped, b5 corresponds to [5][2]
     */
    char board_[8][8] = {
      {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
      {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
    };

    /* Images of the pieces */
    ofImage p;
    ofImage r;
    ofImage k;
    ofImage b;
    ofImage q;
    ofImage k;
    ofImage P;
    ofImage R;
    ofImage K;
    ofImage B;
    ofImage Q;
    ofImage K;
    ofImage lightSquare;
    ofImage darkSquare;


    void buildImageMap();

	public:
		void setup();
		void update();
		void draw();

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
};

