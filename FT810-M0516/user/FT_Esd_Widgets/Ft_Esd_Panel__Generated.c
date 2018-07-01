/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Panel
C Source
*/

#include "Ft_Esd_Panel.h"

#include "Ft_Esd_Elements.h"

extern void Ft_Esd_Noop(void *context);
Ft_Esd_Theme * Ft_Esd_Panel_Theme__Default(void *context) { return Ft_Esd_Theme_GetCurrent(); }
int Ft_Esd_Panel_Radius__Default(void *context) { return 4L; }
ft_bool_t Ft_Esd_Panel_Raised__Default(void *context) { return 0; }


static Ft_Esd_WidgetSlots s_Ft_Esd_Panel__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_Widget_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_Widget_Update,
	(void(*)(void *))Ft_Esd_Panel_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_Widget_End,
};


void Ft_Esd_Panel__Initializer(Ft_Esd_Panel *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_Panel_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_Panel__Slots;
	context->Widget.LocalX = 82;
	context->Widget.LocalY = 44;
	context->Widget.LocalWidth = 276;
	context->Widget.LocalHeight = 198;
	context->Theme = Ft_Esd_Panel_Theme__Default;
	context->Radius = Ft_Esd_Panel_Radius__Default;
	context->Raised = Ft_Esd_Panel_Raised__Default;
}

void Ft_Esd_Elements_Panel(Ft_Esd_Theme *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_bool_t);

void Ft_Esd_Panel_Render(Ft_Esd_Panel *context)
{
	void *owner = context->Owner;
	Ft_Esd_Theme * theme = context->Theme(owner);
	ft_int16_t x = context->Widget.GlobalX;
	ft_int16_t y = context->Widget.GlobalY;
	ft_int16_t width = context->Widget.GlobalWidth;
	ft_int16_t height = context->Widget.GlobalHeight;
	int radius = context->Radius(owner);
	ft_bool_t raised = context->Raised(owner);
	Ft_Esd_Elements_Panel(theme, x, y, width, height, radius, raised);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_Panel Instance;
	Ft_Esd_Theme * Theme;
	int Radius;
	ft_bool_t Raised;
} Ft_Esd_Panel__ESD;

Ft_Esd_Theme * Ft_Esd_Panel__Get_Theme__ESD(void *context) { return ((Ft_Esd_Panel__ESD *)context)->Theme; }
void Ft_Esd_Panel__Set_Theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_Panel__ESD *)context)->Theme = value; }
int Ft_Esd_Panel__Get_Radius__ESD(void *context) { return ((Ft_Esd_Panel__ESD *)context)->Radius; }
void Ft_Esd_Panel__Set_Radius__ESD(void *context, int value) { ((Ft_Esd_Panel__ESD *)context)->Radius = value; }
ft_bool_t Ft_Esd_Panel__Get_Raised__ESD(void *context) { return ((Ft_Esd_Panel__ESD *)context)->Raised; }
void Ft_Esd_Panel__Set_Raised__ESD(void *context, ft_bool_t value) { ((Ft_Esd_Panel__ESD *)context)->Raised = value; }

void *Ft_Esd_Panel__Create__ESD()
{
	Ft_Esd_Panel__ESD *context = (Ft_Esd_Panel__ESD *)malloc(sizeof(Ft_Esd_Panel__ESD));
	Ft_Esd_Panel__Initializer(&context->Instance);
	context->Instance.Owner = context;
	context->Theme = Ft_Esd_Theme_GetCurrent();
	context->Instance.Theme = Ft_Esd_Panel__Get_Theme__ESD;
	context->Radius = 4L;
	context->Instance.Radius = Ft_Esd_Panel__Get_Radius__ESD;
	context->Raised = 0;
	context->Instance.Raised = Ft_Esd_Panel__Get_Raised__ESD;
	return context;
}

void Ft_Esd_Panel__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */
