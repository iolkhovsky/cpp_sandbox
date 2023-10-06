FROM ubuntu:22.04

RUN mkdir /setup
COPY install.sh /setup/install.sh
RUN chmod +x /setup/install.sh
RUN /setup/install.sh

RUN mkdir /workspace
WORKDIR /workspace

CMD ["/bin/bash"]
