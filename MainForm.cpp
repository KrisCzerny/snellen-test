#include "MainMenuForm.h"

using namespace System;
using namespace System::Windows::Forms;
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	snellentest::MainMenuForm form;
	Application::Run(% form);

}