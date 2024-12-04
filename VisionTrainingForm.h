#pragma once
#include <cstdlib>
#include <ctime>
#include <string>

namespace snellentest {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class VisionTrainingForm : public Form
    {
    public:
        VisionTrainingForm()
        {
            srand((unsigned int)time(0)); // Inicializace gener�toru n�hodn�ch ��sel
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
        TextBox^ txtUserInput;
        Label^ lblFeedback;
        Button^ btnSetFontSize;
        NumericUpDown^ numFontSize;
        ComboBox^ cmbFontName;

        System::Drawing::Font^ selectedFont;

        void InitializeComponent(void)
        {
            this->lblSnellenText = gcnew Label();
            this->txtUserInput = gcnew TextBox();
            this->lblFeedback = gcnew Label();
            this->btnSetFontSize = gcnew Button();
            this->numFontSize = gcnew NumericUpDown();
            this->cmbFontName = gcnew ComboBox();

            // Nastaven� Labelu pro n�hodn� p�smeno
            this->lblSnellenText->Text = GetRandomLetter();
            this->lblSnellenText->Location = System::Drawing::Point(150, 100);
            this->lblSnellenText->Size = System::Drawing::Size(500, 150);
            this->selectedFont = gcnew System::Drawing::Font("Arial", 50);
            this->lblSnellenText->Font = this->selectedFont;

            // Textov� pole pro odpov��
            this->txtUserInput->Location = System::Drawing::Point(150, 300);
            this->txtUserInput->Size = System::Drawing::Size(200, 40);
            this->txtUserInput->Font = gcnew System::Drawing::Font("Arial", 20);
            this->txtUserInput->KeyDown += gcnew KeyEventHandler(this, &VisionTrainingForm::txtUserInput_KeyDown);

            // Feedback Label
            this->lblFeedback->Location = System::Drawing::Point(150, 350);
            this->lblFeedback->Size = System::Drawing::Size(400, 40);
            this->lblFeedback->Font = gcnew System::Drawing::Font("Arial", 16);

            // Tla��tko pro nastaven� velikosti
            this->btnSetFontSize->Text = "Nastavit velikost";
            this->btnSetFontSize->Location = System::Drawing::Point(400, 400);
            this->btnSetFontSize->Click += gcnew EventHandler(this, &VisionTrainingForm::btnSetFontSize_Click);

            // ��seln�k pro velikost fontu
            this->numFontSize->Location = System::Drawing::Point(150, 400);
            this->numFontSize->Minimum = 10;
            this->numFontSize->Maximum = 200;
            this->numFontSize->Value = 50;

            // V�b�r fontu
            this->cmbFontName->Location = System::Drawing::Point(150, 450);
            this->cmbFontName->Size = System::Drawing::Size(200, 40);
            this->cmbFontName->Items->AddRange(gcnew cli::array<Object^> { "Arial", "Times New Roman", "Verdana", "Courier New" });
            this->cmbFontName->SelectedIndex = 0;

            // P�id�n� komponent do formul��e
            this->Controls->Add(this->lblSnellenText);
            this->Controls->Add(this->txtUserInput);
            this->Controls->Add(this->lblFeedback);
            this->Controls->Add(this->btnSetFontSize);
            this->Controls->Add(this->numFontSize);
            this->Controls->Add(this->cmbFontName);

            this->Text = "Tr�nink zrakov� ostrosti";
            this->Size = System::Drawing::Size(800, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
        }

        // Funkce pro generov�n� n�hodn�ho p�smene
        String^ GetRandomLetter()
        {
            char letter = 'A' + (rand() % 26); // Generuje n�hodn� p�smeno od 'A' do 'Z'
            return gcnew String(letter, 1);
        }

        // Obsluha Enter kl�vesy
        void txtUserInput_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::Enter)
            {
                String^ userInput = this->txtUserInput->Text;
                String^ correctText = this->lblSnellenText->Text;

                if (userInput->ToUpper()->Equals(correctText->ToUpper()))
                {
                    this->lblFeedback->Text = "Spr�vn�!";
                    this->lblFeedback->ForeColor = System::Drawing::Color::Green;
                }
                else
                {
                    this->lblFeedback->Text = "�patn�, zkuste to znovu.";
                    this->lblFeedback->ForeColor = System::Drawing::Color::Red;
                }

                this->txtUserInput->Text = "";               // Vyma�e text u�ivatele
                this->lblSnellenText->Text = GetRandomLetter(); // Zobraz� nov� p�smeno
            }
        }

        // Nastaven� nov� velikosti a fontu
        void btnSetFontSize_Click(Object^ sender, EventArgs^ e)
        {
            float fontSize = (float)this->numFontSize->Value;
            String^ fontName = this->cmbFontName->SelectedItem->ToString();

            this->selectedFont = gcnew System::Drawing::Font(fontName, fontSize);
            this->lblSnellenText->Font = this->selectedFont;
        }

    private:
        System::ComponentModel::Container^ components;
    };
}
