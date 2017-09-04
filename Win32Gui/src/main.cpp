
#include <application.h>
#include <layout.h>
#include <widget.h>
#include <CommCtrl.h>

//#define TAKE01
#ifdef TAKE01

int main(int args, char* argv[])
{
	Application app;
	
	Widget widget(1024, 640);
	Layout* lay = widget.GetLayout();

	auto bt1 = CreateWindow(WC_BUTTON, TEXT("none"),
		WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, lay->GetHandle(), NULL, app.GetInstance(), NULL);

	auto bt2 = CreateWindow(WC_BUTTON, TEXT("none"),
		WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, lay->GetHandle(), NULL, app.GetInstance(), NULL);

	Widget w1(0, 0, TEXT(""), NULL);
	Widget w2(0, 0, TEXT(""), NULL);
	//Widget w2(0, 0, TEXT(""), lay->GetHandle());
	//Widget w3(0, 0, TEXT(""), lay->GetHandle());

	/*lay->AddWindow(bt2);	
	lay->AddWindow(bt1);*/
	lay->AddWindow(w1);
	lay->AddWindow(w2);
	widget.Show();
	

	int exit = app.Run();
	return exit;

	//SomeData sdata;
	//Data* data = dynamic_cast<Data*>(&sdata);
	//data->run();
	//PAUSE;
	//return 0;
}

#else

#include <CommCtrl.h>

Brush baseBrush(60, 60, 60);
Brush fixBrush(100, 100, 100);
char* baseName = "base window";
char* subName = "sub window";
char* subsubName = "sub sub";


int main(int args, char* argv[])
{
	Application app;

	MainWindow w(700,300,1024,480);
	Frame f(100, 100, 200, 200,"frame", w);

	w.Show();
	
	
	InvalidateRect(w.GetHandle(), &w.GetRect(), TRUE);
	UpdateWindow(w.GetHandle());

	int exitCode = app.Run();
	return exitCode;
}



#endif


