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

    std::string line;
    while (getline(knapsackFile, line))
    {
        std::cout << line << std::endl;
    }

    return std::make_unique<ks::Knapsack>();
}

//===== GM =========================================================== 80 ====>>
