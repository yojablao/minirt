#!/bin/bash
while true; do
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./MRT lol.rt >> valgrind_log.txt 2>&1
    echo "Valgrind run completed. Waiting for 5 seconds..."
    sleep 5
done