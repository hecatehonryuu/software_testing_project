#ifndef _HAVE_SWARM
#define _HAVE_SWARM

//Funcs defined in afl-fuzz to be used in swarm.c
inline u32 UR(u32 limit);

//Funcs defined in swarm.c
int swarm_havoc(u32** swarm);

#endif