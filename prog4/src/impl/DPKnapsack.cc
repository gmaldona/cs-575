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
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <utility> // std::pair
#include <vector>

#include "Knapsack.hh"
#include "KnapsackFileReader.hh"
#include "KnapsackFormattedFileWriter.hh"
#include "impl/DPKnapsack.hh"
#include "spdlog/spdlog.h"

#ifdef BENCHMARK
#include "KnapsackBenchmarker.hh"
#endif

//===== GM =========================================================== 80 ====>>

ks::Knapsack::profit_t ks::dp::computeDPEntry(
    const ks::Knapsack::shared_ptr& knapsack, const DPTable_t& dpTable, point_t&& point)
{
    if (knapsack->getProblemSpace()[point.first - 1].weight <= point.second)
    {
        // clang-format off
        std::vector<int64_t> entries = {
            (*(*dpTable)[point.first - 1])[point.second],
            knapsack->getProblemSpace()[point.first - 1].price + (*(*dpTable)[point.first - 1])[point.second - knapsack->getProblemSpace()[point.first - 1].weight]
        };
        // clang-format on

        return *std::max_element(
            entries.begin(), entries.end(), [](int a, int b) { return std::abs(a) < std::abs(b); });
    }
    else
    {
        return (*(*dpTable)[point.first - 1])[point.second];
    }
}

void ks::dp::rcompute(
    const ks::Knapsack::shared_ptr& knapsack, const DPTable_t& dpTable, std::vector<std::vector<int64_t>>& entries,
    point_t&& point, size_t depth)
{
    if (point.first == 1)
    {
        (*(*dpTable)[point.first])[point.second] = computeDPEntry(knapsack, dpTable, std::move(point));
        entries[point.first].push_back((*(*dpTable)[point.first])[point.second]);
        return;
    }

    // clang-format off
    point_t lpoint = std::make_pair(point.first - 1, point.second);
    point_t rpoint = std::make_pair(point.first - 1, point.second - knapsack->getProblemSpace()[point.first - 1].weight);
    // clang-format on

    depth++;
    if (lpoint.first >= 0 && lpoint.second >= 0)
    {
        rcompute(knapsack, dpTable, entries, std::move(lpoint), depth);
    }

    if (rpoint.first >= 0 && rpoint.second >= 0)
    {
        rcompute(knapsack, dpTable, entries, std::move(rpoint), depth);
    }
    depth--;

    (*(*dpTable)[point.first])[point.second] = computeDPEntry(knapsack, dpTable, std::move(point));
    entries[point.first].push_back((*(*dpTable)[point.first])[point.second]);
}

std::vector<std::vector<int64_t>> ks::dp::compute(
    const ks::Knapsack::shared_ptr& knapsack, ks::dp::DPTable_t& dpTable)
{
    dpTable = std::make_shared<__DPRow_t>(knapsack->getProblemSpace().size() + 1);
    std::vector<std::vector<int64_t>> entries(knapsack->getProblemSpace().size() + 1);
    for (auto& row : *dpTable)
    {
        row = std::make_shared<__DPCol_t>(knapsack->getMaxWeight() + 1, 0);
    }

    rcompute(
        knapsack, dpTable, entries, std::make_pair(knapsack->getProblemSpace().size(), knapsack->getMaxWeight()), 0);

    int64_t i = knapsack->getProblemSpace().size();
    int64_t w = knapsack->getMaxWeight();
    while (i > 0 && w > 0)
    {
        if ((*(*dpTable)[i])[w] != (*(*dpTable)[i - 1])[w])
        {
            knapsack->addItem(knapsack->getProblemSpace()[i - 1]);
            w -= knapsack->getProblemSpace()[i - 1].weight;
            i--;
        }
        else
        {
            i--;
        }
    }

    return entries;
}

int main(
    int args, char** argv)
{
    if (args != 2)
    {
        SPDLOG_ERROR("usage: ./dynpro <input-knapsack-file>");
        return EXIT_FAILURE;
    }

    std::filesystem::path    knapsackInputFile{argv[1]};
    ks::Knapsack::shared_ptr knapsack = ks::KnapsackFileReader::read(knapsackInputFile);

    if (!knapsack)
    {
        return EXIT_FAILURE;
    }

    ks::dp::DPTable_t                 dpTable{};
    std::vector<std::vector<int64_t>> entries;
    // clang-format off
    // Benchmarker usable for each implementation of KS
    #ifdef BENCHMARK
        ks::Benchmarker benchmarker{"ks::dp::compute"};
        
        benchmarker.start();
            entries = ks::dp::compute(knapsack, dpTable);
        benchmarker.end();
    #else
        entries = ks::dp::compute(knapsack, dpTable);
    #endif
    // clang-format on

    // clang-format off
    std::cout << std::endl;
    std::cout << "DP Knapsack Solution = {"
              << " .profit = " << std::to_string(knapsack->getItemsProfit())
              << " .weight = " << std::to_string(knapsack->getItemsWeight())
              << " } " << std::endl;
    // clang-format on

    for (auto& item : *knapsack->getItems())
    {
        std::cout << item << std::endl;
    }
    std::cout << std::endl;

    ks::formatDPKnapsack(knapsack, knapsackInputFile.parent_path().append("entries2.txt"), entries);

    // clang-format off
    ks::KnapsackFormattedFileWriter::at(
        knapsack, 
        knapsackInputFile.parent_path().append(OUTPUT_FILE(2)
    ),
    ks::KnapsackImpl::DP);
    // clang-format on

    return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>
