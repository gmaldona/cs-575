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

#ifndef PROG4__GREEDY_KNAPSACK_HH_
#define PROG4__GREEDY_KNAPSACK_HH_

#include <functional>
#include <initializer_list>
#include <list>

#include "Knapsack.hh"
#include "spdlog/spdlog.h"

//===== GM =========================================================== 80 ====>>

namespace ks::greedy
{

    /**
     * Benefit calculation for the \ns ks::Knapsack::Item as specified Chapter 12. Slide 15.
     */
    struct IBenefit
    {
        ks::Knapsack::Item item;
        double             benefit;

        IBenefit(
            const ks::Knapsack::Item& other)
        {
            item = other;
            // Chapter 12. Slide 18. Design and Analysis of Computer Algorithms.
            benefit = item.price / item.weight;
        }
    };

    /**
     * Chapter 12. Slide 18. Design and Analysis of Computer Algorithms.
     *
     * @brief Greedy4 algorithm as specified Chapter 12. Slide 15.
     *
     * @param [in] knapsack The entire problem space of the knapsack problem
     *
     * @returns The greedy solution set to the knapsack problem space.
     */
    std::vector<ks::Knapsack::Item> Greedy4(const ks::Knapsack::shared_ptr& knapsack);

    /**
     * Chapter 12. Slide 18. Design and Analysis of Computer Algorithms.
     *
     * @brief Greedy4 algorithm as specified Chapter 12. Slide 20.
     *
     * @param [in] knapsack The entire problem space of the knapsack problem
     *
     * @returns The greedy solution set to the knapsack problem space.
     */
    std::vector<ks::Knapsack::Item> MaxB(const ks::Knapsack::shared_ptr& knapsack);

    /**
     * Chapter 12. Slide 18. Design and Analysis of Computer Algorithms.
     *
     * @brief The approximation algorithm is a max over Greedy4 or MaxB
     *
     * The approximation algorithm selects, either the solution to Greedy4, or
     * only the item with benefit MaxB depending on max{BGreedy4, maxB }.
     *
     * @param [in] functors A list of implementations of a greedy solution to the knapsack problem
     * @param [in] knapsack The entire problem space of the knapsack problem
     *
     * @returns The greedy solution set to the knapsack problem space.
     */
    std::vector<Knapsack::Item> max(
        const std::initializer_list<std::function<std::vector<Knapsack::Item>(const Knapsack::shared_ptr&)>>& functors,
        const Knapsack::shared_ptr&                                                                           knapsack);

    /**
     * @brief Finds the subset with the most profit and minimum weight.
     *
     * @param [in] knapsack The entire problem space of the knapsack problem
     */
    void compute(const ks::Knapsack::shared_ptr& knapsack);

} // namespace ks::greedy

std::ostream& operator<<(std::ostream& os, ks::greedy::IBenefit item);

#endif // PROG4__GREEDY_KNAPSACK_HH_

//===== GM =========================================================== 80 ====>>
