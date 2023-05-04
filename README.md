## Para compilar o projeto

gcc -o sicredirestserver sicredirestserver.c -L/lib/x86_64-linux-gnu -lulfius -ljansson -lorcania -lpthread


## Executando o processo

./sicredirestserver


## Comando de leitura
curl --location 'http://localhost:8080/contacorrente/saldo' \
--header 'Content-Type: application/json' 

## Comando de escrita
curl --location 'http://localhost:8080/contacorrente/?id=5' \
--header 'Content-Type: application/json' \
--data '{
    "id" : 1278,
    "name" : "Conta Corrente PF Sicredi"

 }'


 ## Criando a imagem Docker

 docker build . -t sicredi/sicredirestserver 

 ## Rodando a imagem Docker

 docker run -it -p 8080:8080 sicredi/sicredirestserver 