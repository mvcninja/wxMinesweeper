#pragma once
#include "wx\wx.h"
class Main : public wxFrame
{
public:
	Main();
	~Main();
private:
	int fieldWidth{ 10 };
	int fieldHeight{ 10 };
	wxButton** btn;
	int* field{ nullptr };
	bool firstClick{ true };

	void OnButtonClicked(wxCommandEvent& evt);

	int GetMineCount(int x, int y);

	void ResetBoard();

	void GenerateMines(int x, int y);

	wxDECLARE_EVENT_TABLE();
};
