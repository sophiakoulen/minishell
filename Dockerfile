FROM ubuntu

RUN apt update && apt -y install gcc git make zsh wget valgrind vim bat
RUN apt -y install lib32readline8 lib32readline-dev libreadline8 libreadline-dev
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.5/zsh-in-docker.sh)" -- \
    -t eastwood
# ENV DEBUG=1
RUN echo 'alias val="valgrind -s --leak-check=full --show-leak-kinds=definite,indirect,possible --track-origins=yes --log-file=valgrind-out.txt" ./' >> ~/.zshrc && \
	chmod +x ~/.zshrc
COPY . minishell
WORKDIR minishell
ENTRYPOINT [ "/bin/zsh" ]

# usr/bin/valgrind -s --leak-check=full --show-leak-kinds=definite,indirect,possible --track-origins=yes --log-file=valgrind-out.txt
