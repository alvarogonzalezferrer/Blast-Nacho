// Datafind.h
// Prototipos para datafind.c

#ifndef DATAFIND_H
#define DATAFIND_H

DATAFILE *fuzzy_find_datafile_object(AL_CONST DATAFILE *dat, AL_CONST char *objectname);
DATAFILE *find_datafile_object_type(AL_CONST DATAFILE *dat, AL_CONST char *objectname, int type_required);
DATAFILE *fuzzy_find_datafile_object_type(AL_CONST DATAFILE *dat, AL_CONST char *objectname, int type_required);
#endif
