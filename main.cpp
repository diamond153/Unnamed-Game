#include"ai.h"
int main(){
	game::read();
	const DWORD colors[]={BLUE,CYAN,RED,GREEN,BROWN,YELLOW};
start:
	MoveWindow(initgraph(640,480),60,60,640,500,0);
	setbkcolor(WHITE);
	settextstyle(30,0,"Consolas");
	cleardevice();
	game::Ball b;game::Player p;
	BeginBatchDraw();
	game::AI ai(p,b);
	char message[128];
	int t=0;
	while(!b.failed(p)){
		settextcolor(colors[(b.getscore()/5)%6]);
		if(game::cheat)outtextxy(185,204,"You are cheating!");
		else if(game::ai)
			if(game::training)outtextxy(185,204,"The AI is training...");
			else outtextxy(185,204,"The AI is running...");
		else outtextxy(185,204,"The game has started...");
		sprintf(message,"score: %d",b.getscore());
		outtextxy(185,236,message);
		p.print(),b.print();
		if(!game::ai)p.move(GetAsyncKeyState,b.getscore());
		else ai.next_input();
		b.move();
		FlushBatchDraw();
		if(!game::training)Sleep(10);
		cleardevice();
	}
	EndBatchDraw();closegraph();
	sprintf(message,"score: %d, replay?",b.getscore());
	if(!game::reset){
		bool replay=1&MessageBox(0,message,"Game Over!",MB_OKCANCEL|MB_ICONQUESTION);
		if(replay)goto start;
	}else goto start;
	return 0;
}
