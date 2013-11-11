/* BEGIN A3 SETUP */
/*
 * Declarations for file handle and file table management.
 * New for A3.
 */

#ifndef _FILE_H_
#define _FILE_H_

#include <kern/limits.h>

struct vnode;

/**
 * open file struct
 */
struct openfile {
    struct vnode* of_vn;
    int of_flags;
    off_t of_offset;
    int of_refcount;
    struct lock *of_lock;
};

/*
 * filetable struct
 * just an array, nice and simple.  
 * It is up to you to design what goes into the array.  The current
 * array of ints is just intended to make the compiler happy.
 */
struct filetable {
    struct openfile* ft_openfiles[__OPEN_MAX];
};

/* these all have an implicit arg of the curthread's filetable */
int filetable_init(void);
void filetable_destroy(struct filetable *ft);

/* opens a file (must be kernel pointers in the args) */
int file_open(char *filename, int flags, int mode, int *retfd);

/* closes a file */
int file_close(int fd);

/* A3: You should add additional functions that operate on
 * the filetable to help implement some of the filetable-related
 * system calls.
 */

/* add the file to the file table and set the file descriptor to the index */
int filetable_addfile(struct openfile *ofile, int *retfd);

/* check if file descriptor is valid and references an
 * open file, and set file to the file at fd
 */
int filetable_findfile(int fd, struct openfile **ofile);

#endif /* _FILE_H_ */

/* END A3 SETUP */