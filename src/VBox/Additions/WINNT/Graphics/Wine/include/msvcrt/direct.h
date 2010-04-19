/*
 * Path and directory definitions
 *
 * Derived from the mingw header written by Colin Peters.
 * Modified for Wine use by Jon Griffiths and Francois Gouget.
 * This file is in the public domain.
 */

/*
 * Sun LGPL Disclaimer: For the avoidance of doubt, except that if any license choice
 * other than GPL or LGPL is available it will apply instead, Sun elects to use only
 * the Lesser General Public License version 2.1 (LGPLv2) at this time for any software where
 * a choice of LGPL license versions is made available with the language indicating
 * that LGPLv2 or any later version may be used, or where a choice of which version
 * of the LGPL is applied is otherwise unspecified.
 */

#ifndef __WINE_DIRECT_H
#define __WINE_DIRECT_H

#include <crtdefs.h>

#include <pshpack8.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DISKFREE_T_DEFINED
#define _DISKFREE_T_DEFINED
struct _diskfree_t {
  unsigned int total_clusters;
  unsigned int avail_clusters;
  unsigned int sectors_per_cluster;
  unsigned int bytes_per_sector;
};
#endif /* _DISKFREE_T_DEFINED */

int           __cdecl _chdir(const char*);
int           __cdecl _chdrive(int);
char*         __cdecl _getcwd(char*,int);
char*         __cdecl _getdcwd(int,char*,int);
int           __cdecl _getdrive(void);
__msvcrt_ulong __cdecl _getdrives(void);
int           __cdecl _mkdir(const char*);
int           __cdecl _rmdir(const char*);

#ifndef _WDIRECT_DEFINED
#define _WDIRECT_DEFINED
int      __cdecl _wchdir(const wchar_t*);
wchar_t* __cdecl _wgetcwd(wchar_t*,int);
wchar_t* __cdecl _wgetdcwd(int,wchar_t*,int);
int      __cdecl _wmkdir(const wchar_t*);
int      __cdecl _wrmdir(const wchar_t*);
#endif /* _WDIRECT_DEFINED */

#ifdef __cplusplus
}
#endif


static inline int chdir(const char* newdir) { return _chdir(newdir); }
static inline char* getcwd(char * buf, int size) { return _getcwd(buf, size); }
static inline int mkdir(const char* newdir) { return _mkdir(newdir); }
static inline int rmdir(const char* dir) { return _rmdir(dir); }

#include <poppack.h>

#endif /* __WINE_DIRECT_H */
