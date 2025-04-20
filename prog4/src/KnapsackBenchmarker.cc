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

#include "KnapsackBenchmarker.hh"
#include "spdlog/spdlog.h"

//===== GM =========================================================== 80 ====>>

ks::Benchmarker::Benchmarker(
    std::string name)
    : name_{name}
    , start_{}
{
}

void ks::Benchmarker::start()
{
    start_ = std::chrono::high_resolution_clock::now();
    SPDLOG_INFO("Created a Benchmark start point: {}", name_);
}

std::chrono::duration<double> ks::Benchmarker::checkpoint()
{
    return std::chrono::high_resolution_clock::now() - start_;
}

void ks::Benchmarker::end()
{
    SPDLOG_INFO("{} total benchmark runtime: {}", name_, std::to_string(checkpoint().count()));
    ks::Benchmarker::~Benchmarker();
}


//===== GM =========================================================== 80 ====>>
