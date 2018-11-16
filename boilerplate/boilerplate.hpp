
//#include <string>
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>


using namespace eosio;
using namespace std;

CONTRACT boilerplate : public contract
{
    using contract::contract;

  public:
   
    ACTION myaction();

    ACTION transrec(name from, name to, asset quantity, string memo); 
      
  private:
  
   TABLE balance {
        asset funds;
        name token_contract;
        uint64_t primary_key() const { return funds.symbol.code().raw(); }
    };

    typedef eosio::multi_index<"balances"_n, balance> balance_table;

    void paytoken(  const name  token_contract,
                    const name from,
                    const name to,
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
            permission_level{from, "active"_n},
            token_contract, "transfer"_n,
            std::make_tuple(from, to, token_amount, memo))
            .send();

        print("---------- End Payment -------\n");
    }

};

