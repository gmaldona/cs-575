/*
 * CS 575 - Programming Assignment 2
 *
 * Given a natural number n and a chess board with 2n squares on each side
 * (the length of the side is 2n, called the board size) with a missing square
 * in any location, you will use the divide and conquer approach to design and
 * implement an algorithm (see the algorithm skeleton from the class slides) to
 * cover the chess board (with a missing square) by an arrangement of trominoes
 * (an L-shaped arrangement of three squares; see figure below) such that all
 * trominoes are confined to the boundaries of the chess board, and no tromino
 * overlaps another.
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

#pragma once

#ifndef PROG2__TRIMINO_HH_
#define PROG2__TRIMINO_HH_

#include <stdint.h>

//===== GM =========================================================== 80 ====>>

typedef uint8_t   cell_t;
typedef uint8_t*  board_row_t;
/**
 * NOTE: The board has an origin of (0,0) at the bottom left of the a 2D matrix
 * e.g. 4x4 matrix will have an origin of (0, 3).
 *
 * When setting and getting, an offset MUST be applied to get the correct slot.
 *
 * See: #board_get(point_s)
 * See: #board_set(point_s, tile_e)
 */
typedef uint8_t** board_t;

typedef std::pair<int, int> point_t;

enum tile_e {
   MS  =  0,  // Actual Missing Square
   LR  =  1,  // Lower   Right
   LL  =  2,  // Lower   Left
   UR  =  3,  // Upper   Right
   UL  =  4,  // Upper   Left
   EM  =  5,  // EMPTY
};

/**
 *
 * Sets the tile of point on the board. An offset is applied w.r.t board origin.
 * See: board_t
 *
 * @param point point on the board to set
 * @param tile  set the point to tile
 */
void board_set(const point_t& point, tile_e tile);

/**
 *
 * Gets the tile of point on the board. An offset is applied w.r.t. board origin
 * See: board_t
 *
 * @param point point on the board to get
 * @return the point's tile
 */
int board_get(const point_t& point);

/**
 * Returns the correct tile to use given a 2x2 base case and an unavailable tile
 *
 * @param quad a list of points in a 2x2 where:
 *      [0] is top left
 *      [1] is top right
 *      [2] is bottom left
 *      [3] is bottom right
 * @return A tile to be used
 */
tile_e use_tile(const point_t* quad);

/**
 *
 * @param board
 * @param board_size
 */
inline void display_board(board_t board, const int board_size);

/**
 * Allocates memory for tromino board
 *
 * @param board_size board size
 * @return allocated memory for a tromino board of size {@code board_size}
 */
board_t create_board(const int board_size);

/**
 * Frees memory allocated to tromino board
 *
 * @param board allocated tromino board
 */
void destroy_board(board_t board, const int board_size);

/**
 *
 * @param x_board    x coordinate on board
 * @param y_board    y coordinate on board
 * @param x_missing  x coordinate of missing square on board
 * @param y_missing  y coordinate of missing square on board
 * @param board_size size of board, and is a power of 2 (2^n)
 */
void tromino(const int x_board,   const int y_board,
             const int x_missing, const int y_missing,
             const int board_size);

#endif //PROG2__TRIMINO_HH_

//===== GM =========================================================== 80 ====>>