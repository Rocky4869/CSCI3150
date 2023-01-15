#include <sys/stat.h>
#include <assert.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *dp = opendir(".");             // open current directory
    assert(dp != NULL);
    struct dirent *d;
    while ((d = readdir(dp)) != NULL)   // read one directory entry 
    {
        // print outthe name and inode number of each file
        printf("%d %s\n", (int) d->d_ino, d->d_name);
    }
    closedir(dp);                       // close current directory
    return 0;
}

