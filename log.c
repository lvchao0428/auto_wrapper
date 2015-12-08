/*************************************************************************
    > File Name: log.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Dec  8 15:43:11 2015
 ************************************************************************/

#include<stdio.h>
#include"log.h"


void push(Log** lg, int lineno, char* url, char* content, char* time)
{
   Log* head,* p;
   if(*lg == NULL)
   {
	  *lg = (Log*)malloc(sizeof(Log));
	  (*lg)->next = NULL;

	  (*lg)->next = NULL;
	  (*lg)->lineno = lineno;
	  (*lg)->url = (char*)malloc(sizeof(char)*(strlen(url) + 1));
	  memcpy((*lg)->url, url, sizeof(char)*(strlen(url) + 1));
	  (*lg)->content = (char*)malloc(sizeof(char)*(strlen(content) + 1));
	  memcpy((*lg)->content, content, sizeof(char)*(strlen(content) + 1));
	  (*lg)->time = (char*)malloc(sizeof(char)*(strlen(time) + 1));
	  memcpy((*lg)->time, time, sizeof(char)*(strlen(time) + 1));
   }
   else
   {
	  Log* plg = (Log*)malloc(sizeof(Log));
	  plg->next = NULL;
	  p = *lg;
	  head = p;
	  while(p->next)
	  {
		 p = p->next;
	  }
	  plg->lineno = lineno;
	  plg->url = (char*)malloc(sizeof(char)*(strlen(url) + 1));
	  memcpy(plg->url, url, sizeof(char)*(strlen(url) + 1));
	  plg->content = (char*)malloc(sizeof(char)*(strlen(content) + 1));
	  memcpy(plg->content, content, sizeof(char)*(strlen(content) + 1));
	  plg->content = (char*)malloc(sizeof(char)*(strlen(time) + 1));
	  memcpy((*lg)->time, time, sizeof(char)*(strlen(time) + 1));

	  p->next = plg;
	  *lg = head;
   }
}
