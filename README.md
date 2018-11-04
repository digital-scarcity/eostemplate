
# To build Docker
docker-compose build

# To run containers
docker-compose up -d

# To unlock wallet (use your password)
docker exec -it template_nodeosd_1 /opt/eosio/bin/cleos -u http://nodeosd:8888 --wallet-url http://keosd:8900 wallet unlock --password 

# To view live logs
docker logs -f template_nodeosd_1

# Setup the following aliases
alias cleos='docker exec -it template_nodeosd_1 /opt/eosio/bin/cleos -u http://nodeosd:8888 --wallet-url http://keosd:8900'
alias eosiocpp='docker exec -it template_nodeosd_1 eosiocpp'

# Here is the command to compile
eosiocpp -g /eosdev/bplate/bplate.abi /eosdev/bplate/bplate.hpp && eosiocpp -o /eosdev/bplate/bplate.wast /eosdev/bplate/bplate.cpp