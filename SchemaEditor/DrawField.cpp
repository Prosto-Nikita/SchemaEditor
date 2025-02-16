// DrawField.cpp
#include "DrawField.h"

namespace SchemaEditor {

	// Конструктор класса DrawField
	DrawField::DrawField(MainForm^ mainForm) {
		this->mainForm = mainForm;

		this->Size = System::Drawing::Size(900, 500);
		this->MouseClick += gcnew MouseEventHandler(this, &DrawField::OnMouseClick);

		StartingPointLine.X = 0;
		StartingPointLine.Y = 0;

		this->BackColor = Color::Transparent;
		fieldBackground = gcnew Bitmap("\images\\Фон2.png");
		this->BackgroundImage = fieldBackground;

		// Область, занимаемая рабочим полем в глобальных координатах формы
		this->drawingArea = this->Bounds;

		elements = gcnew Dictionary<Point, Element^>(); // Словарь элементов
		WidthElement = 40; //ширина по умолчанию
		HeightElement = 40;// высота по умолчанию
		currentElementType = "lamp"; // Выбранный тип элемента (lamp по умолчанию)
		elementImagesPath = Path::Combine(Directory::GetCurrentDirectory(), "images\\elements\\");

		this->Location = Point(WidthElement, HeightElement);
	}

	// Метод для добавления элемента
	void DrawField::AddElement(Image^ sprite, Point location, String^ name, int flip) {
		//Определение размеров для каждого элемента
		if (name == "lamp" || name == "voltmeter" || name == "ampermeter") {//Лампочка
			WidthElement = 30;
			HeightElement = 30;
		}
		else if (name == "resistor" || name == "heater" || name == "fuse") {//Резистор
			WidthElement = 50;
			HeightElement = 23;
		}
		else if (name == "battery" || name == "galvanic_element" || name == "diode" || name == "coil" || name == "capacitor" || name == "key") {//Батарея
			WidthElement = 60;
			HeightElement = 30;
		}
		else if (name == "reostat") {//Реостат
			WidthElement = 80;
			HeightElement = 40;
		}
		else {
			WidthElement = 0;
			HeightElement = 0;
		}
		Point tempLocation = location;
		Element^ newElement = gcnew Element(mainForm, this, sprite, tempLocation, WidthElement, HeightElement, flip);

		newElement->name = name; // Указание типа элемента

		elements->Add(tempLocation, newElement);
		this->Controls->Add(newElement);
	}

	void DrawField::OnPaint(PaintEventArgs^ e) {
		e->Graphics->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
		this->SuspendLayout();
		this->DoubleBuffered = true;
		Panel::OnPaint(e);
		Graphics^ g = e->Graphics;

		// Отрисовка всех элементов
		for each (auto el in elements) {
			Element^ element = el.Value; // Получение элемента из пары
			element->Draw(g);
		}
		//Отрисовка всех линий
		for (int i = 0; i < ArrayOfLines->Count; i++) {
			Line^ line = ArrayOfLines[i]; // Получение элемента
			line->Draw(g);
		}
		this->ResumeLayout();
	}

	// Конвертация строки в числа
	Point DrawField::ConvertSchemaToPoint(String^ str)
	{
		String^ posXstr;
		String^ posYstr;

		//Выделение двух чисел из строки
		bool next = false;
		for (int i = 0; i < str->Length; i++) {
			if (str[i] == ' ') {
				next = true;
				continue;
			}

			if (!next) {
				posXstr += str[i];
			}
			else {
				posYstr += str[i];
			}
		}
		//Преобразование переменных типа string в int
		int posX = Convert::ToInt32(posXstr);
		int posY = Convert::ToInt32(posYstr);

		return Point(posX, posY); // Возвращаем позицию
	}

	// Запись в XML
	void DrawField::SaveToXml(String^ filePath) {
		File::Delete(filePath);
		XmlDocument^ xmlDoc = gcnew XmlDocument();
		XmlElement^ root = xmlDoc->CreateElement("Elements");
		xmlDoc->AppendChild(root);

		for each (auto elem in elements) {
			Point location = elem.Key;
			Element^ element = elem.Value;
			String^ f = Convert::ToString(element->Flip);
			XmlElement^ ElementFile = xmlDoc->CreateElement("Element");
			ElementFile->SetAttribute("Position", location.X + " " + location.Y); // Сохраняем координаты
			ElementFile->SetAttribute("Type", element->name); //Сохраняем тип элемента
			ElementFile->SetAttribute("Flips", f); //Сохраняем количество поворотов

			root->AppendChild(ElementFile);
		}
		for (int j = 0; j < ArrayOfLines->Count; j++) {
			XmlElement^ ElementFile = xmlDoc->CreateElement("Line");
			String^ tempStr1;
			tempStr1 += Convert::ToString(ArrayOfLines[j]->InitialPoint.X);
			tempStr1 += " ";
			tempStr1 += Convert::ToString(ArrayOfLines[j]->InitialPoint.Y);

			String^ tempStr2;
			tempStr2 += Convert::ToString(ArrayOfLines[j]->FinalPoint.X);
			tempStr2 += " ";
			tempStr2 += Convert::ToString(ArrayOfLines[j]->FinalPoint.Y);
			ElementFile->SetAttribute("FirstPoint", tempStr1);
			ElementFile->SetAttribute("SecondPoint", tempStr2);
			root->AppendChild(ElementFile);
		}

		xmlDoc->Save(filePath);
	}

	// Чтение из XML
	void DrawField::LoadFromXml(String^ filePath) {
		XmlDocument^ xmlDoc = gcnew XmlDocument();
		xmlDoc->Load(filePath);
		XmlNode^ root = xmlDoc->DocumentElement;

		Controls->Clear(); // Удаляем элементы из Controls
		elements->Clear(); // Удаляем элементы из словаря
		ArrayOfLines->Clear(); // Удаляем все линии

		try {
			for each (XmlNode ^ ElementNode in root->ChildNodes) {
				if (ElementNode->Name == "Element") {
					String^ position = ElementNode->Attributes["Position"]->Value;
					String^ type = ElementNode->Attributes["Type"]->Value;
					String^ Flips = ElementNode->Attributes["Flips"]->Value;

					int flips = Convert::ToInt32(Flips);
					// Конвертируем строку в координаты
					Point location = ConvertSchemaToPoint(position);
					Image^ sprite = System::Drawing::Image::FromFile(elementImagesPath + type + ".png");

					try {
						AddElement(sprite, location, type, flips);
					}
					catch (...) { MessageBox::Show("Попытка разместить два разных элемента на одни и те же координаты.", "Ошибка файла", MessageBoxButtons::OK, MessageBoxIcon::Error);
						Controls->Clear();
						elements->Clear(); 
						ArrayOfLines->Clear();
						return;
					}
				}
				else if (ElementNode->Name == "Line") {
					String^ pos_line1 = ElementNode->Attributes["FirstPoint"]->Value;
					String^ pos_line2 = ElementNode->Attributes["SecondPoint"]->Value;
					Point location1 = ConvertSchemaToPoint(pos_line1);
					Point location2 = ConvertSchemaToPoint(pos_line2);
					ArrayOfLines->Add(gcnew Line(location1, location2));
				}
			}
		}
		catch (...) {
			MessageBox::Show("Файл содержит не допустимую структуру или символы.", "Ошибка файла", MessageBoxButtons::OK, MessageBoxIcon::Error);
			Controls->Clear(); // Удаляем элементы из Controls
			elements->Clear(); // Удаляем элементы из словаря
			ArrayOfLines->Clear(); // Удаляем все линии
		}
		this->Invalidate(); // Перерисовать поле после загрузки всех элементов
	}

	// Обработчик нажатия на поле мышкой
	void DrawField::OnMouseClick(Object^ sender, MouseEventArgs^ e) {
		// Обработчик нажатия на поле ЛКМ
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			if (currentElementType == "line") {
				if (StartingPointLine.X != 0 && StartingPointLine.Y != 0) {
					//Рисуем линию
					Graphics^ g = this->CreateGraphics();
					Pen^ pen = gcnew Pen(Color::Black, 2);
					g->DrawLine(pen, StartingPointLine, e->Location);

					ArrayOfLines->Add(gcnew Line(Point(StartingPointLine.X, StartingPointLine.Y), Point(e->Location.X, e->Location.Y)));
					StartingPointLine.X = 0;
					StartingPointLine.Y = 0;
					this->Invalidate();
				}
				else {
					StartingPointLine.X = e->X;
					StartingPointLine.Y = e->Y;
				}
			}
			else {//Ставим выбранный элемент
				Image^ sprite;
				try {
					sprite = System::Drawing::Image::FromFile(elementImagesPath + currentElementType + ".png");
				}
				catch (Exception^ ex) {
					MessageBox::Show("Ошибка - изображение элемента не найдено: " + currentElementType + ".png");
				}
				//Добавление элемента
				AddElement(sprite, Point(e->X, e->Y), currentElementType, 0);

				this->Invalidate(); // Перерисовать поле
			}
		}//Обработчик нажатия на поле ПКМ (Удаление линии)
		else if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			bool NotDel = true;
			//Проверяем все линии
			for (int i = 0; i < ArrayOfLines->Count; i++) {
				//Удаление линии
				int X0_temp = ArrayOfLines[i]->InitialPoint.X - 2;
				int Y0_temp = ArrayOfLines[i]->InitialPoint.Y - 2;
				int X1_temp = ArrayOfLines[i]->FinalPoint.X - 2;
				int Y1_temp = ArrayOfLines[i]->FinalPoint.Y - 2;

				for (int k = 0; k < 4; k++) {
					for (int q = 0; q < 4; q++) {
						if ((e->X == X0_temp && e->Y == Y0_temp) || (e->X == X1_temp && e->Y == Y1_temp)) {
							ArrayOfLines->Remove(ArrayOfLines[i]);
							NotDel = false;
							this->Invalidate();
							break;
						}
						X0_temp++;
						X1_temp++;
					}
					if (!NotDel) { break; }
					X0_temp -= 3;
					X1_temp -= 3;
					Y0_temp++;
					Y1_temp++;
				}
			}
		}
	}
}