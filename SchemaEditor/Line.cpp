// Figure.cpp
#include "Line.h"
#include "DrawField.h"
#include "MainForm.h"

namespace SchemaEditor {

	Line::Line(Point InitialPoint, Point FinalPoint) {
		this->InitialPoint = InitialPoint;
		this->FinalPoint = FinalPoint;
	}

	void Line::Draw(Graphics^ g) {
		Pen^ pen = gcnew Pen(Color::FromArgb(50, 55, 55), 2);
		int j = 0;
		int X0 = this->InitialPoint.X;
		int Y0 = this->InitialPoint.Y;
		int X1 = this->FinalPoint.X;
		int Y1 = this->FinalPoint.Y;

		g->DrawLine(pen, Point(Convert::ToInt32(this->InitialPoint.X), Convert::ToInt32(this->InitialPoint.Y)), Point(Convert::ToInt32(this->FinalPoint.X), Convert::ToInt32(this->FinalPoint.Y)));
		g->DrawRectangle(pen, Convert::ToInt32(this->InitialPoint.X) - 2, Convert::ToInt32(this->InitialPoint.Y) - 2, 4, 4);
		g->DrawRectangle(pen, Convert::ToInt32(this->FinalPoint.X) - 2, Convert::ToInt32(this->FinalPoint.Y) - 2, 4, 4);
	}
}
