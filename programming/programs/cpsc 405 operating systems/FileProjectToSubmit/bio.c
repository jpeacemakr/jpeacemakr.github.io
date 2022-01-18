#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "types.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "stat.h"
#include "proc.h"
#include "fcntl.h"
#include "user.h"

int fs;

// prints the message and exits
void panic(char *words){
    printf("%s", words);
    exit(-1);
}

//reads from the file system to the buffer
int bread(uint block, char *buf) {

    //printf("Trace: starting bread() in bio.c\n");
    //printf("Trace:   bread() reads from the file system to the buffer.\n");
    //printf("Trace:   bread() arguments: block (uint block number being read), buf (buffer)\n");

    int off = lseek(fs, block*BSIZE, SEEK_SET);
    if (off < 0)
        panic("bread lseek fail");
    //printf("off : %d\n", off);
    int sz = read(fs, buf, BSIZE);
    if (sz < 0)
        panic("bread read fail");
    //printf("sz : %d\n", sz);
    return 0;
}

//writes from the buffer to the file system
int bwrite(uint block, char *buf) {
    int off = lseek(fs, block*BSIZE, SEEK_SET);
    if (off < 0)
        panic("bwrite lseek fail");
    //printf("off : %d\n", off);
    int sz = write(fs, buf, BSIZE);
    if (sz < 0)
        panic("bwrite write fail");
    //printf("sz : %d\n", sz);
    return 0;
}


// Creates the file system
// When calling this for FileLab, call as follows.
// createfs("namechoice", NBLOCKS, NBLOCKS-8, 32);
//  namechoice must be <= 12
//  NBLOCKS is total 512 byte blocks allocated to file system
//  Blocks 0 - 8 are allocated as sb, bitmaps, and inodes - see fs.h
//  NBLOCKS-8 are allocated as data blocks
int createfs(char *name, uint blks, uint dblks, uint inds) {
    fs = open(name, O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fs < 0)
        panic("createfs open fail");
    unsigned char b[BSIZE];
    char *c = (char *)b;
    memset(b, 0, BSIZE);
    strcpy(c, "Block 0 - Not used.");
    int sz = write(fs, b, BSIZE);
    if (sz < 0)
        panic("createfs write fail");
    memset(b, 0, BSIZE);
    for (int i = 1; i < blks; i++) {
        if (i > 7) // write block number on data blocks
            b[0] = i;
        int sz = write(fs, b, BSIZE);
        if (sz < 0)
            panic("createfs write fail");
        //printf("sz : %d written.\n", sz);
    }
    struct superblock sb;
    sb.size = blks;
    sb.nblocks = dblks;
    sb.ninodes = inds;
    sb.nlog = 0;
    memset(sb.name, 0, 12);
    strcpy(sb.name, name); 
    memcpy(b, &sb, sizeof(struct superblock));
    if (bwrite(1, (char *)b) < 0)
        panic("createfs bwrite fail");
    close(fs);
    return 0;

}

//opens the file system
int openfs(char *name) {
    fs = open(name, O_RDWR, S_IRUSR | S_IWUSR);
    if (fs < 0)
        panic("openfs open fail");
    return 0;
}


//cloese the file system
int closefs() {
    close(fs);
    return 0;
}

int balloc();
void bfree(uint);
struct inode *iget(uint);
void print_inodes();

//main
int main(int argc, char *argv[]) {

    unsigned char b[BSIZE];
    memset(b, 0, BSIZE);
    if (argc < 2) {
        printf("must enter bio with create, write, read\n");
        exit(1);
    }
    int s;
    if (strcmp(argv[1], "create") == 0) { // create fs file
        printf("create fs file.\n");
        createfs(FSNAME, NBLOCKS, NBLOCKS-8, 32);
        openfs(FSNAME);
        readfsinfo();
        // allocate Root Directory ("/")
        struct inode *ip = ialloc(T_DIR);
        ip->inum = 1;
        ip->ref = 0xab;
        printf("inode num: %d, type: %d\n", ip->inum, ip->type);
        writefsinfo();
        closefs();
        /*
        fs = open("gustyfs", O_CREAT | O_WRONLY | O_RDONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fs < 0) {
            printf("open error.\n");
            exit(1);
        }
        for (int i = 0; i < NBLOCKS; i++) {
            b[0] = i;
            int sz = write(fs, b, BSIZE);
            //printf("sz : %d written.\n", sz);
        }
        close(fs);
        */
    } else if (strcmp(argv[1], "write") == 0) {
        printf("manipulate fs file with writes.\n");

        // Open TFS and establish curr_proc so we can do application code
        // curr_proc is a macro defined in proc.h
        curr_proc = malloc(sizeof(struct proc));
        strcpy(curr_proc->name, "Gusty");
        openfs(FSNAME);
        printf("fs : %d\n", fs);
        memset(b, 0, BSIZE);
        readfsinfo();
        //struct inode *ip = ialloc(T_DIR);
        //ip->inum = 1;
        //ip->ref = 0xab;
        //printf("inode num: %d, type: %d\n", ip->inum, ip->type);
        struct inode *ip = iget(T_DIR);
        curr_proc->cwd = ip;
        /*
        int s = bread(202, (char *)b); 
        printf("b[0] : %d\n", b[0]);
        memset(b,0xbb,BSIZE);
        s = bwrite(10, (char *)b);
        printf("balloc: %d\n", balloc());
        printf("balloc: %d\n", balloc());
        printf("balloc: %d\n", balloc());
        printf("balloc: %d\n", balloc());
        printf("bfree(9)\n");
        bfree(9);
        */

        // Perform application code
        

        ///////////////////////////// question 1

        /*int fd1 = tfs_open("GUSTY", TO_CREATE | TO_RDWR, 0);
        printf("fd1: %d\n", fd1);
        s = tfs_write(fd1, "COOPER123", 9);
        printf("tfs_write bytes: %d\n", s);
        
        int fd2 = tfs_open("HELLOWORLD", TO_CREATE | TO_RDWR, 0);
        printf("fd2: %d\n", fd2);
        s = tfs_write(fd2, "HELLO TO EVERYONE IN the world! Happy New Years!", 48);
        printf("tfs_write bytes: %d\n", s);
        s = tfs_write(fd2, "Writing data to another file. 123456789abcdefgh!", 48);
        printf("tfs_write bytes: %d\n", s);
        
        int fd3 = tfs_open("Another", TO_CREATE | TO_RDWR, 0);
        printf("fd3: %d\n", fd3);
        s = tfs_write(fd3, "Writing data to another file. 123456789abcdefgh!", 48);
        printf("tfs_write bytes: %d\n", s);

        int fd4 = tfs_open("MyFile", TO_CREATE | TO_RDWR, 0);
        printf("fd4: %d\n", fd4);
        s = tfs_write(fd4, "Writing data to my file. ZYXWVUTSRQPONMLKJIHGFED", 48);
        printf("tfs_write bytes: %d\n", s);
        
        tfs_close(fd1);
        tfs_close(fd2);
        tfs_close(fd3);
        tfs_close(fd4);
        */


        ///////////////////////////// question 2
        /*
        int fd5 = tfs_open("James", TO_CREATE | TO_RDWR, 0);
        printf("fd5: %d\n", fd5);
        s = tfs_write(fd5, "This is just a test for the James file.", 39);
        printf("tfs_write bytes: %d\n", s);
        tfs_close(fd5);
        */


        ///////////////////////////// question 8
        /*
        int fd5 = tfs_open("test8", TO_CREATE | TO_RDWR, 0);
        printf("fd5: %d\n", fd5);
        s = tfs_write(fd5, "This is just a test for the James file 1.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 2.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 3.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 4.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 5.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 6.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 7.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 8.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 9.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 10.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 11.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 12.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 13.\n", 42);
        printf("tfs_write bytes: %d\n", s);
        tfs_close(fd5);
        */


        ///////////////////////////// question 9
        /*
        int fd5 = tfs_open("test9A", TO_CREATE | TO_RDWR, 0);
        printf("fd5: %d\n", fd5);
        s = tfs_write(fd5, "This is just a test for the James file 1.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 2.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 3.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 4.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 5.\n", 42);
        s = tfs_write(fd5, "This is just a test for the James file 6.\n", 42);
        printf("tfs_write bytes: %d\n", s);
        tfs_close(fd5);

        int fd6 = tfs_open("test9B", TO_CREATE | TO_RDWR, 0);
        printf("fd5: %d\n", fd6);
        s = tfs_write(fd6, "This is just a test for the James file 7.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 8.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 9.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 10.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 11.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 12.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 13.\n", 42);
        printf("tfs_write bytes: %d\n", s);
        tfs_close(fd6);
        */


        ///////////////////////////// question 10
            

        int fd6 = tfs_open("test10", TO_CREATE | TO_RDWR, 0);
        printf("fd6: %d\n", fd6);
        s = tfs_write(fd6, "This is just a test for the James file 1.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 2.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 3.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 4.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 5.\n", 42);
        s = tfs_write(fd6, "This is just a test for the James file 6.\n", 42);
        printf("tfs_write bytes: %d\n", s);
        
        struct tfs_stat *st = malloc(sizeof(struct tfs_stat));
        tfs_fstat(fd6, st);
        printf("Metadata for file:\n");
        printf("   inode number: %i\n", st->ino);
        char * typearray[4] = {"unused", "directory", "file", "device"};
        printf("   type: %s\n", typearray[st->type]);
        printf("   number of links: %i\n", st->nlink);
        printf("   size: %i\n", st->size);
        tfs_close(fd6);
        


        /////////////////////////////////
        
        

        // Write file info back to TDD and close TFS
        writefsinfo();
        closefs();
        //printf("size of inodes B : %lu\n", sizeof(struct inode));
        //printf("Inodes per block (IP)B : %lu\n", IPB);
        //printf("Block containing inode I - IBLOCK(30) : %lu\n", IBLOCK(30));
        //printf("BPB : %d\n", BPB);
        //printf("Block containin bit for block b - BBLOCK(10, 100) : %lu\n", BBLOCK(10, 100));
        //time_t seconds;
        //time(&seconds);
        //unsigned int ui;
        //memcpy(&ui, &seconds, 4);
        //printf("sizeof(time_t): %lu, time: %lx, %x\n",sizeof(time_t), seconds, ui);
    } else if (strcmp(argv[1], "read") == 0) {
        printf("manipulate fs file with reads.\n");
        // Open TFS and establish curr_proc so we can do application code
        // curr_proc is a macro defined in proc.h
        curr_proc = malloc(sizeof(struct proc));
        strcpy(curr_proc->name, "Gusty");
        openfs(FSNAME);
        printf("fs : %d\n", fs);
        memset(b, 0, BSIZE);
        readfsinfo();
        struct inode *ip = iget(T_DIR);
        curr_proc->cwd = ip;

        // Perform application code
        char buffer[512];
        strcpy(buffer, "sometext");
        
        /*
        int fd3 = tfs_open("Another", TO_RDONLY, 0);
        printf("fd3: %d\n", fd3);
        s = tfs_read(fd3, buffer, 19); 
        printf("tfs_read bytes: fd: %d, bytes read: %d value read: %s\n", fd3, s, buffer);

        int fd4 = tfs_open("MyFile", TO_RDONLY, 0);
        printf("fd4: %d\n", fd4);
        s = tfs_read(fd4, buffer, 47);
        printf("tfs_read bytes: fd: %d, bytes read: %d value read: %s\n", fd4, s, buffer);
        */

        int fd5 = tfs_open("James", TO_RDONLY, 0);
        printf("fd5: %d\n", fd5);
        s = tfs_read(fd5, buffer, 38);
        printf("tfs_read bytes: fd: %d, bytes read: %d value read: %s\n", fd5, s, buffer);

        // Write file info back to TDD and close TFS
        writefsinfo();
        closefs();

    } else {
        printf("must enter bio with create, write, read\n");
        exit(1);
    }
    return 0;
}
