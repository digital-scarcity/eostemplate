#include "boilerplate.hpp"
#include <string>


void boilerplate::myaction ( ) {
    print ("My Action Executed.");
}

ACTION boilerplate::transrec(name from, name to, asset quantity, string memo) {
    
    print ("Code        : ", get_code(), "\n");
    print ("From        : ", from, "\n");
    print ("To          : ", to, "\n");
    print ("Quantity    : ", quantity, "\n");
    print ("Memo        : ", memo, "\n");
    
    balance_table balances(_self, from.value);
    asset new_balance;
    auto it = balances.find(quantity.symbol.code().raw());
    if(it != balances.end()) {
        eosio_assert (it->token_contract == get_code(), "Transfer does not match existing token contract.");
        balances.modify(it, from, [&](auto& bal){
            // Assumption: total currency issued by eosio.token will not overflow asset
            bal.funds += quantity;
            new_balance = bal.funds;
        });
    }
    else
        balances.emplace(from, [&](auto& bal){
            bal.funds = quantity;
            bal.token_contract  = get_code();
            new_balance = quantity;
        });

    print ("\n");
    print(name{from}, " deposited:       ", quantity, "\n");
    print(name{from}, " funds available: ", new_balance);
    print ("\n");
}

extern "C" {
    [[noreturn]] void apply(uint64_t receiver, uint64_t code, uint64_t action) {
        if (action == "transfer"_n.value && code != receiver) {
            eosio::execute_action(eosio::name(receiver), eosio::name(code), &boilerplate::transrec);
        }
        if (code == receiver) {
            switch (action) { 
                EOSIO_DISPATCH_HELPER(boilerplate, (myaction)) 
            }    
        }
        eosio_exit(0);
    }
}
