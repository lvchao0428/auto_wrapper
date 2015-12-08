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

void read_spc_html2(GumboNode* root, GumboNode** contentNode, GumboNode** timeNode)
{
   if(!root)
   {
	  return;
   }
   else if(root->type == GUMBO_NODE_ELEMENT && *contentNode == NULL
		 && root->type != GUMBO_TAG_SCRIPT &&
		 root->type != GUMBO_TAG_STYLE)
   {
	  GumboVector* children = &root->v.element.children;
	  int i;
	  for(i = 0; i < children->length; ++i)
	  {
		 read_spc_html2(children->data[i], contentNode, timeNode);
	  }
   }
   else if(root->type == GUMBO_NODE_TEXT &&
		 root->parent->v.element.tag != GUMBO_TAG_SCRIPT &&
		 root->parent->v.element.tag != GUMBO_TAG_STYLE &&
		 (*contentNode == NULL || *timeNode == NULL) &&
		 root->parent->v.element.tag != GUMBO_TAG_ANNOTATION_XML &&
		 strcasecmp(gumbo_normalized_tagname(root->parent->v.element.tag), "textarea") != 0)
   {
	  /*
	  if(root->v.text.text)
	  {
		 printf("no:%d\n", find_comma_num_out(root->v.text.text));
		 //	printf("str:%s\n", root->v.text.text);
	  }
	  */

	  //content ext
	  //ver1 1只检测标点,并直接找到最近div
	  if(find_comma_num_out(root->v.text.text) > 5)
	  {
		 //如果text的标点符号超过阈值，则向上遍历到div或者table节点
		 GumboNode* tempcontentNode = NULL;
		 tempcontentNode = root->parent;
		 while(tempcontentNode)
		 {
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
	  GumboNode* temptimeNode = NULL;
	  temptimeNode = root;
	  //time ext
	  if(is_time_str(root->v.text.text))
	  {
//		 printf("time:1:str:%s\n", root->v.text.text);
	  }
	  if(is_time_str(root->v.text.text))
	  {
		 temptimeNode = temptimeNode->parent;
		 while(temptimeNode)
		 {
			if(strcasecmp(gumbo_normalized_tagname(temptimeNode->v.element.tag), "span") == 0)
			{
			   *timeNode = temptimeNode;
			   break;
			}

			temptimeNode = temptimeNode->parent;
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

int test_ext(char* htmlfile, char** contentstr, char** timestr)
{
   FILE* fp = fopen(htmlfile, "r");
   if(!fp)
   {
	  printf("error\n");
	  return -1;
   }
   char* input;
   int input_length;
   read_file(fp, &input, &input_length);

   GumboOutput* output = gumbo_parse(input);
   if(!output)
   {
	  printf("parse error\n");
	  return -2;
   }
   char* title = find_title(output->root);
   if(strstr(title, "302") || strstr(title, "404") || strstr(title, "403"))
   {
	  return -1;
   }
   GumboNode* contentNode = NULL;
   GumboNode* timeNode = NULL;
   //char* content = NULL;
   read_spc_html2(output->root, &contentNode, &timeNode);
   
   //test tag output
   

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

   ///time
//   char* timestr = NULL;
   cleantext(timeNode, timestr);
//   printf("time:%s\n", timestr);
   gumbo_destroy_output(&kGumboDefaultOptions, output);
   //free(content);
   fclose(fp);
   return 1;
}

