#include "abstract_graph.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define PARENT_WRITE_PIPE 0
#define PARENT_READ_PIPE  1

#define READ_FD  0
#define WRITE_FD 1

#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD] )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )

#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD] )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD] )

AbstractGraph::AbstractGraph(Graph* graph) {
    this->graph = graph;
}

AbstractGraph::AbstractNode::AbstractNode(string seq, uint32_t id, uint32_t* colors) {
    this->seq = seq;
    this->id = id;
    uint32_t size = colors[0] + 1;
    this->colors = (uint32_t*) malloc(size * sizeof(uint32_t));
    memcpy(this->colors, colors, size);
}

AbstractGraph::AbstractNode::AbstractNode(const AbstractNode& o) {
    this->seq = o.seq;
    this->id = o.id;
    uint32_t size = o.colors[0] + 1;
    this->colors = (uint32_t*) malloc(size * sizeof(uint32_t));
    memcpy(this->colors, o.colors, size);
}

AbstractGraph::AbstractNode::AbstractNode(AbstractNode&& o) noexcept {
    this->seq = std::move(o.seq);
    this->id = std::move(o.id);
    this->colors = std::move(o.colors);
}

AbstractGraph::AbstractNode::~AbstractNode() noexcept {
    free(colors);
}

void AbstractGraph::AbstractNode::appendToSeq(const char c) {
    seq.append(1, c);
}

string AbstractGraph::AbstractNode::getSeq() {
    return seq;
}

uint32_t AbstractGraph::AbstractNode::getId() {
    return id;
}

uint32_t* AbstractGraph::AbstractNode::getColors() {
    return colors;
}

void AbstractGraph::construct(BFT_kmer* startKmer) {
    uint32_t currentId = 0;
}

string AbstractGraph::getDependencies() {
    return "";
}

void handle_sigchld(int sig) {
    int saved_errno = errno;
    while(waitpid((pid_t) (-1), 0, WNOHANG) > 0) {}
    errno = saved_errno;
}

string AbstractGraph::doTopologicalOrdering(string dependencies) {
    // register the SIGCHLD handler to reap the zombie children
    struct sigaction sa;
    sa.sa_handler = &handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if(sigaction(SIGCHLD, &sa, 0) == -1) {
        perror("SIGCHLD in doTopologicalOrdering has errored");
        return "";
    }

    int status;
    int pipes[2][2];
    string output;

    if(pipe(pipes[PARENT_READ_PIPE]) == -1 || pipe(pipes[PARENT_WRITE_PIPE]) == -1) {
        perror("pipe in doTopologicalOrdering has errored");
        return output;
    }

    if(fork() == 0) {
        while((dup2(CHILD_READ_FD, STDIN_FILENO) == -1) && (errno == EINTR)) {}
        while((dup2(CHILD_WRITE_FD, STDOUT_FILENO) == -1) && (errno == EINTR)) {}

        // close the fds that are not required by the child
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);

        execlp("tsort", "tsort");
        // if this is reached, something went wrong with execlp
        perror("error with execlp");
    }
    else {
        // close the fds that are not required by the parent
        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);

        write(PARENT_WRITE_FD, dependencies.c_str(), dependencies.size());
        close(PARENT_WRITE_FD);

        // read from child's stdout 
        char buffer[4096];
        while(1) {
            ssize_t count = read(PARENT_READ_FD, buffer, sizeof(buffer));
            buffer[count] = '\0';
            if(count == -1) {
                if(errno == EINTR) {
                    continue;
                }
                else {
                    perror("reading output from tsort in doTopologicalOrdering has errored");
                    return output;
                }
            }
            else if(count == 0) {
                break;
            }
            else {
                output.append(buffer);
            }
        }
        close(PARENT_READ_FD);
    }

    return output;
}
