# Project Proposal
## Chess Opening Explorer

[pgnlib]: http://pgnlib.sourceforge.net/ "pgnlib"
[pgnmentor]: http://www.pgnmentor.com/files.html "pgnmentor"
[365chess]: https://www.365chess.com/opening.php "365chess"
[stockfish]: https://stockfishchess.org/download/ "Stockfish"
Given a database of PGN files of chess games, provide an interface to load all the games and play a series of moves on a digital chessboard, then see which games in the database had that sequence, and be able to look up information about those games.
PGN files look like the following:
> [Event "Match 3"]
> [Site "London ENG"]
> [Date "1834.??.??"]
> [Round "3"]
> [White "De la Bourdonnais, Louis C"]
> [Black "MacDonnell, Alexander"]
> [Result "1-0"]
> [ECO "D20g"]
> 
> 1.d4 d5 2.c4 dxc4 3.e3 e5 4.Bxc4 exd4 5.exd4 Nf6 6.Nc3 Be7 
> 7.Nf3 O-O 8.h3 Nbd7 9.Be3 Nb6 10.Bb3 c6 11.O-O Nfd5 12.Qe2 
> f5 13.Rae1 g5 14.Bd2 Bf6 15.Ne5 Qe8 16.f4 g4 17.hxg4 fxg4 
> 18.f5 Qh5 19.Bc2 Qh4 20.Qe4 Kh8 21.Nxg4 Nc4 22.Nxf6 Qxf6 
> 23.Nxd5 cxd5 24.Qf4 Nxd2 25.Qxd2 Bd7 26.Re5 Rg8 27.Rfe1 Qh4 
> 28.R1e2 Bb5 29.Rf2 Rg4 30.f6 Rxd4 31.Qe3 Rg4 32.Re7 d4 
> 33.Qe5 Rg5 34.f7+ Rxe5 35.f8=Q+ Rxf8 36.Rxf8# 1-0

#### Libraries/Resources
There is a library for parsing through PGN files called [pgnlib], which can be used to generate C++ objects corresponding to moves, positions, squares, etc... I will use this, and possibly design a tree data structure in order to load the games into memory in a way that is usable. Large databases of PGN files, containing thousands of high level games are readily available, for example at [pgnmentor]. 
#### Design
The application window will contain a chessboard where the user can play moves. On the side of the board, there will be a table which shows the most common moves, their probabilities, and the outcomes of the games with those probabilities (white win, draw, black win). This should replicate an opening explorer like ones available at websites such as [365chess], but for custom databases.
I can potentially use a custom-made tree, where nodes represent moves and each node has a vector of subtrees which represent all the possible moves that can be made from a certain position. The nodes will hold the statistics for the current position (games played, white wins, draws, black wins) so the data can quickly be looked up at any time. I could also attempt to integrate an open-source chess engine such as [stockfish], which is written in C++, into my app to allow an engine to give an objective evaluation of a position as well.
#### Potential Issues
Potential difficulties with this approach include transpositions (where the same position arises from different move orders), which would cause issues with my data structure. Also, making the chessboard itself respond to user input in a way that feels natural may be difficult to do (clicking and dragging pieces? clicking piece to move and destination square? selecting a move from a list?). If I allow the user to play the moves themselves, instead of picking the moves from a list, there may need to be a way to detect legal/illegal moves, which becomes yet another task to handle. Integrating [stockfish] may require me to design some interface from my representation of the chessboard to something the engine can understand. On the other hand, it is written in C++ which makes things slightly easier. 
