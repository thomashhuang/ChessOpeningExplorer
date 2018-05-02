//
//  gui_theme.hpp
//  ChessOpeningExplorer
//
//  Created by Thomas Huang on 5/2/18.
//

#ifndef gui_theme_hpp
#define gui_theme_hpp

#include <stdio.h>

#include "ofxDatGui.h"

class MovePanelTheme : public ofxDatGuiTheme {
  public:
    MovePanelTheme() {
      font.size = 8;
      layout.width = 375.0f;
      init();
    }
};

class FolderTheme : public ofxDatGuiTheme {
  public:
    FolderTheme() {
      font.size = 8;
      layout.width = 480.0f;
      init();
    }
};

class LargeTextInputTheme : public ofxDatGuiTheme {
  public:
    LargeTextInputTheme() {
      font.size = 8;
      layout.width = 480.0f;
      layout.height = 100.0f;
      init();
    }
};

#endif /* gui_theme_hpp */
