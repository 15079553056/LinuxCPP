#include <stdio.h>
#include "../toollib/DirectoryHelper.h"
#include <string.h>

int main()
{
    printf("Hello CMake.\n");
    printf("Hello World.\n");
    char dir[256]={0};
    CDirectoryHelper::GetCurrentDir(dir,256);
    printf("Dir=%s\n",dir);
    strcat(dir,"/APP_Log/20200910/16");
    CDirectoryHelper::DirCreate(dir);
    return 0;
}
