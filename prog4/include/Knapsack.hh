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

#ifndef PROG4__KNAPSACK_HH_
#define PROG4__KNAPSACK_HH_

#include <cstdint>
#include <list>
#include <memory>

#include "spdlog/spdlog.h"

//===== GM =========================================================== 80 ====>>

namespace ks
{

    /**
     * Meta class to hold the state of the Knapsack and the problem space
     */
    class Knapsack
    {
    public:
        typedef std::unique_ptr<Knapsack> unique_ptr;

        typedef uint64_t profit_t;
        typedef double weight_t;

        struct Item
        {
            std::string name;
            profit_t price;
            weight_t weight;
        };

        Knapsack(const std::list<Knapsack::Item>& allItems, weight_t knapsackWeight)
            : allItems_{allItems}
            , knapsackMaxWeight_{knapsackWeight}
        {
            SPDLOG_INFO("Created 0/1 Knapsack = {{ .items = {}, .weight = {} }}", allItems.size(), knapsackWeight);
        }

        size_t getItemCount()
        {
            return items_.size();
        }

        /**
         * @returns all items in the problem space
         */
        std::list<Knapsack::Item> getProblemSpace()
        {
            return allItems_;
        }

        std::list<Knapsack::Item> getItems()
        {
            return items_;
        }

        weight_t getMaxWeight()
        {
            return knapsackMaxWeight_;
        }

    private:
        // All potential items
        std::list<Knapsack::Item> allItems_;
        // A subset of all the potential items. The items which are allowable
        // in the knapsack
        std::list<Knapsack::Item> items_;
        // Weight capacity of knapsack
        weight_t knapsackMaxWeight_;
    };

} // namespace ks

#endif // PROG4__KNAPSACK_HH_

//===== GM =========================================================== 80 ====>>
