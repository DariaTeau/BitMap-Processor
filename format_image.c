#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#pragma pack(1)

typedef struct bmp_fileheader
{
    unsigned char  fileMarker1; /* 'B' */
    unsigned char  fileMarker2; /* 'M' */
    unsigned int   bfSize; /* File's size */
    unsigned short unused1;
    unsigned short unused2;
    unsigned int   imageDataOffset; /* Offset to the start of image data */
}fheader;

typedef struct bmp_infoheader
{
    unsigned int   biSize; /* Size of the info header - 40 bytes */
    signed int     width; /* Width of the image */
    signed int     height; /* Height of the image */
    unsigned short planes;
    unsigned short bitPix;
    unsigned int   biCompression;
    unsigned int   biSizeImage; /* Size of the image data */
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
}iheader;

#pragma pack()

//structura pentru BGR-ul unui pixel
typedef struct pixel{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
}pixel;

//structura entru definirea unei imagini
typedef struct img {
    pixel p;
    fheader f;
    iheader i;

}img;

//structura pentru a retine cifrele, pozitiile si culoarea lor
typedef struct numar{
    int cifra;
    int poz_1;
    int poz_2;
    int culoare;
}numar;

//urmatoarele 10 functii au fost explicate la task-ul 2
void zero(char m[5][5]){
    int i,j;
    for(j=0;j<5;j++){
        m[0][j]='x';
        m[4][j]='x';
    }
    for(i=1;i<=3;i++){
        m[i][0]='x';
        m[i][4]='x';
    }
    for(i=1;i<=3;i++)
        for(j=1;j<=3;j++)
            m[i][j]='.';
}

void unu(char m[5][5]){
    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            if(j==4)
                m[i][j]='x';
            else
                m[i][j]='.';
}

void doi(char m[5][5]){
    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++){
            if(i%2==0)
                m[i][j]='x';
            else{
                if(((i==1)&&(j==4)) || ((i==3)&&(j==0)))
                    m[i][j]='x';
                else
                    m[i][j]='.';
            }
        }
}

void trei (char m[5][5]){
    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            if(i%2==0)
                m[i][j]='x';
            else{
                if(((i==1)&&(j==4)) || ((i==3)&&(j==4)))
                    m[i][j]='x';
                else
                    m[i][j]='.';
            }
}

void patru (char m[5][5]){
    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++){
            if((((i==0) || (i==1)) && ((j==0) || (j==4))) || (i==2) || (j==4))
                m[i][j]='x';
            else
                m[i][j]='.';
        }
}

void cinci (char m[5][5]){
    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++){
            if(i%2==0)
                m[i][j]='x';
            else{
                if(((i==1)&&(j==0)) || ((i==3)&&(j==4)))
                    m[i][j]='x';
                else
                    m[i][j]='.';
             }
        }
    
}

void sase (char m[5][5]){
    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++){
            if(i%2==0)
                m[i][j]='x';
            else{
                if(((i==3) && ((j==0) || (j==4))) || ((i==1) && (j==0)))
                    m[i][j]='x';
                else
                    m[i][j]='.';
             }
        }
}

void sapte (char m[5][5]){
    int i,j;
    for(j=0;j<5;j++)
        m[0][j]='x';
    for(i=1;i<5;i++)
        for(j=0;j<5;j++)
            if(j==4)
                m[i][j]='x';
            else
                m[i][j]='.';

}

void opt (char m[5][5]){
    int i,j;
    for(j=0;j<5;j++){
        m[0][j]='x';
        m[4][j]='x';
    }
    for(i=1;i<=3;i++){
        m[i][0]='x';
        m[i][4]='x';
    }
    for(i=1;i<=3;i++)
        for(j=1;j<=3;j++)
            if(i==2)
                m[i][j]='x';
            else
                m[i][j]='.';

}

void noua (char m[5][5]){
    int i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            if(i%2==0)
                m[i][j]='x';
            else{
                if(((i==1) && ((j==0) || (j==4))) || ((i==3) && (j==4)))
                    m[i][j]='x';
                else
                    m[i][j]='.';
            }

}

/*transforma imaginea intr-o matrice care are 'x' in loc de un 
pixel colorat si '.' in loc de pixel alb, iar daca exista padding pune 'p'
mai creaza o matrice ce are 0 in loc de pixel alb, 1 in loc de padding, si un numar
ce reprezinta BGR in loc de pixel colorat*/
void matrice(char *name_1, char a[200][200],int c[200][200], int *w, int *h, int *pad){
	
    int bgr;
    int poz;
    int count;
	img file;

    FILE *in=fopen(name_1,"rb");
    if(in==NULL)
        printf("Nu s-a deschis fisierul");
    
    fseek(in,18,SEEK_SET);

    
    fread(&file.i.width,sizeof(signed int),1,in);
    *w=file.i.width;
    *pad=file.i.width;
    int t=*w*3;
    if((*w*3)%4!=0)
        while(t%4!=0){
            t++;
        }
    
    
    fread(&file.i.height,sizeof(signed int),1,in);
     *h=file.i.height;
    
    fseek(in,54,SEEK_SET);
    int s;
    int k=1;
    int i=*h-1,j=0;

    while(k<=((*w)*(*h))){
        bgr=0;
    	s=0;

        fread(&file.p.blue,1,1,in);
        bgr=file.p.blue*pow(10,6);
        if(file.p.blue == 255)
        	s++;
       

        fread(&file.p.green,1,1,in);
        bgr=bgr+file.p.green*pow(10,3);
        if(file.p.green == 255)
        	s++;
        

        fseek(in,0,SEEK_CUR);
        

        fread(&file.p.red,1,1,in);
        bgr=bgr+file.p.red;
        if(file.p.red == 255)
        	s++;

        if((i>=0) && (j<*w)){
        	if(s!=3){
        		a[i][j]='x';
                c[i][j]=bgr;
                
        	}else{
        		a[i][j]='.';
                c[i][j]=0;
            }
        }

        if(j == *w-1){
        	i--;
        	j=0;
        }else
        	j++;
        s=0;
        bgr=0;
        count++;
            if (count == *w){
       
                if((*w*3)%4 != 0){
                    poz=t-(*w*3);
            
                    fseek(in,poz,SEEK_CUR);
                
                }
                count=0;
            }
        
       k++;
    }
    if((*w*3)%4 != 0)
        for(i= 0;i< *h;i++)
            for(j= *w;j<= *w+t-(*w*3);j++){
                a[i][j]='p';
                c[i][j]=1;
            }
    *pad=*w+t-(*w*3);

    fclose(in);

}

// la fel ca la task2
int verificare (char a[200][200],int poz1, int poz2, int w){
    int i,s=0;
    for(i=poz1;i<poz1+5;i++)
        if((poz2>0) && (poz2<w-6)){
            if((a[i][poz2-1]=='.') && (a[i][poz2+5]=='.'))
                s++;
        
        }else{
            if(poz2 == 0)
                if(a[i][poz2+5]=='.')
                    s++;
            if(poz2 == w-6)
                if(a[i][poz2-1]=='.')
                    s++;
        }
    if(s == 5)
        return 1;
    else
        return 0;
}

// la fel ca la task2
int cautare(char a[200][200], char m[5][5], int poz1, int poz2, int w){
    int i,j;
    int x=0,y=0;
    int s=0;
    for(i= poz1;i< poz1+5;i++){
        y=0;
        for(j= poz2;j< poz2+5;j++){
            if(a[i][j] == m[x][y]){
                s++;
            }
            y++;
        }
        x++;
    }
    if(s == 25){
        if(verificare(a,poz1,poz2,w)==1){
            for(i= poz1;i< poz1+5;i++)
                for(j= poz2;j< poz2+5;j++)
                    a[i][j]='.';
            return 1;
        }
    }
    return 0;
}

// la fel ca la task2
int testeazaMatrice(char a[200][200], char m[5][5], int poz1, int poz2, int w) {
    int r=0, s=0;

    r=verificare(a,poz1,poz2,w);
    s=cautare(a,m,poz1,poz2,w);

    return r*s;
}

//la fel ca la task2
int identificare (char a[200][200],int poz1, int poz2, int w){
    
    char m0[5][5],m1[5][5],m2[5][5];
    char m3[5][5],m4[5][5],m5[5][5];
    char m6[5][5],m7[5][5],m8[5][5],m9[5][5];

    zero(m0);
    unu(m1);
    doi(m2);
    trei(m3);
    patru(m4);
    cinci(m5);
    sase(m6);
    sapte(m7);
    opt(m8);
    noua(m9);

    if(testeazaMatrice(a,m0, poz1, poz2, w) == 1)
        return 0;
    if(testeazaMatrice(a,m1, poz1, poz2, w) == 1)
        return 1;
    if(testeazaMatrice(a,m2, poz1, poz2, w) == 1)
        return 2;
    if(testeazaMatrice(a,m3, poz1, poz2, w) == 1)
        return 3;
    if(testeazaMatrice(a,m4, poz1, poz2, w) == 1)
        return 4;
    if(testeazaMatrice(a,m5, poz1, poz2, w) == 1)
        return 5;
    if(testeazaMatrice(a,m6, poz1, poz2, w) == 1)
        return 6;
    if(testeazaMatrice(a,m7, poz1, poz2, w) == 1)
        return 7;
    if(testeazaMatrice(a,m8, poz1, poz2, w) == 1)
        return 8;
    if(testeazaMatrice(a,m9, poz1, poz2, w) == 1)
        return 9;
    return -1;
}

//creaza imaginea finala, fara cifrele ce trebuiau eliminate
void imagine (char *name_1, char *name_2, int u[200][200], int w, int h, int pad){
    img file;

    FILE *in=fopen(name_1,"rb");
    FILE *out=fopen(name_2,"wb");
    if(in==NULL)
        printf("Nu s-a deschis fisierul");
    if(out==NULL)
        printf("Nu s-a deschis fisierul");

    fread(&file.f.fileMarker1,sizeof(unsigned char),1,in);
    fwrite(&file.f.fileMarker1,sizeof(unsigned char),1,out);

    fread(&file.f.fileMarker2,sizeof(unsigned char),1,in);
    fwrite(&file.f.fileMarker2,sizeof(unsigned char),1,out);

    fread(&file.f.unused1,sizeof(unsigned short),1,in);
    fwrite(&file.f.unused1,sizeof(unsigned short),1,out);

    fread(&file.f.unused2,sizeof(unsigned short),1,in);
    fwrite(&file.f.unused2,sizeof(unsigned short),1,out);

    fread(&file.f.imageDataOffset,sizeof(unsigned int),1,in);
    fwrite(&file.f.imageDataOffset,sizeof(unsigned int),1,out);

    fread(&file.i.biSize,sizeof(unsigned int),1,in);
    fwrite(&file.i.biSize,sizeof(unsigned int),1,out);

    fread(&file.i.width,sizeof(signed int),1,in);
    fwrite(&file.i.width,sizeof(signed int),1,out);

    fread(&file.i.height,sizeof(signed int),1,in);
    fwrite(&file.i.height,sizeof(signed int),1,out);


    fread(&file.i.planes,sizeof(unsigned short),1,in);
    fwrite(&file.i.planes,sizeof(unsigned short),1,out);


    fread(&file.i.bitPix,sizeof(signed short),1,in);
    fwrite(&file.i.bitPix,sizeof(signed short),1,out);


    fread(&file.i.biCompression,sizeof(signed int),1,in);
    fwrite(&file.i.biCompression,sizeof(signed int),1,out);


    fread(&file.i.biSizeImage,sizeof(signed int),1,in);
    fwrite(&file.i.biSizeImage,sizeof(signed int),1,out);

    fread(&file.i.biXPelsPerMeter,sizeof(int),1,in);
    fwrite(&file.i.biXPelsPerMeter,sizeof(int),1,out);



    fread(&file.i.biYPelsPerMeter,sizeof(int),1,in);
    fwrite(&file.i.biYPelsPerMeter,sizeof(int),1,out);


    fread(&file.i.biClrUsed,sizeof(unsigned int),1,in);
    fwrite(&file.i.biClrUsed,sizeof(unsigned int),1,out);


    fread(&file.i.biClrImportant,sizeof(unsigned int),1,in);
    fwrite(&file.i.biClrImportant,sizeof(unsigned int),1,out);
    int k=255;

    fseek(in,54,SEEK_SET);
    fseek(out,54,SEEK_SET);
    int i,j;
    for(i= h-1;i>= 0;i--){
            //cazul cu padding
            if(pad!=w){
                for(j= 0;j< pad;j++){
                    if(u[i][j] == 0){
                        int k= 255;
                        fwrite(&k,sizeof(char),1,out);
                        fwrite(&k,sizeof(char),1,out);
                        fwrite(&k,sizeof(char),1,out);
                    }
                    if(u[i][j] == 1){
                        k=0;
                        fwrite(&k,sizeof(char),1,out);
                    }
                    if((u[i][j] != 1) && (u[i][j] != 0)){
                        k=u[i][j]/(1000*1000);
                        fwrite(&k,sizeof(char),1,out);

                        k=(u[i][j]/1000)%1000;
                        fwrite(&k,sizeof(char),1,out);

                        k=u[i][j]%1000;
                        fwrite(&k,sizeof(char),1,out);

                    }
                }
            }else{
                //cazul fara padding
                for(j= 0;j< w;j++){
                    if(u[i][j] == 0){
                        k= 255;
                        fwrite(&k,sizeof(char),1,out);
                        fwrite(&k,sizeof(char),1,out);
                        fwrite(&k,sizeof(char),1,out);
                    }else{

                        k=u[i][j]/(1000*1000);
                        fwrite(&k,sizeof(char),1,out);

                        k=(u[i][j]/1000)%1000;
                        fwrite(&k,sizeof(char),1,out);

                        k=u[i][j]%1000;
                        fwrite(&k,sizeof(char),1,out);

                    }
                }
            }
    }
                
            
    fclose(in);
    fclose(out);
}
        
 


int main(){
    int w,h,i,j,pad,k;
    char a[200][200];
    char sir[100];
    int vectorCifre[100];
    int nr=0;
    int c[200][200];

    char m0[5][5],m1[5][5],m2[5][5];
    char m3[5][5],m4[5][5],m5[5][5];
    char m6[5][5],m7[5][5],m8[5][5],m9[5][5];

    char nume[30];
    char nume_task3[30];
    FILE *input=fopen("input.txt","rt");
    fscanf(input,"%s",nume);
    int l=0;
    while(nume[l] != '.') {
        nume_task3[l]=nume[l];
        l++;
    }
    strcat(nume_task3, "_task3.bmp");

    matrice(nume,a,c,&w,&h,&pad);

    zero(m0);
    unu(m1);
    doi(m2);
    trei(m3);
    patru(m4);
    cinci(m5);
    sase(m6);
    sapte(m7);
    opt(m8);
    noua(m9);

    fgets(sir, 100, input);
    fgets(sir, 100, input);
    fgets(sir, 100, input);

    i=0;

    int aux = 0;
    while(sir[i] != '\0') {
        if(sir[i] != ' ' && sir[i] != '\n') {
            aux=sir[i]-48;
            vectorCifre[nr]=aux;
            nr++;
        }
        i++;
    } 

    numar v[50];
    k=0;
    int temp=0;

    for(j=0;j<w;j++){
        for(i=0;i<h;i++){
            if( (temp=identificare(a,i,j,w)) != -1) {
                v[k].cifra=temp;
                v[k].poz_1=i;
                v[k].poz_2=j;
                v[k].culoare=c[i+4][j+4];
                k++;
            }
        }
    }

    int t;
    numar backup[100];

    //punem -1 in vector in locul cifrei ce trebuie eliminata
    for(i=0;i<nr;i++)
        for(int index = 0; index < k; index++)
            if(v[index].cifra == vectorCifre[i])
                v[index].cifra = -1;

    int backupLength = 0;
    //pun cifrele ce trebuie pastrate intr-un alt vector
    for(int index = 0; index < k; index++)
        if(v[index].cifra != -1) {
            backup[backupLength] = v[index];
            backupLength++;
        }

    for(int index = 0; index < backupLength; index++) {
        backup[index].poz_1 = v[index].poz_1;
        backup[index].poz_2 = v[index].poz_2;
    }

    int u[200][200];
    //creaza o matrice ce are '1' in loc de padding si '0' in rest
    for(i=0;i<h;i++)
        for(j=0;j<=pad;j++)
            if(c[i][j]==1)
                u[i][j]=1;
            else
                u[i][j]=0;
    

    int index1,index2;
    //copiaza in a matricele corespunzatoare cifrelor ramase
    for(i= 0;i< h;i++)
        for(j= 0;j< w;j++)
            for(t= 0;t< backupLength;t++){
                if((backup[t].poz_1 == i) && (backup[t].poz_2 == j)){
                    switch (backup[t].cifra){
                        case 0 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){

                                    a[i+index1][j+index2]= m0[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 1 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){

                                    a[i+index1][j+index2]= m1[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 2 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){

                                    a[i+index1][j+index2]= m2[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 3 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){ 

                                    a[i+index1][j+index2]= m3[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 4 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){

                                    a[i+index1][j+index2]= m4[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 5 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){ 

                                    a[i+index1][j+index2]= m5[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 6 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){

                                    a[i+index1][j+index2]= m6[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 7 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){

                                    a[i+index1][j+index2]= m7[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 8 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){

                                    a[i+index1][j+index2]= m8[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        case 9 :
                            for(index1= 0;index1< 5;index1++)
                                for(index2= 0;index2< 5;index2++){

                                    a[i+index1][j+index2]= m9[index1][index2];

                                    if((a[i+index1][j+index2]!='.') && (a[i+index1][j+index2]!='p'))
                                        u[i+index1][j+index2]= backup[t].culoare;
                                }
                            break;
                        default:
                            break;
                    }
                        

                }
            }

    imagine(nume,nume_task3,u,w,h,pad);
    fclose(input);
    
    return 0;
}
                
            
        




