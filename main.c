#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void    checkArg(const char *a)
{
  while (*a)
    {
      if (   (*a == ';')
          || (*a == '&')
          || (*a == '|')
          || (*a == ',')
          || (*a == '$')
          || (*a == '(')
          || (*a == ')')
          || (*a == '{')
          || (*a == '}')
          || (*a == '`')
          || (*a == '>')
          || (*a == '<') ) {
        puts("Forbidden !!!");
        exit(2);
      }
        a++;
    }
}

int     main()
{
  char  *arg = malloc(0x20);
  char  *cmd = malloc(0x400);
  setreuid(geteuid(), geteuid());

  //Использование функции strcpy считается небезопасным, так как она не отслеживает размер своего буфера и ведет к уязвимости buffer overflow
  strcpy(cmd, "/bin/ls -l ");

  printf("Enter directory you want to display : ");

  //Использование функции gets считается небезопасным, так как она не отслеживает размер своего буфера и ведет к уязвимости buffer overflow
  gets(arg);
  checkArg(arg);

  //Функция strcat так же не отслеживает размер своего буфера и ведет к уязвимости buffer overflow
  strcat(cmd, arg);
  system(cmd);

  return 0;
}