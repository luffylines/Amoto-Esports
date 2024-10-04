#include "Prog.h"

using namespace LastAmoto;

[STAThreadAttribute]
int main() {
	Application::Run(gcnew Prog());
	return 0;
}

