//#include <iostream>
//#include <ctime>
//
//using namespace std;
//
//enum EMove {
//    keUp = 'w',
//    keDown = 'z',
//    keLeft = 'a',
//    keRight = 's'
//};
//
//void InitializedBoard(char[4][4]);
//void PrintBoard(char[4][4]);
//void LocateSpace(int&, int&, char[4][4]);
//void Randomize(char[4][4]);
//void Move(char[4][4], const EMove);
//
//int main() {
//    char board[4][4];
//    InitializedBoard(board);
//    Randomize(board);
//
//    do {
//        system("CLS");
//        PrintBoard(board);
//        cout << endl << "w = Up, z = Down, a = Left, s = Right";
//        char cNextMove;
//        cin >> cNextMove;
//        EMove eNextMove = (EMove)cNextMove;
//        Move(board, eNextMove);
//        cout << endl;
//    } while (true);
//
//    return EXIT_SUCCESS;
//}
//
//void InitializedBoard(char board[4][4]) {
//    const char kboard[4][4] = {
//     {'1', '2', '3', '4'},
//     {'5', '6', '7', '8'},
//     {'9', 'A', 'B', 'C'},
//     {'D', 'E', 'F', ' '}
//    };
//    for (int iRow = 0; iRow < 4; ++iRow) {
//        for (int iCol = 0; iCol < 4; ++iCol) {
//            board[iRow][iCol] = kboard[iRow][iCol];
//        }
//    }
//}
//
//void PrintBoard(char board[4][4]) {
//    for (int iRow = 0; iRow < 4; ++iRow) {
//        for (int iCol = 0; iCol < 4; ++iCol) {
//            cout << board[iRow][iCol];
//        }
//        cout << endl;
//    }
//}
//
//void LocateSpace(int& irRow, int& irCol, char board[4][4]) {
//    for (int iRow = 0; iRow < 4; ++iRow) {
//        for (int iCol = 0; iCol < 4; ++iCol) {
//            if (board[iRow][iCol] == ' ') {
//                irRow = iRow;
//                irCol = iCol;
//            }
//        }
//    }
//}
//
//void Randomize(char board[4][4]) {
//    srand((unsigned int)time(0));
//    for (int iIndex = 0; iIndex < 1000000; ++iIndex) {
//        const int iNextMove = (rand() % 4);
//        switch (iNextMove) {
//        case 0:
//        {
//            Move(board, keUp);
//            break;
//        }
//        case 1:
//        {
//            Move(board, keDown);
//            break;
//        }
//        case 2:
//        {
//            Move(board, keLeft);
//            break;
//        }
//        case 3:
//        {
//            Move(board, keRight);
//            break;
//        }
//        default:
//            break;
//        }
//    }
//}
//
//void Move(char board[4][4], const EMove keMove) {
//    int iRowSpace;
//    int iColSpace;
//    LocateSpace(iRowSpace, iColSpace, board);
//    int iRowMove(iRowSpace);
//    int iColMove(iRowSpace);
//    switch (keMove) {
//    case keUp:
//    {
//        iRowMove = iRowSpace + 1;
//        break;
//    }
//    case keDown:
//    {
//        iRowMove = iRowSpace - 1;
//        break;
//    }
//    case keLeft:
//    {
//        iColMove = iColSpace + 1;
//        break;
//    }
//    case keRight:
//    {
//        iColMove = iColSpace - 1;
//        break;
//    }
//    default:
//        break;
//    }
//
//    if (iRowMove >= 0 && iRowMove < 4 && iColMove >= 0 && iColMove < 4) {
//        board[iRowSpace][iColSpace] = board[iRowMove][iColMove];
//        board[iRowMove][iColMove] = ' ';
//    }
//}