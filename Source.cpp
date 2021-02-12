#include "DistanceRenderer.h"
#include "GameObject2D.h"
#include "DataTypes.h"

#include <iostream>
#include <time.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <windows.h>
#include <cmath>

float GenerateRandomNumber(float min, float max) {

	return (float)(min + std::rand() % (unsigned int)((max + 1.0f) - min));

}
void CallLoading(void) {

	std::cout << "loading..." << std::endl;

}

int main(void) {
	
	bool loading = false;
	bool loaded = false;
	bool load = true;
	long long t = 0;
	char t_UserInput;
	float duration = 0.00000f;
	HPEN hPen;
	HBRUSH hBrush;

	float t_Scale = 10.0f;
	unsigned int t_ObjectNumber = 2500 * (unsigned int)(t_Scale);
	float t_Move = 10.0f;
	float t_RenderingDistance = 860.0f / t_Scale;
	float t_RenderingRadius = 400.0f / t_Scale;
	float t_MinPosition = 0.0f / t_Scale;
	float t_MaxPosition = 19200.0f / t_Scale;

	HWND console = GetConsoleWindow();
	HDC hdc = GetDC(console);

	std::thread* update_thr;

	std::string objectNameBuffer;
	Strave::Vector2f objectPositionBuffer;

	std::vector<Strave::GameObject2D*> objectContainer;
	Strave::Renderer::RenderingConstraints* constraints;
	std::shared_ptr<Strave::Renderer::DistanceRendering> t_Renderer;

	constraints = new Strave::Renderer::RenderingConstraints();
	constraints->SetInitPoint(Strave::Vector2f(1920.0f / 2, 1080.0f / 2));
	constraints->SetPreloadRadius(t_RenderingDistance);
	constraints->SetRenderingRadius(t_RenderingRadius);

	std::srand((unsigned)time(NULL));

	for (unsigned int index = 0; index != t_ObjectNumber; index++) {
		objectNameBuffer = "Object " + std::to_string(index);
		objectPositionBuffer = {
			GenerateRandomNumber(t_MinPosition, t_MaxPosition),
			GenerateRandomNumber(t_MinPosition, t_MaxPosition),
		};

		objectContainer.push_back(new Strave::GameObject2D(objectNameBuffer, objectPositionBuffer));
	}

	t_Renderer = std::make_shared<Strave::Renderer::DistanceRendering>(*constraints, objectContainer, Strave::Renderer::DistanceRendering::GetHighestPoints(objectContainer));
	int val;
	while (true) {

		if (load == true) {
			std::cin >> val;
			load = false;
			loaded = true;
		}

		system("CLS");

		if (_kbhit()) {
			t_UserInput = _getch();

			switch (t_UserInput) {
			case 'w':
				t_Renderer->GetRenderSection()->UpdatePointPosition({
						t_Renderer->GetRenderSection()->GetPointPosition().x,
						t_Renderer->GetRenderSection()->GetPointPosition().y - t_Move
				});

				break;
			case 's': 
				t_Renderer->GetRenderSection()->UpdatePointPosition({
						t_Renderer->GetRenderSection()->GetPointPosition().x,
						t_Renderer->GetRenderSection()->GetPointPosition().y + t_Move
				});

				break;
			case 'a':
				t_Renderer->GetRenderSection()->UpdatePointPosition({
						t_Renderer->GetRenderSection()->GetPointPosition().x - t_Move,
						t_Renderer->GetRenderSection()->GetPointPosition().y
					});

				break;
			case 'd':
				t_Renderer->GetRenderSection()->UpdatePointPosition({
						t_Renderer->GetRenderSection()->GetPointPosition().x + t_Move,
						t_Renderer->GetRenderSection()->GetPointPosition().y
					});

				break;
			}

		}

		if (loaded == true) {
			std::cout << "Render speed: " << duration / 1000.0f << " ms";
			std::cout << ", FPS: " << (unsigned)(1000.0f / (duration / 1000.0f));

			hPen = CreatePen(2, 2, RGB(255, 255, 255));
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			Ellipse(
				hdc,
				t_Renderer->GetRenderSection()->GetCenterPoint().x - t_RenderingDistance,
				t_Renderer->GetRenderSection()->GetCenterPoint().y - t_RenderingDistance,
				t_Renderer->GetRenderSection()->GetCenterPoint().x + t_RenderingDistance,
				t_Renderer->GetRenderSection()->GetCenterPoint().y + t_RenderingDistance
			); // preload radius

			t_Renderer->GetRenderSection()->DrawRenderGrid(hdc);

			Ellipse(
				hdc,
				t_Renderer->GetRenderSection()->GetPointPosition().x - t_RenderingRadius,
				t_Renderer->GetRenderSection()->GetPointPosition().y - t_RenderingRadius,
				t_Renderer->GetRenderSection()->GetPointPosition().x + t_RenderingRadius,
				t_Renderer->GetRenderSection()->GetPointPosition().y + t_RenderingRadius
			); // rendering radius


			auto start = std::chrono::high_resolution_clock::now();
			t_Renderer->GetRenderSection()->Update();
			auto stop = std::chrono::high_resolution_clock::now();

			duration = (float)std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

			std::cout << ", Update speed: " << duration / 1000.0f << " ms" << std::endl;

			auto start2 = std::chrono::high_resolution_clock::now();

			t_Renderer->GetRenderSection()->Render(hdc);
			auto stop2 = std::chrono::high_resolution_clock::now();

			duration += (float)std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2).count();


		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	for (unsigned int index = 0; index != 10; index++) {
		delete objectContainer.at(index);
	}

	system("PAUSE");
	return 0;

}
