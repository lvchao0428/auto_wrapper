#ifndef _EXT_SPC_HTML_H
#define _EXT_SPC_HTML_H

#include"def.h"
#include"mystring.h"
#include"read_html.h"


void ret_tag(GumboNode* node, char* tag, int* length);

void read_spc_html2(GumboNode* root, GumboNode** content, GumboNode** timeNode);

void read_spc_html(GumboNode* root, GumboNode** content);

void test_ext(char* htmlfile);


#endif
