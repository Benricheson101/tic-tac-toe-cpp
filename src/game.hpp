#include <vector>

using namespace std;

using game_board = vector<vector<char>>;

class Game {
  private:
    game_board board;

    // board methods
    game_board new_board();
    void set_cell(char letter, int posx, int posy);
    char get_cell(int posx, int poxy);
    vector<int> prompt(int player);
    game_board swap_x_y();

    // win checks
    bool check_full_board();

    char check_rows(game_board b);
    char check_rows();

    char check_diag(game_board b);
    char check_diag();

    char check_win();

  public:
    Game();
    void set_board(game_board new_board);
    void print_board();
    void start();
};
