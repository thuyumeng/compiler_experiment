#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char        *yytext = "";   // lexeme 是 词法分析的最小单位，其实就是一个单词，一个符号或者一个数字
int         yyleng  = 0;    // lexeme的长度
int         yylineno = 0;   // lexeme的line number

// 这一版的lex只实现四则运算的解析
int lex()
{
    static char input_buffer[128];
    char   *current;
    
    current = yytext + yyleng;      // Skip current lexeme
    while(1)
    {
        // current在while开头时是每一行的结尾
        while(*current == '\0')
        {
            // 获取新行，跳过空行，直到一个非空行
            current = input_buffer;
            if (!gets(input_buffer))
            {
                *current = '\0';
                return EOI;
            }

            ++yylineno;
            while(isspace(*current))
                ++current;
        }

        for(; *current ; ++current)
        {
            //获取下一个token
            yytext = current;
            yyleng = 1;

            // lex的核心就是这个switch
            switch (*current)
            {
            case EOF: return EOI;
            case ';': return SEMI;
            case '+': return PLUS;
            case '*': return TIMES;
            case '(': return LP;
            case ')': return RP;
            case '/n':
            case '/t':
            case ' ':  break;
            default:
                if(!isalnum(*current))
                {
                    fprintf(stdout, 
                            "Ignoring illegal input <%c>\n",
                            *current);
                }
                else
                {
                    while (isalnum(*current))
                    {
                        ++current;
                    }
                    
                    yyleng = current - yytext;
                    return NUM_OR_ID;
                }
                break;
            }
        }
    }
}

// 对于parser来讲往往需要读取下一个token才能解析当前token的含义 比如 += *=这种符号
// lookahead时不改变current，根据lookahead的结果操作current
static int Lookahead = -1;

int match(int token)
{
    if(Lookahead == -1)
    {
        Lookahead = lex();
        // 打印当前解析的token
        printToken();
    }
    return token == Lookahead;
}

void advance()
{
    Lookahead = lex();
    // 打印当前解析的token
    printToken();
}

void printToken()
{
    // 打印当前解析的token
    char test_buf[120];
    memcpy((void *)test_buf, (void *)yytext, yyleng);
    test_buf[yyleng] = '\0';
    fprintf(stdout, "%s\n", test_buf);
}