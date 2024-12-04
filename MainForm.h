#pragma once

#include <cstdlib>  // Pro generov�n� n�hodn�ch ��sel
#include <ctime>    // Pro inicializaci gener�toru n�hodn�ch ��sel
#include "MainForm.h"
namespace snellentest {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class MainForm : public Form
    {
    public:
        MainForm()
        {
            srand((unsigned int)time(0)); // Inicializace gener�toru n�hodn�ch ��sel
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
        Label^ lblFeedback; // Nov� label pro zp�tnou vazbu
        int correctAnswers; // Po�et spr�vn�ch odpov�d�
        int currentLevel;   // Aktu�ln� �rove� testu
        System::Drawing::Font^ baseFont; // V�choz� font

        void InitializeComponent(void)
        {
            this->btnRestart = gcnew Button();
            this->lblSnellenText = gcnew Label();
            this->txtUserInput = gcnew TextBox();
            this->lblFeedback = gcnew Label(); // Inicializace feedback labelu

            this->correctAnswers = 0; // Inicializace spr�vn�ch odpov�d�
            this->currentLevel = 1;  // Start na 1. �rovni
            this->baseFont = gcnew System::Drawing::Font("Optician Sans", 100); // Za��n�me s fontem velikosti 200 (pro 20/200)
            this->baseFont = gcnew System::Drawing::Font("Optician Sans", this->baseFont->Size, this->baseFont->Style);
            // Nastaven� tla��tka Restart
            this->btnRestart->Text = "Restart";
            this->btnRestart->Location = System::Drawing::Point(100, 500); // Zv�t�en� prostoru pro tla��tko
            this->btnRestart->Click += gcnew EventHandler(this, &MainForm::btnRestart_Click);

            // Nastaven� labelu pro n�hodn� p�smeno
            this->lblSnellenText->Text = GetRandomLetter(); // Generuje prvn� p�smeno
            this->lblSnellenText->Location = System::Drawing::Point(350, 100); // Zv�t�en� prostoru pro text
            this->lblSnellenText->Size = System::Drawing::Size(600, 150); // Zv�t�en� oblasti pro zobrazen� p�smen
            this->lblSnellenText->Font = this->baseFont;

            // Nastaven� textov�ho pole
            this->txtUserInput->Location = System::Drawing::Point(100, 300); // Zv�t�en� oblasti pro zad�n�
            this->txtUserInput->Size = System::Drawing::Size(400, 40);
            this->txtUserInput->Font = gcnew System::Drawing::Font("Arial", 20);
            this->txtUserInput->KeyDown += gcnew KeyEventHandler(this, &MainForm::txtUserInput_KeyDown); // P�id�n� obsluhy pro kl�vesu Enter

            // Nastaven� feedback labelu pro zobrazen� zp�tn� vazby
            this->lblFeedback->Location = System::Drawing::Point(100, 350);
            this->lblFeedback->Size = System::Drawing::Size(400, 40);
            this->lblFeedback->Font = gcnew System::Drawing::Font("Arial", 20);

            // P�id�n� komponent do formul��e
            this->Controls->Add(this->btnRestart);
            this->Controls->Add(this->lblSnellenText);
            this->Controls->Add(this->txtUserInput);
            this->Controls->Add(this->lblFeedback);

            this->Text = "Test zrakov� ostrosti";
            this->Size = System::Drawing::Size(800, 600);  // Zv�t�en� okna aplikace

            // Zajist�, �e okno nebude mo�n� zm�nit
            this->MaximumSize = this->Size;
            this->MinimumSize = this->Size;

            // Um�st�n� okna na st�ed obrazovky
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        // Funkce pro generov�n� n�hodn�ho p�smene
        String^ GetRandomLetter()
        {
            char letter = 'A' + (rand() % 26); // Generuje n�hodn� p�smeno od 'A' do 'Z'
            return gcnew String(letter, 1);
        }

        // Obsluha tla��tka Restart
        void btnRestart_Click(Object^ sender, EventArgs^ e)
        {
            this->txtUserInput->Text = "";       // Vyma�e text
            this->lblSnellenText->Text = GetRandomLetter(); // Generuje nov� p�smeno
            this->lblSnellenText->Font = this->baseFont; // Reset fontu
            this->correctAnswers = 0;           // Reset spr�vn�ch odpov�d�
            this->currentLevel = 1;             // Reset �rovn�
            this->lblFeedback->Text = "";      // Vyma�e zp�tnou vazbu
        }

        // Obsluha stisknut� kl�vesy Enter
        void txtUserInput_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::Enter) // Kontrola, zda byla stisknuta kl�vesa Enter
            {
                // Z�sk�n� odpov�di u�ivatele
                String^ userInput = this->txtUserInput->Text;
                String^ correctText = this->lblSnellenText->Text;

                // Kontrola spr�vnosti odpov�di
                if (userInput->ToUpper()->Equals(correctText->ToUpper()))
                {
                    this->correctAnswers++;
                    this->lblFeedback->Text = "Spr�vn�!";
                    this->lblFeedback->ForeColor = System::Drawing::Color::Green;
                }
                else
                {
                    this->lblFeedback->Text = "�patn�! Zkuste to znovu.";
                    this->lblFeedback->ForeColor = System::Drawing::Color::Red;
                }

                // Kontrola postupu do dal�� �rovn�
                if (this->correctAnswers >= 3)
                {
                    AdvanceToNextLevel();
                }
                else
                {
                    // Generov�n� nov�ho p�smena pro aktu�ln� �rove�
                    this->lblSnellenText->Text = GetRandomLetter();
                }

                // Vymaz�n� vstupu
                this->txtUserInput->Text = "";
            }
        }

        // Postup do dal�� �rovn�
        void AdvanceToNextLevel()
        {
            this->correctAnswers = 0; // Reset po�tu spr�vn�ch odpov�d�
            this->currentLevel++;

            // Sn�en� velikosti fontu (zmen�en� textu)
            //float newFontSize = this->baseFont->Size;
            float newFontSize = this->baseFont->Size - (this->currentLevel - 1) * 20.0f;
            // Zajist�me, �e velikost p�sma nebude men�� ne� 8
            newFontSize = Math::Max(8.0f, newFontSize);

            // Aplikujeme novou velikost fontu na label
            this->lblSnellenText->Font = gcnew System::Drawing::Font("Arial", newFontSize);

            // Generov�n� nov�ho n�hodn�ho p�smene
            this->lblSnellenText->Text = GetRandomLetter();

            this->lblFeedback->Text = "Postoupili jste na �rove� " + this->currentLevel + "!";
            this->lblFeedback->ForeColor = System::Drawing::Color::Blue;
        }
    private:
        System::ComponentModel::Container^ components;
    };
}
