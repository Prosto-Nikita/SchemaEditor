#pragma once
#include "Windows.h"
#include "Element.h"
#include "DrawField.h"
#include "ButtonElement.h"
#include "GraphicsElement.h"

namespace SchemaEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::IO;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		DrawField^ drawField; // Поле рисования, содержащий все элементы и отвечающий за их прорисовку
	public:
		List<ButtonElement^>^ ElementsMenu = gcnew List<ButtonElement^>;// Массив кнопок для выбора добавляемого элемента
	public:
		MainForm(void)
		{
			InitializeComponent();
			drawField = gcnew DrawField(this);

			this->Controls->Add(drawField);
			drawField->BringToFront();

			CreateElementMenu();
			this->DoubleBuffered = true;
			System::Windows::Forms::ImageLayout::Center;
		}
	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ LabelExplanations;
	private: System::Windows::Forms::Button^ buttonClearField;
	private: System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Button^ buttonLoad;
	private: System::Windows::Forms::Button^ buttonSave;
	public: System::Windows::Forms::Label^ labelCurrentElement;

#pragma region Windows Form Designer generated code
	public:
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->buttonLoad = (gcnew System::Windows::Forms::Button());
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->labelCurrentElement = (gcnew System::Windows::Forms::Label());
			this->buttonClearField = (gcnew System::Windows::Forms::Button());
			this->LabelExplanations = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonLoad
			// 
			this->buttonLoad->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->buttonLoad->Location = System::Drawing::Point(327, 560);
			this->buttonLoad->Name = L"buttonLoad";
			this->buttonLoad->Size = System::Drawing::Size(288, 51);
			this->buttonLoad->TabIndex = 1;
			this->buttonLoad->Text = L"Загрузить схему из xml";
			this->buttonLoad->UseVisualStyleBackColor = true;
			this->buttonLoad->Click += gcnew System::EventHandler(this, &MainForm::buttonLoad_Click);
			// 
			// buttonSave
			// 
			this->buttonSave->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->buttonSave->Location = System::Drawing::Point(17, 560);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(279, 51);
			this->buttonSave->TabIndex = 2;
			this->buttonSave->Text = L"Сохранить схему в xml\r\n";
			this->buttonSave->UseVisualStyleBackColor = true;
			this->buttonSave->Click += gcnew System::EventHandler(this, &MainForm::buttonSave_Click);
			// 
			// labelCurrentElement
			// 
			this->labelCurrentElement->AutoSize = true;
			this->labelCurrentElement->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->labelCurrentElement->Location = System::Drawing::Point(990, 9);
			this->labelCurrentElement->Name = L"labelCurrentElement";
			this->labelCurrentElement->Size = System::Drawing::Size(274, 29);
			this->labelCurrentElement->TabIndex = 4;
			this->labelCurrentElement->Text = L"Выбран элемент: lamp";
			// 
			// buttonClearField
			// 
			this->buttonClearField->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->buttonClearField->Location = System::Drawing::Point(649, 560);
			this->buttonClearField->Name = L"buttonClearField";
			this->buttonClearField->Size = System::Drawing::Size(243, 51);
			this->buttonClearField->TabIndex = 6;
			this->buttonClearField->Text = L"Очистить схему";
			this->buttonClearField->UseVisualStyleBackColor = true;
			this->buttonClearField->Click += gcnew System::EventHandler(this, &MainForm::buttonClearField_Click);
			// 
			// Label_Explanations
			// 
			this->LabelExplanations->AutoSize = true;
			this->LabelExplanations->Location = System::Drawing::Point(955, 488);
			this->LabelExplanations->Name = L"Label_Explanations";
			this->LabelExplanations->Size = System::Drawing::Size(365, 112);
			this->LabelExplanations->TabIndex = 10;
			this->LabelExplanations->Text = resources->GetString(L"Label_Explanations.Text");
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(1297, 655);
			this->Controls->Add(this->LabelExplanations);
			this->Controls->Add(this->buttonClearField);
			this->Controls->Add(this->labelCurrentElement);
			this->Controls->Add(this->buttonSave);
			this->Controls->Add(this->buttonLoad);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->Text = L"Редактор принципиальных схем";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// Создание меню из иконок элементов для добавления
	private: void CreateElementMenu()
	{
		// Создание элементов для меню добавления и помещение их в список
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 40, 40, drawField->elementImagesPath + "\\lamp.png", "lamp"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 40, 40, drawField->elementImagesPath + "\\ampermeter.png", "ampermeter"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 40, 40, drawField->elementImagesPath + "\\voltmeter.png", "voltmeter"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\resistor.png", "resistor"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\galvanic_element.png", "galvanic_element"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\battery.png", "battery"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\fuse.png", "fuse"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\reostat.png", "reostat"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\heater.png", "heater"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\capacitor.png", "capacitor"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\diode.png", "diode"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\coil.png", "coil"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\key.png", "key"));
		ElementsMenu->Add(gcnew ButtonElement(this, drawField, 70, 40, drawField->elementImagesPath + "\\line.png", "line"));
		// Начальная позиция, которая будет обновляться в ходе размещения иконок
		Drawing::Point iconInitialLocationBegin = ElementsMenu[0]->Location;
		Drawing::Point iconInitialLocation = ElementsMenu[0]->Location;

		for (int i = 0; i < ElementsMenu->Count; i++) {
			ElementsMenu[i]->Location = iconInitialLocation;
			iconInitialLocation.X += ElementsMenu[i]->Width + 10;
			if (i % 3 == 0 && i != 0) {
				iconInitialLocation.X = iconInitialLocationBegin.X;
				iconInitialLocation.Y += 50;
			}
		}

	}
		   // Обработка нажатия кнопки сохранения в XML
	private: System::Void buttonSave_Click(System::Object^ sender, System::EventArgs^ e) {

		SaveFileDialog^ saveFileDialog = gcnew SaveFileDialog();
		saveFileDialog->Filter = "XML files (*.xml)|*.xml";
		if (saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			drawField->SaveToXml(saveFileDialog->FileName);
		}
	}
		   // Обработка нажатия кнопки загрузки из XML
	private: System::Void buttonLoad_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "XML files (*.xml)|*.xml";
		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			drawField->LoadFromXml(openFileDialog->FileName);
		}
	}
	private: System::Void buttonClearField_Click(System::Object^ sender, System::EventArgs^ e) {
		drawField->elements->Clear(); // Очищаем массив элементов
		drawField->Controls->Clear(); // Удаляем все элементы из Controls
		drawField->ArrayOfLines->Clear(); // Удаляем все линии
		drawField->StartingPointLine.X = 0;
		drawField->StartingPointLine.Y = 0;

		drawField->Invalidate(); // Обновляем поле
	}
	};
}

