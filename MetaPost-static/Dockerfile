
# Base image
FROM ubuntu:16.04
MAINTAINER Paul Murrell <paul@stat.auckland.ac.nz>

RUN apt-get update && \
    apt-get install -y \
        subversion

# Checkout MetaPost source
RUN mkdir /opt/MetaPost && \
    cd /opt/MetaPost && \
    svn co --username anonsvn --password anonsvn --trust-server-cert https://serveur-svn.lri.fr/svn/modhel/metapost/trunk 

# Build MetaPost
RUN apt-get update && \
    apt-get install -y \
        gcc \
        g++ \
        make \
        texinfo
RUN cd /opt/MetaPost/trunk/ && \
    ./build.sh

