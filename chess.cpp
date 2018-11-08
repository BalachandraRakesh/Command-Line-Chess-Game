#include <iostream>
#include<string.h>
using namespace std;
//Piece Class
class Piece {
private:
  char color;
  virtual bool checkposition(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]) = 0;
public:
  Piece(char Color) : color(Color) {}
  ~Piece() {}
  char GetColor() {
    return color;
  }
  virtual char GetPiece() = 0;
  bool validatemove(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]) {
    Piece* Destination = chessboard[DesRow][DesCol];
    if ((Destination == 0) || (color != Destination->GetColor())) {
      return checkposition(SrcRow, SrcCol, DesRow, DesCol, chessboard);
    }
    return false;
  }

};

//Pawn Class
class Pawn : public Piece {
private:
  virtual char GetPiece() {
    return 'P';
  }
  bool checkposition(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]) {
    Piece* Destination = chessboard[DesRow][DesCol];
    //If the square is unoccupied
    if (Destination == 0) {
      if (SrcCol == DesCol) {
        if (this->GetColor() == 'W') {
          if (DesRow == SrcRow + 1) {
            return true;
          }
       
        else if (SrcRow == 1 && DesRow == SrcRow + 2){
          return true;
        }  
        }
        else if (this->GetColor() == 'B') {
          if (DesRow == SrcRow - 1) {
            return true;
          }
          else if (SrcRow == 6 && DesRow == SrcRow - 2){
          return true;
        }  
        }
      }
    }
    //If the square is occupied
    else {
      if ((DesCol == SrcCol + 1) || (DesCol == SrcCol - 1)) {
        if (this->GetColor() == 'W') {
          if (DesRow == SrcRow + 1) {
            return true;
          }
        }
        else if (this->GetColor() == 'B') {
          if (DesRow == SrcRow - 1) {
            return true;
          }
        }
      }
    }
    return false;
  }
public:
  Pawn(char color) : Piece(color) {}
  ~Pawn() {}
};

//King Class
class King : public Piece {
private:
  virtual char GetPiece() {
    return 'K';
  }
  bool checkposition(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]) {
    int rowdifference = DesRow - SrcRow;
    int coldifference = DesCol - SrcCol;
    //Not checked for colors
    if ((rowdifference >= -1) && (rowdifference <= 1) && (coldifference >= -1) && (coldifference <= 1)) {
      return true;
    }
    return false;
  }

public:
  King(char color) : Piece(color) {}
  ~King() {}
};

//Queen Class
class Queen : public Piece {
private:
  virtual char GetPiece() {
    return 'Q';
  }
  bool checkposition(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]) {
    if (SrcRow == DesRow) {
      int ColOffset = (DesCol - SrcCol > 0) ? 1 : -1;
      for (int col = SrcCol + ColOffset; col != DesCol; col = col + ColOffset) {
        if (chessboard[SrcRow][col] != 0) {
          return false;
        }
      }
      return true;
    }
    else if (SrcCol == DesCol) {
      int RowOffset = (DesRow - SrcRow > 0) ? 1 : -1;
      for (int row = SrcRow + RowOffset; row != DesRow; row = row + RowOffset) {
        if (chessboard[row][SrcCol] != 0) {
          return false;
        }
      }
      return true;
    }
    else if ((DesRow - SrcRow == SrcCol - DesCol) || (DesRow - SrcRow == DesCol - SrcCol)) {
      int RowOffset = (DesRow - SrcRow > 0) ? 1 : -1;
      int ColOffset = (DesCol - SrcCol > 0) ? 1 : -1;
      int row;int col;
      for (row = SrcRow + RowOffset,col = SrcCol + ColOffset; row != DesRow; row = row + RowOffset,col = col + ColOffset) {
  
        if (chessboard[row][col] != 0) {
          return false;
        }
        }
      return true;
    }
    return false;
  }

public:
  Queen(char color) : Piece(color) {}
  ~Queen() {}
};

//Rook Class
class Rook : public Piece {
private:
  virtual char GetPiece() {
    return 'R';
  }
  bool checkposition(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]) {
    if(SrcRow == DesRow) {
      int ColOffset = (DesCol - SrcCol > 0) ? 1 : -1;
      for (int col = SrcCol + ColOffset; col != DesCol; col = col + ColOffset) {
        if (chessboard[SrcRow][col] != 0) {
          return false;
        }
      }
      return true;
    }
    else if (SrcCol == DesCol) {
      int RowOffset = (DesRow - SrcRow > 0) ? 1 : -1;
      for (int row = SrcRow + RowOffset; row != DesRow; row = row + RowOffset) {
        if (chessboard[row][SrcCol] != 0) {
          return false;
        }
       }
      return true;
    }
    return false;
  }
public:
  Rook(char color) : Piece(color) {}
  ~Rook() {}
};

//Knight Class
class Knight : public Piece {
private:
  virtual char GetPiece() {
    return 'N';
  }
  bool checkposition(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]) {
    if ((SrcCol == DesCol + 1) || (SrcCol == DesCol - 1)) {
      if ((SrcRow == DesRow + 2) || (SrcRow == DesRow - 2)) {
        return true;
      }
    }
    if ((SrcCol == DesCol + 2) || (SrcCol == DesCol - 2)) {
      if ((SrcRow == DesRow + 1) || (SrcRow == DesRow - 1)) {
        return true;
      }
    }
    return false;
  }
public:
  Knight(char color) : Piece(color) {}
  ~Knight() {}
};

//Bishop Class
class Bishop : public Piece {
private:
  virtual char GetPiece() {
    return 'B';
  }
  bool checkposition(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]) {
    if ((DesRow - SrcRow == SrcCol - DesCol) || (DesRow - SrcRow == DesCol - SrcCol)) {
      int RowOffset = (DesRow - SrcRow > 0) ? 1 : -1;
      int ColOffset = (DesCol - SrcCol > 0) ? 1 : -1;
      int row;int col;
      for (row = SrcRow + RowOffset,col = SrcCol + ColOffset; row != DesRow; row = row + RowOffset,col = col + ColOffset) {
  
        if (chessboard[row][col] != 0) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
public:
  Bishop(char color) : Piece(color) {}
  ~Bishop() {}
};

//Board Class
class Board {
public:
  Piece * chessboard[8][8];
  Board() {
    //Initialize all boxes to zeros
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        chessboard[row][col] = 0;
      }
    }
    //Initialize all black pieces
    for (int col = 0; col < 8; col++) {
      chessboard[6][col] = new Pawn('B');
    }
    chessboard[7][0] = new Rook('B');
    chessboard[7][1] = new Knight('B');
    chessboard[7][2] = new Bishop('B');
    chessboard[7][3] = new King('B');
    chessboard[7][4] = new Queen('B');
    chessboard[7][5] = new Bishop('B');
    chessboard[7][6] = new Knight('B');
    chessboard[7][7] = new Rook('B');

    //Initialize all white pieces
    for (int col = 0; col < 8; col++) {
      chessboard[1][col] = new Pawn('W');
    }
    chessboard[0][0] = new Rook('W');
    chessboard[0][1] = new Knight('W');
    chessboard[0][2] = new Bishop('W');
    chessboard[0][3] = new King('W');
    chessboard[0][4] = new Queen('W');
    chessboard[0][5] = new Bishop('W');
    chessboard[0][6] = new Knight('W');
    chessboard[0][7] = new Rook('W');
  }
  ~Board() {
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        delete chessboard[row][col];
        chessboard[row][col] = 0;
      }
    }
  }
  void print() {
    for (int row = 7; row >= 0; row--) {

      // Draws Horizontal Row Dividers
      cout << "   ";
      for (int col = 0; col < 8; col++) {
        cout << "--------";
      }
      cout << "-" << endl;


      // Draws Vertical Row Divider and Chess Piece
      cout << row + 1 << "  ";
      for (int col = 0; col < 8; col++) {
        cout << "| ";
        if (chessboard[row][col] != NULL) {
          cout <<" " <<chessboard[row][col]->GetColor() << chessboard[row][col]->GetPiece()<< "  ";
        }
        else {
          cout << "     ";
        }
        cout << " ";
      }

      // Draws Divider for end of Row
      cout << "|" << endl;

    }

    // Draws Horitonal Divider for last Row
    cout << "   ";
    for (int col = 0; col < 8; col++) {
      cout << "--------";
    }
    cout << "-" << endl;

    // Draws Letters on botton of board
    cout << "    ";
    for (int col = 0; col < 8; col++) {
      cout << "    " << col + 1 << "   ";
    }
    cout << endl << endl;
  }
  bool isthereaCheck(char color) {
    int kingX = 0;
    int kingY = 0;
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (chessboard[row][col] != 0) {
          if (chessboard[row][col]->GetColor() == color) {
            if (chessboard[row][col]->GetPiece() == 'K') {
              kingX = row;
              kingY = col;
            }
          }
        }
      }
    }
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (chessboard[row][col] != 0) {
          if (chessboard[row][col]->GetColor() != color) {
            if (chessboard[row][col]->validatemove(row, col, kingX, kingY, chessboard)) {

              return true;
            }
          }
        }
      }
    }
    return false;
  }
  bool CanMove(char color) {
    // Run through all pieces
    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        if (chessboard[row][col] != 0) {
          // If it is a piece of the current player, see if it has a legal move
          if (chessboard[row][col]->GetColor() == color) {
            for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow) {
              for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol) {
                if (chessboard[row][col]->validatemove(row, col, iMoveRow, iMoveCol, chessboard)) {
                  // Make move and check whether king is in check
                  Piece* Temp = chessboard[iMoveRow][iMoveCol];
                  chessboard[iMoveRow][iMoveCol] = chessboard[row][col];
                  chessboard[row][col] = 0;
                  bool bCanMove = !isthereaCheck(color);
                  // Undo the move
                  chessboard[row][col] = chessboard[iMoveRow][iMoveCol];
                  chessboard[iMoveRow][iMoveCol] = Temp;
                  if (bCanMove) {
                    return true;
                  }
                }
              }
            }
          }
        }
      }
    }
    return false;
  }

};

class Chess {
private:
  Board myChess;
  char PlayerTurn;
public:
  Chess() :PlayerTurn('W'){}
  ~Chess() {}
    bool PawnPromotion(int SrcRow, int SrcCol, int DesRow, int DesCol, Piece* chessboard[8][8]){
    Piece* SrcTemp = chessboard[SrcRow][SrcCol];
    Piece* DesTemp1 = chessboard[DesRow][DesCol];
    Piece* DesTemp2 = chessboard[DesRow][DesCol];
    if(SrcTemp->GetPiece() == 'P'){
          if(DesRow == 7 && PlayerTurn == 'W'){
          char temp;
          cout << "You can now promote your pawn"<<endl;
          cout << "Your options are either a) Queen b) Rook c) Bishop and d) Knight" << endl;
          cout << "Enter Q for Queen,R for Rook, B for Bishop, N for Knight : " << endl;
          cin >> temp;
          chessboard[SrcRow][SrcCol] = 0;
          if(temp == 'Q'){
            chessboard[DesRow][DesCol] = new Queen('W');
            return true;            
          }
          else if(temp == 'R'){
            chessboard[DesRow][DesCol] = new Rook('W');
            return true;            
          }
          else if(temp == 'B'){
            chessboard[DesRow][DesCol] = new Bishop('W');
            return true;            
          }
          else if(temp == 'N'){
            chessboard[DesRow][DesCol] = new Knight('W');
            return true;
            
          }
          else{
            return false;
          }

        }
    else if(DesRow == 0 && PlayerTurn == 'B'){
          char temp;
          cout << "You can now promote your pawn"<<endl;
          cout << "Your options are either a) Queen b) Rook c) Bishop and d) Knight" << endl;
          cout << "Enter Q for Queen,R for Rook, B for Bishop, N for Knight : " << endl;
          cin >> temp;
          chessboard[SrcRow][SrcCol] = 0;
          if(temp == 'Q'){
            chessboard[DesRow][DesCol] = new Queen('B');
            return true;            
          }
          else if(temp == 'R'){
            chessboard[DesRow][DesCol] = new Rook('B');
            return true;            
          }
          else if(temp == 'B'){
            chessboard[DesRow][DesCol] = new Bishop('B');
            return true;            
          }
          else if(temp == 'N'){
            chessboard[DesRow][DesCol] = new Knight('B');
            return true;
            
          }
          else{
            return false;
          }

        }
  if (myChess.isthereaCheck(PlayerTurn)){
      chessboard[DesRow][DesCol] = DesTemp2;
      chessboard[SrcRow][SrcCol] = new Pawn(PlayerTurn);
    
  }
}
  return false;

}
  void GetNextMove(Piece* chessboard[8][8]) {
    bool ValidMove = false;
    do {
      myChess.print();
      // Get input and convert to coordinates
      cout << PlayerTurn << "'s Move " << "Enter the starting position: ";
      int StartMove;
      cin >> StartMove;
      int StartRow = (StartMove / 10) - 1;
      int StartCol = (StartMove % 10) - 1;

      cout << "Enter ending position" << "To: ";
      int EndMove;
      cin >> EndMove;
      int EndRow = (EndMove / 10) - 1;
      int EndCol = (EndMove % 10) - 1;
      if ((StartRow >= 0 && StartRow <= 7) &&
        (StartCol >= 0 && StartCol <= 7) &&
        (EndRow >= 0 && EndRow <= 7) &&
        (EndCol >= 0 && EndCol <= 7)) {
        Piece* CurrPiece = chessboard[StartRow][StartCol];
        if ((CurrPiece != 0) && (CurrPiece->GetColor() == PlayerTurn)) {
          if (CurrPiece->validatemove(StartRow, StartCol, EndRow, EndCol, chessboard)) {
            if(PawnPromotion(StartRow,StartCol,EndRow,EndCol,chessboard)){
              ValidMove = true;
              }
          else{           
            Piece* TempPiece = chessboard[EndRow][EndCol];
            chessboard[EndRow][EndCol] = chessboard[StartRow][StartCol];
            chessboard[StartRow][StartCol] = 0;
            if (!myChess.isthereaCheck(PlayerTurn)) {
              delete TempPiece;
              ValidMove = true;
            }
            else { // Undo the last move
              chessboard[StartRow][StartCol] = chessboard[EndRow][EndCol];
              chessboard[EndRow][EndCol] = TempPiece;
            }
          }
          }
        }
      }
      if (!ValidMove) {
        cout << "Invalid Move! " << "Please try again" << endl;
      }

    } while (!ValidMove);
  }
  void SwitchTurn() {
    PlayerTurn = (PlayerTurn == 'W') ? 'B' : 'W';
  }

  bool IsGameOver() {
    // Check that the current player can move
    // If not, we have a stalemate or checkmate
    bool bCanMove(false);
    bCanMove = myChess.CanMove(PlayerTurn);
    if (!bCanMove) {
      if (myChess.isthereaCheck(PlayerTurn)) {
        SwitchTurn();
        std::cout << "Checkmate, " << PlayerTurn << " Wins the Game!" << std::endl;
      }
      else {
        std::cout << "Stalemate!" << std::endl;
      }
    }
    return !bCanMove;
  }
  void StartGame() {
    do {
      GetNextMove(myChess.chessboard);
      SwitchTurn();
    } while (!IsGameOver());
    myChess.print();
  }
};


int main() {
  Chess Game;

  Game.StartGame();
  return 0;
}
