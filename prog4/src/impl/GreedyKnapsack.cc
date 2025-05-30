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

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <stdlib.h>
#include <vector>

#include "Knapsack.hh"
#include "KnapsackFileReader.hh"
#include "KnapsackFormattedFileWriter.hh"
#include "impl/GreedyKnapsack.hh"
#include "spdlog/spdlog.h"

#ifdef BENCHMARK
#include "KnapsackBenchmarker.hh"
#endif

//===== GM =========================================================== 80 ====>>

std::vector<ks::Knapsack::Item> ks::greedy::Greedy4(
    const ks::Knapsack::shared_ptr& knapsack)
{
    SPDLOG_INFO("Computing Greedy4(knapsack)");
    std::vector<ks::greedy::IBenefit> itemBenefits;
    for (auto& item : knapsack->getProblemSpace())
    {
        ks::greedy::IBenefit itemBenefit{item};
        itemBenefits.push_back(itemBenefit);
    }

    ks::Knapsack::weight_t          weight{0};
    std::vector<ks::Knapsack::Item> solution{};

    // clang-format off
    // sort based on benefit
    std::sort(itemBenefits.begin(), itemBenefits.end(),
        [](const ks::greedy::IBenefit& a, const ks::greedy::IBenefit& b) { 
            return a.benefit > b.benefit;
        });
    // clang-format on

    for (auto& benefit : itemBenefits)
    {
        // the greedy computation
        if (benefit.item.weight + weight <= knapsack->getMaxWeight())
        {
            weight = weight + benefit.item.weight;
            solution.push_back(benefit.item);
        }
        // the greedy computation
    }

    return solution;
}

std::vector<ks::Knapsack::Item> ks::greedy::MaxB(
    const ks::Knapsack::shared_ptr& knapsack)
{
    SPDLOG_INFO("Computing MaxB(knapsack)");
    ks::Knapsack::profit_t profit{0};
    ks::Knapsack::Item     solution;

    for (auto& item : knapsack->getProblemSpace())
    {
        // the greedy computation
        if (item.price > profit and item.weight <= knapsack->getMaxWeight())
        {
            solution = item;
            profit   = item.price;
        }
        // the greedy computation
    }
    return std::vector<ks::Knapsack::Item>{solution};
}

std::vector<ks::Knapsack::Item> ks::greedy::max(
    const std::initializer_list<std::function<std::vector<ks::Knapsack::Item>(const ks::Knapsack::shared_ptr&)>>&
                                    functors,
    const ks::Knapsack::shared_ptr& knapsack)
{
    ks::Knapsack::profit_t          maxProfit{0};
    std::vector<ks::Knapsack::Item> solution{0};

    // iterate over each greedy implementation and pick the best.
    for (auto& functor : functors)
    {
        auto items  = functor(knapsack);
        auto profit = ks::Knapsack::computeProfit(items);
        if (profit > maxProfit) // one solution has a greater profit than the other
        {
            SPDLOG_INFO("New solution found");
            maxProfit = profit;
            solution  = items;
        }
    }

    return solution;
}

void ks::greedy::compute(
    const ks::Knapsack::shared_ptr& knapsack)
{
    std::vector<ks::Knapsack::Item> solutionSet;
    // iterate over each greedy implementation and pick the best.
    solutionSet = ks::greedy::max({ks::greedy::Greedy4, ks::greedy::MaxB}, knapsack);
    for (auto it = solutionSet.begin(); it != solutionSet.end(); ++it)
    {
        knapsack->addItem(*it);
    }
}

int main(
    int args, char** argv)
{
    if (args != 2)
    {
        SPDLOG_ERROR("usage: ./igreedy <input-knapsack-file>");
        return EXIT_FAILURE;
    }

    std::filesystem::path    knapsackInputFile{argv[1]};
    ks::Knapsack::shared_ptr knapsack = ks::KnapsackFileReader::read(knapsackInputFile);

    if (!knapsack)
    {
        return EXIT_FAILURE;
    }

    // clang-format off
    // Benchmarker usable for each implementation of KS
    #ifdef BENCHMARK
        ks::Benchmarker benchmarker{"ks::greedy::compute"};
        
        benchmarker.start();
            ks::greedy::compute(knapsack); 
        benchmarker.end();
    #else
        ks::greedy::compute(knapsack);
    #endif
    // clang-format on

    // clang-format off
    std::cout << std::endl;
    std::cout << "Greedy Knapsack Solution = {" 
              << " .profit = " << std::to_string(knapsack->getItemsProfit()) 
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
        knapsackInputFile.parent_path().append(OUTPUT_FILE(3)
    ),
    ks::KnapsackImpl::GREEDY);
    // clang-format on

    return EXIT_SUCCESS;
}

std::ostream& operator<<(
    std::ostream& os, ks::greedy::IBenefit item)
{
    // clang-format off
    os << item.item.name 
       << "\t.price = " << item.item.price 
       << "\t.weight = " << item.item.weight
       << "\t.benefit = " << item.benefit;
    // clang-format on   
    return os;
}

//===== GM =========================================================== 80 ====>>