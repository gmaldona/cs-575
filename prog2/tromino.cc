/*
* CS 575 - Programming Assignment 2
*
* Graduate student @ School of Computing, Binghamton University.
*
* author: Gregory Maldonado
* email : gmaldonado@cs.binghamton.edu
* date  : 2025-02-26
* web   : https://cs.binghamton.edu/~gmaldonado
*
*  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include "tromino.h"

// https://stackoverflow.com/questions/600293
#define IS_POWER_OF_2(x) ((x & (x - 1)) == 0)

static board_t board;
static int     total_board_size;

using namespace std;

//===== GM =========================================================== 80 ====>>

void board_set(const point_t& point, tile_e tile) {
   board[total_board_size - 1 - point.second][point.first] = tile;
}

int board_get(const point_t& point) {
   return board[total_board_size - 1 - point.second][point.first];
}

tile_e use_tile(const point_t* quad) {
   if (board_get(quad[0]) != tile_e::EM) {
      return tile_e::LR;
   }
   else if (board_get(quad[1]) != tile_e::EM) {
      return tile_e::LL;
   }
   else if (board_get(quad[2]) != tile_e::EM) {
      return tile_e::UR;
   }
   else if (board_get(quad[3]) != tile_e::EM) {
      return tile_e::UL;
   }

   return tile_e::LR;
}

board_t create_board(const int board_size) {
   board_t _board = (board_t) malloc(sizeof(board_row_t) * board_size);
   for  (int row = 0; row < board_size; ++row) {
      _board[row] = (board_row_t) malloc(sizeof(cell_t) * board_size);
      for (int col = 0; col < board_size; ++col) {
         _board[row][col] = tile_e::EM;
      }
   }
   return _board;
}

void destroy_board(board_t _board, const int board_size) {
   for  (int row = 0; row < board_size; ++row) {
      delete _board[row];
   }
   delete _board;
}

inline void display_board(board_t _board, const int board_size) {
   for  (int row = 0; row < board_size; ++row) {
      for (int col = 0; col < board_size; ++col) {
         switch (_board[row][col]) {
            case MS:
               std::cout << "MS";
               break;
            case EM:
               std::cout << "XX";
               break;
            case LR:
               std::cout << "LR";
               break;
            case LL:
               std::cout << "LL";
               break;
            case UR:
               std::cout << "UR";
               break;
            case UL:
               std::cout << "UL";
               break;
            default:
               std::cout << "XX"; // null
               break;
         }
         std::cout << " ";
      }
      std::cout << std::endl;
   }
}

void tromino(const int x_board,   const int y_board,
             const int x_missing, const int y_missing,
             const int board_size) {

   int offset = (board_size / 2);
   point_t p1 = make_pair(x_board + offset - 1, y_board + offset);
   point_t p2 = make_pair(x_board + offset,     y_board + offset);
   point_t p3 = make_pair(x_board + offset - 1, y_board + offset - 1);
   point_t p4 = make_pair(x_board + offset,     y_board + offset - 1);

   point_t quad[] = {p1, p2, p3, p4};
   if (board_size == 2) {
      tile_e tile = use_tile(quad);
      for (auto& point : quad) {
         if (board_get(point) == tile_e::EM) {
            board_set(point, tile);
         }
      }
      return;
   }

   point_t missing = make_pair(x_missing, y_missing);
   point_t mid     = make_pair(x_board + offset, y_board + offset);

   tile_e tile;

   if (missing.first <= mid.first && missing.second > mid.second) {
      tile = tile_e::LR;
      board_set(p2, tile);
      board_set(p3, tile);
      board_set(p4, tile);
   }
   else if (missing.first > mid.first && missing.second > mid.second) {
      tile = tile_e::LL;
      board_set(p1, tile);
      board_set(p3, tile);
      board_set(p4, tile);
   }
   else if (missing.first <= mid.first && missing.second <= mid.second) {
      tile = tile_e::UR;
      board_set(p1, tile);
      board_set(p2, tile);
      board_set(p4, tile);
   }
   else if (missing.first > mid.first && missing.second <= mid.second) {
      tile = tile_e::UL;
      board_set(p1, tile);
      board_set(p2, tile);
      board_set(p3, tile);
   }

   offset = board_size / 2;
   // Q1
   if (board_get(p1) != tile_e::EM && board_get(p1) != tile_e::MS)
   {
      tromino(x_board, y_board + offset, p1.first, p1.second, board_size / 2);
   } else
   {
      tromino(x_board, y_board + offset, x_missing, y_missing, board_size / 2);
   }

   // Q2
   if (board_get(p2) != tile_e::EM && board_get(p2) != tile_e::MS)
   {
      tromino(x_board + offset, y_board + offset, p2.first, p2.second, board_size / 2);
   } else
   {
      tromino(x_board + offset, y_board + offset, x_missing, y_missing, board_size / 2);
   }

   // Q3
   if (board_get(p3) != tile_e::EM && board_get(p3) != tile_e::MS)
   {
      tromino(x_board, y_board, p3.first, p3.second, board_size / 2);
   } else
   {
      tromino(x_board, y_board, x_missing, y_missing, board_size / 2);
   }

   // Q4
   if (board_get(p4) != tile_e::EM && board_get(p4) != tile_e::MS)
   {
      tromino(x_board + offset, y_board, p4.first, p4.second, board_size / 2);
   } else
   {
      tromino(x_board + offset, y_board, x_missing, y_missing, board_size / 2);
   }
}

int main() {

   while (true) {
      /* User input parsing for board size and missing tile (x,y) coordinate */

      int board_size;
      int x_missing, y_missing;

      std::string input;

      std::cout << "Please enter size of board (need to be 2^n and 0 to quit): ";
      if (!std::getline(std::cin, input) || input.empty()) {
         std::cerr << "[ERROR] Exiting...";
         return EXIT_FAILURE;
      }
      try {
         board_size = std::stoi(input);
      } catch (std::exception &e) {
         std::cerr << "[ERROR] Failed to convert input to board size. Exiting ...";
         return EXIT_FAILURE;
      }
      if (board_size == 0) {
         continue;
      }

      if (!IS_POWER_OF_2(board_size) || board_size < 0) {
         std::cerr << "[ERROR] Board size is not a power of 2. Exiting ...";
         return EXIT_FAILURE;
      }

      std::cout <<
                "Please enter coordinates of missing square (seperated by a space): ";
      if (!std::getline(std::cin, input) || input.empty()) {
         std::cerr << "[ERROR] Exiting ...";
         return EXIT_FAILURE;
      }
      size_t delimiter = input.find(' ');
      if (delimiter == std::string::npos) {
         std::cerr << "[ERROR] Exiting ...";
         return EXIT_FAILURE;
      }
      try {
         x_missing = stoi(input.substr(0, delimiter));
         y_missing = stoi(input.substr(delimiter));
      } catch (std::exception &e) {
         std::cerr <<
                   "[ERROR] Failed to convert input to (x, y) coordinate. Exiting ...";
         return EXIT_FAILURE;
      }

      board = create_board(board_size);
      total_board_size = board_size;

      board[board_size - y_missing - 1][x_missing] = tile_e::MS;

      tromino(0, 0, x_missing, y_missing, board_size);

      display_board(board, board_size);
      destroy_board(board, board_size);
   }

   return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>