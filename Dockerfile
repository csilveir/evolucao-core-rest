FROM ubuntu

RUN apt-get update
RUN apt-get install gcc libulfius-dev uwsc -y
RUN mkdir -p /usr/sicredi
COPY . /usr/sicredi
WORKDIR /usr/sicredi
RUN chmod +x run.sh

RUN gcc -o sicredirestserver sicredirestserver.c -L/lib/x86_64-linux-gnu -lulfius -ljansson -lorcania

EXPOSE 8080

ENTRYPOINT ["/usr/sicredi/run.sh"]
