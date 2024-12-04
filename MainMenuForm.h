#pragma once

#include "MainForm.h"
#include "VisionTrainingForm.h"
namespace snellentest {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class MainMenuForm : public Form
    {
    public:
        MainMenuForm()
        {
            InitializeComponent();
        }

    protected:
        ~MainMenuForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        Button^ btnSnellenTest;   // Tlaèítko pro test zrakové ostrosti
        Button^ btnVisionTraining; // Tlaèítko pro trénink zrakové ostrosti

        void InitializeComponent(void)
        {
            this->btnSnellenTest = gcnew Button();
            this->btnVisionTraining = gcnew Button();

            // Nastavení tlaèítka pro test zrakové ostrosti
            this->btnSnellenTest->Text = "Test zrakové ostrosti";
            this->btnSnellenTest->Location = System::Drawing::Point(100, 100);
            this->btnSnellenTest->Size = System::Drawing::Size(200, 50);
            this->btnSnellenTest->Click += gcnew EventHandler(this, &MainMenuForm::btnSnellenTest_Click);

            // Nastavení tlaèítka pro trénink zrakové ostrosti
            this->btnVisionTraining->Text = "Trénink zrakové ostrosti";
            this->btnVisionTraining->Location = System::Drawing::Point(100, 200);
            this->btnVisionTraining->Size = System::Drawing::Size(200, 50);
            this->btnVisionTraining->Click += gcnew EventHandler(this, &MainMenuForm::btnVisionTraining_Click);

            // Pøidání tlaèítek do formuláøe
            this->Controls->Add(this->btnSnellenTest);
            this->Controls->Add(this->btnVisionTraining);

            // Nastavení formuláøe
            this->Text = "Hlavní menu";
            this->Size = System::Drawing::Size(400, 400);
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        // Událost pro spuštìní testu zrakové ostrosti
        void btnSnellenTest_Click(Object^ sender, EventArgs^ e)
        {
            MainForm^ snellenTestForm = gcnew MainForm();
            snellenTestForm->ShowDialog();
        }

        // Událost pro spuštìní tréninku zrakové ostrosti
       void btnVisionTraining_Click(Object^ sender, EventArgs^ e)
{
    VisionTrainingForm^ visionTrainingForm = gcnew VisionTrainingForm();
    visionTrainingForm->ShowDialog();
}


    private:
        System::ComponentModel::Container^ components;
    };
}
