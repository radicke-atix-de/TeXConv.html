%{
#include <stdio.h>
#include <stdlib.h>
%}
%option main
%%
"<username>" printf("%s", getenv("USER"));