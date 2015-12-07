/*************************************************************************
    > File Name: main.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Dec  7 14:29:55 2015
 ************************************************************************/

#include<stdio.h>
#include"def.h"
#include"read_html.h"
#include"ext_spc_html.h"

int main(int argc, char* argv[])
{
   if(argc < 2)
   {
	  printf("need file name\n");
	  exit(1);
   }

   test_ext(argv[1]);

   return 0;
}
