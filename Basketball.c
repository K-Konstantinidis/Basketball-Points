/*************************************************************************
        Copyright © 2021 Konstantinidis Konstantinos
        
	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at
    
        http://www.apache.org/licenses/LICENSE-2.0
        
	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*************************************************************************/
#include <stdio.h>
#include "genlib.h"
#include <ctype.h>
#include "simpio.h"
#include <string.h>

typedef struct{
int no;
char fullname[29];
int points;
}team_basket;

main(){
    team_basket basket[10];
    FILE *infile, *outfile;

    infile = fopen("i11f9.dat","r");
    if(infile == NULL){
        printf("Can't open the file %s", "i11f9.dat");
        exit(1);
    }
    else{
        readFromFile(infile, basket);
        outfile = fopen("o11f9.dat","w");
        writeToFile(outfile, basket);
    }

    fclose(infile);
    fclose(outfile);

    system("PAUSE");
}

void readFromFile(FILE *infile, team_basket basket[])
{
    int nscan, i=0, line=0;
    char termch;

    while(TRUE){
        nscan = fscanf(infile,"%d, %29[^,], %d%c", &basket[i].no, basket[i].fullname, &basket[i].points, &termch);
        if(nscan == EOF)break;
        line++;
        if(nscan != 4 || termch != '\n'){
            printf("There is a problem with the file in line: %d", line);
            exit(1);
        }
        else
            i++;
    }

    return 0;
}

void writeToFile(FILE *outfile, team_basket basket[]){
    int i;
    int total_points = 0;
    int more_than_10_points = 0;

    printf("%-28s%11s\n","FULL NAME","POINTS");
    fprintf(outfile,"%-28s%11s\n","FULL NAME","POINTS");
    for(i=0; i<39; i++){
        printf("-");
        fputc('-',outfile);
    }
    printf("\n");
    fputc('\n',outfile);

    for(i=0; i<10; i++){
        printf("%-28s%11d\n", basket[i].fullname, basket[i].points);
        fprintf(outfile,"%-28s%11d\n", basket[i].fullname, basket[i].points);
    }

    for(i = 0; i < 39; i++){
        printf("-");
        fputc('-',outfile);
    }
    printf("\n");
    fputc('\n',outfile);

    for(i=0; i<10; i++){
        total_points += basket[i].points;
        if(basket[i].points >= 10)
            more_than_10_points ++;
    }
    printf("%-28s%11d","TOTAL POINTS",total_points);
    fprintf(outfile,"%-28s%11d","TOTAL POINTS",total_points);

    printf("\n");
    fputc('\n',outfile);

    printf("%-28s%8d","TOTAL PLAYERS with points >= 10",more_than_10_points);
    printf("\n");
    fprintf(outfile,"%-28s%8d","TOTAL PLAYERS with points >= 10",more_than_10_points);

    return 0;
}
