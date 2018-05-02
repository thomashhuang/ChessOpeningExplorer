# CS 126 FinalProject
This is an OpenFrameworks application to analyze and review chess openings and player repertoire.

[pgnlib]: http://pgnlib.sourceforge.net/ "pgnlib"
[ofxDatGui]: https://github.com/braitsch/ofxDatGui "ofxDatGui"

## Libraries
[pgnlib] is used to import PGN files into memory, and the internal game tree data structure will organize the games in a way that can easily be traversed.
To install pgnlib, you will need to run the following in the pgnlib directory:
> ./configure  
> make  
> make install  

[ofxDatGui] is used for several UI elements.
To install ofxDatGui, clone the repo into your openFrameworks/addons directory, then copy the ofxbraitsch directory into bin/data. Run the project generator with ofxDatGui selected as an addon, then simply add:  
> #include "ofxDatGui.h"  
to ofApp.h.

## Classes
#### GameTree:  
This holds the internal structure that keeps track of all the positions, games, and results. It uses TreeNodes which represent a certain position and hold a Ply and a map of continuations from that particular position.  
  
#### GameTraversal:  
Used to traverse through the GameTree. It is constructed with a GameTree object and uses the method push_back(Ply) to traverse through the "database" represented by the GameTree. It also supports going back up the tree using pop_back().  

#### Communication:
UI and Model communicate through the GameTraversal, which will get continuations using GetContinuations, and will send the position to the UI using a pgn::Position object. The UI converts the Position object to FEN notation and draws the board from that.
