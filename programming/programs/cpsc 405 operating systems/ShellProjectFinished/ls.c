//a simple program to be like ls
//used as a source: 
//https://www.thegeekstuff.com/2012/06/c-directory/
//https://linux.die.net/man/2/stat
//https://man7.org/linux/man-pages/man3/strftime.3.html

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>


int main() 
{

	DIR *directory = NULL; //pointer to directory
    struct dirent *directory_item = NULL; //pointer to item in directory like files
    char directory_path[256]; //full path of cwd

    //get current working directory
    getcwd(directory_path, 256);
    printf("directory: %s\n", directory_path);

    //get a pointer to the cwd 
	directory = opendir(directory_path);

	//get pointer to first item in the directory
	directory_item = readdir (directory);

	//while pointer to next item is not null, print the information
	while (directory_item) 
	{

		/* info we can print
		struct dirent
		{
		    ino_t          d_ino;       // inode number 
		    off_t          d_off;       // offset to the next dirent 
		    unsigned short d_reclen;    // length of this record 
		    unsigned char  d_type;      // type of file; not supported
		                                //   by all file system types 
		    char           d_name[256]; // filename 
		};
		*/

		struct stat file_to_print; //used to get stats of file

		//int stat(const char *path, struct stat *buf);
		stat(directory_item->d_name, &file_to_print);

		//print owner
		//printf(", owner: %i", (int)file_to_print.st_uid);

		//print time
		char time_string[26];
	    struct tm* time_struct;
	    time_struct = localtime(&file_to_print.st_mtime);
	    strftime(time_string, 26, "%Y-%m-%d %H:%M:%S", time_struct);
		printf("last modified: %s", time_string);

		//print file size in bytes
		printf("\tsize: %iB", (int)file_to_print.st_size);

		/*
		All of these system calls return a stat structure, which contains the following fields:
		struct stat {
		    dev_t     st_dev;     // ID of device containing file 
		    ino_t     st_ino;     // inode number 
		    mode_t    st_mode;    // protection 
		    nlink_t   st_nlink;   // number of hard links 
		    uid_t     st_uid;     // user ID of owner 
		    gid_t     st_gid;     // group ID of owner 
		    dev_t     st_rdev;    // device ID (if special file) 
		    off_t     st_size;    // total size, in bytes 
		    blksize_t st_blksize; // blocksize for file system I/O 
		    blkcnt_t  st_blocks;  // number of 512B blocks allocated 
		    time_t    st_atime;   // time of last access 
		    time_t    st_mtime;   // time of last modification 
		    time_t    st_ctime;   // time of last status change 
		};
		*/

		printf("\t%s\n", directory_item->d_name);
		
		//get next item in the directory
		directory_item = readdir (directory);
	}
}
