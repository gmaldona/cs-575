/*
 * CS 575 - Programming Assignment 4
 *
 * Graduate student @ School of Computing, Binghamton University.
 *
 * author: Gregory Maldonado
 * email : gmaldonado@cs.binghamton.edu
 * date  : 2025-04-25
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

#ifndef PROG4__CREATE_RANDOM_KNAPSACK_HH_
#define PROG4__CREATE_RANDOM_KNAPSACK_HH_

#define ITEMS_LOWER_BOUND 5
#define ITEMS_UPPER_BOUND 10

#define ITEM_PROFIT_LOWER_BOUND 10
#define ITEM_PROFIT_UPPER_BOUND 30

#define ITEM_WEIGHT_LOWER_BOUND 5
#define ITEM_WEIGHT_UPPER_BOUND 20

#include "Knapsack.hh"

//===== GM =========================================================== 80 ====>>

/**
 * [10%] Randomly create a 0/1 Knapsack problem
 */

namespace ks::random
{

    /**
     * @brief Randomly create a 0/1 Knapsack problem.
     *
     * Create n items where n is an integer randomly selected between 5 and 10.
     * Display the selected n value. Create a list of n items where each item has
     * profit pi and weight wi where 1) pi is a positive integer randomly selected
     * between 10 and 30; and 2) wi is a positive integer randomly selected between
     * 5 and 20. Set the capacity of the knapsack W = floor(0.6 * ∑! 𝑤i).
     */
    ks::Knapsack::shared_ptr createKnapsack();

} // namespace ks::random

#endif // PROG4__CREATE_RANDOM_KNAPSACK_HH_

//===== GM =========================================================== 80 ====>>
