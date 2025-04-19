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
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

//===== GM =========================================================== 80 ====>>

namespace ks
{

    enum KnapsackImpl
    {
        INIT,
        BRUTEFORCE,
        DP,
        GREEDY
    };

    /**
     * Meta class to hold the state of the Knapsack and the problem space
     */
    class Knapsack
    {
    public:
        typedef uint64_t                  profit_t;
        typedef double                    weight_t;
        typedef std::shared_ptr<Knapsack> shared_ptr;

        struct Item
        {
            std::string name;
            profit_t    price;
            weight_t    weight;
        };

        Knapsack()
            : allItems_{}
            , knapsackMaxWeight_{}
        {
            Knapsack({}, 0.0);
        }

        Knapsack(
            const std::vector<Knapsack::Item>& allItems, weight_t knapsackWeight)
            : allItems_{allItems}
            , knapsackMaxWeight_{knapsackWeight}
        {
            items_ = std::make_shared<std::vector<Knapsack::Item>>();
            // clang-format off
            SPDLOG_INFO("Created 0/1 Knapsack = {{ .items = {}, .weight = {} }}", 
                std::to_string(allItems_.size()),
                std::to_string(knapsackMaxWeight_)
            );
            // clang-format on
        }

        size_t getItemCount()
        {
            return items_->size();
        }

        /**
         * @returns all items in the problem space
         */
        std::vector<Knapsack::Item> getProblemSpace()
        {
            return allItems_;
        }

        std::shared_ptr<std::vector<Knapsack::Item>> getItems()
        {
            return items_;
        }

        weight_t getMaxWeight()
        {
            return knapsackMaxWeight_;
        }

        void setProblemSpace(
            std::vector<Knapsack::Item> items)
        {
            allItems_ = items;
        }

        void addItem(
            const ks::Knapsack::Item& item)
        {
            items_->push_back(item);
        }

        void setMaxWeight(
            weight_t weight)
        {
            knapsackMaxWeight_ = weight;
        }

        weight_t getItemsWeight()
        {
            // clang-format off
            return std::accumulate(items_->begin(), 
                                  items_->end(), 
                                  0, 
                                 [](const auto sum, const auto & next) {
                                        return sum + next.weight;
                                    }
            );
            // clang-format on
        }

        profit_t getItemsProfit()
        {
            // clang-format off
            return std::accumulate(items_->begin(), 
                                  items_->end(), 
                                  0, 
                                 [](const auto sum, const auto & next) {
                                        return sum + next.price;
                                    }
            );
            // clang-format on
        }


    private:
        // All potential items
        std::vector<Knapsack::Item> allItems_;
        // A subset of all the potential items. The items which are allowable
        // in the knapsack
        std::shared_ptr<std::vector<Knapsack::Item>> items_;
        // Weight capacity of knapsack
        weight_t knapsackMaxWeight_;
    };

} // namespace ks

#endif // PROG4__KNAPSACK_HH_

std::ostream& operator<<(std::ostream& os, ks::Knapsack::Item item);

std::ostream& operator<<(std::ostream& os, ks::Knapsack knapsack);

//===== GM =========================================================== 80 ====>>
