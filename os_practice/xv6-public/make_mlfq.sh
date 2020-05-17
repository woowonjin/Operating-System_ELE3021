#! /bin/bash
make clean
make SCHED_POLICY=MLFQ_SCHED MLFQ_K=3
make SCHED_POLICY=MLFQ_SCHED MLFQ_K=3 fs.img
