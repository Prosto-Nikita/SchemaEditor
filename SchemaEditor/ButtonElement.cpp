#include "ButtonElement.h"
#include "MainForm.h"

// Основной конструктор элемента, принимающий ссылку на форму, ширину и высоту изображения, путь до изображения, название элемента
SchemaEditor::ButtonElement::ButtonElement(MainForm^ form, DrawField^ drawField, int Width, int Height, String^ path, String^ name)
{
    this->mainForm = form;
    this->drawField = drawField;
    this->name = name; // Имя размещаемого элемента

    this->drawField->WidthElement = Width;
    this->drawField->HeightElement = Height;

    this->Size = System::Drawing::Size(drawField->WidthElement, drawField->HeightElement); // Назначение размера спрайта
    this->Location = System::Drawing::Point(1000, 70); // Начальное положение иконки на форме (в левой части окна)

    this->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage; // Растягивание изображения до размеров spriteSize

    try {
        this->Image = System::Drawing::Image::FromFile(path); // Изображение для данного СurrentElementButton
    }
    catch (Exception^ e) {
        MessageBox::Show("Отсутствует изображение для элемента с названием вида:" + e->ToString(), "Отсутствует изображение", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }

    // Добавление созданной иконки на форму mainForm
    mainForm->Controls->Add(this);
    this->BringToFront();
    this->MouseClick += gcnew MouseEventHandler(this, &ButtonElement::MouseClickOnButon); // Подписка на событие MouseClick
}

// Реализация метода Draw из интерфейса GraphicsElement
void SchemaEditor::ButtonElement::Draw(Graphics^ g) {

    if (this->Image != nullptr) {
        // Отрисовка изображения кнопки
        g->DrawImage(this->Image, this->Location.X, this->Location.Y, this->Width, this->Height);
    }
}

// Обработчик нажатия на поле ЛКМ
void SchemaEditor::ButtonElement::MouseClickOnButon(Object^ sender, MouseEventArgs^ e)
{
    drawField->currentElementType = this->name; // Меняем тип размещаемой элемента в соответствии с именем элемента на иконке
    mainForm->labelCurrentElement->Text = "Выбран элемент: " + this->name;
    for each (auto icon in mainForm->ElementsMenu)
    {
        icon->Invalidate(); // Перерисовываем все иконки в меню элементов
    }
}

void SchemaEditor::ButtonElement::OnPaint(PaintEventArgs^ e)
{
    PictureBox::OnPaint(e); // Вызов базового метода отрисовки

    // Условная логика для изменения цвета фона кнопки в зависимости от выбранного элемента
    if (drawField->currentElementType == this->name) {
        this->BackColor = Color::FromArgb(130, 255, 160); // Цвет для выбранного элемента
    }
    else {
        this->BackColor = Color::Transparent; // Прозрачный фон для невыбранного элемента
    }
}

