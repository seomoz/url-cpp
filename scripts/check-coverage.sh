#! /usr/bin/env bash

set -e

if [ "$#" -ne 1 ]; then
    echo "Usage:"
    echo "    check-coverage.sh <path-to-project-root>"
    exit 1
fi

root="${1}"

results=`gcovr \
    --root=${root} \
    --exclude-unreachable-branches \
    --output=/dev/null \
    --print-summary \
    --object-directory=${root} \
    --exclude test`

lines=`echo ${results} | sed -E 's#^.*lines: ([0-9]+)(\.[0-9]+)?%.+$#\1#'`
branches=`echo ${results} | sed -E 's#^.*branches: ([0-9]+)(\.[0-9]+)?%.+$#\1#'`

if [ "${lines}" -ne "100" ]; then
    echo "Incomplete line coverage (${lines})"
    echo "${results}"
    exit 2
else
    echo "Coverage looks good!"
    echo "${results}"
fi
