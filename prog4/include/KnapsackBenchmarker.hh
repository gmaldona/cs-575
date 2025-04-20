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

#ifndef PROG4__KNAPSACK_BENCHMARKER_HH_
#define PROG4__KNAPSACK_BENCHMARKER_HH_

#include <chrono>
#include <functional>
#include <string>

#include "Knapsack.hh"
#include "spdlog/spdlog.h"

//===== GM =========================================================== 80 ====>>

namespace ks
{

    /**
     *
     */
    class Benchmarker
    {
    public:
        /**
         * @brief Creates a benchmark timer capable of logging several benchmark times
         *
         * @param [in] name Benchmark name
         */
        Benchmarker(std::string name);

        ~Benchmarker() = default;

        /**
         * @brief Starts the benchmark timer
         */
        void start();

        /**
         * @returns A time lapse between now and the start of the benchmark
         */
        std::chrono::duration<double> checkpoint();

        /**
         * @brief Logs out final benchmark time and destroys benchmarker
         */
        void end();

    private:
        std::string                                                 name_;
        std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    };

} // namespace ks

#endif // PROG4__KNAPSACK_BENCHMARKER_HH_

//===== GM =========================================================== 80 ====>>
