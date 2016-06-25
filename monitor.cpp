#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int printFirstLinesOfFile(char* fileName, int numberOfLines){
    FILE *fp;
    if((fp = fopen(fileName, "r"))){
      char line[255];
      for(int i = 0 ; i<numberOfLines; ++i){
        if( fgets (line, 255, fp) ){
          printf("%s",line);
        }
      }
      fclose(fp);
    }
    return 0;
}

int main(int argc, char *argv[]) {
  struct stat fileStats;
  DIR *dirp;
  struct dirent* dent;

  int a_xml_count=0;
  int a_pnl_count=0;
  int a_res_count=0;

  int b_xml_count=0;
  int non_empty_err_count=0;

  int folderNameLength = strlen(argv[1]);
  char* pathToFolder;
  char* errorFileExample;
  
  if(!(dirp=opendir(argv[1]))){
    printf("ERROR:Invalid path name\n");
    return 1;
  }

  //fix folder path if missing slash
  pathToFolder = (char*)malloc(folderNameLength+2);
  strcpy(pathToFolder,argv[1]);
  if(argv[1][folderNameLength-1] != '/'){
    pathToFolder[folderNameLength] = '/';
    pathToFolder[folderNameLength+1] = '\0';
    folderNameLength++;
  }

  while((dent = readdir(dirp))){
    int fileNameLength = strlen(dent->d_name);
    char* fullPathToFile;
    fullPathToFile = (char*)malloc(folderNameLength+fileNameLength+1);
    strcpy(fullPathToFile,pathToFolder);
    strcat(fullPathToFile,dent->d_name);

    char* fileEnding = &dent->d_name[strlen(dent->d_name)-4];

    if     (dent->d_name[0]=='a' && !strcmp(fileEnding, ".xml")){a_xml_count++;}
    else if(dent->d_name[0]=='a' && !strcmp(fileEnding, ".pnl")){a_pnl_count++;}
    else if(dent->d_name[0]=='a' && !strcmp(fileEnding, ".res")){a_res_count++;}
    else if(dent->d_name[0]=='b' && !strcmp(fileEnding, ".xml")){b_xml_count++;}
    else if(dent->d_name[0]=='b' && !strcmp(fileEnding, ".err")){
      if (!stat(fullPathToFile, &fileStats)){
        if(fileStats.st_size>0){
          non_empty_err_count++;
          if(non_empty_err_count==1){
            errorFileExample = (char*)malloc(strlen(fullPathToFile)+1);
            strcpy(errorFileExample,fullPathToFile);
          }
        }
      }
    }
    free(fullPathToFile);
  }
  closedir(dirp);
  printf("%s\n\n",pathToFolder);
  free(pathToFolder);
  printf("batch xml-files:\t%d\n", b_xml_count);
  printf("alpha xml-files:\t%d\n", a_xml_count);
  printf("alpha pnl-files:\t%d\n", a_pnl_count);
  printf("alpha res-files:\t%d\n", a_res_count);
  printf("\n");
  printf("non-empty error files:\t%d\n", non_empty_err_count);
  if(non_empty_err_count>0){
    printf("\nfor example %s:\n",errorFileExample);
    printFirstLinesOfFile(errorFileExample,10);
    free(errorFileExample);
  }
  return 0;
}

