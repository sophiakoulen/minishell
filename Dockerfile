FROM ubuntu

RUN apt update && apt -y install gcc git make zsh wget
RUN apt -y install lib32readline8 lib32readline-dev libreadline8 libreadline-dev
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.5/zsh-in-docker.sh)" -- \
    -t eastwood
ENV DEBUG=1
COPY . minishell

ENTRYPOINT [ "/bin/zsh" ]
