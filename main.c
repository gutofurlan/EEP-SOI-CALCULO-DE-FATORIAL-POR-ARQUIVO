
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int num=0;
int calc_metade1 = 0;
int res_pai = 0;
int res_filho =0;
int calc_metade2 = 0;
int calc_fat (int num);
int calc_fat_arq ();
int le_valor_arquivo ();
void write_file (int cont);
int main(int argc,char *argv[]) {
    int estado;int exec = 0;
    printf("Digite o numero que sera calculado o fatorial : ");
    scanf("%d", &num);
    if(num%2 != 0) {
        calc_metade1 = num/2;
        write_file(calc_metade1);
        calc_metade2 = num;
    } else {
        calc_metade1 = num/2;
        write_file(calc_metade1);
        calc_metade2 = num;
    }
    int i;
    pid_t pid;
    pid = fork();
    
    if (pid == 0)
    {
        //O código aqui dentro será executado no processo filho
        int res_metade = calc_fat_arq();
        //printf("\n\n %d \n\n", res_metade);
        write_file(res_metade);
    }
    else
    {
        //O código neste trecho será executado no processo pai
        //res_pai = calc_fat(calc_metade2);
        int k =1;
        int z = num;
        for(z = num; z>(calc_metade1); z--) {
            k = k*z;
        }
        res_pai = k;
    }
    
    exec++;
    
     waitpid(pid,estado,0);
    if(pid > 0) {
        int total = le_valor_arquivo() * res_pai;
        printf("\n O FATORIAL E : %d", total);
    }
    
    //exit(0);
    
}

void write_file (int cont) {
    FILE *arq;
    
    arq = fopen("ArqGrav.txt", "w");  // Cria um arquivo texto para gravação
    if (arq == NULL) // Se não conseguiu criar
    {
        printf("Problemas na CRIACAO do arquivo\n");
    }
    
    fprintf(arq, "%d",cont);
    fclose(arq);
}

int calc_fat_arq () {
    int num=0, total=1, cont=0;
    FILE *arquivo;
    
    arquivo=fopen("ArqGrav.txt","r");
    if ( arquivo == NULL ) {
        printf("Nao foi possivel abrir o arquivo.\n");
        exit(0);
    } else {
        fscanf(arquivo,"%d",&num);
        fclose(arquivo);
        for (cont = num; num > 1; num--) {
            total = total * (num);
        }
        
    }
    write_file(total);
    return total;
}

int calc_fat (int num) {
    int total=1, cont=0;
    for (cont = num; num > 1; num--) {
        total = total * (num);
    }
    return total;
}

int le_valor_arquivo () {
    int num=0, total=1, cont=0;
    FILE *arquivo;
    
    arquivo=fopen("ArqGrav.txt","r");
    if ( arquivo == NULL ) {
        printf("Nao foi possivel abrir o arquivo.\n");
        exit(0);
    } else {
        fscanf(arquivo,"%d",&num);
        fclose(arquivo);
        
    }
    return num;
}
