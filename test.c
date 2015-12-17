/*************************************************************************
    > File Name: test.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Dec  8 15:20:11 2015
 ************************************************************************/

#include<stdio.h>
#include"test.h"
#include"savehtml.h"
#include<time.h>

void test_single(char* html)
{
   char* content = NULL;
   char* time = NULL;
   char* title = NULL;
   test_ext(html, &content, &title, &time);

   printf("title:%s\n", title);
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
  
   FILE* logfile = NULL;
   logfile = fopen("logfile", "w");
   
   UrlBuf* p = ub;
   while(p)
   {
	  char* contentstr = NULL;
	  char* timestr = NULL;
	  char* titlestr = NULL;
	  char filename[50];
	  
	  bzero(filename, sizeof(filename));
	  sprintf(filename, "../kejiUtfhtmls/%d.html", p->lineno);
	  int ret = test_ext(filename, &contentstr, &titlestr, &timestr);
	  printf("%d complete...", p->lineno);
	  if(p->lineno == 28309)
	  {
		 break;
	  }
	  time_t timep;
	  time(&timep);
	  if(ret == -1 || ret == -2)
	  {

		 p = p->next;
		 continue;
	  }
	 
	  char tempcontent[100];
	  bzero(tempcontent, sizeof(tempcontent));
	  snprintf(tempcontent, sizeof(char)*100, "%s", contentstr);

	  totalhtml++;
	  if(contentstr != NULL)
	  {
		 //printf("contentstr:%s\n", tempcontent);
		 contenthit++;
	  }
	  if(timestr != NULL)
	  {
		 //printf("timestr:%s\n", timestr);
		 timehit++;
	  }
	   if(contentstr == NULL)
	  {
		 contentstr = (char*)malloc(sizeof(char)*(strlen("null") + 1));
		 memcpy(contentstr, "null", sizeof(char)*(strlen("null") + 1));

	  }
	  if(timestr == NULL)
	  {
		 timestr = (char*)malloc(sizeof(char)*(strlen("null") + 1));
		 memcpy(timestr, "null", sizeof(char)*(strlen("null") + 1));

	  }
	  if(titlestr == NULL)
	  {
		 titlestr = (char*)malloc(sizeof(char)*(strlen("null") + 1));
		 memcpy(titlestr, "null", sizeof(char)*(strlen("null") + 1));
	  }


	  //push(&lg, p->lineno, p->str, tempcontent, timestr);
	  fprintf(logfile, "systime:%s, file_no:%d, url:%s, title:%s, time:%s, content:%s\n",
			asctime(gmtime(&timep)), p->lineno, p->str, titlestr, timestr, tempcontent);
	  
	  printf("systime:%s, file_no:%d, url:%s, title:%s, time:%s, content:%s\n",
			asctime(gmtime(&timep)), p->lineno, p->str, titlestr, timestr, tempcontent);
	  free(titlestr);
	  free(contentstr);
	  free(timestr);
	  p = p->next;
   }
   fclose(logfile);
   //char fileansw[50];
   FILE* fp = fopen("answer", "w");
   fprintf(fp, "total:%dhtmls\n", totalhtml);
   fprintf(fp, "content hit:%d \n", contenthit);
   fprintf(fp, "time hit:%d\n", timehit);
   fclose(fp);
}

void test_ver4()
{//test log
   UrlBuf* ub = NULL;
   
   Log* lg = NULL;
   read_urls_to_UrlBuf(&ub, "./suculswave");
   printf("read buf complet\n");
   int totalhtml = 0;
   int contenthit = 0;
   int timehit = 0;
  
   UrlBuf* p = ub;
   do
   {
	  int fileno;
	  p = ub;
	  printf("input fileno:");
	  scanf("%d", &fileno);
	  if(fileno == 0)
	  {
		 print_log(lg);
		 continue;
	  }
	  char* contentstr = NULL;
	  char* timestr = NULL;
	  char* titlestr = NULL;
	  char filename[50];
	  
	  bzero(filename, sizeof(filename));
	  sprintf(filename, "../kejiUtfhtmls/%d.html", fileno);
	  while(p->lineno != fileno)
	  {
		 printf("url:%s\n", p->str);
		 p = p->next;
	  }

	  int ret = test_ext(filename, &contentstr, &titlestr, &timestr);
	  printf("title:%s\n", titlestr);
	  printf("contentstr:%s\n", contentstr);
	  printf("timestr:%s\n", timestr);
	  char tempcontent[100];
	  bzero(tempcontent, sizeof(tempcontent));
	  snprintf(tempcontent, sizeof(char)*100, "%s", contentstr);
	  //if null
	  if(contentstr == NULL)
	  {
		 contentstr = (char*)malloc(sizeof(char)*(strlen("null") + 1));
		 memcpy(contentstr, "null", sizeof(char)*(strlen("null") + 1));

	  }
	  if(timestr == NULL)
	  {
		 timestr = (char*)malloc(sizeof(char)*(strlen("null") + 1));
		 memcpy(timestr, "null", sizeof(char)*(strlen("null") + 1));

	  }
	  if(titlestr == NULL)
	  {
		 titlestr = (char*)malloc(sizeof(char)*(strlen("null") + 1));
		 memcpy(titlestr, "null", sizeof(char)*(strlen("null") + 1));
	  }

	  if(ret != -1 && ret != -2)
	  {
		 printf("url:%s\n", p->str);
		 push_log(&lg, p->lineno, p->str, titlestr, tempcontent, timestr);
	  }

   }while(fileno != -1);

}
