#ifndef MESH_CALC_CONFIG_INCLUDED
#define MESH_CALC_CONFIG_INCLUDED

#ifdef MARC_ONLY_COMPILATION_STUFF
#define DEBUG_NEW new
#endif

#define _SECURE_SCL 0 // Disables the bound check for vectors (a bit faster)
#define SIM_MIN(a,b) (((a)<(b)) ? (a) : (b))
#define SIM_MAX(a,b) (((a)>(b)) ? (a) : (b))

#endif // MESH_CALC_CONFIG_INCLUDED
