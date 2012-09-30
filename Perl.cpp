#include <iostream>
//#include <string>
using namespace std;
#include <EXTERN.h>               /* from the Perl distribution     */
#include <perl.h>                 /* from the Perl distribution     */
//#include <direct.h>


    static PerlInterpreter *my_perl;  /***    The Perl interpreter    ***/

    int main(int argc, char **argv, char **env)
    {

		cout<<"========*=========**  perl解析器  By 许剑。**==========*========="<<endl;

		char filename[30];
		cout<<"\n请输入perl文件名(包含路径)：\n"<<endl;
		cout<<">>";
		cin>>filename;
        PERL_SYS_INIT3(&argc,&argv,&env);
		char *embedding[] = {"",filename,""};
        my_perl = perl_alloc();
        perl_construct(my_perl);
        PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
        perl_parse(my_perl, NULL, 3, embedding, (char **)NULL);
        perl_run(my_perl);
        perl_destruct(my_perl);
        perl_free(my_perl);
        PERL_SYS_TERM();
		return 0;
    }