/*
* CS 575 - Programming Assignment 1
*
* Graduate student @ School of Computing, Binghamton University.
*
* author: Gregory Maldonado
* email : gmaldonado@cs.binghamton.edu
* date  : 2025-01-30
* web   : https://cs.binghamton.edu/~gmaldonado/
*
*  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#pragma once

#ifndef PROG1__BASEBALL_CARDS_H_
#define PROG1__BASEBALL_CARDS_H_

#include <chrono>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

#include <unistd.h>

//===== GM =========================================================== 80 ====>>

typedef uint64_t cost_t;
typedef std::chrono::duration<double_t> duration_t;

struct card_s {
   std::string name;
   cost_t      cost;

   bool operator==(const card_s& other) const;
};

struct price_list_s {
   uint64_t cards;
   uint64_t max_cost;

   bool operator==(const price_list_s& other) const;
};

/**
 * Hashing functor for price_list_s
 *
 * A hashing functor is required to set a price_list_s as a key to an unordered
 * map<price_list_s, card_set_ptr_t>.
 *
 * source for creating a hashing functor:
 * https://stackoverflow.com/questions/17016175
 */
template <>
struct std::hash<price_list_s> {
   std::size_t operator()(const price_list_s& price_list) const {
      std::hash<size_t> hash_cards;
      std::hash<size_t> hash_max_cost;

      return hash_cards(price_list.cards)
         ^ (hash_max_cost(price_list.max_cost) << 1);
   }
};

typedef std::vector<card_s>                               __card_set_t;
typedef std::shared_ptr<__card_set_t>                       card_set_t;

typedef std::unordered_map<std::string, cost_t>          __market_price_t;
typedef std::shared_ptr<__market_price_t>                  market_price_t;

typedef std::unordered_map<price_list_s, card_set_t>     __price_lists_t;
typedef std::shared_ptr<__price_lists_t>                   price_lists_t;

typedef std::pair<price_list_s, card_set_t>                price_list_t;

/**
 * A "Result" struct to store computation results in.
 * The data recorded within this struct ultimately is what ends up in the output
 * file.
 */
struct result_s {
   size_t       input_size;
   cost_t       profit;
   __card_set_t card_set;
   double_t     duration;
};

std::ostream& operator<<(std::ostream& os, const market_price_t& market_price);

std::ostream& operator<<(std::ostream& os, const price_lists_t& price_list);

std::ostream& operator<<(std::ostream& os, const card_set_t& card_set);

void write_output(const std::string& filename,
                  const result_s&    result);

void read_market_price(const std::string&     filename,
                       const market_price_t&  market_price);

void read_price_lists(const std::string&  filename,
                     const price_lists_t& price_lists);

/**
 * Function that looks each card in a card set and computes the market price for
 * a given card MINUS what the user paid for the card
 *
 * @param market_price
 * @param set
 * @return
 */
cost_t compute_profit(const market_price_t& market_price,
                      const card_set_t& set);

/**
 *
 * @param market_price is the name of a file that contains baseball card market
 * prices (that is, the price at which you could sell each card). The first line
 * of the file contains only an integer that indicates how many cards and prices
 * reside in the rest of the file, one card per line
 * @param price_list is the name of a file that contains a sequence of “price
 * lists” for Gertrude’s baseball cards. You will use the price lists file to
 * test your program for several potential price lists, so that you are sure you
 * are ready for whatever price list Gertrude gives you, and for however much
 * money you will be able to spend.
 * @param output is the name of a file that contains the output. Each line in
 * the output file corresponds to a single problem and will contain four numbers
 * (separated by one space), in the following order:
        • The size of the input (the number of cards in the price list for this
            problem)
        • The computed maximum profit, in integer dollars
        • The number of cards that you could purchase to achieve the maximum
            profit
        • The time (in seconds) it took to solve the problem.
 */
void compute_max_profit(const std::string& market_price,
                        const std::string& price_list,
                        const std::string& output);


/**
 * Pseudo-code for maximizing.
 *
 * ComputeMaxProfit(I, W):
 *      maxProfit = 0
 *      S         = empty set
 *      M         = empty set
 *
 *      if the sum of weights in I <= W:
 *          return the profit of items in I, and I
 *      while more subsets to generate:
 *          if the sum of the weights in S <= W:
 *              if the profit of the items in S > maxProfit:
 *                  update maxProfit
 *
 *          generate next subset
 *      return maxProfit and M
 *
 * @param market_price
 * @param price_list
 */

result_s
compute_max_profit(const market_price_t& market_price,
                   const price_list_t&   price_list);

#endif //PROG1__BASEBALL_CARDS_H_

//===== GM =========================================================== 80 ====>>
