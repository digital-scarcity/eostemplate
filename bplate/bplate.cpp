#include "bplate.hpp"
#include <string>


void bplate::myaction ( ) {
    print ("My Action Executed.");
}


void bplate::apply(const account_name contract, const account_name act)
{
    if (act == N(transfer))
    {
        transferReceived(unpack_action_data<currency::transfer>(), contract);
        return;
    }

    auto &thiscontract = *this;

    switch (act)
    {
        EOSIO_API(bplate, (myaction))
    };
}

void bplate::transferReceived(const currency::transfer &transfer, const account_name code)
{
    if (transfer.to != _self)
    {
        return;
    }
              
    print("Account Name     :   ", name{code}, "\n");
    print("From             :   ", name{transfer.from}, "\n");
    print("To               :   ", name{transfer.to}, "\n");
    print("Asset            :   ", transfer.quantity, "\n");
    print("Received Amount  :   ", transfer.quantity.amount, "\n");
    print("Received Symbol  :   ", transfer.quantity.symbol, "\n");
    print("Memo             :   ", transfer.memo, "\n");
    
    balance_table balances(_self, transfer.from);
    asset new_balance;
    auto it = balances.find(transfer.quantity.symbol);
    if(it != balances.end()) {
        eosio_assert (it->token_contract == code, "Transfer does not match existing token contract.");
        balances.modify(it, transfer.from, [&](auto& bal){
            // Assumption: total currency issued by eosio.token will not overflow asset
            bal.funds += transfer.quantity;
            new_balance = bal.funds;
        });
    }
    else
        balances.emplace(transfer.from, [&](auto& bal){
            bal.funds = transfer.quantity;
            bal.token_contract  = code;
            new_balance = transfer.quantity;
        });

    print(name{transfer.from}, " deposited:       ", transfer.quantity, "\n");
    print(name{transfer.from}, " funds available: ", new_balance);
}


extern "C"
{
    using namespace eosio;

    void apply(uint64_t receiver, uint64_t code, uint64_t action)
    {
        auto self = receiver;
        bplate contract(self);
        contract.apply(code, action);
        eosio_exit(0);
    }
}
