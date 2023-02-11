FROM archlinux

RUN pacman -Syu --noconfirm gcc git make zsh valgrind vim bat

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" -- \
# RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.5/zsh-in-docker.sh)" -- \
#     -t eastwood

# ENV DEBUG=1

RUN rm ~/.zshrc
RUN echo 'export ZSH="$HOME/.oh-my-zsh"' > ~/.zshrc
RUN echo 'ZSH_THEME="eastwood"' >> ~/.zshrc
RUN echo 'plugins=(git)' >> ~/.zshrc
RUN echo 'source $ZSH/oh-my-zsh.sh' >> ~/.zshrc

RUN echo 'alias val="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt" ./' >> ~/.zshrc && \
	chmod +x ~/.zshrc

COPY . dockershell
WORKDIR dockershell
RUN make re
ENTRYPOINT [ "/bin/zsh" ]
