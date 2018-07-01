/*
This file is automatically generated
DO NOT MODIFY BY HAND
App
C Source
*/

#include "App.h"

#include "stdlib.h"

extern void Ft_Esd_Noop(void *context);
extern ft_int16_t FT_DispWidth;
extern ft_int16_t FT_DispHeight;
extern void Ft_Esd_Spinner_Popup();



void App__App_Screen__Initializer(App *context)
{
	AppScreen *object = &context->App_Screen;
	AppScreen__Initializer(object);
	object->Owner = context;
	object->Widget.Root = 1;
	object->Widget.Active = 0;
	object->Widget.GlobalX = 0;
	object->Widget.GlobalY = 0;
	object->Widget.GlobalWidth = FT_DispWidth;
	object->Widget.GlobalHeight = FT_DispHeight;
	object->Widget.LocalX = 0;
	object->Widget.LocalY = 0;
	object->Widget.LocalWidth = 400;
	object->Widget.LocalHeight = 300;
}

void App__Initializer(App *context)
{
	context->Owner = 0;
	App__App_Screen__Initializer(context);
	App_Initialize(context);
}

void App_Initialize(App *context)
{
	void *owner = context->Owner;
}

void App_Start(App *context)
{
	void *owner = context->Owner;
	((Ft_Esd_Widget *)&context->App_Screen)->Slots->Start(&context->App_Screen);
	Ft_Esd_Widget_SetActive((Ft_Esd_Widget *)&context->App_Screen, 1);
}

void App_Update(App *context)
{
	void *owner = context->Owner;
	if (((Ft_Esd_Widget *)&context->App_Screen)->Active)
	{
		((Ft_Esd_Widget *)&context->App_Screen)->Slots->Update(&context->App_Screen);
	}
}

void App_Render(App *context)
{
	void *owner = context->Owner;
	if (((Ft_Esd_Widget *)&context->App_Screen)->Active)
	{
		((Ft_Esd_Widget *)&context->App_Screen)->Slots->Render(&context->App_Screen);
	}
}

void App_Idle(App *context)
{
	void *owner = context->Owner;
	if (((Ft_Esd_Widget *)&context->App_Screen)->Active)
	{
		((Ft_Esd_Widget *)&context->App_Screen)->Slots->Idle(&context->App_Screen);
	}
}

void App_End(App *context)
{
	void *owner = context->Owner;
	Ft_Esd_Widget_SetActive((Ft_Esd_Widget *)&context->App_Screen, 0);
	((Ft_Esd_Widget *)&context->App_Screen)->Slots->End(&context->App_Screen);
}

static App application;

void Ft_Main__Start()
{
	App__Initializer(&application);
	App_Start(&application);
}

void Ft_Main__Update()
{
	App_Update(&application);
}

void Ft_Main__Render()
{
	App_Render(&application);
}

void Ft_Main__Idle()
{
	App_Idle(&application);
}

void Ft_Main__End()
{
	App_End(&application);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	App Instance;
} App__ESD;


void *App__Create__ESD()
{
	App__ESD *context = (App__ESD *)malloc(sizeof(App__ESD));
	App__Initializer(&context->Instance);
	context->Instance.Owner = context;
	return context;
}

void App__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */
