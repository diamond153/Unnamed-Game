#ifndef __COMMON_H
#define __COMMON_H

#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<time.h>
extern inline void clear(){cleardevice();}
namespace Image{
	void getImage(IMAGE& img,const char* str,int width=0,int height=0,bool resize=0){
		char *src=new char[128];
		sprintf(src,"library\\images\\%s",str);
		return loadimage(&img,src,width,height,resize);
	}
}
namespace game{
	int ai;
	int reset;
	int cheat;
	int training;
	void read(){
		FILE *fp=fopen("library\\settings.txt","r");
		fscanf(fp,"using_ai=%d;\n",&ai);
		fscanf(fp,"auto_reset=%d;\n",&reset);
		fscanf(fp,"allow_cheat=%d;\n",&cheat);
		fscanf(fp,"ai_training=%d;\n",&training);
	}
}
template<typename T> inline T max(const T& a,const T& b){return a>b?a:b;}

#endif /*COMMON_H*/
