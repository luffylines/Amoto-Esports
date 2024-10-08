#pragma once

namespace LastAmoto {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	public ref class Database
	{
	private:
		String^ connectionString = "server=localhost;database=amoto;user=root;password=;convert zero datetime=True;";

	public:
		MySqlConnection^ GetConnection()
		{
			return gcnew MySqlConnection(connectionString);
		}

		void OpenConnection(MySqlConnection^ connection)
		{
			try
			{
				connection->Open();
				Console::WriteLine("Database connection established successfully.");
			}
			catch (Exception^ ex)
			{
				Console::WriteLine("Error: " + ex->Message);
			}
		}

		void InsertUser(String^ username, String^ password, String^ price, String^ hours)
		{
			MySqlConnection^ connection = GetConnection();
			OpenConnection(connection);
			String^ query = "INSERT INTO adduser (username, password, price, hours) VALUES (@username, @password, @price, @hours)";
			MySqlCommand^ cmd = gcnew MySqlCommand(query, connection);
			cmd->Parameters->AddWithValue("@username", username);
			cmd->Parameters->AddWithValue("@password", password);
			cmd->Parameters->AddWithValue("@price", price);
			cmd->Parameters->AddWithValue("@hours", hours);

			try
			{
				cmd->ExecuteNonQuery();
				Console::WriteLine("User inserted successfully.");
			}
			catch (Exception^ ex)
			{
				Console::WriteLine("Error: " + ex->Message);
			}
			finally
			{
				connection->Close();
			}
		}

		DataTable^ LoadUsers()
		{
			DataTable^ dataTable = gcnew DataTable();
			MySqlConnection^ connection = GetConnection();
			OpenConnection(connection);

			String^ query = "SELECT username, password, price, hours FROM adduser";
			MySqlCommand^ cmd = gcnew MySqlCommand(query, connection);

			try
			{
				MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
				adapter->Fill(dataTable);
			}
			catch (Exception^ ex)
			{
				Console::WriteLine("Error: " + ex->Message);
			}
			finally
			{
				connection->Close();
			}

			return dataTable;
		}

		void UpdateUser(String^ username, String^ password, String^ price, String^ hours)
		{
			MySqlConnection^ connection = GetConnection();
			OpenConnection(connection);
			String^ query = "UPDATE adduser SET password=@password, price=@price, hours=@hours WHERE username=@username";
			MySqlCommand^ cmd = gcnew MySqlCommand(query, connection);
			cmd->Parameters->AddWithValue("@username", username);
			cmd->Parameters->AddWithValue("@password", password);
			cmd->Parameters->AddWithValue("@price", price);
			cmd->Parameters->AddWithValue("@hours", hours);

			try
			{
				cmd->ExecuteNonQuery();
				Console::WriteLine("User updated successfully.");
			}
			catch (Exception^ ex)
			{
				Console::WriteLine("Error: " + ex->Message);
			}
			finally
			{
				connection->Close();
			}
		}

		void DeleteUser(String^ username)
		{
			MySqlConnection^ connection = GetConnection();
			OpenConnection(connection);
			String^ query = "DELETE FROM adduser WHERE username=@username";
			MySqlCommand^ cmd = gcnew MySqlCommand(query, connection);
			cmd->Parameters->AddWithValue("@username", username);

			try
			{
				cmd->ExecuteNonQuery();
				Console::WriteLine("User deleted successfully.");
			}
			catch (Exception^ ex)
			{
				Console::WriteLine("Error: " + ex->Message);
			}
			finally
			{
				connection->Close();
			}
		}
	};

	/// <summary>
	/// Summary for DeleteForm
	/// </summary>
	public ref class DeleteForm : public System::Windows::Forms::Form
	{
	public:
		Form^ newuser;
		Database^ db;
		System::Windows::Forms::Timer^ countdownTimer;
		DateTime endTime; // The time when the countdown ends
		TimeSpan remainingTime; // Remaining time for the countdown
		bool isPaused;

		DeleteForm(void)
		{
			InitializeComponent();
			db = gcnew Database();
			LoadData();
			
			//
			//TODO: Add the constructor code here
			//
		}
		DeleteForm(Form^ next1)
		{
			newuser = next1;
			InitializeComponent();
			db = gcnew Database();
			LoadData();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DeleteForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private:
		void LoadData()
		{
			DataTable^ users = db->LoadUsers();
			dataGridView1->AutoGenerateColumns = false;

			// Clear existing columns (if any)
			dataGridView1->Columns->Clear();

			// Create and add columns
			dataGridView1->Columns->Add("username", "Username");
			dataGridView1->Columns["username"]->DataPropertyName = "username";

			dataGridView1->Columns->Add("password", "Password");
			dataGridView1->Columns["password"]->DataPropertyName = "password";

			dataGridView1->Columns->Add("price", "Price");
			dataGridView1->Columns["price"]->DataPropertyName = "price";

			dataGridView1->Columns->Add("hours", "Hours");
			dataGridView1->Columns["hours"]->DataPropertyName = "hours";

			dataGridView1->DataSource = users;
		}


	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ txtuser;
	private: System::Windows::Forms::TextBox^ txtpass;
	private: System::Windows::Forms::TextBox^ txtprice;
	private: System::Windows::Forms::TextBox^ txthours;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(DeleteForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->txtuser = (gcnew System::Windows::Forms::TextBox());
			this->txtpass = (gcnew System::Windows::Forms::TextBox());
			this->txtprice = (gcnew System::Windows::Forms::TextBox());
			this->txthours = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
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
			this->pictureBox1->Click += gcnew System::EventHandler(this, &DeleteForm::pictureBox1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(884, 12);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(59, 53);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 12;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &DeleteForm::pictureBox2_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(0) {

			});
			this->dataGridView1->Location = System::Drawing::Point(530, 146);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGridView1->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridView1->Size = System::Drawing::Size(451, 316);
			this->dataGridView1->TabIndex = 13;
			this->dataGridView1->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &DeleteForm::dataGridView1_CellContentClick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(398, 65);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(174, 40);
			this->label1->TabIndex = 14;
			this->label1->Text = L"NEW USER\r\n";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(72, 189);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(96, 20);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Username:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(72, 238);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 20);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Password:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(72, 290);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(54, 20);
			this->label4->TabIndex = 17;
			this->label4->Text = L"Price:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(72, 337);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(62, 20);
			this->label5->TabIndex = 18;
			this->label5->Text = L"Hours:";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Lime;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button1->Location = System::Drawing::Point(154, 426);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 36);
			this->button1->TabIndex = 19;
			this->button1->Text = L"Add";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &DeleteForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(291, 426);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(92, 36);
			this->button2->TabIndex = 20;
			this->button2->Text = L"Update";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &DeleteForm::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Red;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(415, 426);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(86, 36);
			this->button3->TabIndex = 21;
			this->button3->Text = L"Delete";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &DeleteForm::button3_Click);
			// 
			// txtuser
			// 
			this->txtuser->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtuser->Location = System::Drawing::Point(198, 179);
			this->txtuser->Name = L"txtuser";
			this->txtuser->Size = System::Drawing::Size(275, 35);
			this->txtuser->TabIndex = 22;
			// 
			// txtpass
			// 
			this->txtpass->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtpass->Location = System::Drawing::Point(198, 228);
			this->txtpass->Name = L"txtpass";
			this->txtpass->Size = System::Drawing::Size(275, 35);
			this->txtpass->TabIndex = 23;
			// 
			// txtprice
			// 
			this->txtprice->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtprice->Location = System::Drawing::Point(198, 275);
			this->txtprice->Name = L"txtprice";
			this->txtprice->Size = System::Drawing::Size(275, 35);
			this->txtprice->TabIndex = 24;
			// 
			// txthours
			// 
			this->txthours->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txthours->Location = System::Drawing::Point(198, 327);
			this->txthours->Name = L"txthours";
			this->txthours->Size = System::Drawing::Size(275, 35);
			this->txthours->TabIndex = 25;
			// 
			// DeleteForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1020, 542);
			this->ControlBox = false;
			this->Controls->Add(this->txthours);
			this->Controls->Add(this->txtprice);
			this->Controls->Add(this->txtpass);
			this->Controls->Add(this->txtuser);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"DeleteForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Load += gcnew System::EventHandler(this, &DeleteForm::DeleteForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma 
	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit(); // Close the application
	}
	private: System::Void pictureBox2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
		newuser->Show();

	}
	private: System::Void DeleteForm_Load(System::Object^ sender, System::EventArgs^ e) {
		LoadData(); // Load users when form loads
	}
private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ username = txtuser->Text;
	String^ password = txtpass->Text;
	String^ price = txtprice->Text;
	String^ hours = txthours->Text;

	db->InsertUser(username, password, price, hours);
	LoadData(); // Refresh the grid
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (dataGridView1->SelectedRows->Count > 0)
	{
		// Get the username from the selected row
		String^ username = dataGridView1->SelectedRows[0]->Cells["username"]->Value->ToString();
		String^ password = txtpass->Text;
		String^ price = txtprice->Text;
		String^ hours = txthours->Text;

		// Update the user by username instead of id
		db->UpdateUser(username, password, price, hours);
		LoadData(); // Refresh the grid
	}
	else
	{
		MessageBox::Show("Please select a user to update.");
	}
}

private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	if (dataGridView1->SelectedRows->Count > 0)
	{
		// Get the username from the selected row
		String^ username = dataGridView1->SelectedRows[0]->Cells["username"]->Value->ToString();
		db->DeleteUser(username); // Pass the username to DeleteUser
		LoadData(); // Refresh the grid
	}
	else
	{
		MessageBox::Show("Please select a user to delete.");
	}
}
};
}