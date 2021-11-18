#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>  /* Defines LIBM_SO (which will be a
							   string such as "libm.so.6") */
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
 
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
  
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  
  ch = getchar();
  
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  
  if(ch != EOF)
  {
    //ungetc(ch, stdin);
    return ch;
  }
  
  return 0;
}
  
void *handle;

void rutime_load_predict_so(int (**func_predict)(int))
{
	char *error;

	handle = dlopen("obj/predict.so", RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	dlerror();    /* Clear any existing error */

	*func_predict = (int(*)(int))dlsym(handle, "func_predict");

	error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
}



int
main(void)
{
	int (*func_predict)(int) = NULL;
	rutime_load_predict_so(&func_predict);
	while(1) {
		int key = kbhit();
		if('u' == key) {
			dlclose(handle);
			rutime_load_predict_so(&func_predict);
		}
		printf("\rfunc_predict=%d          ", (*func_predict)(1));
	}
	exit(EXIT_SUCCESS);
}
