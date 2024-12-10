#pragma once
#include <cstdlib>
#include <ctime>
#include <msclr/marshal_cppstd.h>

namespace snellentest {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class VisionTrainingForm : public Form
    {
    public:
        VisionTrainingForm()
        {
            srand(static_cast<unsigned int>(time(0))); // Inicializace generátoru náhodných čísel
            InitializeComponent();
        }

    protected:
        ~VisionTrainingForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        Label^ lblSnellenText;
        Label^ lblFeedback;
        TextBox^ txtErrorLog; // Textové pole pro zobrazení chyb
        NumericUpDown^ numFontSize; // Číselník pro nastavení velikosti fontu
        ComboBox^ cmbFontName; // Výběr fontu
        Button^ btnSetFontSize; // Tlačítko pro nastavení fontu

        System::Drawing::Font^ selectedFont;

        void InitializeComponent(void)
        {
            this->lblSnellenText = gcnew Label();
            this->lblFeedback = gcnew Label();
            this->txtErrorLog = gcnew TextBox();
            this->numFontSize = gcnew NumericUpDown();
            this->cmbFontName = gcnew ComboBox();
            this->btnSetFontSize = gcnew Button();

            // Nastavení vlastnosti KeyPreview
            this->KeyPreview = true;

            // Label pro zobrazení náhodného písmena
            this->lblSnellenText->Text = GetRandomLetter();
            this->lblSnellenText->Location = System::Drawing::Point(150, 50);
            this->lblSnellenText->Size = System::Drawing::Size(500, 150);
            this->selectedFont = gcnew System::Drawing::Font("Arial", 50);
            this->lblSnellenText->Font = this->selectedFont;

            // Feedback Label
            this->lblFeedback->Location = System::Drawing::Point(150, 220);
            this->lblFeedback->Size = System::Drawing::Size(400, 40);
            this->lblFeedback->Font = gcnew System::Drawing::Font("Arial", 16);

            // Textové pole pro log chyb
            this->txtErrorLog->Location = System::Drawing::Point(150, 270);
            this->txtErrorLog->Size = System::Drawing::Size(500, 150);
            this->txtErrorLog->Font = gcnew System::Drawing::Font("Arial", 12);
            this->txtErrorLog->Multiline = true;
            this->txtErrorLog->ReadOnly = true;
            this->txtErrorLog->ScrollBars = ScrollBars::Vertical;

            // Číselník pro nastavení velikosti fontu
            this->numFontSize->Location = System::Drawing::Point(150, 450);
            this->numFontSize->Minimum = 10;
            this->numFontSize->Maximum = 200;
            this->numFontSize->Value = 50;
            this->numFontSize->Size = System::Drawing::Size(100, 30);

            // ComboBox pro výběr fontu
            this->cmbFontName->Location = System::Drawing::Point(280, 450);
            this->cmbFontName->Size = System::Drawing::Size(200, 30);
            this->cmbFontName->Items->AddRange(gcnew cli::array<Object^> { "Arial", "Times New Roman", "Verdana", "Courier New" });
            this->cmbFontName->SelectedIndex = 0;

            // Tlačítko pro potvrzení nastavení fontu
            this->btnSetFontSize->Text = "Nastavit font";
            this->btnSetFontSize->Location = System::Drawing::Point(500, 450);
            this->btnSetFontSize->Size = System::Drawing::Size(150, 30);
            this->btnSetFontSize->Click += gcnew EventHandler(this, &VisionTrainingForm::btnSetFontSize_Click);

            // Přidání obsluhy události KeyPress
            this->KeyPress += gcnew KeyPressEventHandler(this, &VisionTrainingForm::Form_KeyPress);

            // Přidání komponent do formuláře
            this->Controls->Add(this->lblSnellenText);
            this->Controls->Add(this->lblFeedback);
            this->Controls->Add(this->txtErrorLog);
            this->Controls->Add(this->numFontSize);
            this->Controls->Add(this->cmbFontName);
            this->Controls->Add(this->btnSetFontSize);

            this->Text = "Trénink zrakové ostrosti";
            this->Size = System::Drawing::Size(800, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        // Funkce pro generování náhodného písmene
        String^ GetRandomLetter()
        {
            char letter = 'A' + (rand() % 26); // Generuje náhodné písmeno od 'A' do 'Z'
            return gcnew String(letter, 1);
        }

        // Obsluha události KeyPress
        void Form_KeyPress(Object^ sender, KeyPressEventArgs^ e)
        {
            String^ userInput = gcnew String(Char::ToUpper(e->KeyChar).ToString());
            String^ correctText = this->lblSnellenText->Text;

            if (userInput->Equals(correctText->ToUpper()))
            {
                this->lblFeedback->Text = "Správně!";
                this->lblFeedback->ForeColor = System::Drawing::Color::Green;
            }
            else
            {
                this->lblFeedback->Text = "Špatně!";
                this->lblFeedback->ForeColor = System::Drawing::Color::Red;

                // Zápis chyby do textového pole
                this->txtErrorLog->AppendText("Očekáváno: " + correctText + ", Zadané: " + userInput + "\r\n");
            }

            // Generování nového písmene
            this->lblSnellenText->Text = GetRandomLetter();
        }

        // Nastavení nové velikosti a fontu
        void btnSetFontSize_Click(Object^ sender, EventArgs^ e)
        {
            float fontSize = static_cast<float>(this->numFontSize->Value);
            String^ fontName = this->cmbFontName->SelectedItem->ToString();

            this->selectedFont = gcnew System::Drawing::Font(fontName, fontSize);
            this->lblSnellenText->Font = this->selectedFont;
        }

    private:
        System::ComponentModel::Container^ components;
    };
}
