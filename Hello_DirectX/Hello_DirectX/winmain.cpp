#include <Windows.h>

//Forwards Declarations
bool InitMainWindows(HINSTANCE, int);
LRESULT CALLBACK MsgProc(HWND, UINT, WPARAM, LPARAM);

//Constants
const int WIDTH = 800;
const int HEIGHT = 600;

HWND hwnd = NULL;//Handle to window

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	return(1);
}

bool InitMainWindow(HINSTANCE hInstance, int nCmdShow){

	//Inital structure setup
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;//Set to redraw on resize

	//0 extra bytes if data
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.lpfnWndProc = MsgProc;

	wcex.hInstance = hInstance;//Set handle for window

	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);//Set App icon to defualt
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);//Set defualt cursor
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//Set app background intialy
	wcex.lpszClassName = "HelloDirectXClass";
	wcex.lpszMenuName = NULL;
	wcex.hIconSm = LoadIcon(NULL, IDI_WINLOGO);


	if (!RegisterClassEx(&wcex)){//If window structure fails to load program will exit
		return false;
	}

	//Create the window
	hwnd = CreateWindow(
		"HelloDirectXClass",//Class name, defined above
		"Hello DirectX",//Top bar title
		WS_OVERLAPPED | WS_SYSMENU, WS_CAPTION,//Window style, using default
		GetSystemMetrics(SM_CXSCREEN) / 2 - WIDTH / 2,//Position relitive to top left corner, X CXSCREEN notice the CX<--for X or width
		GetSystemMetrics(SM_CYSCREEN) / 2 - HEIGHT / 2,//Position relitive to top left corner, Y CYSCREEN notice the CY<--for Y or height
		WIDTH,
		HEIGHT,
		(HWND)NULL,//Setting window parent
		(HMENU)NULL,
		hInstance,//Window instance defined above
		(LPVOID)NULL);

	if (!hwnd){//Check if window exists
		return false;//If not exit program
	}

	ShowWindow(hwnd, nCmdShow);
}