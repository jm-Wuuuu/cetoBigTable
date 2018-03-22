#ifndef CETO_SOCKET_HPP
#define CETO_SOCKET_HPP

namespace ceto
{
    typedef int ctSocket;

    INT32 ctListen(ctSocket fd);

    INT32 ctAccept(ctSocket fd);
}
#endif
