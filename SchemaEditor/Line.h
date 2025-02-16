//Line.h
#pragma once
#include "GraphicsElement.h"

namespace SchemaEditor {
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	ref class DrawField; // Предварительное объявление класса DrawField
	ref class MainForm; // Предварительное объявление класса MainForm

	public ref class Line : public GraphicsElement, public Windows::Forms::PictureBox {
	public:
		Point InitialPoint;
		Point FinalPoint;

		Line(Point InitialPoint, Point FinalPoint);

		void Draw(Graphics^ g) override;
	};
}

