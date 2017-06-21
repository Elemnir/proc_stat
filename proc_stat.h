/*
Copyright (c) 2017, Adam Howard
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
     
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the names of its 
      contributors may be used to endorse or promote products derived from 
      this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "errno.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct proc_stat_t {
    int pid;
    char *comm, state;
    int ppid, pgrp, session, tty_nr, tpgid;
    unsigned int flags;
    unsigned long int minflt, cminflt, majflt, cmajflt, utime, stime;
    long int cutime, cstime, priority, nice, num_threads, itrealvalue;
    unsigned long long int starttime;
    unsigned long int vsize;
    long int rss;
    unsigned long int rsslim;
    void *startcode, *endcode, *startstack, *kstkesp, *kstkeip;
    unsigned long int signal, blocked, sigignore, sigcatch;
    void *wchan;
    unsigned long int nswap, cnswap;
    int exit_signal, processor;
    unsigned int rt_priority, policy;
    unsigned long long int delayacct_blkio_ticks;
    unsigned long int guest_time;
    long int cguest_time;
    void *start_data, *end_data, *start_brk, *arg_start, *arg_end;
    void *env_start, *env_end;
    int exit_code;
} ProcStat;


ProcStat *get_proc_stat_info() {
    // Allocate and initialize the struct, open the file
    FILE *procfp = fopen("/proc/self/stat", "r");
    if (procfp == NULL) {
        perror("Could not open /proc/self/stat"); exit(errno);
    }
    ProcStat *ps = (ProcStat *) calloc(sizeof(ProcStat), 1);
    ps->comm = (char*) calloc(sizeof(char), 200);
    
    // Do the read, feel bad about this format string
    fscanf(procfp,
        "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu "
        "%ld %ld %ld %ld %ld %ld %llu %lu %ld %lu "
        "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu "
        "%d %d %u %u %llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %d",
        &ps->pid, ps->comm, &ps->state, &ps->ppid, &ps->pgrp, &ps->session, 
        &ps->tty_nr, &ps->tpgid, &ps->flags, &ps->minflt, &ps->cminflt, 
        &ps->majflt, &ps->cmajflt, &ps->utime, &ps->stime, &ps->cutime, 
        &ps->cstime, &ps->priority, &ps->nice, &ps->num_threads, 
        &ps->itrealvalue, &ps->starttime, &ps->vsize, &ps->rss, &ps->rsslim, 
        &ps->startcode, &ps->endcode, &ps->startstack, &ps->kstkesp, 
        &ps->kstkeip, &ps->signal, &ps->blocked, &ps->sigignore, &ps->sigcatch,
        &ps->wchan, &ps->nswap, &ps->cnswap, &ps->exit_signal, &ps->processor, 
        &ps->rt_priority, &ps->policy, &ps->delayacct_blkio_ticks, 
        &ps->guest_time, &ps->cguest_time, &ps->start_data, &ps->end_data, 
        &ps->start_brk, &ps->arg_start, &ps->arg_end, &ps->env_start, 
        &ps->env_end, &ps->exit_code
    );
    fclose(procfp);
    return ps;
}

void delete_proc_stat(ProcStat *ps) {
    free(ps->comm);
    free(ps);
}
