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

#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>

#include "KnapsackFormattedFileWriter.hh"

//===== GM =========================================================== 80 ====>>

namespace ks
{
    std::string formatInitKnapsack(
        const Knapsack::shared_ptr& knapsack)
    {
        // clang-format off
        std::string formatted = std::to_string(knapsack->getProblemSpace().size()) + " "
                              + std::to_string(knapsack->getMaxWeight()) + "\n";
        // clang-format on

        for (auto& item : knapsack->getProblemSpace())
        {
            // clang-format off
            formatted += (item.name + " " 
                      +   std::to_string(item.price) + " " 
                      +   std::to_string(item.weight) + "\n"
                    );
            // clang-format on
        }

        return formatted;
    }

    std::string formatKnapsackSolution(
        const Knapsack::shared_ptr& knapsack)
    {
        // clang-format off
        std::string formatted = std::to_string(knapsack->getItems()->size()) + " "
                              + std::to_string(knapsack->getItemsProfit())   + " "
                              + std::to_string(knapsack->getItemsWeight())   + "\n\n";

        std::sort(knapsack->getItems()->begin(), knapsack->getItems()->end(),
                    [](const ks::Knapsack::Item& a, const ks::Knapsack::Item& b) {
                        return a.name < b.name;
                    });
        // clang-format on

        for (auto& item : *(knapsack->getItems()))
        {
            // clang-format off
            formatted += (item.name + " " 
                      +   std::to_string(item.price) + " " 
                      +   std::to_string(item.weight) + "\n"
                    );
            // clang-format on
        }

        return formatted;
    }

    void formatDPKnapsack(
        const Knapsack::shared_ptr&, const std::filesystem::path& entriesOutputPath,
        const std::vector<std::vector<int64_t>>& entries)
    {
        std::ofstream entriesOutputFile;

        entriesOutputFile.open(entriesOutputPath);
        if (!entriesOutputFile.is_open())
        {
            SPDLOG_ERROR("Failed to write Dynamic Programming table to: {}", entriesOutputPath.c_str());
        }

        std::string formatted;
        for (size_t row = 1; row < entries.size(); ++row)
        {
            formatted += ("row" + std::to_string(row));
            for (size_t col = 0; col < entries[row].size(); ++col)
            {
                if (entries[row][col] >= 0)
                {
                    formatted += ("\t" + std::to_string(entries[row][col]));
                }
            }

            formatted += "\n";
        }

        entriesOutputFile << formatted;
        SPDLOG_INFO("Writing to: {}", entriesOutputPath.c_str());
    }

    bool ks::KnapsackFormattedFileWriter::at(
        const Knapsack::shared_ptr& knapsack, const std::filesystem::path& outputPath, ks::KnapsackImpl impl)
    {
        std::ofstream outputFile;

        outputFile.open(outputPath);
        if (!outputFile.is_open())
        {
            SPDLOG_ERROR("Failed to write Knapsack to: {}", outputPath.c_str());
            return false;
        }

        switch (impl)
        {
        case ks::KnapsackImpl::INIT:
            outputFile << formatInitKnapsack(knapsack);
            break;
        case ks::KnapsackImpl::DP:
        case ks::KnapsackImpl::GREEDY:
        case ks::KnapsackImpl::BRUTEFORCE:
            outputFile << formatKnapsackSolution(knapsack);
            break;
        default:
            SPDLOG_WARN("Failed to write knapsack solution on disk.");
            return false;
        }

        SPDLOG_INFO("Writing to: {}", outputPath.c_str());
        return true;
    }
} // namespace ks

//===== GM =========================================================== 80 ====>>
