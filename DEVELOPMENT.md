1. Installed pgnlib for parsing pgn files. Needed to run ./configure, make, and make install to get the library working.

2. Have a tree structure that emulates the "tree" of possible chess games, with each node representing a ply (half of a move). Each node stores the most recent ply as well as a map of pointers for next moves.
Memory may still be leaking, need to look into cleaning that up and implementing the rule of 5 for the entire tree.

3. Figuring out a way to traverse through the tree node-by-node without exposing the internal structure was something I haven't thought about. I have added a GameTraversal class which is a friend of GameTree which holds a current node and can move through the tree without exposing the internal implementation.

4. Tests have been added to make sure the tree is being constructed as expected and game counts/results are all correct.

5. Added a Position field to the TreeNodes, so the nodes now keep track of the current position. This should simplify drawing the position in the app, and communication through FEN notation should work well.

6. Position field in TreeNodes is now tested, fixed a bug where Positions were not updating properly.

7. Splitting drawing stage into several parts: DrawBoard, DrawPosition, and DrawButtons. Board simply draws alternating colored squares in an 8x8. Position takes in a pgn::Position object, converts to FEN notation, then draws the pieces onto the board. Buttons will find the continuations in the tree and draw a button for each.

8. Added more UI elements including the current position's statistics and a movelist.
