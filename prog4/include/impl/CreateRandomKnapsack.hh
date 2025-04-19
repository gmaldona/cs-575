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

namespace ks::random
{
    ks::Knapsack::shared_ptr createKnapsack();
} // namespace ks::random

#endif // PROG4__CREATE_RANDOM_KNAPSACK_HH_

//===== GM =========================================================== 80 ====>>
