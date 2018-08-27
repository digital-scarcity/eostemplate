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

  private:
    // @abi table mytables i64
    struct mytable
    {
        uint64_t id;
        account_name account;

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(mytable, (id)(account));
    };

    typedef eosio::multi_index<N(mytables), mytable> mytable_table;

};


EOSIO_ABI(bplate, (myaction) )