//
//  Player.hpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Piece.hpp"
#include <iostream>
#include <vector>

namespace ECE141 {
  
  class Game; //forward declare...  

  struct MoveOption {
      const Piece* piece;
      Location      location;
      int           score;
      MoveOption(const Piece* aPiece, Location aLocation, int aScore) : piece(aPiece), location(aLocation), score(aScore){}

  };
  
  class Player {
  public:
                      Player();
    virtual bool      takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog);
    const Tile* const getForwardLeftTile(Game& aGame, const Piece* thePiece);
    const Tile* const getForwardRightTile(Game& aGame, const Piece* thePiece);
    const Tile* const getDubForwardLeftTile(Game& aGame, const Piece* thePiece);
    const Tile* const getDubForwardRightTile(Game& aGame, const Piece* thePiece);
    const Tile* const getBackwardLeftTile(Game& aGame, const Piece* thePiece);
    const Tile* const getBackwardRightTile(Game& aGame, const Piece* thePiece);
    const Tile* const getDubBackwardLeftTile(Game& aGame, const Piece* thePiece);
    const Tile* const getDubBackwardRightTile(Game& aGame, const Piece* thePiece);
    bool isOppLastRow(Location aLocation, const Piece* thePiece);
    bool canPawnBeJumped(Game& aGame, const Piece* thePiece, Location aLocation);
    bool pawnHasDubJump(Game& aGame, const Piece* thePiece, Location aLocation);
    int incForLeftRow(const Piece* thePiece, int anInt);
    int incForLeftCol(const Piece* thePiece, int anInt);
    int incForRightRow(const Piece* thePiece, int anInt);
    int incForRightCol(const Piece* thePiece, int anInt);
    int incBackLeftRow(const Piece* thePiece, int anInt);
    int incBackLeftCol(const Piece* thePiece, int anInt);
    int incBackRightRow(const Piece* thePiece, int anInt);
    int incBackRightCol(const Piece* thePiece, int anInt);
    Location getNextJumpLocation(Game& aGame, const Piece* thePiece);
    const PieceColor  color;
    static int        pcount; //how many created so far?
  };

  class JaredVPlayer : public Player {
  public:
      
  };
}

#endif /* Player_hpp */
