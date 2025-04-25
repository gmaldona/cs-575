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

#include "Knapsack.hh"

//===== GM =========================================================== 80 ====>>

std::ostream& operator<<(
    std::ostream& os, ks::Knapsack::Item item)
{
    os << item.name << "\t.price = " << item.price << "\t.weight = " << item.weight;
    return os;
}

std::ostream& operator<<(
    std::ostream& os, ks::Knapsack knapsack)
{
    auto size   = knapsack.getProblemSpace().size();
    auto weight = knapsack.getMaxWeight();

    os << std::endl;
    os << "==== Knapsack Info ====" << std::endl;
    os << "items = " << std::to_string(size);
    os << ", max weight = " << std::to_string(weight) << std::endl << std::endl;
    os << "all potential items = [" << std::endl;
    for (auto& item : knapsack.getProblemSpace())
    {
        os << "   " << item;
    }
    os << "]" << std::endl;
    os << "==== Knapsack Info ====" << std::endl;

    return os;
}

//===== GM =========================================================== 80 ====>>