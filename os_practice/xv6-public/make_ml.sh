#! /bin/bash
make clean
make SCHED_POLICY=MULTILEVEL_SCHED
make SCHED_POLICY=MULTILEVEL_SCHED fs.img
