#include <stdio.h>
#include <stdlib.h>
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


/*formeaza o matrice de 5x5 
pentru cifra 0, punand '.'
unde ar fi pixel alb si 'x' unde
ar fi pixel colorat*/
void zero(char m[5][5]){
    int i=0,j=0;
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

// la fel ca mai sus dar petru 1
void unu(char m[5][5]){
    int i=0,j=0;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
            if(j==4)
                m[i][j]='x';
            else
                m[i][j]='.';
}

// la fel ca mai sus dar petru 2
void doi(char m[5][5]){
    int i=0,j=0;
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

// la fel ca mai sus dar petru 3
void trei (char m[5][5]){
    int i=0,j=0;
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

// la fel ca mai sus dar petru 4
void patru (char m[5][5]){
    int i=0,j=0;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++){
            if((((i==0) || (i==1)) && ((j==0) || (j==4))) || (i==2) || (j==4))
                m[i][j]='x';
            else
                m[i][j]='.';
        }
}

// la fel ca mai sus dar petru 5
void cinci (char m[5][5]){
    int i=0,j=0;
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

// la fel ca mai sus dar petru 6
void sase (char m[5][5]){
    int i=0,j=0;
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

// la fel ca mai sus dar petru 1
void sapte (char m[5][5]){
    int i=0,j=0;
    for(j=0;j<5;j++)
        m[0][j]='x';
    for(i=1;i<5;i++)
        for(j=0;j<5;j++)
            if(j==4)
                m[i][j]='x';
            else
                m[i][j]='.';

}

// la fel ca mai sus dar petru 8
void opt (char m[5][5]){
    int i=0,j=0;
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

// la fel ca mai sus dar petru 9
void noua (char m[5][5]){
    int i=0,j=0;
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
pixel colorat si '.' in loc de pixel alb*/
void matrice(char *name_1, char a[100][100], int *w, int *h){
    int poz=0;
    int count=0;
	img file;

    FILE *in=fopen(name_1,"rb");
    if(in==NULL)
        printf("Nu s-a deschis fisierul");
    
    fseek(in,18,SEEK_SET);

    
    fread(&file.i.width,sizeof(signed int),1,in);
    *w=file.i.width;
    int t=*w*3;

    if((*w*3)%4 != 0)
        while(t%4 != 0){
            t++;
        }
    
    fread(&file.i.height,sizeof(signed int),1,in);
     *h=file.i.height;
    
    fseek(in,54,SEEK_SET);
    int s=0;
    int k=1;
    int i=*h-1,j=0;

    while(k<=((*w)*(*h))){
    	s=0;

        fread(&file.p.blue,1,1,in);
        if(file.p.blue == 255)
        	s++;
       
        fread(&file.p.green,1,1,in);
        if(file.p.green == 255)
        	s++;
        

        fseek(in,0,SEEK_CUR);
        

        fread(&file.p.red,1,1,in);  
        if(file.p.red == 255)
        	s++;
        
        if((i>=0) && (j<*w)){
        	if(s!=3)
        		a[i][j]='x';
        	else
        		a[i][j]='.';
        }

        if(j == *w-1){
        	i--;
        	j=0;
        }else
        	j++;

        s=0;
        count++;

        if (count == *w){
            // daca gaseste padding sare peste el       
            if((*w*3)%4 != 0){
                
                poz=t-(*w*3);
                fseek(in,poz,SEEK_CUR);
            }
            count=0;
            }
        k++;   
       
    }

    fclose(in);

}

/*verifica daca in dreapata si in stanga unei cifre gasite 
exista cate o coloana de '.', adica pixeli albi*/
int verificare (char a[100][100],int poz1, int poz2, int w){
    int i=0,s=0;
    for(i=poz1;i<poz1+5;i++)
        if((poz2>0) && (poz2<w-6)){
            if((a[i][poz2-1] == '.') && (a[i][poz2+5] == '.'))
                s++;
        
        }else{
            if(poz2 == 0)
                if(a[i][poz2+5] == '.')
                    s++;
            if(poz2 == w-6)
                if(a[i][poz2-1] == '.')
                    s++;
        }
    if(s == 5)
        return 1;
    else
        return 0;
}

/*cauta in matricea formata cu ajutorul functiei 'matrice' cifra care
ii este trimisa ca parametru prin intermediul matricei m*/
int cautare(char a[100][100], char m[5][5], int poz1, int poz2, int w){
    int i=0,j=0;
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

        if(verificare(a,poz1,poz2,w) == 1){
            for(i= poz1;i< poz1+5;i++)
                for(j= poz2;j< poz2+5;j++)
                    a[i][j]= '.';
            return 1;
        }
    }
    return 0;
}

// verifica daca cifra a fost identificata corect
int testeazaMatrice(char a[100][100], char m[5][5], int poz1, int poz2, int w) {
    int r=0, s=0;

    r=verificare(a,poz1,poz2,w);
    s=cautare(a,m,poz1,poz2,w);

    return r*s;
}

//intoarce cifra identificata
int identificare (char a[100][100],int poz1, int poz2, int w){
    
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


int main(){
    int w,h,i,j;
    char a[100][100];
    FILE *input=fopen("input.txt","rt");
    char nume[30];
    char nume_task2[30];
    fscanf(input,"%s",nume);

    int k=0;
    while(nume[k] != '.') {
        nume_task2[k]=nume[k];
        k++;
    }
    strcat(nume_task2, "_task2.txt");

    FILE *output=fopen(nume_task2,"wt");
    matrice(nume,a,&w,&h);

    int cifra;
    
    for(j= 0;j< w;j++){
        for(i= 0;i< h;i++){
            if( (cifra=identificare(a, i, j, w)) != -1)
                fprintf(output, "%d", cifra);
        }
    }
    
    fclose(output);
    fclose(input);
    
    return 0;

}

