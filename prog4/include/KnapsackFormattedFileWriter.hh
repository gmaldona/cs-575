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

#ifndef PROG4__KNAPSACK_FORMATTED_FILE_WRITER_HH_
#define PROG4__KNAPSACK_FORMATTED_FILE_WRITER_HH_


#include <filesystem>
#include <string>

#include "Knapsack.hh"

//===== GM =========================================================== 80 ====>>

namespace ks
{
    /**
     * @brief Takes an knapsack instance and formats into a readable string
     *
     * @param [in] knapsack Pointer to knapsack to format into a string
     * @returns a formatted string containing the metadata of the knapsack problem space
     */
    std::string formatKnapsack(const Knapsack::unique_ptr& knapsack);

    class KnapsackFormattedFileWriter
    {

    public:
        /**
         * @brief Writes a knapsack instance to file
         *
         * @param [in] knapsack Knapsack to write to file
         * @param [in] outputPath Output file to write formatted knapsack string
         *
         * @returns If knapsack write to file was successful
         */
        static bool at(const Knapsack::unique_ptr& knapsack, const std::filesystem::path& outputPath);

    private:
        KnapsackFormattedFileWriter() = default;
    };
} // namespace ks

#endif // PROG4__KNAPSACK_FORMATTED_FILE_WRITER_HH_

//===== GM =========================================================== 80 ====>>
