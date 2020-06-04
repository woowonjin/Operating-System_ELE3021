#! /bin/bash
make clean
make SCHED_POLICY=DEFAULT
make SCHED_POLICY=DEFAULT fs.img
