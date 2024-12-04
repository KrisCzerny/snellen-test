#pragma once

#include <cstdlib>  // Pro generování náhodných èísel
#include <ctime>    // Pro inicializaci generátoru náhodných èísel
#include "MainForm.h"
namespace snellentest {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class MainForm : public Form
    {
    public:
        MainForm()
        {
            srand((unsigned int)time(0)); // Inicializace generátoru náhodných èísel
            InitializeComponent();
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        Button^ btnRestart;
        Label^ lblSnellenText;
        TextBox^ txtUserInput;
        Label^ lblFeedback; // Nový label pro zpìtnou vazbu
        int correctAnswers; // Poèet správných odpovìdí
        int currentLevel;   // Aktuální úroveò testu
        System::Drawing::Font^ baseFont; // Výchozí font

        void InitializeComponent(void)
        {
            this->btnRestart = gcnew Button();
            this->lblSnellenText = gcnew Label();
            this->txtUserInput = gcnew TextBox();
            this->lblFeedback = gcnew Label(); // Inicializace feedback labelu

            this->correctAnswers = 0; // Inicializace správných odpovìdí
            this->currentLevel = 1;  // Start na 1. úrovni
            this->baseFont = gcnew System::Drawing::Font("Optician Sans", 100); // Zaèínáme s fontem velikosti 200 (pro 20/200)
            this->baseFont = gcnew System::Drawing::Font("Optician Sans", this->baseFont->Size, this->baseFont->Style);
            // Nastavení tlaèítka Restart
            this->btnRestart->Text = "Restart";
            this->btnRestart->Location = System::Drawing::Point(100, 500); // Zvìtšení prostoru pro tlaèítko
            this->btnRestart->Click += gcnew EventHandler(this, &MainForm::btnRestart_Click);

            // Nastavení labelu pro náhodné písmeno
            this->lblSnellenText->Text = GetRandomLetter(); // Generuje první písmeno
            this->lblSnellenText->Location = System::Drawing::Point(350, 100); // Zvìtšení prostoru pro text
            this->lblSnellenText->Size = System::Drawing::Size(600, 150); // Zvìtšení oblasti pro zobrazení písmen
            this->lblSnellenText->Font = this->baseFont;

            // Nastavení textového pole
            this->txtUserInput->Location = System::Drawing::Point(100, 300); // Zvìtšení oblasti pro zadání
            this->txtUserInput->Size = System::Drawing::Size(400, 40);
            this->txtUserInput->Font = gcnew System::Drawing::Font("Arial", 20);
            this->txtUserInput->KeyDown += gcnew KeyEventHandler(this, &MainForm::txtUserInput_KeyDown); // Pøidání obsluhy pro klávesu Enter

            // Nastavení feedback labelu pro zobrazení zpìtné vazby
            this->lblFeedback->Location = System::Drawing::Point(100, 350);
            this->lblFeedback->Size = System::Drawing::Size(400, 40);
            this->lblFeedback->Font = gcnew System::Drawing::Font("Arial", 20);

            // Pøidání komponent do formuláøe
            this->Controls->Add(this->btnRestart);
            this->Controls->Add(this->lblSnellenText);
            this->Controls->Add(this->txtUserInput);
            this->Controls->Add(this->lblFeedback);

            this->Text = "Test zrakové ostrosti";
            this->Size = System::Drawing::Size(800, 600);  // Zvìtšení okna aplikace

            // Zajistí, že okno nebude možné zmìnit
            this->MaximumSize = this->Size;
            this->MinimumSize = this->Size;

            // Umístìní okna na støed obrazovky
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        // Funkce pro generování náhodného písmene
        String^ GetRandomLetter()
        {
            char letter = 'A' + (rand() % 26); // Generuje náhodné písmeno od 'A' do 'Z'
            return gcnew String(letter, 1);
        }

        // Obsluha tlaèítka Restart
        void btnRestart_Click(Object^ sender, EventArgs^ e)
        {
            this->txtUserInput->Text = "";       // Vymaže text
            this->lblSnellenText->Text = GetRandomLetter(); // Generuje nové písmeno
            this->lblSnellenText->Font = this->baseFont; // Reset fontu
            this->correctAnswers = 0;           // Reset správných odpovìdí
            this->currentLevel = 1;             // Reset úrovnì
            this->lblFeedback->Text = "";      // Vymaže zpìtnou vazbu
        }

        // Obsluha stisknutí klávesy Enter
        void txtUserInput_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::Enter) // Kontrola, zda byla stisknuta klávesa Enter
            {
                // Získání odpovìdi uživatele
                String^ userInput = this->txtUserInput->Text;
                String^ correctText = this->lblSnellenText->Text;

                // Kontrola správnosti odpovìdi
                if (userInput->ToUpper()->Equals(correctText->ToUpper()))
                {
                    this->correctAnswers++;
                    this->lblFeedback->Text = "Správnì!";
                    this->lblFeedback->ForeColor = System::Drawing::Color::Green;
                }
                else
                {
                    this->lblFeedback->Text = "Špatnì! Zkuste to znovu.";
                    this->lblFeedback->ForeColor = System::Drawing::Color::Red;
                }

                // Kontrola postupu do další úrovnì
                if (this->correctAnswers >= 3)
                {
                    AdvanceToNextLevel();
                }
                else
                {
                    // Generování nového písmena pro aktuální úroveò
                    this->lblSnellenText->Text = GetRandomLetter();
                }

                // Vymazání vstupu
                this->txtUserInput->Text = "";
            }
        }

        // Postup do další úrovnì
        void AdvanceToNextLevel()
        {
            this->correctAnswers = 0; // Reset poètu správných odpovìdí
            this->currentLevel++;

            // Snížení velikosti fontu (zmenšení textu)
            //float newFontSize = this->baseFont->Size;
            float newFontSize = this->baseFont->Size - (this->currentLevel - 1) * 20.0f;
            // Zajistíme, že velikost písma nebude menší než 8
            newFontSize = Math::Max(8.0f, newFontSize);

            // Aplikujeme novou velikost fontu na label
            this->lblSnellenText->Font = gcnew System::Drawing::Font("Arial", newFontSize);

            // Generování nového náhodného písmene
            this->lblSnellenText->Text = GetRandomLetter();

            this->lblFeedback->Text = "Postoupili jste na úroveò " + this->currentLevel + "!";
            this->lblFeedback->ForeColor = System::Drawing::Color::Blue;
        }
    private:
        System::ComponentModel::Container^ components;
    };
}
