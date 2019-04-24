#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>


/* declaration des variables */
int a, b;
int val;
int g_answer = 0, b_answer = 0, to_answer = 0;
sigjmp_buf env;


/* declaration des fonctions */
void ctrl_c();
void timer(int sig);
void fonction();


void ctrl_c()
{
	printf("\n %d bonnes réponses et %d mauvaises réponse sur %d.\n", g_answer,b_answer+to_answer, g_answer+b_answer+to_answer);
	exit(0);
}


void timer(int sig)
{
	printf("Trop tard !");
	to_answer++;
	siglongjmp(env, 2);
}


int main()
{
	srand(getpid());
	while(1)
	{
		int rep;
		signal(SIGINT, ctrl_c);

		val = sigsetjmp(env, 2);

		a = (rand() %8)+2;
		b = (rand() %8)+2;
		printf("\n%d * %d = ", a, b);

		signal(SIGALRM, timer);
		alarm(5);

		scanf("%d", &rep);
		if(rep == a * b)
		{
			printf("Vrai");
			g_answer++;
		} else
		{
			printf("Faux : %d + %d = %d", a, b, a*b);
			b_answer++;;
		}
	}

	return 0;
}
