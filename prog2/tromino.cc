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

// https://stackoverflow.com/questions/600293
#define IS_POWER_OF_2(x) ((x & (x - 1)) == 0)

#define ORIGIN_X 0
#define ORIGIN_Y 0

using namespace std;

//===== GM =========================================================== 80 ====>>

void tromino(const int x_board,   const int y_board,
             const int x_missing, const int y_missing,
             const int board_size) {

}

int main(void) {

   /* User input parsing for board size and missing tile (x,y) coordinate */
   int board_size;
   int x_missing, y_missing;

   std::string input;

   std::cout << "Please enter size of board as a power of 2 (0 to quit): ";
   if (!std::getline(std::cin, input) || input.empty()) {
      std::cerr << "[ERROR] Exiting...";
      return EXIT_FAILURE;
   }
   try {
      board_size = std::stoi(input);
   } catch (std::exception& e) {
      std::cerr << "[ERROR] Failed to convert input to board size. Exiting ...";
      return EXIT_FAILURE;
   }
   if (board_size == 0) {
      std::cerr << "[FINEST] Exiting ...";
      return EXIT_SUCCESS;
   }

   if (! IS_POWER_OF_2(board_size)) {
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
   } catch (std::exception& e) {
      std::cerr <<
         "[ERROR] Failed to convert input to (x, y) coordinate. Exiting ...";
      return EXIT_FAILURE;
   }

   std::cerr <<
      "[FINEST] Missing tile: (" << x_missing << ", "
                                 << y_missing << ")" << std::endl;

   tromino(ORIGIN_X, ORIGIN_Y, x_missing, y_missing, board_size);

   return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>