#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/currency.hpp>

#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/types.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/crypto.h>
#include <cstring>
#include <functional>

using namespace eosio;
using namespace std;

class bplate : public contract
{

  public:
    bplate(account_name self) : contract(self) {}

    // @abi action
    void myaction();

    void apply(const account_name contract, const account_name act);

    void transferReceived(const currency::transfer &transfer, const account_name code);
    
  private:
  
    // @abi table balances i64
    struct balance {
        asset funds;
        account_name token_contract;
        uint64_t primary_key() const { return funds.symbol; }
    };

    typedef eosio::multi_index<N(balances), balance> balance_table;

    void paytoken(  const account_name  token_contract,
                    const account_name from,
                    const account_name to,
                    const asset token_amount,
                    const string memo)
    {
        print("---------- Payment -----------\n");
        print("Token Contract   : ", name{token_contract}, "\n");
        print("From             : ", name{from}, "\n");
        print("To               : ", name{to}, "\n");
        print("Amount           : ", token_amount, "\n");
        print("Memo             : ", memo, "\n");

        action(
            permission_level{from, N(active)},
            token_contract, N(transfer),
            std::make_tuple(from, to, token_amount, memo))
            .send();

        print("---------- End Payment -------\n");
    }

};


EOSIO_ABI(bplate, (myaction) )