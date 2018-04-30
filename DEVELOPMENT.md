1. Installed pgnlib for parsing pgn files. Needed to run ./configure, make, and make install to get the library working.

2. Have a tree structure that emulates the "tree" of possible chess games, with each node representing a ply (half of a move). Each node stores the most recent ply as well as a map of pointers for next moves.
Memory may still be leaking, need to look into cleaning that up and implementing the rule of 5 for the entire tree.

3. Figuring out a way to traverse through the tree node-by-node without exposing the internal structure was something I haven't thought about. I have added a GameTraversal class which is a friend of GameTree which holds a current node and can move through the tree without exposing the internal implementation.

4. Tests have been added to make sure the tree is being constructed as expected and game counts/results are all correct.

5. Added a Position field to the TreeNodes, so the nodes now keep track of the current position. This should simplify drawing the position in the app, and communication through FEN notation should work well.

6. Position field in TreeNodes is now tested, fixed a bug where Positions were not updating properly.
