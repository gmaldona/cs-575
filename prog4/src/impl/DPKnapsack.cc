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
#include <filesystem>
#include <stdlib.h>
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
        return (*(*dpTable)[point.first - 1])[knapsack->getMaxWeight()];
    }
}

void ks::dp::rcompute(
    const ks::Knapsack::shared_ptr& knapsack, const DPTable_t& dpTable, point_t&& point, size_t depth)
{
    if (point.first == 1)
    {
        (*(*dpTable)[point.first])[point.second] = computeDPEntry(knapsack, dpTable, std::move(point));
        // std::cout << std::string(depth, '\t') << point << " = "
        //           << std::to_string((*(*dpTable)[point.first])[point.second]) << std::endl;
        return;
    }

    // clang-format off
    point_t lpoint = std::make_pair(point.first - 1, point.second);
    point_t rpoint = std::make_pair(point.first - 1, point.second - knapsack->getProblemSpace()[point.first - 1].weight);
    // clang-format on

    depth++;

    rcompute(knapsack, dpTable, std::move(lpoint), depth);
    rcompute(knapsack, dpTable, std::move(rpoint), depth);

    depth--;

    (*(*dpTable)[point.first])[point.second] = computeDPEntry(knapsack, dpTable, std::move(point));

    /*
    std::cout << std::string(depth, '\t') << point << " = " << std::to_string((*(*dpTable)[point.first])[point.second])
              << std::endl;


    std::cout << std::endl;
    */
}

ks::dp::DPTable_t ks::dp::compute(
    const ks::Knapsack::shared_ptr& knapsack)
{
    ks::dp::DPTable_t dpTable = std::make_shared<__DPRow_t>(knapsack->getProblemSpace().size() + 1);
    for (auto& row : *dpTable)
    {
        row = std::make_shared<__DPCol_t>(knapsack->getMaxWeight() + 1, 0);
    }

    for (auto& item : knapsack->getProblemSpace())
    {
        std::cout << item << std::endl;
    }

    rcompute(knapsack, dpTable, std::make_pair(knapsack->getProblemSpace().size(), knapsack->getMaxWeight()), 0);

    size_t i = knapsack->getProblemSpace().size();
    size_t w = knapsack->getMaxWeight();
    while (i > 0 && w > 0)
    {
        if ((*(*dpTable)[i])[w] != (*(*dpTable)[i - 1])[w])
        {
            knapsack->addItem(knapsack->getProblemSpace()[i - 1]);
            w -= knapsack->getProblemSpace()[i - 1].weight;
            i--;
        }
    }

    return dpTable;
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

    ks::dp::DPTable_t dpTable{};
    // clang-format off
    // Benchmarker usable for each implementation of KS
    #ifdef BENCHMARK
        ks::Benchmarker benchmarker{"ks::dp::compute"};
        
        benchmarker.start();
            dpTable = ks::dp::compute(knapsack); 
        benchmarker.end();
    #else
        dpTable = ks::dp::compute(knapsack);
    #endif
    // clang-format on

    for (auto& item : *knapsack->getItems())
    {
        std::cout << item << std::endl;
    }
    std::cout << std::endl;

    ks::formatDPKnapsack(knapsack, knapsackInputFile.parent_path().append("entries2.txt"), dpTable);

    // clang-format off
    ks::KnapsackFormattedFileWriter::at(
        knapsack, 
        knapsackInputFile.parent_path().append(OUTPUT_FILE(2)
    ),
    ks::KnapsackImpl::BRUTEFORCE);
    // clang-format on

    return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>
