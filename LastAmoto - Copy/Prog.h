#pragma once

#include "log.h" // Include your MainForm header

namespace LastAmoto {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Prog : public System::Windows::Forms::Form
	{
	public:
		Prog(void)
		{
			InitializeComponent();
			timer1 = gcnew System::Windows::Forms::Timer();
			timer1->Tick += gcnew System::EventHandler(this, &Prog::OnTimerTick);
			timer1->Interval = 100; // Set interval to 100 ms
		}

	protected:
		~Prog()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Timer^ timer1;
	private: int progressValue;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(187, 307);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(652, 64);
			this->progressBar1->TabIndex = 0;
			this->progressBar1->Click += gcnew System::EventHandler(this, &Prog::OnTimerTick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Snap ITC", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::DarkOrange;
			this->label1->Location = System::Drawing::Point(336, 213);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(353, 42);
			this->label1->TabIndex = 1;
			this->label1->Text = L"AMOTO ESPORTS";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(492, 392);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Loading...";
			// 
			// Prog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::MenuText;
			this->ClientSize = System::Drawing::Size(1020, 565);
			this->ControlBox = false;
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar1);
			this->ForeColor = System::Drawing::SystemColors::ActiveCaption;
			this->MaximizeBox = false;
			this->Name = L"Prog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &Prog::Prog_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void Prog_Load(System::Object^ sender, System::EventArgs^ e) {
		progressValue = 0; // Initialize progress value
		timer1->Start();   // Start the timer
	}

	private: System::Void OnTimerTick(System::Object^ sender, System::EventArgs^ e) {
		progressValue += 10; // Increment progress
		progressBar1->Value = progressValue;

		// Update label2 to show current progress
		label2->Text = "Loading... " + progressValue.ToString() + "%";

		if (progressValue >= 100) {
			timer1->Stop(); // Stop the timer
			this->Hide();   // Hide the progress form
			log^ mainForm = gcnew log(); // Create MainForm
			mainForm->Show(); // Show MainForm
		}
	}
	};
}
