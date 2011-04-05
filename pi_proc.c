/*
Problema: Estimar o valor de PI atrav?s do M?todo de Monte Carlo.
          Deve-se utilizar 2 processos filhos para c?lculo,
          cabendo ao processo pai a sumariza??o dos dados e c?lculo do PI.
          N?o ? necess?rio corrigir o vi?s estat?stico.

Autor: Guilherme Giacchetto Moreira
SO: FreeBSD
Versão: 2.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int chute(int n, int seed);

int main(int argc, char *argv) {
  FILE *fp;
  
  fp = fopen("arquivo.txt","w+");
  int pid;
  
  printf("%d. Pai\n\n", getpid());
  pid = fork();
  
  //Filho 1
  if(pid == 0) {
    printf("%d. Filho1\n", getpid());
    int n = rand();
    fprintf(fp, "%d\n%d\n", chute(n, 1), n);
  }
  
  if(pid > 0) {
    int pid2;
    
    pid2 = fork();
    //Filho 2
    if(pid2 == 0) {
      printf("%d. Filho2\n", getpid());
      int n = rand()/66;
      fprintf(fp, "%d\n%d\n", chute(n, 666666), n);
    }
    
    wait(NULL); //Espera Filho 1
    if(pid2 > 0) {
      wait(NULL); //Espera Filho 2
      
      //Pai
      FILE *entrada;
      entrada = fopen ("arquivo.txt", "r");
      char le[20], ne[200], ce[20];
      int c, n, i, j;
      i = 0;
      j = 0;
      c = 0;
      n = 0;
      while (!feof(entrada)) {
	fscanf(entrada,"%c",&le[0]);
  	if(le[0] == '\n') {
	  if(i == 0) {
	    n += atoi(ne);
	    j = 0;
	    i = 1;
	    *ne = '\0';
	  } else {
	    c += atoi(ce);
	    j = 0;
	    i = 0;
	    *ce = '\0';
	  }
	} else {
	  if(i == 0) {
	    ne[j] = le[0];
	    j++;
	  } else {
	    ce[j] = le[0];
	    j++;
	  }
	}
      } 
      fclose (entrada);

      printf("PI => 4*(%d/%d) = %g\n", n, c, (double)n * 4.0 / c);
    }
  }
  
  fclose(fp);
  
  return EXIT_SUCCESS;
}

int chute(int n, int seed) {
  int i, c;
  double x, y;
  srand(seed);

  for(c=0, i=0; i<n; i++) {
    x = (double)rand()/RAND_MAX;
    y = (double)rand()/RAND_MAX;
    if(x*x+y*y <= 1) c++;
  }
  return c;
}
