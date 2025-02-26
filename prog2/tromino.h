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

//===== GM =========================================================== 80 ====>>

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