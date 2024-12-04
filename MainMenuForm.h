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
        Button^ btnSnellenTest;   // Tla��tko pro test zrakov� ostrosti
        Button^ btnVisionTraining; // Tla��tko pro tr�nink zrakov� ostrosti

        void InitializeComponent(void)
        {
            this->btnSnellenTest = gcnew Button();
            this->btnVisionTraining = gcnew Button();

            // Nastaven� tla��tka pro test zrakov� ostrosti
            this->btnSnellenTest->Text = "Test zrakov� ostrosti";
            this->btnSnellenTest->Location = System::Drawing::Point(100, 100);
            this->btnSnellenTest->Size = System::Drawing::Size(200, 50);
            this->btnSnellenTest->Click += gcnew EventHandler(this, &MainMenuForm::btnSnellenTest_Click);

            // Nastaven� tla��tka pro tr�nink zrakov� ostrosti
            this->btnVisionTraining->Text = "Tr�nink zrakov� ostrosti";
            this->btnVisionTraining->Location = System::Drawing::Point(100, 200);
            this->btnVisionTraining->Size = System::Drawing::Size(200, 50);
            this->btnVisionTraining->Click += gcnew EventHandler(this, &MainMenuForm::btnVisionTraining_Click);

            // P�id�n� tla��tek do formul��e
            this->Controls->Add(this->btnSnellenTest);
            this->Controls->Add(this->btnVisionTraining);

            // Nastaven� formul��e
            this->Text = "Hlavn� menu";
            this->Size = System::Drawing::Size(400, 400);
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        // Ud�lost pro spu�t�n� testu zrakov� ostrosti
        void btnSnellenTest_Click(Object^ sender, EventArgs^ e)
        {
            MainForm^ snellenTestForm = gcnew MainForm();
            snellenTestForm->ShowDialog();
        }

        // Ud�lost pro spu�t�n� tr�ninku zrakov� ostrosti
       void btnVisionTraining_Click(Object^ sender, EventArgs^ e)
{
    VisionTrainingForm^ visionTrainingForm = gcnew VisionTrainingForm();
    visionTrainingForm->ShowDialog();
}


    private:
        System::ComponentModel::Container^ components;
    };
}
