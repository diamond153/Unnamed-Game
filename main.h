#ifndef __MAIN_H
#define __MAIN_H

#include"common.h"
namespace game{
	const double dx[]={-8.5,-8.5,8.5,8.5};
	const double dy[]={1.5,-1.5,1.5,-1.5};
	const int p[]={-1,-1,1,1};
	class AI;
	unsigned random(unsigned seed){
		seed^=seed<<3|seed<<1&seed>>3&seed>>1;
		seed^=(seed>>1)^(seed<<1^seed>>1<<seed>>(seed&1));
		seed^=seed<<3^seed>>2&seed<<5|seed<<1;
		return seed;
	}
	class Player{
	friend class Ball;
	friend class AI;
	private:
		int y=80;
		double cnt=0;
		IMAGE img;
	public:
		Player(){Image::getImage(img,"Player.png",40,120,1);}
		inline void print()const{
			putimage(580,y-60,&img);
		}
		template<typename _FT> bool move(_FT f,int x){
			if(f(0x57))
				if(y>60)return y-=9-(x>10?2:x/5);
			if(f(0x53))
				if(y<420)return y+=9-(x>10?2:x/5);
			return cnt=0;
		}
	};
	class Ball{
	friend class AI;
	private:
		double score=0;
		double posx=200;
		double posy=300;
		double randomdy=1;
		int randomc=0;
		int fac=3;
		double il=0;
		IMAGE img;
		inline double len(){
			if(p[fac]==-1)return 580-posx;
			return 580+posx;
		}
		double il_pt(){
			if(il>0)return il;
			int rc=randomc;double rdy=randomdy,px=posx,py=posy,sc=score,fc=fac;
			while(1){
				bool f=0;
				px+=dx[fac]+(score>40?8:score/5)*p[fac];
				py+=(dy[fac]*randomdy)*(2+randomc%4)*(1+(randomc%3-1)/2);
				if(px<30)f=1,px=60-px,fac=(fac+2)&3;
				if(px>580){
					f=1,px=1160-px,fac=(fac+2)&3,score++;
					break;
				}
				if(py<30){
					f=1,py=60-py;
					if(fac<2)fac=(fac+1)&1;
					else fac=((fac-1)&1)+2;
				}
				if(py>450){
					f=1,py=900-py;
					if(fac<2)fac=(fac+1)&1;
					else fac=((fac-1)&1)+2;
				}
				f&&(randomc=10,randomdy=0.95);
			}
			randomc=rc,randomdy=rdy,score=sc,fac=fc;
			return il=py;
		}
	public:
		Ball(){Image::getImage(img,"Ball.png",60,60,1);}
		inline void print()const{
			putimage(posx-30,posy-30,&img);
		}
		void move(){
			bool f=0;
			posx+=dx[fac]+(score>40?8:score/5)*p[fac];
			posy+=(dy[fac]*randomdy)*(2+randomc%4)*(1+(randomc%3-1)/2);
			if(posx<30)f=1,posx=60-posx,fac=(fac+2)&3;
			if(posx>580)f=1,posx=1160-posx,fac=(fac+2)&3,score++;
			if(posy<30){
				f=1,posy=60-posy;
				if(fac<2)fac=(fac+1)&1;
				else fac=((fac-1)&1)+2;
			}
			if(posy>450){
				f=1,posy=900-posy;
				if(fac<2)fac=(fac+1)&1;
				else fac=((fac-1)&1)+2;
			}
			srand(random(rand()^time(0)));
			f&&(randomc=rand(),randomdy=0.66+(double)(random(time(0))%21)/30,il=-1);
		}
		inline bool failed(const Player& p)const{
			if(posx<570)return 0;
			if(posy>p.y+87||posy<p.y-87)return 1&&!cheat;
			return 0;
		}
		inline int getscore()const{
			return score;
		}
	};
}

#endif /*MAIN_H*/
