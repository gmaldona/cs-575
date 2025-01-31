#include <iostream>
#include <string>
#include <getopt.h>

#include "baseball_cards.h"

using namespace std;

void compute_max_profit(const string& market_price, const string& price_list) {

}

void compute_max_profit(const string& market_price,
                        const string& price_list,
                        const string& output) {
   return compute_max_profit(market_price, price_list);
}


int main(int argc, char *argv[]) {
   std::cout << "Hello, World!" << std::endl;

   int opt;
   string market_price, price_list, output;

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
