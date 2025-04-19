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

#include <filesystem>
#include <stdlib.h>

#include "Knapsack.hh"
#include "KnapsackFileReader.hh"
#include "spdlog/spdlog.h"

//===== GM =========================================================== 80 ====>>

int main(
    int args, char** argv)
{
    if (args != 2)
    {
        SPDLOG_ERROR("usage: ./bruteforce <output-knapsack-file>");
        return EXIT_FAILURE;
    }

    std::filesystem::path    knapsackInputFile{argv[1]};
    ks::Knapsack::shared_ptr knapsack = ks::KnapsackFileReader::read(knapsackInputFile);

    return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>
