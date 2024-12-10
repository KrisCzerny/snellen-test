#pragma once

#include <cstdlib>  // Pro generování náhodných čísel
#include <ctime>    // Pro inicializaci generátoru náhodných čísel
#include <msclr/marshal_cppstd.h> // Pro převod String^ na std::string
#include "MainForm.h"

namespace snellentest {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class MainForm : public Form
    {
    public:
        MainForm()
        {
            srand(static_cast<unsigned int>(time(0))); // Inicializace generátoru náhodných čísel
            InitializeComponent();
        }

    protected:
        ~MainForm()
        {
            if (components != nullptr) // Kontrola na CLR nullptr
            {
                delete components;
            }
        }

    private:
        Button^ btnRestart;
        Button^ btnEndTest; // Tlačítko pro ukončení testu
        Label^ lblSnellenText;
        TextBox^ txtUserInput;
        Label^ lblFeedback;
        TextBox^ txtTestResult; // Textové pole pro zobrazení výsledků
        int correctAnswers;
        int currentLevel;
        int totalAttempts; // Počet celkových pokusů
        int errors; // Počet chyb
        System::Drawing::Font^ currentFont;

        void InitializeComponent(void)
        {
            this->btnRestart = gcnew Button();
            this->btnEndTest = gcnew Button(); // Tlačítko pro ukončení testu
            this->lblSnellenText = gcnew Label();
            this->txtUserInput = gcnew TextBox();
            this->lblFeedback = gcnew Label();
            this->txtTestResult = gcnew TextBox(); // Nové textové pole

            this->correctAnswers = 0;
            this->currentLevel = 1;
            this->totalAttempts = 0;
            this->errors = 0;
            this->currentFont = gcnew System::Drawing::Font("Optician Sans", 80);

            // Nastavení tlačítka Restart
            this->btnRestart->Text = "Restart";
            this->btnRestart->Location = System::Drawing::Point(20, 300);
            this->btnRestart->Size = System::Drawing::Size(120, 40);
            this->btnRestart->Click += gcnew EventHandler(this, &MainForm::btnRestart_Click);

            // Nastavení tlačítka Ukončit test
            this->btnEndTest->Text = "Ukončit test";
            this->btnEndTest->Location = System::Drawing::Point(160, 300);
            this->btnEndTest->Size = System::Drawing::Size(120, 40);
            this->btnEndTest->Click += gcnew EventHandler(this, &MainForm::btnEndTest_Click);

            // Nastavení labelu pro náhodné písmeno
            this->lblSnellenText->Text = GetRandomLetter();
            this->lblSnellenText->Size = System::Drawing::Size(300, 100);
            this->lblSnellenText->Font = this->currentFont;

            // Nastavení textového pole pro zadávání odpovědí
            this->txtUserInput->Location = System::Drawing::Point(20, 200);
            this->txtUserInput->Size = System::Drawing::Size(200, 40);
            this->txtUserInput->Font = gcnew System::Drawing::Font("Arial", 14);
            this->txtUserInput->KeyDown += gcnew KeyEventHandler(this, &MainForm::txtUserInput_KeyDown);

            // Nastavení zpětné vazby
            this->lblFeedback->Location = System::Drawing::Point(20, 250);
            this->lblFeedback->Size = System::Drawing::Size(300, 40);
            this->lblFeedback->Font = gcnew System::Drawing::Font("Arial", 12);

            // Nastavení textového pole pro výsledky testu
            this->txtTestResult->Location = System::Drawing::Point(20, 360);
            this->txtTestResult->Size = System::Drawing::Size(300, 80);
            this->txtTestResult->Font = gcnew System::Drawing::Font("Arial", 10);
            this->txtTestResult->Multiline = true;
            this->txtTestResult->ReadOnly = true;

            // Přidání komponent do formuláře
            this->Controls->Add(this->btnRestart);
            this->Controls->Add(this->btnEndTest);
            this->Controls->Add(this->lblSnellenText);
            this->Controls->Add(this->txtUserInput);
            this->Controls->Add(this->lblFeedback);
            this->Controls->Add(this->txtTestResult);

            // Nastavení formuláře
            this->Text = "Test zrakové ostrosti";
            this->Size = System::Drawing::Size(1280, 720); // Nastavení okna na specifickou velikost
            this->StartPosition = FormStartPosition::CenterScreen;

            CenterLabel();
        }

        String^ GetRandomLetter()
        {
            char letter = 'A' + (rand() % 26);
            return gcnew String(letter, 1);
        }

        void CenterLabel()
        {
            int centerX = (this->ClientSize.Width - this->lblSnellenText->Width) / 2 + 50; // Posun doprava o 50 pixelů
            int centerY = (this->ClientSize.Height - this->lblSnellenText->Height) / 2;
            this->lblSnellenText->Location = System::Drawing::Point(centerX, centerY);
        }

        void btnRestart_Click(Object^ sender, EventArgs^ e)
        {
            this->txtUserInput->Text = "";
            this->lblSnellenText->Text = GetRandomLetter();
            this->lblSnellenText->Font = this->currentFont;
            this->correctAnswers = 0;
            this->currentLevel = 1;
            this->totalAttempts = 0;
            this->errors = 0;
            this->lblFeedback->Text = "";
            this->txtTestResult->Text = ""; // Vymazat výsledky testu
            CenterLabel();
        }

        void btnEndTest_Click(Object^ sender, EventArgs^ e)
        {
            ShowFinalResults();
        }

        void txtUserInput_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::Enter)
            {
                String^ userInput = this->txtUserInput->Text;
                String^ correctText = this->lblSnellenText->Text;

                this->totalAttempts++;
                if (userInput->ToUpper()->Equals(correctText->ToUpper()))
                {
                    this->correctAnswers++;
                    this->lblFeedback->Text = "Správně!";
                    this->lblFeedback->ForeColor = System::Drawing::Color::Green;
                }
                else
                {
                    this->errors++;
                    this->lblFeedback->Text = "Špatně!";
                    this->lblFeedback->ForeColor = System::Drawing::Color::Red;
                }

                if (this->correctAnswers >= 3)
                {
                    AdvanceToNextLevel();
                }
                else
                {
                    this->lblSnellenText->Text = GetRandomLetter();
                    CenterLabel();
                }

                this->txtUserInput->Text = "";
            }
        }

        void AdvanceToNextLevel()
        {
            this->correctAnswers = 0;
            this->currentLevel++;

            float newFontSize = this->currentFont->Size - 10.0f; // Zmenšení fontu
            if (newFontSize < 10.0f)
                newFontSize = 10.0f;

            this->currentFont = gcnew System::Drawing::Font("Optician Sans", newFontSize);
            this->lblSnellenText->Font = this->currentFont;
            this->lblSnellenText->Text = GetRandomLetter();
            this->lblFeedback->Text = "Postup na úroveň " + this->currentLevel.ToString();
            this->lblFeedback->ForeColor = System::Drawing::Color::Blue;
            CenterLabel();
        }

        void ShowFinalResults()
        {
            String^ result = "Maximální dosažená ostrost: Úroveň " + this->currentLevel.ToString() +
                "\nCelkový počet pokusů: " + this->totalAttempts.ToString() +
                "\nCelkový počet chyb: " + this->errors.ToString();
            this->txtTestResult->Text = result; // Zobrazí výsledky v textovém poli
        }

    private:
        System::ComponentModel::Container^ components;
    };
}
