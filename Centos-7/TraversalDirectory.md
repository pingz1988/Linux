* 遍历目录：<br />

```c
int CompressDir(const char* dir, const char* savePath)
{
	char* path[MAX_PATH*2] = {0};
	char fullPath[MAX_PATH*2] = {0};
	char relativePath[MAX_PATH*2] = {0};
	size_t len = 0;

	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL)
	{
		return 1;
	}

	chdir(dir);

	while((entry = readdir(dp)) != NULL)
	{
		memset(path,0,sizeof(path));
		strncpy(path, dir, strlen(dir));
		strcat(path, "/");
		strcat(path, entry->d_name);
		lstat(path,&statbuf);

		if(S_ISDIR(statbuf.st_mode))			//directory
		{
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
			{
				continue;
			}
			/* compress directory */
			CompressSubDir(dir, path, savePath);
		} 
		else if(S_ISREG(statbuf.st_mode))
		{
			/* compress file */
			memset(fullPath,0,sizeof(fullPath));
			strncpy(fullPath,dir,strlen(dir));
			strcat(fullPath,"/");
			strcat(fullPath,entry->d_name);
			len = strlen(fullPath)-strlen(dir);
			memset(relativePath,0,sizeof(relativePath));
			strncpy(relativePath,fullPath+strlen(dir),len);
			relativePath[len] = '\0';
			CompressFile(relativePath,fullPath,savePath);
		}
	}
	chdir("..");
	closedir(dp);

	return 0;
}
```
