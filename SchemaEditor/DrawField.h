// DrawField.h
#pragma once
#include "Element.h"
#include "Line.h"

namespace SchemaEditor {
	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;
	using namespace System::Data;
	using namespace System::IO;
	using namespace System::Xml;

	ref class MainForm; // Предварительное объявление класса главной формы

	public ref class DrawField : public Panel {
	public:
		void SaveToXml(String^ filePath);
		void LoadFromXml(String^ filePath);
	public:
		Dictionary<Point, Element^>^ elements; // Словарь типа позиция-элемент
		MainForm^ mainForm; // Ссылка на главную форму

		Point StartingPointLine;
		List<Line^>^ ArrayOfLines = gcnew List<Line^>;

		int WidthElement, HeightElement; // Размер элемента
		Bitmap^ fieldBackground; // Bitmap-фон поля
		String^ currentElementType; // Выбранный тип элемента
		String^ elementImagesPath; // Путь к папке со спрайтами элементов

		// Область, занимаемая доской в глобальынх координатах формы
		System::Drawing::Rectangle drawingArea;

		// Конструктор DrawField
		DrawField(MainForm^ mainForm);

		// Метод для добавления элемента
		void AddElement(Image^ sprite, Point location, String^ name, int flip);

	protected:
		// Переопределение метода отрисовки
		virtual void OnPaint(PaintEventArgs^ e) override;

	private:
		// Конвертация из стркои в числа
		Point ConvertSchemaToPoint(String^ notation);

	private:
		// Обработка клика мыши
		void OnMouseClick(Object^ sender, MouseEventArgs^ e);
	};
}

