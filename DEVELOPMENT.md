1. Installed pgnlib for parsing pgn files. Needed to run ./configure, make, and make install to get the library working.

2. Have a tree structure that emulates the "tree" of possible chess games, with each node representing a ply (half of a move). Each node stores the most recent ply as well as a map of pointers for next moves.
Memory may still be leaking, need to look into cleaning that up and implementing the rule of 5 for the entire tree.