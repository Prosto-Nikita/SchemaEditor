#pragma once
#include "GraphicsElement.h"

namespace SchemaEditor {
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;
	using namespace System::Data;
	using namespace System::IO;

	ref class MainForm; // Предварительное объявление класса главной формы
	ref class DrawField; // Предварительное объявление класса поля отрисовки

	// Класс кнопки, позволяющей выбрать размещаемый элемент
	public ref class ButtonElement : public System::Windows::Forms::PictureBox, public GraphicsElement
	{
	public:
		String^ name; // Название размещаемого элемента
		Point InitialLocation; // Начальное положение элемента на форме

		MainForm^ mainForm; // Ссылка на класс главной формы, на которой размещены кнопки
		DrawField^ drawField; // Ссылка на класс поля рисования (поля), которая хранит путь до спрайтов элементов и их размеров

		// Основной конструктор элемента, принимающий ссылку на форму, путь до изображения, название элемента
		ButtonElement(MainForm^ form, DrawField^ drawField, int Width, int Height, String^ path, String^ name);

		// Реализация метода Draw из интерфейса GraphicsElement
		virtual void Draw(Graphics^ g) override;

	protected:
		// Обработчик нажатия ЛКМ
		void MouseClickOnButon(Object^ sender, MouseEventArgs^ e);

		// Перерисовка иконки
		virtual void OnPaint(PaintEventArgs^ e) override;
	};
}

