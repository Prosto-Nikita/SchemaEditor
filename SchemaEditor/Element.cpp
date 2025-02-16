// Figure.cpp
#include "MainForm.h"
#include "Element.h"
#include "DrawField.h"

namespace SchemaEditor {

	Element::Element(MainForm^ mainForm, DrawField^ drawField, Drawing::Image^ sprite, Point location, int Width, int Height, int Flip) {
		this->drawField = drawField;
		this->mainForm = mainForm;

		this->Flip = Flip;
		this->Image = sprite;

		this->Size = System::Drawing::Size(drawField->WidthElement, drawField->HeightElement); //Размер элемента (спрайта)
		//Повороты изображения
		for (int i = 0; i < Flip; i++) {
			int tempsize = this->Width;
			this->Width = this->Height;
			this->Height = tempsize;
			this->Size = System::Drawing::Size(this->Width, this->Height);
			this->Image->RotateFlip(RotateFlipType::Rotate90FlipNone);
		}
		this->Location = location;


		// Подписка на события мыши для перемещения
		this->MouseDown += gcnew MouseEventHandler(this, &Element::Element_MouseDown);
		this->MouseMove += gcnew MouseEventHandler(this, &Element::Element_MouseMove);
		this->MouseUp += gcnew MouseEventHandler(this, &Element::Element_MouseUp);
		this->MouseDoubleClick += gcnew MouseEventHandler(this, &Element::Element_MouseDoubleClick);
		this->MouseClick += gcnew MouseEventHandler(this, &Element::DeleteElementClick);
	}

	void Element::Draw(Graphics^ g) {
		if (Image != nullptr) {
			// Отрисовка изображения элемента
			g->DrawImage(Image, this->Location.X, this->Location.Y, this->Width, this->Height);
		}
	}

	// Обработка зажатия ЛКМ на элементе
	void Element::Element_MouseDown(Object^ sender, MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			initialLocation = this->Location;	// Сохраняем положение фигуры на случай некорректного перемещения (чтобы вернуть обратно)
			isDragging = true;					// Начинается перетаскивание
			dragStartPoint = e->Location;		// Сохраняем положение курсора в точке, за которую перетаскиваем фигуру (в её локальных координатах)
		}
		drawField->Invalidate();

	}

	// Обработка передвижения мыши с зажатым ЛКМ
	void Element::Element_MouseMove(Object^ sender, MouseEventArgs^ e) {
		if (isDragging) {
			// Вычисляем новое положение элемента
			int newX = this->Location.X + e->X;
			int newY = this->Location.Y + e->Y;


			// Обновляем положение элемента
			this->Location = System::Drawing::Point(newX, newY);
			// Перерисовка для корректного отображения
			drawField->Update();
		}
	}

	// Обработка отпускания мыши от элемента
	void Element::Element_MouseUp(Object^ sender, MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left && isDragging) {
			isDragging = false;

			// Вычисление курсора внутри поля отрисовки и проверка на наличие курсора в его области
			if (!(drawField->drawingArea.Contains(drawField->PointToClient(Cursor->Position)))) {
				// Возвращаем элемент на прежнее место
				this->Location = initialLocation;
				return;
			}

			int newX = this->Location.X;
			int newY = this->Location.Y;


			Point newLocation(newX, newY);

			// Добавляем новую пару с обновленным положением
			// Если на точке назначения уже есть элемент
			if (drawField->elements->ContainsKey(newLocation)) {
				this->Location = initialLocation;
				return;
			}
			else { // Если точка назначения пуста
				// Удаляем из словаря старое положение до зажатия ЛКМ 
				drawField->elements->Remove(this->initialLocation);

				// Добавляем новую пару с обновленным положением
				drawField->elements->Add(newLocation, this);
			}
			drawField->Invalidate();
		}
	}
	void Element::Element_MouseDoubleClick(Object^ sender, MouseEventArgs^ e) {
		//Меняем местами ширину и высоту
		int tempsize = this->Width;
		this->Width = this->Height;
		this->Height = tempsize;
		this->Size = System::Drawing::Size(this->Width, this->Height);
		//Поворачиваем изображение на 90 градусов
		Image->RotateFlip(RotateFlipType::Rotate90FlipNone);
		//Считаем количество поворотов
		this->Flip++;
		if (Flip % 4 == 0) { this->Flip = 0; }
		//Обновляем изображение
		drawField->Invalidate();
	}
	void Element::DeleteElementClick(Object^ sender, MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			drawField->elements->Remove(this->Location);
			drawField->Invalidate();
			this->Invalidate();
		}
	}
}
