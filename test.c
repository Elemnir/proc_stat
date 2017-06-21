#include "proc_stat.h"

int main() {
    ProcStat *ps = get_proc_stat_info();
    printf("%s\n", ps->comm);
    printf("%c %d %d %lu\n", ps->state, ps->ppid, ps->session, ps->minflt);
    return 0;
}
