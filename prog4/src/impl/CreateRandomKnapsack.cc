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

#include <cmath>
#include <fstream>
#include <list>
#include <numeric>
#include <random>

#include "KnapsackFormattedFileWriter.hh"
#include "impl/CreateRandomKnapsack.hh"
#include "spdlog/spdlog.h"

//===== GM =========================================================== 80 ====>>

/**
 * Randomly create a 0/1 Knapsack problem as follows:
 *
 * Create n items where n is an integer randomly selected between 5 and 10.
 * Display the selected n value. Create a list of n items where each item has
 * profit pi and weight wi where 1) pi is a positive integer randomly selected
 * between 10 and 30; and 2) wi is a positive integer randomly selected between
 * 5 and 20. Set the capacity of the knapsack W = floor(0.6 * ∑! 𝑤i).
 */

ks::Knapsack::unique_ptr ks::random::createKnapsack()
{
    std::random_device randomDeviceSeed;
    std::mt19937       generator(randomDeviceSeed());

    // clang-format off
    // randomizier item count
    std::uniform_int_distribution<size_t> knapsackSize(ITEMS_LOWER_BOUND, ITEMS_UPPER_BOUND);
    // randomizier item profit
    std::uniform_int_distribution<ks::Knapsack::profit_t> profit(ITEM_PROFIT_LOWER_BOUND, ITEM_PROFIT_UPPER_BOUND);
    // randomizier item weight
    std::uniform_real_distribution<ks::Knapsack::weight_t> weight(ITEM_WEIGHT_LOWER_BOUND, ITEM_WEIGHT_UPPER_BOUND);
    // clang-format on

    std::list<ks::Knapsack::Item> items;
    for (size_t i = 0; i < knapsackSize(generator); ++i)
    {
        ks::Knapsack::profit_t itemProfit = profit(generator);
        ks::Knapsack::weight_t itemWeight = weight(generator);
        // clang-format off
        items.push_back(ks::Knapsack::Item {
            .name = "item" + std::to_string(i),
            .price = itemProfit,
            .weight = itemWeight
        });
        // clang-format on
    }

    // clang-format off
    ks::Knapsack::weight_t knapsackWeight = std::floor(0.6 * std::accumulate(items.begin(), 
                                                                             items.end(), 
                                                                             0, 
                                                                             [](const auto sum, const auto & next) {
                                                                                    return sum + next.weight;
                                                                            }
                                                                        )
                                                    );
    // clang-format on

    return std::make_unique<Knapsack>(items, knapsackWeight);
}

int main(
    int args, char** argv)
{
    if (args != 2)
    {
        SPDLOG_ERROR("usage: ./createkn01 <output-knapsack-file>");
        return EXIT_FAILURE;
    }

    std::filesystem::path    knapsackOutputFile{argv[1]};
    ks::Knapsack::unique_ptr knapsack{ks::random::createKnapsack()};

    ks::KnapsackFormattedFileWriter::at(knapsack, knapsackOutputFile);
}

//===== GM =========================================================== 80 ====>>
