#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkTextRepresentation.h>
#include <vtkTextWidget.h>

using namespace std;
#define vNew(type, name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

int main(int argc, int** argv)
{
	vNew(vtkCylinderSource, cylinder);
	cylinder->SetResolution(6);
	cylinder->Update();

	// renderer polydata
	vNew(vtkPolyDataMapper, mapper);
	mapper->SetInputData(cylinder->GetOutput());
	vNew(vtkActor, actor);
	actor->SetMapper(mapper);
	//actor->GetProperty()->SetPointSize(3);
	actor->GetProperty()->EdgeVisibilityOn();
	vNew(vtkNamedColors, colors);
	actor->GetProperty()->SetColor(1, 0.39, 0.28);
	vNew(vtkRenderer, renderer);
	renderer->AddActor(actor);
	renderer->SetBackground(0.33, 0.35, 0.43);
	vNew(vtkRenderWindow, renderWindow);
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(900, 600);
	vNew(vtkRenderWindowInteractor, rwInteractor);
	rwInteractor->SetRenderWindow(renderWindow);
	vNew(vtkInteractorStyleTrackballCamera, style);
	rwInteractor->SetInteractorStyle(style);

	// vtkTextWidget
	string chsText = u8"你好，思源宋体";
	string fontFilePath = "../data/SourceHanSerifSC-Regular.otf";
	vNew(vtkTextActor, textActor);
	textActor->SetInput(chsText.c_str());
	textActor->GetTextProperty()->SetColor(1.0, 0.08, 0.57);
	textActor->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
	textActor->GetTextProperty()->SetFontFile(fontFilePath.c_str());

	vNew(vtkTextWidget, textWidget);
	vNew(vtkTextRepresentation, textRepresent); // set windget position
	textRepresent->GetPositionCoordinate()->SetValue(0.05, 0.9); //corner
	textRepresent->GetPosition2Coordinate()->SetValue(0.3, 0.06); //size
	textWidget->SetRepresentation(textRepresent);

	textWidget->SetInteractor(rwInteractor);
	textWidget->SetTextActor(textActor);
	textWidget->On();

	// render and interact
	renderWindow->Render();
	rwInteractor->Start();

    return EXIT_SUCCESS;
}