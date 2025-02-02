#include <iostream>
#include <getopt.h>
#include <fstream>
#include <unistd.h>
#include <unordered_map>

#include "baseball_cards.h"

using namespace std;

ostream& operator<<(ostream& os, market_price_t market_price) {
   os << "Market Prices: " << std::endl;
   for (auto& [name, price] : *market_price) {
      os << name << " : " << price << std::endl;
   }
   os << std::endl;
   return os;
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

         if (line_number > 1) {
            string name = line.substr(0, line.find(' '));
            uint64_t price    = stoi(line.substr(line.find(' ') + 1));

            market_price->insert(make_pair(name, price));
         }

         line_number++;
      }
   } else {
      std::cerr << "Failed to open: " << filename << std::endl;
   }
}

void compute_max_profit(const market_price_t& market_price,
                        const price_list_t&   price_list) {

}

void compute_max_profit(const string& market_price_filename,
                        const string& price_list_filename,
                        const string& output_filename) {
   market_price_t market_price = std::make_shared<__market_price_t>();
   price_list_t   price_list   = std::make_shared<__price_list_t>();

   read_market_price(market_price_filename, market_price);

   std::cout << market_price << std::endl;
   return compute_max_profit(market_price, price_list);
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

   compute_max_profit(market_price, price_list, output);

   return EXIT_SUCCESS;
}
