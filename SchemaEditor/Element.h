// Element.h
#pragma once
#include "GraphicsElement.h"

namespace SchemaEditor {
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	ref class DrawField; // Предварительное объявление класса DrawField
	ref class MainForm; // Предварительное объявление класса MainForm

	public ref class Element : public GraphicsElement, public Windows::Forms::PictureBox {
	public:
		System::Drawing::Image^ Image; // Переменная, хранящая спрайт элемента
		bool isDragging; // Флаг, равный true, если происходит перетаскивание элемента
		int Flip = 0;

		Point dragStartPoint; // Положение курсора на спрайте элемента (точка, за которую цепляем элемент)
		Point initialLocation; // Начальное положение в момент начала переноса
		String^ name; // Название (тип) элемента

		DrawField^ drawField; // Ссылка на поле рисования, хранящее все элементы
		MainForm^ mainForm;

		Element(MainForm^ mainForm, DrawField^ drawField, Drawing::Image^ sprite, Point location, int Width, int Height, int Flip);

		void Draw(Graphics^ g) override;

	private:
		// Обработка зажатия ЛКМ
		void Element_MouseDown(Object^ sender, MouseEventArgs^ e);
		// Обработка передвижения мыши с зажатым ЛКМ
		void Element_MouseMove(Object^ sender, MouseEventArgs^ e);
		// Обработка отпускания мыши
		void Element_MouseUp(Object^ sender, MouseEventArgs^ e);
		//Поворот элемента
		void Element_MouseDoubleClick(Object^ sender, MouseEventArgs^ e);
		//Удаление элемента
		void DeleteElementClick(Object^ sender, MouseEventArgs^ e);
	};
}

