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

#ifndef PROG4__KNAPSACK_FILE_READER_HH_
#define PROG4__KNAPSACK_FILE_READER_HH_

#define DELIMITER " "

// Log and return macro for error on read
#define RET_KS_ERROR                                                                                      \
    do                                                                                                    \
    {                                                                                                     \
        SPDLOG_WARN("Error detected in auto-generated knapsack file. Please regenerate knapsack input."); \
        return nullptr;                                                                                   \
    } while (0)
;

#include <filesystem>
#include <memory>

#include "Knapsack.hh"

//===== GM =========================================================== 80 ====>>

namespace ks
{

    class KnapsackFileReader
    {

    public:
        /**
         * @brief Reads in Knapsack file and generates a \ns ks::Knapsack instance
         *
         * @param [in] knapsackFilePath Input path to a knapsack file
         * @returns A knapsack instance created by read in file
         */
        static ks::Knapsack::shared_ptr read(const std::filesystem::path& knapsackFilePath);

    private:
        KnapsackFileReader()  = default;
        ~KnapsackFileReader() = default;
    };

} // namespace ks

#endif // PROG4__KNAPSACK_FILE_READER_HH_

//===== GM =========================================================== 80 ====>>
