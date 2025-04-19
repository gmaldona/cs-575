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

#ifndef PROG4__BRUTEFORCE_KNAPSACK_HH_
#define PROG4__BRUTEFORCE_KNAPSACK_HH_

#include "Knapsack.hh"

//===== GM =========================================================== 80 ====>>

namespace ks::bf
{

    /**
     * @brief Computes a brute force solution on a subset of all items in the
     * problem space
     *
     * @param [in] subset A subset of items within the problem space
     */
    void compute(
        std::vector<ks::Knapsack::Item> subset, ks::Knapsack::profit_t* profit, ks::Knapsack::weight_t* weight);

    void compute(ks::Knapsack::unique_ptr& knapsack);

} // namespace ks::bf

#endif // PROG4__BRUTEFORCE_KNAPSACK_HH_

//===== GM =========================================================== 80 ====>>
