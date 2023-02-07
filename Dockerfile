FROM ubuntu

RUN apt update && apt -y install gcc make bash

COPY . minishell

RUN ["/bin/bash"]