FROM debian:buster-backports

WORKDIR /root

RUN apt-get -q update && apt-get upgrade -y
RUN apt-get install -y --no-install-recommends \
      git make gcc llvm-8 valgrind ca-certificates libc6-dev python3
