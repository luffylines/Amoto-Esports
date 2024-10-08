					#pragma once

					namespace LastAmoto {

						using namespace System;
						using namespace System::ComponentModel;
						using namespace System::Collections;
						using namespace System::Windows::Forms;
						using namespace System::Data;
						using namespace System::Drawing;
						using namespace MySql::Data::MySqlClient;
						/// <summary>
						/// Summary for TimeForm
						/// </summary>
						public ref class TimeForm : public System::Windows::Forms::Form
						{
						public:
								Form^tims;
							TimeForm(void)
							{
								InitializeComponent();
								//
								//TODO: Add the constructor code here
								//
							}
							TimeForm(Form^ next2)
							{
								tims = next2;
								InitializeComponent();
								//
								//TODO: Add the constructor code here
								//
							}

						protected:
							/// <summary>
							/// Clean up any resources being used.
							/// </summary>
							~TimeForm()
							{
								if (components)
								{
									delete components;
								}
							}

							void LoadData()
							{
								String^ connectionString = "server=localhost;database=amoto;user=root;password=;convert zero datetime=True;";
								MySqlConnection^ connection = gcnew MySqlConnection(connectionString);

								try
								{
									connection->Open();
									MySqlCommand^ command = gcnew MySqlCommand("SELECT id, username, hours, price FROM adduser", connection);
									MySqlDataReader^ reader = command->ExecuteReader();

									while (reader->Read())
									{
										int rowIndex = dataGridView1->Rows->Add();
										dataGridView1->Rows[rowIndex]->Cells["id"]->Value = reader["id"];
										dataGridView1->Rows[rowIndex]->Cells["username"]->Value = reader["username"];
										dataGridView1->Rows[rowIndex]->Cells["price"]->Value = reader["price"];

										// Handle TimeSpan correctly
										TimeSpan hoursWorked = reader["hours"] != DBNull::Value ? (TimeSpan)reader["hours"] : TimeSpan::Zero;
										int totalHoursWorked = (int)hoursWorked.TotalHours; // Get total hours from TimeSpan

										dataGridView1->Rows[rowIndex]->Cells["hours"]->Value = totalHoursWorked;

										// Assuming total hours is a constant (e.g., 10 hours) or fetched from the database
										int totalHours = 10; // Replace with your logic for total hours
										int remainingHours = totalHours - totalHoursWorked;

										dataGridView1->Rows[rowIndex]->Cells["remainingTime"]->Value = remainingHours > 0 ? remainingHours : 0;
									}
									reader->Close();
								}
								catch (MySqlException^ ex)
								{
									MessageBox::Show("Error: " + ex->Message);
								}
								finally
								{
									connection->Close();
								}
							}


						private: System::Windows::Forms::PictureBox^ pictureBox1;
						private: System::Windows::Forms::DataGridView^ dataGridView1;




						private: System::Windows::Forms::Label^ label1;
						private: System::Windows::Forms::PictureBox^ pictureBox2;
						private: System::Windows::Forms::TextBox^ textBox1;
						private: System::Windows::Forms::Button^ button1;
						private: System::Windows::Forms::DataGridViewTextBoxColumn^ id;
						private: System::Windows::Forms::DataGridViewTextBoxColumn^ username;
						private: System::Windows::Forms::DataGridViewTextBoxColumn^ hours;
						private: System::Windows::Forms::DataGridViewTextBoxColumn^ price;
						private: System::Windows::Forms::DataGridViewTextBoxColumn^ remainingTime;
						private: System::Windows::Forms::Timer^ timer1;
						private: System::ComponentModel::IContainer^ components;




						protected:

						private:
							/// <summary>
							/// Required designer variable.
							/// </summary>


					#pragma region Windows Form Designer generated code
							/// <summary>
							/// Required method for Designer support - do not modify
							/// the contents of this method with the code editor.
							/// </summary>
							void InitializeComponent(void)
							{
								this->components = (gcnew System::ComponentModel::Container());
								System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(TimeForm::typeid));
								this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
								this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
								this->id = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
								this->username = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
								this->hours = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
								this->price = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
								this->remainingTime = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
								this->label1 = (gcnew System::Windows::Forms::Label());
								this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
								this->textBox1 = (gcnew System::Windows::Forms::TextBox());
								this->button1 = (gcnew System::Windows::Forms::Button());
								this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
								(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
								(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
								(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
								this->SuspendLayout();
								// 
								// pictureBox1
								// 
								this->pictureBox1->ErrorImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.ErrorImage")));
								this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
								this->pictureBox1->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.InitialImage")));
								this->pictureBox1->Location = System::Drawing::Point(949, 12);
								this->pictureBox1->Name = L"pictureBox1";
								this->pictureBox1->Size = System::Drawing::Size(59, 53);
								this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
								this->pictureBox1->TabIndex = 7;
								this->pictureBox1->TabStop = false;
								this->pictureBox1->Click += gcnew System::EventHandler(this, &TimeForm::pictureBox1_Click);
								// 
								// dataGridView1
								// 
								this->dataGridView1->AllowUserToAddRows = false;
								this->dataGridView1->AllowUserToDeleteRows = false;
								this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
								this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
									this->id, this->username,
										this->hours, this->price, this->remainingTime
								});
								this->dataGridView1->Location = System::Drawing::Point(162, 188);
								this->dataGridView1->Name = L"dataGridView1";
								this->dataGridView1->ReadOnly = true;
								this->dataGridView1->RowHeadersVisible = false;
								this->dataGridView1->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
								this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
								this->dataGridView1->Size = System::Drawing::Size(674, 323);
								this->dataGridView1->TabIndex = 8;
								this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &TimeForm::dataGridView1_CellContentClick);
								// 
								// id
								// 
								this->id->HeaderText = L"PC";
								this->id->Name = L"id";
								this->id->ReadOnly = true;
								// 
								// username
								// 
								this->username->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
								this->username->HeaderText = L"User";
								this->username->Name = L"username";
								this->username->ReadOnly = true;
								// 
								// hours
								// 
								this->hours->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
								this->hours->HeaderText = L"Time";
								this->hours->Name = L"hours";
								this->hours->ReadOnly = true;
								// 
								// price
								// 
								this->price->HeaderText = L"Price";
								this->price->Name = L"price";
								this->price->ReadOnly = true;
								// 
								// remainingTime
								// 
								this->remainingTime->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
								this->remainingTime->HeaderText = L"Remaining Time";
								this->remainingTime->Name = L"remainingTime";
								this->remainingTime->ReadOnly = true;
								// 
								// label1
								// 
								this->label1->AutoSize = true;
								this->label1->Location = System::Drawing::Point(413, 80);
								this->label1->Name = L"label1";
								this->label1->Size = System::Drawing::Size(83, 13);
								this->label1->TabIndex = 9;
								this->label1->Text = L"Time Remaining";
								this->label1->Click += gcnew System::EventHandler(this, &TimeForm::label1_Click);
								// 
								// pictureBox2
								// 
								this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
								this->pictureBox2->Location = System::Drawing::Point(884, 12);
								this->pictureBox2->Name = L"pictureBox2";
								this->pictureBox2->Size = System::Drawing::Size(59, 53);
								this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
								this->pictureBox2->TabIndex = 13;
								this->pictureBox2->TabStop = false;
								this->pictureBox2->Click += gcnew System::EventHandler(this, &TimeForm::pictureBox2_Click);
								// 
								// textBox1
								// 
								this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
									static_cast<System::Byte>(0)));
								this->textBox1->Location = System::Drawing::Point(429, 131);
								this->textBox1->Name = L"textBox1";
								this->textBox1->Size = System::Drawing::Size(290, 31);
								this->textBox1->TabIndex = 14;
								this->textBox1->TextChanged += gcnew System::EventHandler(this, &TimeForm::textBox1_TextChanged);
								// 
								// button1
								// 
								this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
									static_cast<System::Byte>(0)));
								this->button1->Location = System::Drawing::Point(739, 131);
								this->button1->Name = L"button1";
								this->button1->Size = System::Drawing::Size(97, 30);
								this->button1->TabIndex = 15;
								this->button1->Text = L"Search";
								this->button1->UseVisualStyleBackColor = true;
								this->button1->Click += gcnew System::EventHandler(this, &TimeForm::button1_Click);
								// 
								// timer1
								// 
								this->timer1->Tick += gcnew System::EventHandler(this, &TimeForm::timer1_Tick);
								// 
								// TimeForm
								// 
								this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
								this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
								this->ClientSize = System::Drawing::Size(1020, 542);
								this->ControlBox = false;
								this->Controls->Add(this->button1);
								this->Controls->Add(this->textBox1);
								this->Controls->Add(this->pictureBox2);
								this->Controls->Add(this->label1);
								this->Controls->Add(this->dataGridView1);
								this->Controls->Add(this->pictureBox1);
								this->Name = L"TimeForm";
								this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
								this->Load += gcnew System::EventHandler(this, &TimeForm::TimeForm_Load);
								(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
								(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
								(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
								this->ResumeLayout(false);
								this->PerformLayout();

							}
					#pragma endregion
						private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
							Application::Exit(); // Close the application
						}
						private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
						}
					private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
					}
					private: System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) {
						this->Hide();
						tims->Show();
					}
					private: System::Void TimeForm_Load(System::Object^ sender, System::EventArgs^ e) {
						LoadData();
					}
					private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
						String^ searchText = textBox1->Text->ToLower();
						bool foundMatch = false; // Track if any match is found

						// Loop through the DataGridView rows
						for each (DataGridViewRow ^ row in dataGridView1->Rows) {
							bool idMatch = row->Cells["id"]->Value != nullptr &&
								row->Cells["id"]->Value->ToString()->Contains(searchText);
							bool usernameMatch = row->Cells["username"]->Value != nullptr &&
								row->Cells["username"]->Value->ToString()->ToLower()->Contains(searchText);

							// Show the row if either id or username matches
							if (idMatch || usernameMatch) {
								row->Visible = true;
								foundMatch = true; // Set foundMatch to true if a match is found
							}
							else {
								row->Visible = false; // Hide non-matching rows
							}
						}

						// Optionally, inform the user if no matches were found
						if (!foundMatch) {
							MessageBox::Show("No matches found.");
						}
					}

					private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
					}
					private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
					}
					};
					}
