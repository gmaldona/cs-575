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

#include <iostream>
#include <utility>
#include <vector>

#include "Knapsack.hh"

//===== GM =========================================================== 80 ====>>

/**
 * [40%] Implement the refinement algorithm of dynamic programming approach (slides 38-40 of Ch12 lecture notes)
 */

namespace ks::dp
{
    /// pointer types for components of the dynamic programming table ///
    typedef std::vector<int64_t>       __DPCol_t;
    typedef std::shared_ptr<__DPCol_t> DPCol_t;

    typedef std::vector<DPCol_t>       __DPRow_t;
    typedef std::shared_ptr<__DPRow_t> DPRow_t;

    typedef DPRow_t DPTable_t;

    typedef int64_t                     coord_t;
    typedef std::pair<coord_t, coord_t> point_t;

    ks::Knapsack::profit_t computeDPEntry(
        const ks::Knapsack::shared_ptr& knapsack, const DPTable_t& dpTable, point_t&& point);

    /**
     *
     */
    // clang-format off
    void rcompute(const ks::Knapsack::shared_ptr& knapsack, 
                  const DPTable_t& dpTable, 
                  point_t&& point,
                  size_t depth
        );
    // clang-format on

    /**
     * @brief Finds the subset with the most profit and minimum weight.
     *
     * @param [in] knapsack The entire problem space of the knapsack problem
     * @returns computed dynamic programming table
     */
    ks::dp::DPTable_t compute(const ks::Knapsack::shared_ptr& knapsack);

} // namespace ks::dp

/**
 * @brief Pretty print \ns ks::dp::point_t
 */
std::ostream& operator<<(
    std::ostream& os, const ks::dp::point_t& point)
{
    os << "[" << std::to_string(point.first) << ", " << std::to_string(point.second) << "]";
    return os;
}

#endif // PROG4__DP_KNAPSACK_HH_

//===== GM =========================================================== 80 ====>>
