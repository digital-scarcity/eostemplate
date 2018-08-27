
# To build Docker
docker-compose build

# To run containers
docker-compose up -d

# To unlock wallet (use your password)
docker exec -it opencrowd_nodeosd_1 /opt/eosio/bin/cleos -u http://nodeosd:8888 --wallet-url http://keosd:8900 wallet unlock --password PW5K6tHhBdjD7JGK4jwJKNnduamH3GfwmgJjnkmGvSPokKtanDrt3

# To view live logs
docker logs -f opencrowd_nodeosd_1

# Setup the following aliases
alias cleos='docker exec -it opencrowd_nodeosd_1 /opt/eosio/bin/cleos -u http://nodeosd:8888 --wallet-url http://keosd:8900'
alias eosiocpp='docker exec -it opencrowd_nodeosd_1 eosiocpp'

# Here is the command to compile
eosiocpp -g /eosdev/bplate/bplate.abi /eosdev/bplate/bplate.hpp && eosiocpp -o /eosdev/bplate/bplate.wast /eosdev/bplate/bplate.cpp