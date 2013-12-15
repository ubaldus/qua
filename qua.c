/*
 * Qùa circular shift cipher algorithm.
 *
 * Copyright (C) 2013 Ubaldo Porcheddu <ubaldo@eja.it>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
       
int main (int argc, char *argv[]) {
 FILE *fdIn=NULL;
 FILE *fdOut=NULL;
 char fileIn[64]="";
 char fileOut[64]=""; 
 char key[1024]="";
 int decode=0;
 int c=0;
 int b=0;
 int i=0;
 
 for (i=1; i<argc; i++) {
  if (argv[i][0] == '-') {
   if (argv[i][1]=='k') { strcpy(key,argv[i+1]); i++; }
   if (argv[i][1]=='d') { decode=1; }
  } else {
   if (fileIn[0] == 0) { strcpy(fileIn,argv[i]); } else { strcpy(fileOut,argv[i]); }
  }
 }
 
 if (strlen(key) > 0 && strlen(fileIn) > 0 && strlen(fileOut) > 0) {
  if ((fdIn=fopen(fileIn,"r")) == NULL) {
   fprintf(stderr,"Error: input file not found.\n");
   return -1;
  }
  if ((fdOut=fopen(fileOut,"w")) == NULL) {
   fprintf(stderr,"Error: output file problem.\n");
   return -1;
  }
  i=0; 
  while (1==1) {   
   c=fgetc(fdIn);
   if (c < 0) { break; }
   i++;
   if (decode < 1) {
    c=(c+b) % 256;
    b=c;
   } else {
    c=(c-b) % 256;
    b=(c+b);
   }
   if (strlen(key) > i) { 
    b=b+key[i];
   }
   fputc(c,fdOut);    
  }
  fclose(fdIn);
  fclose(fdOut);
 } else { 
  printf("Copyright (C) 2013 by Ubaldo Porcheddu <ubaldo@eja.it>\n");
  printf("Usage: qua [OPTIONS] [FILE_IN] [FILE_OUT]\n\n");
  printf(" -k key  keycode\n");
  printf(" -d      decode\n");   
  printf(" -h      this help\n\n");
 }
 
 return 0;
}
