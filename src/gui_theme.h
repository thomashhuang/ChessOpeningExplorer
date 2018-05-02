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

class MyGuiTheme : public ofxDatGuiTheme {
  public:
    MyGuiTheme() {
      font.size = 9;
      layout.width = 400.0f;
      init();
    }
};

#endif /* gui_theme_hpp */
