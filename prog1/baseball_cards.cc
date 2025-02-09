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

#include <fstream>
#include <stdexcept>
#include <cmath>

#include <getopt.h>

#include "baseball_cards.h"

using namespace std;
using namespace std::chrono;

//===== GM =========================================================== 80 ====>>

bool card_s::operator==(const card_s &other) const {
   return this->name == other.name && this->cost == other.cost;
}

bool price_list_s::operator==(const price_list_s& other) const {
   return this->cards == other.cards && this->max_cost == other.max_cost;
}

ostream& operator<<(ostream& os, const __card_set_t& card_set) {
   for (auto& card : card_set) {
      os << card.name << ":" << card.cost << "; ";
   }
   return os;
}

ostream& operator<<(ostream& os, const market_price_t& market_price) {
   os << "Market Prices: " << std::endl;
   for (auto& [name, price] : *market_price) {
      os << "\t" << name << " : " << price << std::endl;
   }
   return os;
}

ostream & operator<<(ostream& os, const price_lists_t& price_list) {
   uint64_t current_entry = 1;
   for (auto& [list_entry, card_set ] : *price_list) {
      os << "Problem #" << current_entry << ":" << std::endl;
      for (auto& [name, price] : *card_set) {
         os << "\t" << name << " : " << price << std::endl;
      }
      current_entry++;
   }
   return os;
}

void write_output(const std::string& filename,
                  const result_s&    result) {
   string output_text = to_string(result.input_size).append(" ")
                     .append(to_string(result.profit)).append(" ")
                     .append(to_string(result.card_set.size())).append(" ")
                     .append(to_string(result.duration))
                     .append("\n");

   for (auto& card : result.card_set) {
      output_text.append(card.name).append("\n");
   }

   ofstream output_file(filename, std::ios_base::app);
   if (output_file.is_open()) {
      output_file << output_text;
      output_file.close();
   } else {
      std::cerr << "[ERROR] could not write to " << filename << std::endl;
   }

   cout << output_text << std::endl;
}


void read_market_price(const string& filename,
                       const market_price_t& market_price) {

   ifstream market_price_file;
   string line;
   size_t line_number = 1;

   market_price_file.open(filename);
   if (market_price_file.is_open()) {

      while(market_price_file) {
         getline(market_price_file, line);

         if (line.empty()) { continue; }

         if (line_number > 1) {
            string name    = line.substr(0, line.find(' '));
            uint64_t price = stoi(line.substr(line.find(' ') + 1));

            (*market_price)[name] = price;
         }

         line_number++;
      }
   } else {
      std::cerr << "Failed to open: " << filename << std::endl;
      exit(1);
   }
}

void read_price_lists(const std::string& filename,
                      const price_lists_t& price_lists) {
   ifstream price_lists_file;
   string line;

   price_lists_file.open(filename);
   if(price_lists_file.is_open()) {

      while(price_lists_file.peek() != EOF) {
         getline(price_lists_file, line);

         if (line.empty()) { break; }

         uint64_t cards    = stoi(line.substr(0, line.find(' ')));
         uint64_t max_cost = stoi(line.substr(line.find(' ') + 1));

         price_list_s list_entry = { .cards = cards, .max_cost = max_cost };
         card_set_t card_set = std::make_shared<__card_set_t>();

         // Used as a hack for hashing
         list_entry.random_memory_ptr = reinterpret_cast<std::uintptr_t>(card_set.get());

         price_lists->insert(make_pair(list_entry, card_set));

         for (int i = 0; i < cards; ++i) {
            if (price_lists_file.peek() == EOF) { break; }

            getline(price_lists_file, line);

            if (line.empty()) { continue; }

            string name    = line.substr(0, line.find(' '));
            uint64_t cost  = stoi(line.substr(line.find(' ') + 1));
            card_s card = { .name = name, .cost = cost };
            (*price_lists)[list_entry]->push_back(card);
         }
      }
   } else {
      std::cerr << "Failed to open: " << filename << std::endl;
   }
}

inline cost_t compute_set_cost(const __card_set_t& set) {
   cost_t total_cost = 0;
   for (auto& card : set) {
      total_cost += card.cost;
   }
   return total_cost;
}

cost_t compute_profit(const market_price_t& market_price,
                      const __card_set_t& set) {
   cost_t profit = 0;
   for (auto& card : set) {
      __market_price_t::const_iterator itr = market_price->find(card.name);
      if (itr == market_price->end()) {
         std::cerr << "[ERROR] Card \"" << card.name
                   << "\" was not found in market_price list." << std::endl;
         std::cerr << "[INFO] Skipping price list problem ... "     << std::endl;
       throw std::exception();
      } else {
         profit += ((*market_price)[card.name] - card.cost);
      }
   }
   return profit;
}

result_s
compute_max_profit(const market_price_t& market_price,
                     const price_list_t&   price_list) {
   size_t cards       = price_list.first.cards;
   cost_t max_cost    = price_list.first.max_cost;
   card_set_t set     = price_list.second;

   __card_set_t maximized_set;
   cost_t max_profit = 0;

   auto start = high_resolution_clock::now();
   if (compute_set_cost(*set) <= max_cost) {
      try {
         result_s result = {
            .input_size = set->size(),
            .profit     = compute_profit(market_price, *set),
            .card_set   = *set
         };

         auto end = high_resolution_clock::now();
         result.duration = duration_cast<duration_t>(end - start).count();

         return result;

      } catch (const std::exception& e) {
         throw;
      }
   }

   size_t subsets = pow(2, cards) - 1;
   for (size_t subset_index = 0; subset_index < subsets; ++subset_index) {
      __card_set_t subset;
      for (size_t card_index = 0; card_index < cards; ++card_index) {
         if ( (subset_index >> card_index) & 1 ) {
            subset.push_back((*set)[card_index]);
         }
      }

      try {
         cost_t profit = compute_profit(market_price, subset);
         if (compute_set_cost(subset) <= max_cost && profit > max_profit) {
            max_profit    = profit;
            maximized_set = subset;
         }
      } catch (const std::exception& e) {
         throw;
      }
   }

   result_s result = {
      .input_size = set->size(),
      .profit     = max_profit,
      .card_set   = maximized_set,
   };

   auto end = high_resolution_clock::now();
   result.duration =  duration_cast<duration_t>(end - start).count();

   return result;
}

void compute_max_profit(const string& market_price_filename,
                        const string& price_list_filename,
                        const string& output_filename) {
   market_price_t market_price = std::make_shared<__market_price_t>();
   price_lists_t   price_list  = std::make_shared<__price_lists_t>();

   read_market_price(market_price_filename, market_price);
   read_price_lists(price_list_filename, price_list);

   std::cout << market_price << std::endl;
   std::cout << price_list   << std::endl;

   uint64_t problem = 1;
   for (
      auto& [list_entry, card_set] : *price_list
   ) {
      result_s result;
      try {
         result
            = compute_max_profit(market_price, make_pair(list_entry, card_set));
      } catch (const std::exception& e) {
         continue;
      }

      if (problem == 1) {
         cout << endl << "============ OUTPUT ============" << endl << endl;
      }
      write_output(output_filename, result);

      problem++;
   }
}


int main(int argc, char *argv[]) {
   int opt;
   std::string market_price;
   std::string price_list;
   std::string output;

   while ((opt = getopt(argc, argv, "m:p:o:")) != -1) {
      switch (opt) {
         case 'm':
            market_price = string(optarg);
            break;
         case 'p':
            price_list = string(optarg);
            break;
         case 'o':
            output = string(optarg);
            break;
         default:
            std::cerr << "[ERROR] bad argument: " << opt << std::endl;
      }
   }

   if (market_price.empty() || price_list.empty() || output.empty()) {
      std::cerr << "[ERROR] failed to provide one or more correct arguments."
                << std::endl;
      return EXIT_FAILURE;
   }

   ofstream output_file(output, std::ofstream::out | std::ofstream::trunc);
   if (output_file.is_open()) {
      output_file.close();
   }

   compute_max_profit(market_price, price_list, output);

   cout << "[INFO] Writing results to: " << output << endl << endl;

   return EXIT_SUCCESS;
}

//===== GM =========================================================== 80 ====>>
