#include <iostream>
#include<cstdlib>
#include "game.hpp"

Game::Game() {
  board = new_board();
}

game_board Game::new_board() {
  return {
    {'\0', '\0', '\0'},
    {'\0', '\0', '\0'},
    {'\0', '\0', '\0'}
  };
}

void Game::set_cell(char letter, int posx, int posy) {
  board[posy][posx] = letter;
}

void Game::set_board(game_board new_board) {
  board = new_board;
}

void Game::print_board() {
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

char Game::get_cell(int posx, int posy) {
  return board[posy][posx];
}

vector<int> Game::prompt(int player) {
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
    if (!get_cell(y-1, x-1)) {
      coords[0] = y;
      coords[1] = x;

      return coords;
    } else {
      cout << "There is already a letter there. Pick a different cell.\n";
    }
  }
  return coords;
}

game_board Game::swap_x_y() {
  game_board swapped = {{}, {}, {}};

  for (int row=2; row >= 0; row--) {
    for (int cell=0; cell < 3; cell++) {
      swapped[cell].push_back(board[row][cell]);
    }
  }

  return swapped;
}

// check functions
bool Game::check_full_board() {
  for (int row=0; row < 3; row++) {
    for (int cell=0; cell < 3; cell++) {
      if (board[row][cell] == '\0') return false;
    }
  }
  return true;
}

char Game::check_rows(game_board b) {
  for (int row=0; row<3; row++) {
    vector<char> cells = b[row];
    if (
      (cells[0] == cells[1]) &&
      (cells [0] == cells[2]) &&
      (cells[1] == cells[2]) &&
      (cells[0] != '\0')
    ) return cells[0];
  }

  return '\0';
}

char Game::check_rows() {
  return check_rows(board);
}

char Game::check_diag(game_board b) {
  if (
    (b[0][0] == b[1][1]) &&
    (b[0][0] == b[2][2]) &&
    (b[1][1] == b[2][2]) &&
    (b[0][0] != '\0')
  ) return board[0][0];
  return '\0';
}

char Game::check_diag() {
  return check_diag(board);
}

char Game::check_win() {
  char winner;

  // check rows first
  winner = check_rows();
  if (winner) return winner;

    // check cols
  game_board swapped = swap_x_y();
  winner = check_rows(swapped);
  if (winner) return winner;

  // check diag
  winner = check_diag();
  if (winner) return winner;

  winner = check_diag(swapped);
  if (winner) return winner;

  return '\0';
}

void Game::start() {
  int winner = 0;
  int current = 0;
  bool end = false;

  while (!end) {
    system("clear");
    cout << "===== Player " << current << " =====\n\n";

    print_board();
    cout << "\n";

    vector<int> coords = prompt(current);

    set_cell(current == 0 ? 'X' : 'O', coords[0]-1, coords[1]-1);

    char check_winner = check_win();
    bool is_full = check_full_board();

    if (check_winner) {
      winner = check_winner == 'X' ? 0 : 1;
      end = true;

      break;
    } else if (is_full) {
      winner = -1;
      end = true;

      break;
    }

    current = current == 0 ? 1 : 0;
  }

  system("clear");
  cout << "===== Player " << current << " =====\n\n";
  print_board();

  if (winner == -1) {
    cout << "\nIt's a tie.\n";
  } else {
    cout << "\nPlayer " << winner << " wins!\n";
  }
}
