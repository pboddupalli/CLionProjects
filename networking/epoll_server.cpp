#include <cstdio>
#include <iostream>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <fcntl.h>

using namespace::std;

int main(int argc, char **argv)
{
  cout << "Hello Server" << endl;
  return 0;
}

static int set_nonblocking(int fd)
{
  int flags = fcntl(fd, F_GETFL);
  return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

void event_loop(int listen_sock)
{
  int epollfd = epoll_create1(0);
  if (epollfd == -1) {
    perror("epoll_create1");
    exit(EXIT_FAILURE);
  }

  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = listen_sock;
  if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
    perror("epoll_ctl: listen_sock");
    exit(EXIT_FAILURE);
  }

  #define MAX_EVENTS 10

  struct epoll_event events[MAX_EVENTS];
  for (;;)
  {
    int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
    if (nfds == -1) {
      perror("epoll_wait");
      exit(EXIT_FAILURE);
    }

    socklen_t sockaddr_len;
    for (int n = 0; n < nfds; ++n)
    {
      if (events[n].data.fd == listen_sock)
      {
        struct sockaddr_in client_sockaddr;
        int conn_sock = accept(listen_sock, (struct sockaddr *) &client_sockaddr, &sockaddr_len);
        if (conn_sock == -1) {
          perror("accept");
          exit(EXIT_FAILURE);
        }
        set_nonblocking(conn_sock);
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = conn_sock;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
          perror("epoll_ctl: conn_sock");
          exit(EXIT_FAILURE);
        }
      }
      else {
        do_use_fd(events[n].data.fd);
      }
    }
  }
} /* end of event_loop function */