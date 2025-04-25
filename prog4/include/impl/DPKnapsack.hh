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

#ifndef PROG4__DP_KNAPSACK_HH_
#define PROG4__DP_KNAPSACK_HH_

#include <vector>

#include "Knapsack.hh"

//===== GM =========================================================== 80 ====>>

/**
 * [40%] Implement the refinement algorithm of dynamic programming approach (slides 38-40 of Ch12 lecture notes)
 */

namespace ks::dp
{

    typedef std::vector<ks::Knapsack::Item>              DPCol_t;
    typedef std::vector<std::vector<ks::Knapsack::Item>> DPRow_t;
    typedef DPRow_t                                      DPTable_t;

    /**
     * @brief Finds the subset with the most profit and minimum weight.
     *
     * @param [in] knapsack The entire problem space of the knapsack problem
     */
    void compute(const ks::Knapsack::shared_ptr& knapsack);

} // namespace ks::dp

#endif // PROG4__DP_KNAPSACK_HH_

//===== GM =========================================================== 80 ====>>
