#pragma once
#include "Main.h"
#include "wx/wx.h"

class App : public wxApp
{ 
public:
	virtual bool OnInit();

private:
	Main* frame1{ nullptr };
};