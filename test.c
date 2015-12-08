/*************************************************************************
    > File Name: test.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Dec  8 15:20:11 2015
 ************************************************************************/

#include<stdio.h>
#include"test.h"
#include"savehtml.h"

void test_single(char* html)
{
   char* content = NULL;
   char* time = NULL;
   test_ext(html, &content, &time);

   printf("content:%s\n", content);
   printf("time:%s\n", time);
}

void test_ver3()
{
   UrlBuf* ub = NULL;
   
   Log* lg = NULL;
   read_urls_to_UrlBuf(&ub, "./suculswave");
   printf("read buf complet\n");
   int totalhtml = 0;
   int contenthit = 0;
   int timehit = 0;
   
   UrlBuf* p = ub;
   while(p)
   {
	  char* contentstr = NULL;
	  char* timestr = NULL;
	  char filename[50];
	  
	  
	  bzero(filename, sizeof(filename));
	  sprintf(filename, "../kejiUtfhtmls/%d.html", p->lineno);
	  int ret = test_ext(filename, &contentstr, &timestr);
	  printf("%d complete...", p->lineno);
	  if(ret == -1)
	  {
		 p = p->next;
		 continue;
	  }
	  char tempcontent[30];
	  bzero(tempcontent, sizeof(tempcontent));
	  snprintf(tempcontent, sizeof(char)*25, "%s", contentstr);

	  totalhtml++;
	  if(contentstr != NULL)
	  {
		 printf("contentstr:%s\n", contentstr);
		 contenthit++;
	  }
	  if(timestr != NULL)
	  {
		 printf("timestr:%s\n", timestr);
		 timehit++;
	  }

	  //push(&lg, p->lineno, p->str, tempcontent, timestr);
	  	  
	  p = p->next;
   }

   //char fileansw[50];
   FILE* fp = fopen("answer", "w");
   fprintf(fp, "total:%dhtmls\n", totalhtml);
   fprintf(fp, "content hit:%d \n", contenthit);
   fprintf(fp, "time hit:%d\n", timehit);

}
