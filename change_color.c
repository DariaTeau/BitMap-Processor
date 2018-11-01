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

//stuctura pentru BGR-ul unui pixel
typedef struct pixel{
    unsigned char blue;
    unsigned char green;
    unsigned char red;
}pixel;

//structura pentru definirea unei imagini
typedef struct img {
    pixel p;
    fheader f;
    iheader i;

}img;

//calculeaza latimea imaginii
int width(char *filename){
	int w;
	FILE *in=fopen(filename,"rb");
	fseek(in,18,SEEK_SET);
	fread(&w,sizeof(int),1,in);
    fclose(in);
	return w;
}

int main(){
	int b,g,r;
	int padding;
    img file;
    char *nume_imagine;
    nume_imagine=malloc(100*sizeof(char));
    FILE *input=fopen("input.txt","rt");
    fscanf(input,"%s", nume_imagine);

    char *nume_imagine_task1;
    nume_imagine_task1=malloc(100*sizeof(char));
    int a=0;
    while(nume_imagine[a] != '.') {
    	nume_imagine_task1[a]=nume_imagine[a];
    	a++;
    }
    nume_imagine_task1[a]=0;
    strcat(nume_imagine_task1, "_task1.bmp");

  	fscanf(input,"%d %d %d",&b,&g,&r);

    FILE *in=fopen(nume_imagine,"rb");
    FILE *out=fopen(nume_imagine_task1,"wb");
    if ( (in==NULL) || (out==NULL) )
    {
        printf("Nu s-a deschis fisierul");
        free(nume_imagine);
        free(nume_imagine_task1);
        return 1;
    }




    int w=width(nume_imagine);
    /*folosesc t pentru a calcula padding-ul
    dupa incrementare lui t padding-ul va fi t-(w*3)*/
    int t=w*3;
    if( (w*3)%4 != 0){
    	while( t%4 != 0){
    		t++;
    	}
    }
    
    //citesc si scriu header-ele
    fread(&file.f, sizeof(fheader), 1, in);
    fread(&file.i, sizeof(iheader), 1, in);

    fwrite(&file.f, sizeof(fheader), 1, out);
    fwrite(&file.i, sizeof(iheader), 1, out);


    pixel x;
    int s, k;
    int count=0;
    int h = file.i.height;
    
    int i=1;
    //cazul in care imaginea are padding
    if((w*3)%4!=0){
    	while(i<=w*h) {
    		s=0;

        	fread(&file.p.blue,1,1,in);
        	x.blue=file.p.blue;
        	if(file.p.blue == 255)
        		s++;
      

        	fread(&file.p.green,1,1,in);
        	x.green=file.p.green;
        	if(file.p.green == 255)
        		s++;
        

        	fseek(in,0,SEEK_CUR);
        

        	fread(&file.p.red,1,1,in);
        	x.red=file.p.red;
        	if(file.p.red == 255)
        		s++;

            //daca s!=3 inseamna ca pixelul nu e alb
        	if(s!=3){
        		x.blue=b;
        		x.green=g;
        		x.red=r;
       		}
        	s=0;

        	fwrite(&x.blue,1,1,out);
        	fwrite(&x.green,1,1,out);
        	fwrite(&x.red,1,1,out);

        	count++;
            /*atunci cand count==w inseamna ca au fost 
            scrisi pixelii de pe o linie deci putem scrie padding-ul*/
        	if (count==w){
       
        		if( (w*3)%4 != 0 ){
        			for(k=0;k<t-(w*3);k++){
        				fread(&padding,1,1,in);
        				padding='\0';
        				fwrite(&padding,1,1,out);
        			}
        		}
        		count=0;
        	}
        
        
        	i++;
    	}
    }else{
        //cazul in care imaginea nu are padding
    	while(i<=w*h){
    	s=0;

        fread(&file.p.blue,1,1,in);
        x.blue=file.p.blue;
        if(file.p.blue == 255)
        	s++;
      

        fread(&file.p.green,1,1,in);
        x.green=file.p.green;
        if(file.p.green == 255)
        	s++;
               

        fseek(in,0,SEEK_CUR);
        

        fread(&file.p.red,1,1,in);
        x.red=file.p.red;
        if(file.p.red == 255)
        	s++;

        if(s!=3){
        	x.blue=b;
        	x.green=g;
        	x.red=r;
        }
        s=0;
        
        fwrite(&x.blue,1,1,out);
        fwrite(&x.green,1,1,out);
        fwrite(&x.red,1,1,out);

        i++;
      	}
     }
    


    fclose(in);
    fclose(out);
    fclose(input);

    free(nume_imagine);
    free(nume_imagine_task1);
    return 0;
}

