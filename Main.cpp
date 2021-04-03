#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

Main::Main() : wxFrame(nullptr, wxID_ANY, "wxWidgets App", wxPoint(30, 30), wxSize(800, 600))
{
	btn = new wxButton*[fieldWidth * fieldHeight];
	wxGridSizer* grid = new wxGridSizer(fieldWidth, fieldHeight, 0, 0);

	field = new int[fieldWidth * fieldHeight];

	wxFont font{ 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false };

	for (int index{ 0 }; index < fieldWidth * fieldHeight; ++index) {
		auto button = new wxButton(this, 10000 + index);
		button->SetFont(font);
		button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::OnButtonClicked, this);

		grid->Add(button, 1, wxEXPAND | wxALL);

		btn[index] = button;
		field[index] = 0;
	}

	this->SetSizer(grid);
	grid->Layout();
}

Main::~Main()
{
	delete[]btn;
}

void Main::OnButtonClicked(wxCommandEvent& evt)
{
	int x{ (evt.GetId() - 10000) % fieldWidth };
	int y{ (evt.GetId() - 10000) / fieldWidth };
	int index{ y * fieldWidth + x };

	if (firstClick) {
		GenerateMines(x, y);
		firstClick = false;
	}

	btn[index]->Disable();

	if (field[index] == -1) {
		wxMessageBox("Game Over");
		ResetBoard();
	}
	else {
		int mineCount{ GetMineCount(x, y) };

		if (mineCount > 0) {
			btn[index]->SetLabel(std::to_string(mineCount));
		}
	}

	evt.Skip();
}

int Main::GetMineCount(int x, int y)
{
	int mineCount{ 0 };
	for (int i{ -1 }; i < 2; ++i) {
		for (int j{ -1 }; j < 2; ++j) {
			if (x + i >= 0 && x + i < fieldWidth && y + j >= 0 && y + j < fieldHeight) {
				if (field[(y + j) * fieldWidth + (x + i)] == -1) {
					++mineCount;
				}
			}
		}
	}
	return mineCount;
}

void Main::ResetBoard()
{
	firstClick = true;
	for (int x{ 0 }; x < fieldWidth; ++x) {
		for (int y{ 0 }; y < fieldHeight; ++y) {
			field[y * fieldWidth + x] = 0;
			btn[y * fieldWidth + x]->SetLabel("");
			btn[y * fieldWidth + x]->Enable();
		}
	}
}

void Main::GenerateMines(int x, int y)
{
	int mines{ 30 };

	while (mines) {
		int rx{ rand() % fieldWidth };
		int ry{ rand() % fieldHeight };

		if (field[ry * fieldWidth + rx] == 0 && rx != x && ry != y) {
			field[ry * fieldWidth + rx] = -1;
			--mines;
		}
	}
}
