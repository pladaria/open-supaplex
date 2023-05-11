#ifndef _ERRNO_H
#define _ERRNO_H 1

#define EPERM 1   /* Operation not permitted */
#define EIO 5     /* I/O error */
#define ENOENT 2  /* No such file or directory */
#define ENOSYS 38 /* Invalid system call number */

extern int errno;

#endif