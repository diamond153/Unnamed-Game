#ifndef __AI_H
#define __AI_H

#include"main.h"
namespace game{
	inline double abs(double x){return x>0?x:-x;}
	class AI{
	private:
		Player &p;
		Ball &b;
		inline double F_val(int py,int by){return abs(b.il_pt()-py);}
		inline static bool moveup(int x){return x==0x57;}
		inline static bool nomove(int x){return 0;}
		inline static bool movedown(int x){return x==0x53;}
	public:
		AI(Player &_p,Ball &_b):p(_p),b(_b){}
		void next_input(){
			double py=p.y,lst[3];
			p.move(moveup,b.getscore());
			lst[0]=F_val(p.y,b.posy);
			p.y=py;
			lst[1]=F_val(p.y,b.posy);
			p.move(movedown,b.getscore());
			lst[2]=F_val(p.y,b.posy);
			p.y=py;
			int r=0;
			for(int i=2;i<3;i++)if(lst[i]<lst[r])r=i;
			if(lst[1]-lst[r]<=5)r=1;
			if(r==0)p.move(moveup,b.getscore());
			if(r==1)p.move(nomove,b.getscore());
			if(r==2)p.move(movedown,b.getscore());
		}
	};
}

#endif /*AI_H*/
