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
#include <spdlog/spdlog.h>

#include "KnapsackFileReader.hh"
#include "impl/BruteforceKnapsack.hh"

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
    ks::Knapsack::unique_ptr& knapsack)
{
    ks::Knapsack::profit_t max_profit{0};
    ks::Knapsack::weight_t min_weight{std::numeric_limits<ks::Knapsack::weight_t>::max()};

    size_t subsets = std::pow(2, knapsack->getProblemSpace().size()) - 1;
    for (size_t subset_index = 0; subset_index < subsets; ++subset_index)
    {
        std::vector<ks::Knapsack::Item> subset;
        for (size_t item_index = 0; item_index < subsets; ++item_index)
        {
            if ((subset_index >> item_index) & 1)
            {
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

        if (profit > max_profit && weight < min_weight)
        {
            max_profit = profit;
            min_weight = weight;

            SPDLOG_INFO("New max profit = {}, min weight = {}", max_profit, min_weight);
        }
    }
}

int main(
    int args, char** argv)
{
    if (args != 2)
    {
        SPDLOG_ERROR("usage: ./createkn01 <output-knapsack-file>");
        return EXIT_FAILURE;
    }

    std::filesystem::path    knapsackInputFile{argv[1]};
    ks::Knapsack::unique_ptr knapsack = ks::KnapsackFileReader::read(knapsackInputFile);

    ks::bf::compute(knapsack);

    return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>
