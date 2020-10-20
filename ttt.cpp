#include<iostream>
#include<vector>
#include "ttt_fns.hpp"

using namespace std;

int main () {
  vector<vector<char>> board = new_board();
  int winner = 0;
  int current = 0;

  bool end = false;

  while (!end) {

    cout << "===== Player " << current << " =====\n\n";

    print_board(board);
    cout << "\n";

    vector<int> coords = prompt(board, current);
    cout << "\n";

    board = add_letter(board, current == 0 ? 'X' : 'O', coords[1]-1, coords[0]-1);

    char cw = check_win(board);
    bool full = check_full_board(board);

    if (cw) {
      winner = cw == 'X' ? 0 : 1;
      end = true;

      break;
    } else if (full) {
      winner = -1;
      end = true;

      break;
    }

    current = current == 0 ? 1 : 0;
  }

  print_board(board);

  if (winner == -1) {
    cout << "\nIt's a tie.\n";
  } else {
    cout << "\nPlayer " << winner << " wins!\n";
  }

  return 0;
}
