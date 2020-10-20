#include<iostream>
#include<vector>

using namespace std;

// misc stuff
vector<vector<char>> swap_x_y(vector<vector<char>> board) {
  vector<vector<char>> swapped = {{}, {}, {}};

  for (int row=2; row >= 0; row--) {
    for (int cell=0; cell < 3; cell++) {
      swapped[cell].push_back(board[row][cell]);
    }
  }

  return swapped;
}

// board stuff
vector<vector<char>> new_board() {
  return {
    {'\0', '\0', '\0'},
    {'\0', '\0', '\0'},
    {'\0', '\0', '\0'}
  };
}

vector<vector<char>> add_letter(vector<vector<char>> board, char letter, int posx, int posy) {
  board[posy][posx] = letter;
  return board;
}

void print_board(vector<vector<char>> board) {
  cout << "    1   2   3\n";
  cout << "  -------------\n";
  for (int row=0; row < 3; row++) {
    for (int cell=0; cell < 3; cell++) {
      char c = board[row][cell];
      if (cell == 0) cout << row+1 << " ";
      cout << "| ";
      if (c == '\0') {
        cout << "-";
      } else {
        cout << board[row][cell];
      }
      cout << " ";
    }
    cout << "|\n";
    cout << "  -------------\n";
  }
}

char check_cell(vector<vector<char>> board, int posx, int posy) {
  return board[posy][posx];
}

vector<int> prompt(vector<vector<char>> board, int player) {
  vector<int> coords = {0, 0};

  while (!coords[0] && !coords[1]) {
    // x coord

    int x, y;
    while (!coords[0]) {
      cout << "[" << player << "] Choose a row\n";
      cout << "> ";

      cin >> x;

      if (x < 1 || x > 3) {
        cout << "Invalid number. Number must be between 1 and 3.\n";
      } else {
        break;
      }
    }

    while (!coords[1]) {
      cout << "[" << player << "] Choose a column\n";
      cout << "> ";

      cin >> y;

      if (y < 1 || y > 3) {
        cout << "Invalid number. Number must be between 1 and 3.\n";
      } else {
        break;
      }
    }
    if (!check_cell(board, y-1, x-1)) {
      coords[0] = x;
      coords[1] = y;

      return coords;
    } else {
      cout << "There is already a letter there. Pick a different cell.\n";
    }
  }
  return coords;
}

// check stuff

bool check_full_board(vector<vector<char>> board) {
  for (int row=0; row < 3; row++) {
    for (int cell=0; cell < 3; cell++) {
      if (board[row][cell] == '\0') return false;
    }
  }

  return true;
}

char check_rows(vector<vector<char>> board) {
  for (int row=0; row<3; row++) {
    vector<char> cells = board[row];
    if (
      (cells[0] == cells[1]) &&
      (cells [0] == cells[2]) &&
      (cells[1] == cells[2]) &&
      (cells[0] != '\0')
    ) return cells[0];
  }

  return '\0';
}

char check_diag(vector<vector<char>> board) {
  if (
    (board[0][0] == board[1][1]) &&
    (board[0][0] == board[2][2]) &&
    (board[1][1] == board[2][2]) &&
    (board[0][0] != '\0')
  ) return board[0][0];
  return '\0';
}

char check_win(vector<vector<char>> board) {
  char winner;

  // check rows first
  winner = check_rows(board);
  if (winner) return winner;

    // check cols
  vector<vector<char>> swapped = swap_x_y(board);
  winner = check_rows(swapped);
  if (winner) return winner;

  // check diag
  winner = check_diag(board);
  if (winner) return winner;

  winner = check_diag(swapped);
  if (winner) return winner;

  return '\0';
}
