#include<vector>

using namespace std;

vector<vector<char>> new_board();

vector<vector<char>> add_letter(vector<vector<char>> board, char letter, int posx, int posy);

void print_board(vector<vector<char>> board);

char check_cell(vector<vector<char>> board, int posx, int posy);
vector<int> prompt(vector<vector<char>> board, int player);

// check stuff
bool check_full_board(vector<vector<char>> board);
char check_win(vector<vector<char>> board);
