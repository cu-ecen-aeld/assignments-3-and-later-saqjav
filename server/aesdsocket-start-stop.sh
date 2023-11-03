#!/bin/sh

case $1 in
    start)
        start-stop-daemon -S -n aesdsocket -a /usr/bin/aesdsocket -- -d
    ;;
    stop)
        start-stop-daemon -K -n aesdsocket
    ;;
esac