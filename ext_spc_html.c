/*************************************************************************
    > File Name: ext_com_main.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Fri Dec  4 15:23:18 2015
 ************************************************************************/

#include<stdio.h>
#include"read_html.h"
#include"mystring.h"
#include"ext_spc_html.h"

void ret_tag(GumboNode* node, char* tag, int* length)
{
    int j = 0;
	int i = 0;
	if(!node && node->v.element.original_tag.length < 2)
	{
	   return;
	}
	i++;

	while(node->v.element.original_tag.data[i] != '\0' && 
		  node->v.element.original_tag.data[i] != '\n' &&
		  node->v.element.original_tag.data[i] != ' ' && 
		  node->v.element.original_tag.data[i] != '>')
	{
	   tag[j++] = node->v.element.original_tag.data[i++];
	}
	tag[j] = '\0';
	*length = j;
}

void read_spc_html2(GumboNode* root, GumboNode** contentNode, GumboNode** timeNode, char** timestr)
{
   if(!root)
   {
	  return;
   }
   else if(root->type == GUMBO_NODE_ELEMENT && (*contentNode == NULL || *timestr)
		 && root->type != GUMBO_TAG_SCRIPT &&
		 root->type != GUMBO_TAG_STYLE)
   {
	  GumboVector* children = &root->v.element.children;
	  int i;
	  for(i = 0; i < children->length; ++i)
	  {
		 read_spc_html2(children->data[i], contentNode, timeNode, timestr);
	  }
   }
   else if(root->type == GUMBO_NODE_TEXT &&
		 root->parent->v.element.tag != GUMBO_TAG_SCRIPT &&
		 root->parent->v.element.tag != GUMBO_TAG_STYLE &&
		 (*contentNode == NULL || *timestr == NULL) &&
		 root->parent->v.element.tag != GUMBO_TAG_ANNOTATION_XML)// &&
		 //strcasecmp(gumbo_normalized_tagname(root->parent->v.element.tag), "textarea") != 0)
   {
	  /*
	  if(root->v.text.text)
	  {
		 printf("no:%d\n", find_comma_num_out(root->v.text.text));
		 //	printf("str:%s\n", root->v.text.text);
	  }
	  */
//	  printf("tag num:%d\n", )
	  //content ext
	  //ver1 1只检测标点,并直接找到最近div
	  if(find_comma_num_out(root->v.text.text) > 5)
	  {
		 //如果text的标点符号超过阈值，则向上遍历到div或者table节点
		 GumboNode* tempcontentNode = NULL;
		 tempcontentNode = root->parent;
		
		 while(tempcontentNode)
		 {
		//	printf("tagnum:%d\n", tempcontentNode->v.element.tag);
		//	printf("tag last:%d\n", GUMBO_TAG_LAST);
			if(strcasecmp(gumbo_normalized_tagname(tempcontentNode->v.element.tag), "div") == 0 ||
				  strcasecmp(gumbo_normalized_tagname(tempcontentNode->v.element.tag), "table") == 0)
			{
			   *contentNode = tempcontentNode;
			   break;
			}

			tempcontentNode = tempcontentNode->parent;
		 }
		 
		 /*
		   if(tempcontentNode->v.element.children.length > 6)
		 {
			while(tempcontentNode)
			{

			   if(strcasecmp(gumbo_normalized_tagname(tempcontentNode->v.element.tag), "div") == 0 ||
					 strcasecmp(gumbo_normalized_tagname(tempcontentNode->v.element.tag), "table") == 0)
			   {
				  *content = tempcontentNode;
				  break;
			   }
			   tempcontentNode = tempcontentNode->parent;
			}

		 }

		 */
	  }
	  if(*timestr == NULL)
	  {
		 GumboNode* temptimeNode = NULL;
		 temptimeNode = root;
		 //time ext
		 char* timebeg, * timeend;
		 timebeg = NULL;
		 timeend = NULL;
		 if(is_time_str(root->v.text.text, &timebeg, &timeend))
		 {
			temptimeNode = temptimeNode->parent;
			while(temptimeNode)
			{
			   //printf("time tagnum:%d\n", temptimeNode->v.element.tag);
			   //printf("time tag last:%d\n", GUMBO_TAG_LAST);
			   if(temptimeNode->v.element.tag != GUMBO_TAG_LAST)
			   {
				  *timestr = (char*)malloc(sizeof(char)*(timeend - timebeg + 2));
				  snprintf(*timestr, sizeof(char)*(timeend - timebeg + 2), "%s", timebeg);
				  *timeNode = temptimeNode;
				  break;
			   }

			   temptimeNode = temptimeNode->parent;
			}
		 }

	  }

   }
}

void read_spc_html(GumboNode* root, GumboNode** content)
{
   if(!root)
   {
	  return;
   }
   else if(*content == NULL)
   {
	  if(root->type == GUMBO_NODE_ELEMENT)
	  {
		 GumboVector* attrVec = &root->v.element.attributes;
		 GumboAttribute* attr;
		 int i;
		 for(i = 0; i < attrVec->length; ++i)
		 {
			attr = attrVec->data[i];

			if(strcmp(attr->value, "artibody") == 0)
			{	
			   //print_with_length(root->v.element.original_tag.data, root->v.element.original_tag.length);
			   *content = root;
			   return;
			}
		 }

		 GumboVector* children = &root->v.element.children;
	//	 int i;
		 for(i = 0; i < children->length; ++i)
		 {
			read_spc_html(children->data[i], content);
		 }

	  }
   }
}

void find_body(GumboNode* root, GumboNode** bodyNode)
{
   if(!root)
   {
	  return;
   }
   else if(*bodyNode == NULL && root->type == GUMBO_NODE_ELEMENT)
   {
	  if(strcasecmp(gumbo_normalized_tagname(root->v.element.tag), "body") == 0)
	  {
		 *bodyNode = root;
		 return;
	  }
	  else
	  {
		 GumboVector* children = &root->v.element.children;
		 int i;
		 for(i = 0; i < children->length; ++i)
		 {
			find_body(children->data[i], bodyNode);
		 }
	  }
   }
}

int test_ext(char* htmlfile, char** contentstr, char** titlestr,char** timestr)
{
   FILE* fp = fopen(htmlfile, "r");
   if(!fp)
   {
	  printf("file not exsit\n");
	  return -1;
   }
   char* input = NULL;
   int input_length;
   read_file(fp, &input, &input_length);

   GumboOutput* output = gumbo_parse(input);
   if(!output)
   {
	  printf("parse error\n");
	  return -2;
   }
   
   char* title = find_title(output->root);
   *titlestr = (char*)malloc(sizeof(char)*(strlen(title) + 1));
   memcpy(*titlestr, title, sizeof(char)*(strlen(title) + 1));
   if(strstr(title, "302") || strstr(title, "404") || strstr(title, "403"))
   {
//	  printf("")
	  free(input);

	  gumbo_destroy_output(&kGumboDefaultOptions, output);
	  return -1;
   }
   GumboNode* contentNode = NULL;
   GumboNode* timeNode = NULL;
   //char* content = NULL;
   GumboNode* bodyNode = NULL;
   find_body(output->root, &bodyNode);
  // printf("bodyNode:%s\n", gumbo_normalized_tagname(bodyNode->v.element.tag));
   read_spc_html2(bodyNode, &contentNode, &timeNode, timestr);
   
   //test tag outpu
   

//   contentNode->v.element.tag
   //if(contentNode)
   //printf("tagname:%s\n", gumbo_normalized_tagname(contentNode->v.element.tag));
   //printf("roottagname:%s\n", gumbo_normalized_tagname(output->root->v.element.tag));
  // print_with_length(contentNode->v.element.original_tag.data, contentNode->v.element.original_tag.length);
   char tag[100];
   int length;
   bzero(tag, sizeof(tag));
   //ret_tag(contentNode, tag, &length);
   //printf("tag:%s\n", tag);
   cleantext(contentNode, contentstr);
   //printf("content:%s\n", content);
   
   free(input);
   ///time
//   char* timestr = NULL;
   //cleantext(timeNode, timestr);
//   printf("time:%s\n", timestr);
   gumbo_destroy_output(&kGumboDefaultOptions, output);
   //free(content);
   fclose(fp);
   return 1;
}

