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

#include <cstdint>
#include <filesystem>
#include <stdlib.h>
#include <utility>
#include <vector>

#include "Knapsack.hh"
#include "KnapsackFileReader.hh"
#include "impl/DPKnapsack.hh"
#include "spdlog/spdlog.h"

#ifdef BENCHMARK
#include "KnapsackBenchmarker.hh"
#endif

//===== GM =========================================================== 80 ====>>

void ks::dp::compute(
    const ks::Knapsack::shared_ptr& knapsack)
{
    // Refinement DP Approach
    /**
     * a list (
     *  max { (x1, y1), (x2, y2) }
     * ) for each row in DPTable
     *
     * trace are the cells in the DP Table that are required to compute the solution
     * to the kapsack problem. All other cells are not needed
     */
    std::vector<std::vector<std::pair<uint64_t, uint64_t>>> trace;


    // initialize the DP Table: vector<vector<Item>>
    ks::dp::DPTable_t dpTable(knapsack->getProblemSpace().size() + 1);
    for (auto& row : dpTable)
    {
        row = ks::dp::DPCol_t(knapsack->getMaxWeight() + 1);
    }
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

    // clang-format off
    // Benchmarker usable for each implementation of KS
    #ifdef BENCHMARK
        ks::Benchmarker benchmarker{"ks::dp::compute"};
        
        benchmarker.start();
            ks::dp::compute(knapsack); 
        benchmarker.end();
    #else
        ks::dp::compute(knapsack);
    #endif
    // clang-format on

    return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>
