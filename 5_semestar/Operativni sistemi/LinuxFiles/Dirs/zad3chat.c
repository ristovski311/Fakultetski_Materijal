#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

struct info
{
    char name[400];
    long size;
};

void obradiDir(char* path, struct info** files, int* count);

int main(int argc, char* argv[])
{
    struct stat statbuf;
    struct info* files = NULL;
    int i, j;
    struct info pom;
    int count = 0;

    if(argc < 2)
    {
        printf("Niste uneli putanju do direktorijuma!\n");
        return -1;
    }

    if(stat(argv[1], &statbuf) == -1)
    {
        printf("Stat je vratio -1 u main-u!\n");
        return -1;
    }

    if(!S_ISDIR(statbuf.st_mode))
    {
        printf("Morate proslediti direktorijum!\n");
        return -1;
    }

    //printf("%ld\n",sizeof(struct info));

    obradiDir(argv[1], &files, &count);

    for(i = 0; i < count-1; i++)
    {
        for(j = i+1; j < count; j++)
        {
            if(files[i].size > files[j].size)
            {
                pom = files[i];
                files[i] = files[j];
                files[j] = pom;
            }
        }
    }

    printf("Datoteke velicine > 100KB:\n\n");
    for(i = 0;i < count; i++)
    {
        printf("%d\t%20s\t%ld\n", (i+1), files[i].name, files[i].size);
    }

    free(files);  // Don't forget to free the allocated memory

    return 0;
}

void obradiDir(char* path, struct info** files, int* count)
{
    DIR* dir;
    struct dirent* dirp;
    struct stat statbuf;
    char path1[1024];
    struct info* temp;

    dir = opendir(path);
    if(!dir)
    {
        printf("Greska pri otvaranju: %s\n", path);
        return;
    }

    while((dirp = readdir(dir)) != NULL)
    {
        if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;

        strcpy(path1, path);
        strcat(path1, "/");
        strcat(path1, dirp->d_name);

        if(stat(path1, &statbuf) == -1)
        {
            printf("Stat je vratio -1 u obradi: %s!\n", path1);
            return;
        }

        if(S_ISDIR(statbuf.st_mode))
        {
            obradiDir(path1, files, count);
        }
        else if(S_ISREG(statbuf.st_mode) && statbuf.st_size > 100 * 1024)
        {
            temp = (struct info*)realloc(*files, ((*count)+1) * sizeof(struct info));
            if(temp == NULL)
            {
                printf("Greska! Null je temp!\n");
                return;
            }
            *files = temp;
            strcpy((*files)[*count].name, dirp->d_name);
            (*files)[*count].size = statbuf.st_size;
            (*count)++;
        }
    }

    rewinddir(dir);
    closedir(dir);

    return;
}
