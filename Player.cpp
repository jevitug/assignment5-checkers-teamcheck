//
//  Player.cpp
//  Checkers
//
//  Created by rick gessner on 2/22/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Player.hpp"
#include "Game.hpp"
#include <vector>

namespace ECE141 {
  
  int Player::pcount = 0; //init our static member to track # of players...
  
  static PieceColor autoColor() { //auto assigns a color
    return (++Player::pcount % 2) ? PieceColor::blue : PieceColor::gold;
  }
  
  Player::Player() : color(autoColor()) {}

  
 
  const Tile* const Player::getForwardLeftTile(Game& aGame, const Piece* thePiece) {
    int pieceCol = thePiece->getLocation().col;
    int pieceRow = thePiece->getLocation().row;
    if (thePiece->getColor() == PieceColor::blue) {
        return aGame.getTileAt(Location(pieceRow -1, pieceCol -1));
    }
    return aGame.getTileAt(Location(pieceRow + 1, pieceCol + 1));
  }

  const Tile* const Player::getBackwardRightTile(Game& aGame, const Piece* thePiece) {
      int pieceCol = thePiece->getLocation().col;
      int pieceRow = thePiece->getLocation().row;
      if (thePiece->getColor() == PieceColor::gold) {
          return aGame.getTileAt(Location(pieceRow - 1, pieceCol - 1));
      }
      return aGame.getTileAt(Location(pieceRow + 1, pieceCol + 1));
  }

  const Tile* const Player::getForwardRightTile(Game& aGame, const Piece* thePiece) {
      int pieceCol = thePiece->getLocation().col;
      int pieceRow = thePiece->getLocation().row;
      if (thePiece->getColor() == PieceColor::blue) {
          return aGame.getTileAt(Location(pieceRow - 1, pieceCol + 1));
      }
      return aGame.getTileAt(Location(pieceRow + 1, pieceCol - 1));
  }

  const Tile* const Player::getBackwardLeftTile(Game& aGame, const Piece* thePiece) {
      int pieceCol = thePiece->getLocation().col;
      int pieceRow = thePiece->getLocation().row;
      if (thePiece->getColor() == PieceColor::gold) {
          return aGame.getTileAt(Location(pieceRow - 1, pieceCol + 1));
      }
      return aGame.getTileAt(Location(pieceRow + 1, pieceCol - 1));
  }

  const Tile* const Player::getDubBackwardLeftTile(Game& aGame, const Piece* thePiece) {
      int pieceCol = thePiece->getLocation().col;
      int pieceRow = thePiece->getLocation().row;
      if (thePiece->getColor() == PieceColor::gold) {
          return aGame.getTileAt(Location(pieceRow - 2, pieceCol + 2));
      }
      return aGame.getTileAt(Location(pieceRow + 2, pieceCol - 2));
  }

  const Tile* const Player::getDubBackwardRightTile(Game& aGame, const Piece* thePiece) {
      int pieceCol = thePiece->getLocation().col;
      int pieceRow = thePiece->getLocation().row;
      if (thePiece->getColor() == PieceColor::gold) {
          return aGame.getTileAt(Location(pieceRow - 2, pieceCol - 2));
      }
      return aGame.getTileAt(Location(pieceRow + 2, pieceCol + 2));
  }

  const Tile* const Player::getDubForwardLeftTile(Game& aGame, const Piece* thePiece) {
      int pieceCol = thePiece->getLocation().col;
      int pieceRow = thePiece->getLocation().row;
      if (thePiece->getColor() == PieceColor::blue) {
          return aGame.getTileAt(Location(pieceRow - 2, pieceCol - 2));
      }
      return aGame.getTileAt(Location(pieceRow + 2, pieceCol + 2));
  }

  const Tile* const Player::getDubForwardRightTile(Game& aGame, const Piece* thePiece){
      int pieceCol = thePiece->getLocation().col;
      int pieceRow = thePiece->getLocation().row;
      if (thePiece->getColor() == PieceColor::blue) {
          return aGame.getTileAt(Location(pieceRow - 2, pieceCol + 2));
      }
      return aGame.getTileAt(Location(pieceRow + 2, pieceCol - 2));
  }

  //helper method to see if a piece at a location can be jumped by another pawn
  bool Player::canPawnBeJumped(Game& aGame, const Piece* thePiece, Location aLocation) {
      int newRow = aLocation.row;
      int newCol = aLocation.col;
      if (thePiece->getColor() == PieceColor::blue) {
          //check if top left to bottom right jump exists for blue
          if (aGame.getTileAt(Location(newRow - 1, newCol - 1)) && aGame.getTileAt(Location(newRow - 1, newCol - 1))->getPiece()) {
              const Piece* temp = aGame.getTileAt(Location(newRow - 1, newCol - 1))->getPiece();
              if (temp->getColor() != thePiece->getColor()) {
                  if (aGame.getTileAt(Location(newRow + 1, newCol + 1)) && !(aGame.getTileAt(Location(newRow + 1, newCol + 1))->getPiece())) {
                      return true;
                  }
              }
          }
          //check if top right to bottom left jump exists for blue
          if (aGame.getTileAt(Location(newRow - 1, newCol + 1)) && aGame.getTileAt(Location(newRow - 1, newCol + 1))->getPiece()) {
              const Piece* temp = aGame.getTileAt(Location(newRow - 1, newCol + 1))->getPiece();
              if (temp->getColor() != thePiece->getColor()) {
                  if (aGame.getTileAt(Location(newRow + 1, newCol - 1)) && !(aGame.getTileAt(Location(newRow + 1, newCol - 1))->getPiece())) {
                      return true;
                  }
              }
          }
          return false;
      }
      //otherwise piece is gold
      //check if bottom left to top right jump exists for gold
      if (aGame.getTileAt(Location(newRow + 1, newCol - 1)) && aGame.getTileAt(Location(newRow + 1, newCol - 1))->getPiece()) {
          const Piece* temp = aGame.getTileAt(Location(newRow + 1, newCol - 1))->getPiece();
          if (temp->getColor() != thePiece->getColor()) {
              if (aGame.getTileAt(Location(newRow - 1, newCol + 1)) && !(aGame.getTileAt(Location(newRow - 1, newCol + 1))->getPiece())) {
                  return true;
              }
          }
      }
      //check if bottom right to top left jump exists for gold
      if (aGame.getTileAt(Location(newRow + 1, newCol + 1)) && aGame.getTileAt(Location(newRow + 1, newCol + 1))->getPiece()) {
          const Piece* temp = aGame.getTileAt(Location(newRow + 1, newCol + 1))->getPiece();
          if (temp->getColor() != thePiece->getColor()) {
              if (aGame.getTileAt(Location(newRow - 1, newCol - 1)) && !(aGame.getTileAt(Location(newRow - 1, newCol - 1))->getPiece())) {
                  return true;
              }
          }
      }
      return false;
  }

  bool Player::isOppLastRow(Location aLocation, const Piece* thePiece) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (aLocation.row == 0);
      }
      return (aLocation.row == 7);
  }

  Location Player::getNextJumpLocation(Game& aGame, const Piece* thePiece) {
          //check forward left jump availability
          if (getForwardLeftTile(aGame, thePiece) && getDubForwardLeftTile(aGame, thePiece)) {
              if (getForwardLeftTile(aGame, thePiece)->getPiece()) {
                  const Piece* temp = getForwardLeftTile(aGame, thePiece)->getPiece();
                  if (temp->getColor() != thePiece->getColor() && !getDubForwardLeftTile(aGame, thePiece)->getPiece()) {
                      return getDubForwardLeftTile(aGame, thePiece)->getLocation();
                  }
              }
          }
          //check forward right jump availability
          if (getForwardRightTile(aGame, thePiece) && getDubForwardRightTile(aGame, thePiece)) {
              if (getForwardRightTile(aGame, thePiece)->getPiece()) {
                  const Piece* temp = getForwardRightTile(aGame, thePiece)->getPiece();
                  if (temp->getColor() != thePiece->getColor() && !getDubForwardRightTile(aGame, thePiece)->getPiece()) {
                      return getDubForwardRightTile(aGame, thePiece)->getLocation();
                  }
              }
          }
  }

  int Player::incForLeftRow(const Piece* thePiece, int anInt) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (anInt - 1);
      }
      return anInt + 1;
  }

  int Player::incForLeftCol(const Piece* thePiece, int anInt) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (anInt - 1);
      }
      return anInt + 1;
  }

  int Player::incForRightRow(const Piece* thePiece, int anInt) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (anInt - 1);
      }
      return anInt + 1;
  }
  int Player::incForRightCol(const Piece* thePiece, int anInt) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (anInt + 1);
      }
      return anInt - 1;
  }
  int Player::incBackLeftRow(const Piece* thePiece, int anInt) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (anInt + 1);
      }
      return anInt - 1;
  }
  int Player::incBackLeftCol(const Piece* thePiece, int anInt) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (anInt - 1);
      }
      return anInt + 1;
  }
  int Player::incBackRightRow(const Piece* thePiece, int anInt) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (anInt + 1);
      }
      return anInt - 1;
  }
  int Player::incBackRightCol(const Piece* thePiece, int anInt) {
      if (thePiece->getColor() == PieceColor::blue) {
          return (anInt + 1);
      }
      return anInt - 1;
  }

  //location parameter is location of piece after previous jump
  bool Player::pawnHasDubJump(Game& aGame, const Piece* thePiece, Location aLocation) {
      int newRow = aLocation.row;
      int newCol = aLocation.col;
      //blue pawns move bottom to top
      if (thePiece->getColor() == PieceColor::blue) {
        //check if jump to forward right exists
        if (aGame.getTileAt(Location(newRow - 1, newCol + 1)) && aGame.getTileAt(Location(newRow - 2, newCol + 2))) {
            if (aGame.getTileAt(Location(newRow - 1, newCol + 1))->getPiece()) {
                const Piece* temp = aGame.getTileAt(Location(newRow - 1, newCol + 1))->getPiece();
                if (temp->getColor() != thePiece->getColor() && !(aGame.getTileAt(Location(newRow - 2, newCol + 2))->getPiece())) {
                    return true;
                }
            }
        }
        //check if jump to forward left exists
        if (aGame.getTileAt(Location(newRow - 1, newCol - 1)) && aGame.getTileAt(Location(newRow - 2, newCol - 2))) {
            if (aGame.getTileAt(Location(newRow - 1, newCol - 1))->getPiece()) {
                const Piece* temp = aGame.getTileAt(Location(newRow - 1, newCol - 1))->getPiece();
                if (temp->getColor() != thePiece->getColor() && !(aGame.getTileAt(Location(newRow - 2, newCol - 2))->getPiece())) {
                    return true;
                }
            }
        }
        return false;
      }
      //gold pawns move bottom to top
      //check if jump to forward right exists
      if (aGame.getTileAt(Location(newRow + 1, newCol - 1)) && aGame.getTileAt(Location(newRow + 2, newCol - 2))) {
          if (aGame.getTileAt(Location(newRow + 1, newCol - 1))->getPiece()) {
              const Piece* temp = aGame.getTileAt(Location(newRow + 1, newCol - 1))->getPiece();
              if (temp->getColor() != thePiece->getColor() && !(aGame.getTileAt(Location(newRow + 2, newCol - 2))->getPiece())) {
                  return true;
              }
          }
      }
      //check if jump to forward left exists
      if (aGame.getTileAt(Location(newRow + 1, newCol + 1)) && aGame.getTileAt(Location(newRow + 2, newCol + 2))) {
          if (aGame.getTileAt(Location(newRow + 1, newCol + 1))->getPiece()) {
              const Piece* temp = aGame.getTileAt(Location(newRow + 1, newCol + 1))->getPiece();
              if (temp->getColor() != thePiece->getColor() && !(aGame.getTileAt(Location(newRow + 2, newCol + 2))->getPiece())) {
                  return true;
              }
          }
      }
      return false;
  }

  bool Player::takeTurn(Game &aGame, Orientation aDirection, std::ostream &aLog) {
    size_t theCount=aGame.countAvailablePieces(color);
    //container to hold jump move options
    std::vector<MoveOption> jumps;
    //container to hold non jump moves
    std::vector<MoveOption> steps;
    for(int pos=0;pos<theCount;pos++) {
      const Piece* thePiece = aGame.getAvailablePiece(color, pos);
      //if piece is pawn
      if (thePiece->getKind() == PieceKind::pawn) {
          //if forward left tile exists
          if (getForwardLeftTile(aGame, thePiece)) {
              //if forward left tile is occupied by piece
              if (getForwardLeftTile(aGame, thePiece)->getPiece()) {
                  //if this piece is of opposite color
                  if (getForwardLeftTile(aGame, thePiece)->getPiece()->getColor() != thePiece->getColor()) {
                      //if double forward left tile exists
                      if (getDubForwardLeftTile(aGame, thePiece)) {
                          //if double forward left tile is unnocupied
                          if (!(getDubForwardLeftTile(aGame, thePiece)->getPiece())) {
                              //check if double jump exists
                              if (pawnHasDubJump(aGame, thePiece, getDubForwardLeftTile(aGame, thePiece)->getLocation())) {
                                  jumps.push_back(MoveOption(thePiece, getDubForwardLeftTile(aGame, thePiece)->getLocation(), 7));
                              }
                              //add this jump to jumps vector
                              else{
                                jumps.push_back(MoveOption(thePiece, getDubForwardLeftTile(aGame, thePiece)->getLocation(), 5));
                              }
                          }
                      }
                  }
              }
              //if forward left tile is NOT occupied by piece
              else {
                  //if forward left tile is opponent's last row
                  if (isOppLastRow(getForwardLeftTile(aGame, thePiece)->getLocation(), thePiece)) {
                      //add this step (that would create a KING) to the steps vector
                      steps.push_back(MoveOption(thePiece, getForwardLeftTile(aGame, thePiece)->getLocation(), 3));
                  }
                  //if forward left is NOT opponent's last row
                  else {
                      if (canPawnBeJumped(aGame, thePiece, getForwardLeftTile(aGame, thePiece)->getLocation())) {
                          steps.push_back(MoveOption(thePiece, getForwardLeftTile(aGame, thePiece)->getLocation(), 1));
                      }
                      else {
                          steps.push_back(MoveOption(thePiece, getForwardLeftTile(aGame, thePiece)->getLocation(), 2));
                      }
                  }
              }
          }
          //CODE FOR RIGHT
          //if forward right tile exists
          if (getForwardRightTile(aGame, thePiece)) {
              //if forward right tile is occupied by piece
              if (getForwardRightTile(aGame, thePiece)->getPiece()) {
                  //if this piece is of opposite color
                  if (getForwardRightTile(aGame, thePiece)->getPiece()->getColor() != thePiece->getColor()) {
                      //if double forward right tile exists
                      if (getDubForwardRightTile(aGame, thePiece)) {
                          //if double forward right tile is unnocupied
                          if (!(getDubForwardRightTile(aGame, thePiece)->getPiece())) {
                              //check if double jump exists
                              if (pawnHasDubJump(aGame, thePiece, getDubForwardRightTile(aGame, thePiece)->getLocation())) {
                                  jumps.push_back(MoveOption(thePiece, getDubForwardRightTile(aGame, thePiece)->getLocation(), 7));
                              }
                              //add this jump to jumps vector
                              else {
                                  jumps.push_back(MoveOption(thePiece, getDubForwardRightTile(aGame, thePiece)->getLocation(), 5));
                              }
                          }
                      }
                  }
              }
              //if forward right tile is NOT occupied by piece
              else {
                  //if forward right tile is opponent's last row
                  if (isOppLastRow(getForwardRightTile(aGame, thePiece)->getLocation(), thePiece)) {
                      //add this step (that would create a KING) to the steps vector
                      steps.push_back(MoveOption(thePiece, getForwardRightTile(aGame, thePiece)->getLocation(), 3));
                  }
                  //if forward right is NOT opponent's last row
                  else {
                      if (canPawnBeJumped(aGame, thePiece, getForwardRightTile(aGame, thePiece)->getLocation())) {
                          steps.push_back(MoveOption(thePiece, getForwardRightTile(aGame, thePiece)->getLocation(), 1));
                      }
                      else{
                        steps.push_back(MoveOption(thePiece, getForwardRightTile(aGame, thePiece)->getLocation(), 2));
                      }
                  }
              }
          }

      }
      //else if piece is a KING
      else if (thePiece->getKind() == PieceKind::king) {
          //check if King has jumps
          //check forward left jump
          if (getForwardLeftTile(aGame, thePiece) && getDubForwardLeftTile(aGame, thePiece)) {
              //if forward left tile is occupied by a piece
              if (getForwardLeftTile(aGame, thePiece)->getPiece()) {
                  const Piece* temp = getForwardLeftTile(aGame, thePiece)->getPiece();
                  if (temp->getColor() != thePiece->getColor() && !getDubForwardLeftTile(aGame, thePiece)->getPiece()) {
                      //TODO implement king double jump logic
                      jumps.push_back(MoveOption(thePiece, getDubForwardLeftTile(aGame, thePiece)->getLocation(), 5));
                  }
              }
          }
          //check if forward left step exists
          if (getForwardLeftTile(aGame, thePiece)) {
              //if forward left tile isn't occupied
              if (!getForwardLeftTile(aGame, thePiece)->getPiece()) {
                  int score = 3;
                  int newRow = getForwardLeftTile(aGame, thePiece)->getLocation().row;
                  int newCol = getForwardLeftTile(aGame, thePiece)->getLocation().col;
                  //while next forward left tile exists and is unnocupied
                  while (aGame.getTileAt(Location(newRow + incForLeftRow(thePiece, newRow), newCol + incForLeftCol(thePiece, newCol)))
                      && !aGame.getTileAt(Location(newRow + incForLeftRow(thePiece, newRow), newCol + incForLeftCol(thePiece, newCol)))->getPiece()) {
                      newRow = newRow + incForLeftRow(thePiece, newRow);
                      newCol = newCol + incForLeftCol(thePiece, newCol);
                      score = score + 1;
                  }
                  steps.push_back(MoveOption(thePiece, Location(newRow, newCol), score));
              }
          }
          //check forward right jump
          if (getForwardRightTile(aGame, thePiece) && getDubForwardRightTile(aGame, thePiece)) {
              //if forward left tile is occupied by a piece
              if (getForwardRightTile(aGame, thePiece)->getPiece()) {
                  const Piece* temp = getForwardRightTile(aGame, thePiece)->getPiece();
                  if (temp->getColor() != thePiece->getColor() && !getDubForwardRightTile(aGame, thePiece)->getPiece()) {
                      //TODO implement king double jump logic
                      jumps.push_back(MoveOption(thePiece, getDubForwardRightTile(aGame, thePiece)->getLocation(), 5));
                  }
              }
          }
          //check if forward right step exists
          if (getForwardRightTile(aGame, thePiece)) {
              //if forward left tile isn't occupied
              if (!getForwardRightTile(aGame, thePiece)->getPiece()) {
                  int score = 3;
                  int newRow = getForwardRightTile(aGame, thePiece)->getLocation().row;
                  int newCol = getForwardRightTile(aGame, thePiece)->getLocation().col;
                  //while next forward left tile exists and is unnocupied
                  while (aGame.getTileAt(Location(newRow + incForRightRow(thePiece, newRow), newCol + incForRightCol(thePiece, newCol)))
                      && !aGame.getTileAt(Location(newRow + incForRightRow(thePiece, newRow), newCol + incForRightCol(thePiece, newCol)))->getPiece()) {
                      newRow = newRow + incForRightRow(thePiece, newRow);
                      newCol = newCol + incForRightCol(thePiece, newCol);
                      score = score + 1;
                  }
                  steps.push_back(MoveOption(thePiece, Location(newRow, newCol), score));
              }
          }
          //check backward left jump
          if (getBackwardLeftTile(aGame, thePiece) && getDubBackwardLeftTile(aGame, thePiece)) {
              if (getBackwardLeftTile(aGame, thePiece)->getPiece()) {
                  const Piece* temp = getBackwardLeftTile(aGame, thePiece)->getPiece();
                  if (temp->getColor() != thePiece->getColor() && !getDubBackwardLeftTile(aGame, thePiece)->getPiece()) {
                      //TODO implement king double jump logic
                      jumps.push_back(MoveOption(thePiece, getDubBackwardLeftTile(aGame, thePiece)->getLocation(), 6));
                  }
              }
          }
          //check if backward left step exists
          if (getBackwardLeftTile(aGame, thePiece)) {
              //if forward left tile isn't occupied
              if (!getBackwardLeftTile(aGame, thePiece)->getPiece()) {
                  int score = 3;
                  int newRow = getBackwardLeftTile(aGame, thePiece)->getLocation().row;
                  int newCol = getBackwardLeftTile(aGame, thePiece)->getLocation().col;
                  //while next forward left tile exists and is unnocupied
                  while (aGame.getTileAt(Location(newRow + incBackLeftRow(thePiece, newRow), newCol + incBackLeftCol(thePiece, newCol)))
                      && !aGame.getTileAt(Location(newRow + incBackLeftRow(thePiece, newRow), newCol + incBackLeftCol(thePiece, newCol)))->getPiece()) {
                      newRow = newRow + incBackLeftRow(thePiece, newRow);
                      newCol = newCol + incBackLeftCol(thePiece, newCol);
                      score = score + 1;
                  }
                  steps.push_back(MoveOption(thePiece, Location(newRow, newCol), score));
              }
          }
          //check backward right jump
          if (getBackwardRightTile(aGame, thePiece) && getDubBackwardRightTile(aGame, thePiece)) {
              if (getBackwardRightTile(aGame, thePiece)->getPiece()) {
                  const Piece* temp = getBackwardRightTile(aGame, thePiece)->getPiece();
                  if (temp->getColor() != thePiece->getColor() && !getDubBackwardRightTile(aGame, thePiece)->getPiece()) {
                      //TODO implement king double jump logic
                      jumps.push_back(MoveOption(thePiece, getDubBackwardRightTile(aGame, thePiece)->getLocation(), 6));
                  }
              }
          }
          //check if backward right step exists
          if (getBackwardRightTile(aGame, thePiece)) {
              //if forward left tile isn't occupied
              if (!getBackwardRightTile(aGame, thePiece)->getPiece()) {
                  int score = 3;
                  int newRow = getBackwardRightTile(aGame, thePiece)->getLocation().row;
                  int newCol = getBackwardRightTile(aGame, thePiece)->getLocation().col;
                  //while next forward left tile exists and is unnocupied
                  while (aGame.getTileAt(Location(newRow + incBackRightRow(thePiece, newRow), newCol + incBackRightCol(thePiece, newCol)))
                      && !aGame.getTileAt(Location(newRow + incBackRightRow(thePiece, newRow), newCol + incBackRightCol(thePiece, newCol)))->getPiece()) {
                      newRow = newRow + incBackRightRow(thePiece, newRow);
                      newCol = newCol + incBackRightCol(thePiece, newCol);
                      score = score + 1;
                  }
                  steps.push_back(MoveOption(thePiece, Location(newRow, newCol), score));
              }
          }
      }
    }

    //if a jump exists, we have to take it
    if (!jumps.empty()) {
        MoveOption bestMov = jumps.front();
        for (std::vector<MoveOption>::iterator it = jumps.begin(); it != jumps.end(); ++it) {
            if (bestMov.score < (*it).score) {
                bestMov = *it;
            }
        }
        aGame.movePieceTo(*bestMov.piece, bestMov.location);
        /*Add code to double jump*/
        if (bestMov.score == 7) {
            aGame.movePieceTo(*bestMov.piece,getNextJumpLocation(aGame, bestMov.piece));
        }
        return true;
    }
    if (!steps.empty()) {
        MoveOption bestMov = steps.front();
        //iterate through steps vector, get the MoveOption with highest score
        for (std::vector<MoveOption>::iterator it = steps.begin(); it != steps.end(); ++it) {
            if (bestMov.score < (*it).score) {
                bestMov = *it;
            }
        }
        aGame.movePieceTo(*bestMov.piece, bestMov.location);
        return true;
    }

    return false; //if you return false, you forfeit!
  }
}
