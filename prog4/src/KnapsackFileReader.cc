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
#include <memory>
#include <string>

#include "KnapsackFileReader.hh"
#include "spdlog/spdlog.h"

//===== GM =========================================================== 80 ====>>

ks::Knapsack::unique_ptr ks::KnapsackFileReader::read(
    const std::filesystem::path& knapsackFilePath)
{
    std::ifstream knapsackFile;
    knapsackFile.open(knapsackFilePath);

    if (!knapsackFile.is_open())
    {
        SPDLOG_WARN("Failed to open knapsack file: {}", knapsackFilePath.c_str());
        return nullptr;
    }

    bool isHeader = true;

    size_t                          itemCount{0};
    ks::Knapsack::weight_t          maxWeight{0};
    std::vector<ks::Knapsack::Item> items{};

    std::string line;
    while (getline(knapsackFile, line))
    {
        if (line.empty())
        {
            continue;
        }
        // The first line in the file: <number of items> <knapsack max weight>
        if (isHeader)
        {
            auto delimiterIndex = line.find(DELIMITER);
            if (delimiterIndex != std::string::npos)
            {
                itemCount = std::stoi(line.substr(0, delimiterIndex));
                maxWeight = std::stoi(line.substr(delimiterIndex + 1, line.size()));
            }
            else
            {
                RET_KS_ERROR;
            }
            isHeader = !isHeader;
        }
        // The remaining of the file, each line is an item: <item.name> <item.price> <item.weight>
        else
        {
            auto delimiterIndex = line.find(DELIMITER);
            if (delimiterIndex != std::string::npos)
            {
                std::string itemName  = line.substr(0, delimiterIndex);
                std::string remaining = line.substr(delimiterIndex + 1, line.size());

                delimiterIndex = remaining.find(DELIMITER);
                if (delimiterIndex != std::string::npos)
                {
                    // clang-format off
                    ks::Knapsack::profit_t itemPrice  = std::stoi(remaining.substr(0, delimiterIndex));
                    ks::Knapsack::weight_t itemWeight = std::stod(remaining.substr(delimiterIndex + 1, remaining.size()));
                    
                    items.push_back(ks::Knapsack::Item {
                        .name   = itemName,
                        .price  = itemPrice,
                        .weight = itemWeight
                    });
                    // clang-format on
                }
                else
                {
                    RET_KS_ERROR;
                }
            }
            else
            {
                RET_KS_ERROR;
            }
        }
    }

    if (itemCount != items.size())
    {
        RET_KS_ERROR;
    }

    return std::make_unique<ks::Knapsack>(items, maxWeight);
}

//===== GM =========================================================== 80 ====>>
