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

#include <climits>
#include <cmath>
#include <fstream>
#include <memory>
#include <ostream>
#include <stdlib.h>

#include "Knapsack.hh"
#include "KnapsackFileReader.hh"
#include "KnapsackFormattedFileWriter.hh"
#include "impl/BruteforceKnapsack.hh"
#include "spdlog/spdlog.h"

#ifdef BENCHMARK
#include "KnapsackBenchmarker.hh"
#endif

//===== GM =========================================================== 80 ====>>

void ks::bf::compute(
    std::vector<ks::Knapsack::Item> subset, ks::Knapsack::profit_t* profit, ks::Knapsack::weight_t* weight)
{
    for (auto& item : subset)
    {
        *profit = *profit + item.price;
        *weight = *weight + item.weight;
    }
}

void ks::bf::compute(
    const ks::Knapsack::shared_ptr& knapsack)
{
    ks::Knapsack::profit_t          maxProfit{0};
    ks::Knapsack::weight_t          minWeight{knapsack->getMaxWeight()};
    std::vector<ks::Knapsack::Item> solutionSubset{};

    // Compute subsets to find which subset optimizes the problem
    size_t subsets = std::pow(2, knapsack->getProblemSpace().size()) - 1;
    for (size_t subset_index = 0; subset_index < subsets; ++subset_index)
    {
        std::vector<ks::Knapsack::Item> subset;
        for (size_t item_index = 0; item_index < subsets; ++item_index)
        {
            if ((subset_index >> item_index) & 1)
            {
                // std::cout << knapsack->getProblemSpace()[item_index] << std::endl;
                subset.push_back(knapsack->getProblemSpace()[item_index]);
            }
        }

        if (subset.size() == 0)
        {
            continue;
        }

        ks::Knapsack::profit_t profit{0};
        ks::Knapsack::weight_t weight{0};

        ks::bf::compute(subset, &profit, &weight);
        // std::cout << "   total profit = " << profit << " total weight = " << weight << std::endl;

        if (profit > maxProfit && weight < knapsack->getMaxWeight())
        {
            maxProfit      = profit;
            minWeight      = weight;
            solutionSubset = subset;

            SPDLOG_INFO("New max profit = {}, weight = {}", maxProfit, minWeight);
        }

        // std::cout << std::endl;
    }

    for (auto& item : solutionSubset)
    {
        knapsack->addItem(item);
    }
}

int main(
    int args, char** argv)
{
    if (args != 2)
    {
        SPDLOG_ERROR("usage: ./bruteforce <input-knapsack-file>");
        return EXIT_FAILURE;
    }

    std::filesystem::path    knapsackInputFile{argv[1]};
    ks::Knapsack::shared_ptr knapsack{ks::KnapsackFileReader::read(knapsackInputFile)};

    // clang-format off
    // Benchmarker usable for each implementation of KS
    #ifdef BENCHMARK
        ks::Benchmarker benchmarker{"ks::bf::compute"};
        
        benchmarker.start();
            ks::bf::compute(knapsack); 
        benchmarker.end();
    #else
        ks::bf::compute(knapsack);
    #endif
    // clang-format on

    // clang-format off
    std::cout << std::endl;
    std::cout << "Bruteforce Knapsack Solution = {" 
              << " .profit = " << std::to_string(knapsack->computeProfit()) 
              << " .weight = " << std::to_string(knapsack->getItemsWeight()) 
              << " } " << std::endl;
    // clang-format on

    for (auto& item : *knapsack->getItems())
    {
        std::cout << item << std::endl;
    }
    std::cout << std::endl;

    // clang-format off
    ks::KnapsackFormattedFileWriter::at(
        knapsack, 
        knapsackInputFile.parent_path().append(OUTPUT_FILE(1)
    ),
    ks::KnapsackImpl::BRUTEFORCE);
    // clang-format on

    return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>
