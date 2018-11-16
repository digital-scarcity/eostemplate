cmake_minimum_required(VERSION 3.5)

find_package(eosio.cdt)

### generate both the wasm and abi
add_contract( token token token.cpp )


