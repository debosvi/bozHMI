
#include "nxjson_test.h"

char* load_file(const char* filepath) {
  struct stat st;
  if (stat(filepath, &st)==-1) {
    // ERROR("can't find file", filepath);
    return 0;
  }
  int fd=open(filepath, O_RDONLY);
  if (fd==-1) {
    ERROR("can't open file", filepath);
    return 0;
  }
  char* text=malloc(st.st_size+1); // this is not going to be freed
  if (st.st_size!=read(fd, text, st.st_size)) {
    ERROR("can't read file", filepath);
    close(fd);
    return 0;
  }
  close(fd);
  text[st.st_size]='\0';
  return text;
}

int save_file(const char* filepath, const char* text) {
  int fd=open(filepath, O_WRONLY|O_CREAT|O_TRUNC, 0644);
  if (fd==-1) {
    ERROR("can't open file", filepath);
    return -1;
  }
  int length=strlen(text);
  if (length!=write(fd, text, length)) {
    ERROR("can't write file", filepath);
    close(fd);
    return -1;
  }
  close(fd);
  return 0;
}
